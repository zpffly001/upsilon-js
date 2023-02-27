import {mqttClass} from './quickjs-mqtt.so'
import * as std from "std";
import * as os from "os";



var srv = new mqttClass()
var connect = srv.createMqttClient();
console.log(connect)
// new
srv.mqttSubscribe("path/to/my/topic");
var message = null;



var count = 0;



for (let index = 0; index < 10000000000; index++) {

    message = srv.mqttPacketRead();
    if(message){
        console.log("get message: ", message)
        message = null
    }
    if(count == 0)
    {
        srv.mqttPublish("path/to/my/topic", "hello world", 111)
        count++;
    }
}































os.setTimeout(() => {
    console.log("gaga")
}, 5000);