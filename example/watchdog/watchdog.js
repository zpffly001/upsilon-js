import {watchdogClass} from './quickjs-watchdog.so'
import * as std from "std";
import * as os from "os";

var watchdog = new watchdogClass()

var wdt = watchdog.watchdogOpen(1, 1);
watchdog.watchdogStart(wdt)
watchdog.watchdogIsPoweron(wdt, 3000)
// var res = gpio.gpioRequest()
// console.log("res: ", res)
