import {sqliteClass} from '../../src/qjsbindsqlite.so'
import * as std from "std";
import * as os from "os";

var sqlite = new sqliteClass()

/* 打开数据库连接 */
sqlite.sqlite3Open("./testDb.db")

/* 关闭数据库连接 */
sqlite.sqlite3Close()