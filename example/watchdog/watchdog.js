import {watchdogClass} from './quickjs-watchdog.so'
import * as std from "std";
import * as os from "os";

var watchdog = new watchdogClass()

watchdog.watchdogOpen(1, 1);
// var res = gpio.gpioRequest()
// console.log("res: ", res)
