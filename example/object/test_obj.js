/**
 * 测试c结构体转换为js对象
 */
import * as std from "std";
import * as os from "os";
import {getObj} from "./test_obj.so";


var account = getObj()
console.log("name: ", account.name)
console.log("balance: ", account.balance)

console.log("mymode1.modeNum: ", account.mymode1.modeNum)
console.log("mymode1.modeName: ", account.mymode1.modeName)

console.log("mymode2.modeNum: ", account.mymode2.modeNum)
console.log("mymode2.modeName: ", account.mymode2.modeName)


