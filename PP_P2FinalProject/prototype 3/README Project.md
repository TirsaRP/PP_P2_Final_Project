# json-serial-bridge

This demonstrates bidirectional communication between an Arduino sketch and Javascript running in the browser. JSON is used as the data format.

# Architecture

Three components are needed.

1. An Arduino sketch that sends/receives via serial. A example is included.
2. A Node.js app connects to the computer's serial port
3. Browser code that receives data from the Node.js process and does something with the data


## Setup: Arduino
The Arduino sketch is a demonstration on how to use an input device to trigger changes on a neo pixels.
We wired a momentary push button to connect from ground to a digital IO pin.  When you press the button it will change to a new pixel animation. 


## Project: 
We managed to set up the Arduino sketch successfully and set up the Json Serial Bridge. Taner(TA) helped us with the following code for Arduino (it sets up connection between the browser and the Arduino sketch, when you input {"cmd", 5} the led should light on): 

int Value = root["cmd"];
  if (Value == 5) {
      Serial.println(String("Read"));
    digitalWrite(PIXEL_PIN, HIGH);
  }
}

and the following code for script.js (it sets connection between the browser and the Arduino sketch, receives information after lighting up the led and it logs the information in the browser): 

// SEARCH FOR d2 INSIDE d

// IF d2 == 1.. then 
console.log(d);
socket.send('{"cmd":5}');


## Conclusion:
This sketch was not finished successfully, as there is no output from the serial bridge in the Arduino sketch. 


