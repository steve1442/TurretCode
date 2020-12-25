const path = require('path');
const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);
const cv = require('opencv4nodejs');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const { isPrimitive } = require('util');
const port = new SerialPort('/dev/ttyUSB0', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
const FPS = 5;
const wCap = new cv.VideoCapture(0);
//wCap.set(cv.CAP_PROP_FRAME_WIDTH, 300);
//wCap.set(cv.CAP_PROP_FRAME_HEIGHT, 300);

app.get('/', (req, res)=>{
  res.sendFile(path.join(__dirname, 'index.html'));
});

setInterval(() => {
  const frame = wCap.read();
  const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);

    const faceRects = classifier.detectMultiScale(frame.bgrToGray()).objects;
    if (!faceRects.length) {
        //throw new Error('failed to detect faces');
    }
    else{
        faceRects.forEach(face =>{
            rectangle = new cv.Rect(face.x,face.y,face.width,face.height);
            frame.drawRectangle(rectangle, new cv.Vec(0, 0, 0),10);
            console.log("found face");
            port.write(((face.x + face.width/2.0)* (180/1920)) + ":" + ((face.y + face.height/2.0) * (180/1080)));
        });
    }
  const image = cv.imencode('.jpg', frame).toString('base64');
  io.emit('image', image);
},1000/FPS);
/*
// Read the port data
var i = 0;
port.on("open", () => {
  console.log('serial port open');
  //port.write("0:70");
});
parser.on('data', data =>{  
  console.log('got word from arduino:', data);
  
  console.log(x, y)
 port.write((x * (180/1920)) + ":" + (y * (180/1080)));
});
//port.write("0:70"); 
console.log('sent');
*/
server.listen(3000);