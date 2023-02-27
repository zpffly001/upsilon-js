import {gpioClass} from './quickjs-gpio.so'
import * as std from "std";
import * as os from "os";

var gpio = new gpioClass()

gpio.gpioInit()
var res = gpio.gpioRequest()
console.log("res: ", res)
