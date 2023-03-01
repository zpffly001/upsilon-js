import {funcClass} from './testFunc.so'
import * as std from "std";
import * as os from "os";

var func = new funcClass()

function haha(){
    return 6;
}

func.funcCall(haha)
haha(2, 3)