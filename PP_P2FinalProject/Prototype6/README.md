# Prototype6

## Discription 
- This prototype uses the ultrasonic sensor to measure distance and based on the distance different lights(LEDs) activates.
- We used the night rider arduino sketch combined with an edited sketch done by Christoffer. 
- When we had a working arduino sketch we sent the data to our computer via the serial bridge and used JavaScript to be able to communicate and change the lights on our arduino board. 
- We use this prototype to simulate an automated situation where lights turn on based on the proximity of the user. 

##  Contributors
- Simon Ulvsand 
- Christoffer Zackheden

## Setup and running

In the directory you've got this sample:

1. Run `npm install`
2. Upload _Arduino\Arduino.ino_ to your Arduino
3. Open the serial monitor and ensure that you're getting occasional data from the Arduino. Once satisfied, close the monitor so the port is available again. If you're getting gibberish, double check to make sure the baud rate of the serial monitor is 115,200 (set in the Arduino sketch)
4. Start the Node.js sketch: `node app`. Since you didn't specify which serial port represents the Arduino, you'll get a list of ports displayed. Once you identify the right port, run it again with the port. On Windows this might be something like `node app com5` or on a Mac: `node app /dev/tty.usbmodem1411`. The port name is the often the same or similar to what shows up in the Arduino IDE.
5. Once started, you'll see the same periodic data showing up in the terminal, yay - data is being piped from the Arduino to browser land.
6. In your browser, open up `http://localhost:4000`. This will allow you to send commands to the Node.js server, which in turn forwards it to the Arduino. Likewise, messages sent by the Arduino are displayed in the web page.

Hack away! Try making a simple command system so that a particular function runs on the Arduino when a certain command is sent from the browser, or making something happen in the browser based on a command sent from the Arduino.

## Built upon

[Clint Heyer serial-bridge demo](https://github.com/ClintH/interactivity/tree/master/websockets/serial-bridge)
