#include <stdio.h>

#include "sqlite3.h"

//typedef int (*sqlite3_callback)(void*,int,char**, char**);


static int sql_callback(void *args, int nCol, char **rowArr, char **colName)
{
	printf("nCol = %d\n",nCol);
	for(int i = 0 ;i < nCol; i++){
		printf("%s = %s\n", colName[i], rowArr[i] ? rowArr[i] : "NULL");
	}
	printf("\n");

	return 0;
}

int main(int argc, const char *argv[])
{
	int ret;
	sqlite3 *ppDb = NULL;

    //不存在创建并打开;
	ret = sqlite3_open("./config.db", &ppDb);
	if(ret != SQLITE_OK){
		printf("open config.db failed %s\n",sqlite3_errmsg(ppDb));
		return -1;
	}

	printf("open config.db ok\n");

	/* crate sql table */
	char *sql = NULL;
	sql =   "CREATE TABLE COMPANY(" \
            "ID 	INT 	PRIMARY KEY	NOT NULL," \
            "NAME	TEXT 	NOT NULL," \
            "AGE 	INT		NOT NULL," \
            "ADDRESS		CHAR(50)," \
            "SALARY		REAL);" ;


	char *errMsg = NULL;
	ret = sqlite3_exec(ppDb,sql, NULL ,NULL, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_exec create err %s\n",errMsg);
		sqlite3_free(errMsg);
	}

	printf("crate config.db table ok\n");


	/* insert sql */
	sql =   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (1, 'bkWu', 26, 'KaiYang', 12000.0);" \
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (2, 'xlLiu', 27, 'GaoYun', 5000); "\
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (3,'xWang', 32, 'GuiYang', '14000');"\
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (4, 'rgCheng',24,'QiangNan',6000);"\
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (5, 'jjXian',24,'',6000);";
	ret = sqlite3_exec(ppDb,sql, NULL ,NULL, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_exec insert err %s\n",errMsg);
		sqlite3_free(errMsg);
	}

	printf("insert config.db table ok\n");

	/* select sql */
	sql = "SELECT * from COMPANY";
	#if 0 //法1
	ret = sqlite3_exec(ppDb,sql, sql_callback ,NULL, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_exec select err %s\n",errMsg);
		sqlite3_free(errMsg);
	}

	/*

	open config.db ok
	crate config.db table ok
	insert config.db table ok
	nCol = 5
	ID = 1
	NAME = bkWu
	AGE = 26
	ADDRESS = KaiYang
	SALARY = 12000.0

	nCol = 5
	ID = 2
	NAME = xlLiu
	AGE = 27
	ADDRESS = GaoYun
	SALARY = 5000.0

	nCol = 5
	ID = 3
	NAME = xWang
	AGE = 32
	ADDRESS = GuiYang
	SALARY = 14000.0

	nCol = 5
	ID = 4
	NAME = rgCheng
	AGE = 24
	ADDRESS = QiangNan
	SALARY = 6000.0

	nCol = 5
	ID = 5
	NAME = jjXian
	AGE = 24
	ADDRESS =
	SALARY = 6000.0
	*/
	#else //法2
	int nRow, nCol;
	char **pazResult = NULL;
	ret = sqlite3_get_table(ppDb, sql, &pazResult, &nRow, &nCol, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_get_table err %s\n",errMsg);
		sqlite3_free(errMsg);
		return -1;
	}

	printf("nRow = %d , nCol = %d\n", nRow, nCol);
	for(int i = 0; i < nCol*(nRow+1); i++){
		printf("pazResult[%d] = %s\n",i,pazResult[i]);
	}

	//正确且安全的释放内存
	sqlite3_free_table(pazResult);
	#endif

    printf("---------------------------------------------\n");

	/* update sql & select */
	sql =   "UPDATE COMPANY set SALARY = 20000.0 where ID=3;" \
            "UPDATE COMPANY set SALARY = 15000.0 where ID=4;" \
            "SELECT * from COMPANY";
	ret = sqlite3_exec(ppDb,sql, sql_callback ,NULL, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_exec select err %s\n",errMsg);
		sqlite3_free(errMsg);
	}

	/* delete sql */
	sql =   "DELETE from COMPANY where ID=2;" \
            "DELETE from COMPANY where ID=5;" \
            "SELECT * from COMPANY";
	ret = sqlite3_exec(ppDb,sql, sql_callback ,NULL, &errMsg);
	if(ret != SQLITE_OK){
		printf("sqlite3_exec select err %s\n",errMsg);
		sqlite3_free(errMsg);
	}

	sqlite3_close(ppDb);

	return 0;
}
