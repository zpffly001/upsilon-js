/**
 * 测试对象的引用传递 把js对象传递给c c修改后，js这边对象属性内容也随之修改
 */
import * as std from "std";
import * as os from "os";
import {objRef} from "./testObjRef.so";


var obj = {}
obj.name = "lalal"
console.log("oldName: ", obj.name)

objRef(obj)
console.log("newName: ", obj.name)

