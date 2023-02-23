#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

typedef struct {
    int id;
    char name[100];
    int age;
} Person;

int main() {
    sqlite3 *db;
    /* 打开数据库 */
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    /* 创建表 */
    rc = sqlite3_exec(db, "CREATE TABLE person(id INTEGER PRIMARY KEY, name TEXT, age INTEGER);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    /* 插入表 */
    rc = sqlite3_exec(db,   "INSERT INTO person(id, name, age) VALUES(1, 'Alice', 25);"
                            "INSERT INTO person(id, name, age) VALUES(2, 'Bob', 30);"
                            "INSERT INTO person(id, name, age) VALUES(3, 'Charlie', 35);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    /* 查询表 */
    const char *sql = "SELECT id, name, age FROM person;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    /* 遍历查询结果，填充到结构体中 */
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Person person;
        person.id = sqlite3_column_int(stmt, 0);
            strcpy(person.name, sqlite3_column_text(stmt, 1));
        person.age = sqlite3_column_int(stmt, 2);
        // do something with person struct
        printf("ID: %d, Name: %s, Age: %d\n", person.id, person.name, person.age);
    }

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Can't step statement: %s\n", sqlite3_errmsg(db));
    }

sqlite3_finalize(stmt);
sqlite3_close(db);
return 0;
}