import {channelClass} from './quickjs-channel.so'
import * as std from "std";
import * as os from "os";
// import { arrayBuffer } from 'stream/consumers';

function toHex(a)
{
    var i, s = "", tab, v;
    tab = new Uint8Array(a);
    for(i = 0; i < tab.length; i++) {
        v = tab[i].toString(16);
        if (v.length < 2)
            v = "0" + v;
        if (i !== 0)
            s += " ";
        s += v;
    }
    return s;
}

var channelObj = new channelClass()

channelObj.channelOpen(5, 6)

console.log("send: ", channelObj.channelSend("helloworld", 11))

var buffer = new ArrayBuffer(6)
var milliseconds = 3000
console.log("recv: ", channelObj.channelRecv(buffer, milliseconds))
toHex(buffer)

console.log("ioctl: ", channelObj.channelIoctl(77, 88))

channelObj.channelClose()

console.log("flush: ", channelObj.channelFlush(66))

