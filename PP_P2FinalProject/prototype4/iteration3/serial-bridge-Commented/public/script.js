var lastMsgEl = null;
if (document.readyState != 'loading') onDocumentReady();
else document.addEventListener('DOMContentLoaded', onDocumentReady);

/*
function handleCommand(d) {
   lastMsgEl.innerHTML =  `text: ${d.text} <br />int: ${d.integer} <br />float: ${d.float}`;
}
*/

function onDocumentReady() {
    var socket = new ReconnectingWebsocket("ws://" + location.host + "/serial");
    var sendFormEl = document.getElementById('sendForm');
    var lastMsg = null;
    lastMsgEl = document.getElementById('lastMsg');
    socket.onmessage = function(evt) {
        // Debug: see raw received message
        //console.log(evt.data);
        
        // Parse message, assuming <Text,Int,Float>
        var d = evt.data.trim();
        if (d.charAt(0) == '<' && d.charAt(d.length-1) == '>') {
           let distance = d.substring(1, d.length-1); //test if endindex should be 1 or 2
           let distanceAsNumber = parseInt(distance);
           setColorWithDistance(distanceAsNumber);
        } else {
            console.log(d);
        }
        
        // Doesn't seem to be formatted correctly, just display as-is
        if (evt.data != lastMsg) {
            lastMsgEl.innerText =  evt.data;
            lastMsg = evt.data;
        }
    }
    socket.onopen = function(evt) {
        console.log("Socket opened");
    }

    sendFormEl.addEventListener('submit', function(evt) {
        evt.preventDefault();
        var send = document.getElementById('sendtoSerial').value;
        socket.send(send);  
    })
}

////////////// NEW CODE THAT HANDLES THE CLICK EVENTS OF THE GRID  //////////////////

//array of shape ID's and color
let shapeColorArray = [
    ["hexagon-1", "#FFFF00"],
    ["triangle-up-2", "#FF6600"],
    ["circle-3", "#FF0000"],
    ["trapezoid-4", "#FFFF80"],
    ["circle-5", "#FF8533"],
    ["parallelogram-6", "#FF4D4D"],
    ["pentagon-7", "#FFFFB3"],
    ["rombus-8", "#FFB380"],
    ["triangle-down-9", "#FF9999"],
    ["circle-10", "#FFFFE6"],
    ["parallelogram-11", "#FFE0CC"],
    ["hexagon-12", "#FFE6E6"]
  ];
  
  function changeColor(index) {
      for (i = 0; i < shapeColorArray.length; i++) {
        let color = "";
        if (index === i) {
          color = shapeColorArray[i][1];
        }
        document.getElementById(shapeColorArray[i][0]).style.fill = color;
      }
    }

    function setColorWithDistance(distance) {
        //Here you have the distance as a number (0 - 300)

        let rangeIndex = Math.floor(distance/300 * 4);

        if(rangeIndex === 0) {

        } else if (rangeIndex === 1) {

        } else if (rangeIndex === 2){

        } else {

        }


    }