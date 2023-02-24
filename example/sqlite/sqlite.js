import {sqliteClass} from '../../src/qjsbindsqlite.so'
import * as std from "std";
import * as os from "os";

var sqlite = new sqliteClass()

/* 打开数据库连接 */
sqlite.sqlite3Open("./testDb.db")

var sql1 = `CREATE  TABLE COMPANY(
            ID 	    INT 	PRIMARY KEY	NOT NULL,
            NAME	TEXT 	NOT NULL,
            AGE 	INT		NOT NULL,
            ADDRESS		CHAR(50),
            SALARY		REAL);` ;
var res1 = sqlite.sqlite3SqlExec(sql1)
console.log("exec sql1, result: ", res1)

var sql2 =  `INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)
            VALUES (1, 'bkWu', 26, 'KaiYang', 12000.0);
            INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)
            VALUES (2, 'xlLiu', 27, 'GaoYun', 5000);
            INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)
            VALUES (3,'xWang', 32, 'GuiYang', '14000');
            INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)
            VALUES (4, 'rgCheng',24,'QiangNan',6000);
            INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)
            VALUES (5, 'jjXian',24,'',6000);`;
var res2 = sqlite.sqlite3SqlExec(sql2);
console.log("exec sql2, result: ", res2)


var sql3 = "SELECT * from COMPANY";
var res3 = sqlite.sqlite3Select(sql3);
console.log("exec sql3, result: ", res3)


var sql4 = `UPDATE COMPANY set SALARY = 20000.0 where ID=3;
            UPDATE COMPANY set SALARY = 15111.0 where ID=5;`;
var res4 = sqlite.sqlite3SqlExec(sql4);
console.log("exec sql4, result: ", res4)

var sql5 = "SELECT * from COMPANY";
var res5 = sqlite.sqlite3Select(sql5);
console.log("exec sql5, result: ", res5)

/* 关闭数据库连接 */
sqlite.sqlite3Close()