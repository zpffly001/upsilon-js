import * as std from "std";
import * as os from "os";
import {getObj} from "./test_obj.so";


var account = getObj()
console.log("name: ", account.name)
console.log("balance: ", account.balance)


