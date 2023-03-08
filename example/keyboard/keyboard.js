import {keyboardClass} from './quickjs-keyboard.so'
import * as std from "std";
import * as os from "os";

var keyboard1 = new keyboardClass()

var res1 = keyboard1.keyboardInit()
console.log("res1: ", res1)

keyboard1.keyboardExit()

var res2 = keyboard1.keyboardCallbackRegister(1,2)
console.log("res2: ", res2)