/* information on events for SVG elements found at: https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/Events
   https://stackoverflow.com/questions/16472224/add-onclick-event-to-svg-element */

// Code edited by: Tirsa Ramos-Pedersen

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
  

/* First attempt at the coding */
/*function changeColor(ev) {
    console.log(ev.target);
    document.getElementById("hexagon-1").style.fill = "#FFFF00";
    console.log("you have changed: hexagon-1" + "to the color: #FFF00");
}
document.getElementById("hexagon-1").addEventListener("click", changeColor);*/


/* Second attempt at the coding */

/*function changeColor(i) {
    for (i = 0; i < shapeColorArray.length; i++) {
        document.getElementById([i][0]).style.fill([i][1])
    }
    console.log("you have changed: "+ [i][0] + "to the color " + [i][1]);
}*/

