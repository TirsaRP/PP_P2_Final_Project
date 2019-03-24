var lastMsgEl = null;
if (document.readyState != "loading") onDocumentReady();
else document.addEventListener("DOMContentLoaded", onDocumentReady);

function handleCommand(d) {
  lastMsgEl.innerHTML = `text: ${d.text} <br />int: ${d.integer} <br />float: ${
    d.float
  }`;
}

function onDocumentReady() {
  var socket = new ReconnectingWebsocket("ws://" + location.host + "/serial");
  var sendFormEl = document.getElementById("sendForm");
  var lastMsg = null;
  lastMsgEl = document.getElementById("lastMsg");
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
    /*
    //added code 
      let distance = d.substring(1, d.length - 1); //test if end index should be 1 or 2
      let distanceAsNumber = parseInt(distance);
      setColorWithDistance(distanceAsNumber);
    } else {
      console.log(d);
    }
*/
    // Doesn't seem to be formatted correctly, just display as-is
    if (evt.data != lastMsg) {
      lastMsgEl.innerText = evt.data;
      lastMsg = evt.data;

      highlightRow(evt.data);
    }
  };
  socket.onopen = function(evt) {
    console.log("Socket opened");
  };

  sendFormEl.addEventListener("submit", function(evt) {
    evt.preventDefault();
    var send = document.getElementById("sendtoSerial").value;
    socket.send(send);
  });
}

////////////// NEW CODE THAT HANDLES THE CLICK EVENTS OF THE GRID  //////////////////

//array of shape ID's and color
let shapeColorArray = [
  ["hexagon-1", "#FFFF00"], //shape 1, yellow at highest brightness and hue. [0]
  ["triangle-up-2", "#FF6600"], //shape 2, orange at highest brightness and hue level. [1]
  ["circle-3", "#FF0000"], //shape 3, red at highest brightness and hue level. [2]
  ["trapezoid-4", "#FFFF80"], //shape 4, yellow at middle-high brightness and hue level. [3]
  ["circle-5", "#FF8533"], //shape 5, orange at middle-high brightness and hue level. [4]
  ["parallelogram-6", "#FF4D4D"], //shape 6, red at middle-high brightness and hue level. [5]
  ["pentagon-7", "#FFFFB3"], //shape 7, yellow at middle-low brightness and hue level. [6]
  ["rombus-8", "#FFB380"], //shape 8, orange at middle-low brightness and hue level. [7]
  ["triangle-down-9", "#FF9999"], //shape 9, red at middle-low brightness and hue level. [8]
  ["circle-10", "#FFFFE6"], //shape 10, yellow at lowest brightness and hue level. [9]
  ["parallelogram-11", "#FFE0CC"], //shape 11, orange at lowest brightness and hue level. [10]
  ["hexagon-12", "#FFE6E6"] //shape 12, red at lowest brightness and hue level. [11]
];

function changeColor(index) {
  //function that changes the color of the GUI tiles
  for (i = 0; i < shapeColorArray.length; i++) {
    let color = "";
    if (index === i) {
      color = shapeColorArray[i][1];
    }
    document.getElementById(shapeColorArray[i][0]).style.fill = color;
  }
}

function highlightRow(buttonData) {
  if (buttonData.indexOf("2") > -1) {
    document.getElementById("circle-10").style.fill = "#FFFFE6";
    document.getElementById("parallelogram-11").style.fill = "#FFE0CC";
    document.getElementById("hexagon-12").style.fill = "#FFE6E6";
  } else if (buttonData.indexOf("3") > -1) {
    document.getElementById("pentagon-7").style.fill = "#FFFFB3";
    document.getElementById("rombus-8").style.fill = "#FFB380";
    document.getElementById("triangle-down-9").style.fill = "#FF9999";
  } else if (buttonData.indexOf("4") > -1) {
    document.getElementById("trapezoid-4").style.fill = "#FFFF80";
    document.getElementById("circle-5").style.fill = "#FF8533";
    document.getElementById("parallelogram-6").style.fill = "#FF4D4D";
  } else if (buttonData.indexOf("5") > -1) {
    document.getElementById("hexagon-1").style.fill = "#FFFF00";
    document.getElementById("triangle-up-2").style.fill = "#FF6600";
    document.getElementById("circle-3").style.fill = "#FF0000";
  } else if (buttonData.indexOf("6") > -1) {
    for (i = 0; i < shapeColorArray.length; i++) {
      let color = "";
      document.getElementById(shapeColorArray[i][0]).style.fill = color;
    }
  }
}
