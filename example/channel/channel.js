import {channelClass} from './quickjs-channel.so'
import * as std from "std";
import * as os from "os";

var channelObj = new channelClass()

channelObj.channelOpen(5, 6)

console.log("send: ", channelObj.channelSend("helloworld"))

console.log("recv: ", channelObj.channelRecv())

console.log("ioctl: ", channelObj.channelIoctl(77, 88))

channelObj.channelClose()

console.log("flush: ", channelObj.channelFlush(66))

