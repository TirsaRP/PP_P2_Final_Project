////// 
let socket;
let oldLetter;


var lastMsgEl = null;
if (document.readyState != 'loading') onDocumentReady();
else document.addEventListener('DOMContentLoaded', onDocumentReady);

function handleCommand(d) {
   lastMsgEl.innerHTML =  `text: ${d.text} <br />int: ${d.integer} <br />float: ${d.float}`;
}

function sendForm() {
    var send = document.getElementById('sendtoSerial').value;
    socket.send(send);  
}

function onDocumentReady() {
    socket = new ReconnectingWebsocket("ws://" + location.host + "/serial");
    var sendFormEl = document.getElementById('sendForm');
    var lastMsg = null;
    lastMsgEl = document.getElementById('lastMsg');
    socket.onmessage = function(evt) {
        // Debug: see raw received message
        //console.log(evt.data);
        
         // Parse message, assuming <Text,Int,Float>
    var d = evt.data.trim();
    if (d.charAt(0) == "<" && d.charAt(d.length - 1) == ">") {
     
     // Clint's Code commented out
      d = d.split(",");
      if (d.length == 3) {
        // Yes, it has three components as we hoped
        handleCommand({
          text: d[0].substr(1),
          integer: parseInt(d[1]),
          float: parseFloat(d[2].substr(0, d.length - 1))
        });
        return;
      }
    }
        
        // Doesn't seem to be formatted correctly, just display as-is
        if (evt.data != lastMsg) {
            lastMsgEl.innerText =  evt.data;
            lastMsg = evt.data;

            chooseLed(evt.data);   //ADDED FUNCTION THAT WILL TAKE THE INPUT OF THE SENSOR

        }

        
    }
    socket.onopen = function(evt) {
        console.log("Socket opened");
    }

    sendFormEl.addEventListener('submit', function(evt) {
        evt.preventDefault();
        sendForm();

    })
}
function buttonLedOn() {
    document.getElementById('sendtoSerial').value = 'a';
  }
  function buttonLedOff() {
    document.getElementById('sendtoSerial').value = 'd';
  }

///// TRIGGER EVENT LED BASED ON DISTANCE //////

function chooseLed(distance) {
   let newLetter; 
    if (distance <= 10) {
        newLetter = 'a'
        
    } else if (distance <= 20)  {
        newLetter = 'b'
        
    } else if (distance <= 30) {
        newLetter = 'c'
        
    } else if (distance > 30) {
        newLetter = 'd'
    }

    if (newLetter != oldLetter) {
        
        document.getElementById("sendtoSerial").value = newLetter;
        oldLetter = newLetter;
        sendForm();

    }
    

}
