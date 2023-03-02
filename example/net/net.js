import {netClass} from './quickjs-net.so'
import * as std from "std";
import * as os from "os";

var net = new netClass()


var res = net.netInit()
console.log("res: ", res)

function hh()
{
    console.log("gagagag")
}

net.netStatusCallbackRegister(hh, "hhhh");
// net.netStatusCallbackRegister(hh, hh);
