
//added extra comments to better understand what is going on in the code

//Defining the variables:
//Requires the express module and places it in a variable; Express is the most common used wed framework for Node; 
var express = require('express');


//The following variables define and sets the middleware; 
//Middleware: software that acts as a bridge between an operating system or database and applications, especially on a network. 
//Requires a path module and places it in a variable; (middleware)
var path = require('path');

//Requires the favicon; This module caches the icon in memory to improve performance by skipping disk access. (middleware)
var favicon = require('serve-favicon');

//Requires the http logger (middleware) - a simple middleware that writes and log all http requests to the file
var logger = require('morgan');

//Requires to read and write cookies (middleware)
var cookieParser = require('cookie-parser');

//The bodyParser object exposes various factories to create middlewares. 
//All middlewares will populate the req.body property with the parsed body when the Content-Type request header matches the type option or an empty object 
//({}) if there was no body to parse, the Content-Type was not matched, or an error occurred.
var bodyParser = require('body-parser');

//Requires access to serialport
var SerialPort = require('serialport');

//Requires the websocket's endpoint for the Express application 
var expressWs = require('express-ws');

//Requires the index and users for the route; Routing refers to how an application’s endpoints (URIs) respond to client requests
var index = require('./routes/index');
var users = require('./routes/users');

//Defines the variable ews to handle the websocket connection using ws via the express route 
var ews = expressWs(express());

//Ews = Exchange Web Service; 
var app = ews.app;

//Function to log "Ws received and the info of the port"
app.ws('/serial', function(ws, req) {
  ws.on('message', function(msg) {
    // Received a message via websocket (ie, from the browser)
    // send it to the serial port
    console.log("Ws received: " + msg);
    port.write(msg + "\r\n");
    port.drain();
  });
});
var serialWs = ews.getWss('/serial');

//var expressWs = require('express-ws')(app);
app.use(require('middleware-static-livereload')({
  documentRoot: 'public/'
}));

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handler
app.use(function(err, req, res, next) {
  if (err.status)
    res.sendStatus(err.status);
  else
    res.sendStatus(500);
});

//Using the method app.listen() to return the message "Webserver started on port 4000: http://localhost:4000" 
app.listen(4000);
console.log("Webserver started on port 4000: http://localhost:4000");

//The process.argv property returns an array containing the command line arguments passed when the Node.js process was launched. 
//The first element will be process.execPath. 
//The second element will be the path to the JavaScript file being executed. 
//The remaining elements will be any additional command line arguments.
process.argv.forEach(function (val, index, array) {
  if (index >= 2) portArg = val;
  else portArg = "";
});


//If the number in the portArg array is 0, an error message will be displayed and the port information; 
if (portArg.length == 0) {
  SerialPort.list(function (err, ports) {
    console.log("Here are the serial ports on your system. Find your Arduino and pass that as cmd line argument to this app");
    ports.forEach(function(port) {
        console.log(port.comName, " - ", port.manufacturer);
    });
    process.exit();
  });
  return;
}

//Function that logs the serial port connection, if error it will log first message; else it will log second message; 
var parser = new SerialPort.parsers.Readline;
var port = new SerialPort(portArg, {baudRate:115200}, function (err) {
  if (err) {
      console.log('Could not open port.\n ', err.message);
      process.exit();
  } else {
      console.log("Opened port, now waiting for client connection.")
      console.log("Use CTRL+C to stop.");
  } 
});
port.on('close', function(err) {
  console.log('Port closed ' + err);
})
port.on('error', function(err){
  console.log('Port error: ' + err);
})
port.pipe(parser);
parser.on('data', function(data) {
 console.log("Serial Received: " + data); //ARDUINO CODE SENDS TO ME AND IT PRINTS 

/*
// THE NEW CODE THAT CHANGES THE LED DEPENDING ON THE VALUE RECEIVED FROM THE ARDUINO
if (data > 512) {
  port.write('H');
}
else {
  port.write('L');
}
*/


  


 // Send the text we received on the serial port to all clients
 if (serialWs) {  
    serialWs.clients.forEach(function(client) {
      try {
        client.send(data);
      } catch (e) {}
    });
  }
});

//The module.exports or exports is a special object which is included in every JS file in the Node.js application by default. 
//Module is a variable that represents current module and exports is an object that will be exposed as a module.
module.exports = app;

