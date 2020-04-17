var p = new Object();
p.color = 0;
p.move = [0,1,2,3,4,5,6,7,8,9,10,14,15,16,17,18,19,20,25,33,34,38,40,41,42,44,45,46,49,50,51,52,54,55,56,65,67,68,70,73,74,75,76,77,78,79,81,85,86,87,88,89,91,92,93,94,97,98,102,103,104,111,112,113,114,118,121,122,123,124,125,126,127,128,129,130,133,134,135,136,137,138,139,140,141,142,143];
var pl = new Object();
pl.color = 1;
pl.move = [11,12,13,16,17,18,20,21,22,23,24,26,27,28,29,30,31,32,35,36,37,38,39,43,46,47,48,50,52,53,54,56,57,58,59,60,61,62,63,64,66,67,68,69,71,72,77,79,80,82,83,84,85,86,87,88,89,90,91,95,96,97,98,99,100,101,103,105,106,107,108,109,110,114,115,116,117,119,120,123,124,125,126,127,130,131,132];
/*var p = new Object();
p.move = [0,1,2,6,9,13,14,15,15];
var pl = new Object();
pl.move = [6,6,6,6,18];
*/
/*var p = new Object();
p.move = [22,10,11,18,13,26];
var pl = new Object();
pl.move = [19,10,11,25,21,14];
*/

      /*  var player2 = new Object();
        player2.fabricant = "Ford";
        player2.modèle = "Mustang";
        player2.move = 3;
        var player1 = new Object();
        player1.fabricant = "Ford";
        player1.modèle = "Mustang";
        player1.move = 5;*/
(function(){
    var canvas = document.getElementById('hexmap');

    var hexHeight,
        hexRadius,
        hexRectangleHeight,
        hexRectangleWidth,
        hexagonAngle = 0.523598776, // 30 degrees in radians
        sideLength = 10,
        boardWidth = 100,
        boardHeight = 100;
        player1 = 2;
        size = 4;
    var   color1,
    color2;
    if (pl["color"==1]){
        color1 = "green";
        color2 = "red";
    }
    else{
        color2 = "green";
        color1 = "red";        
    }

        var ctx = canvas.getContext('2d');
    hexHeight = Math.sin(hexagonAngle) * sideLength;
    hexRadius = Math.cos(hexagonAngle) * sideLength;
    hexRectangleHeight = sideLength + 2 * hexHeight;
    hexRectangleWidth = 2 * hexRadius;

    if (canvas.getContext){
        var ctx = canvas.getContext('2d');

        ctx.fillStyle = "#000000";
        ctx.strokeStyle = "#000000";
        ctx.lineWidth = 1;

        drawBoard(ctx, boardWidth, boardHeight,size);
        play(ctx, boardWidth, boardHeight, pl, p);

        canvas.addEventListener("mousemove", function(eventInfo) {
            var x,
                y,
                hexX,
                hexY,
                screenX,
                screenY,
                rect;

            rect = canvas.getBoundingClientRect();

            x = eventInfo.clientX - rect.left;
            y = eventInfo.clientY - rect.top;

            hexY = Math.floor(y / (hexHeight + sideLength));
            hexX = Math.floor((x - (hexY % 2) * hexRadius) / hexRectangleWidth);

            screenX = hexX * hexRectangleWidth + ((hexY % 2) * hexRadius);
            screenY = hexY * (hexHeight + sideLength);

            ctx.clearRect(0, 0, canvas.width, canvas.height);

            drawBoard(ctx, boardWidth, boardHeight);

            // Check if the mouse's coords are on the board
            if(hexX >= 0 && hexX < boardWidth) {
                if(hexY >= 0 && hexY < boardHeight) {
                    ctx.fillStyle = "#000000";
                    drawHexagon(ctx, screenX, screenY, true);
                }
            }
        });
    }

    function drawBoard(canvasContext, width, height, size) {
        var i,
            j;

        for(i = 0; i <size; ++i) {
            for(j = 0; j < size; ++j) {
                drawHexagon(
                    ctx, 
                    i * hexRectangleWidth + (j * hexRadius), 
                    j * (sideLength + hexHeight), 
                    false,
                    'white'
                );
            }
        }
        for(i = 0; i <size; ++i) {
            for(j = 1; j < size; ++j) {
                drawHexagon(
                    ctx, 
                    0 * hexRectangleWidth + (j* hexRadius), 
                    j * (sideLength + hexHeight), 
                    false,
                    'red'
                );
                drawHexagon(
                    ctx, 
                    i * hexRectangleWidth + (0* hexRadius), 
                    0 * (sideLength + hexHeight), 
                    false,
                    'green'
                );

                drawHexagon(
                    ctx, 
                    (size-1) * hexRectangleWidth + (j* hexRadius), 
                    j * (sideLength + hexHeight), 
                    false,
                    'red'
                    );
                drawHexagon(
                    ctx, 
                    i * hexRectangleWidth + ((size-1)* hexRadius), 
                    (size-1) * (sideLength + hexHeight), 
                    false,
                    'green'
                );
            }
        }
        drawHexagon(
            ctx, 
            (size-1) * hexRectangleWidth + (0* hexRadius), 
            0 * (sideLength + hexHeight), 
            false,
            'red'
            );
    }

    function drawHexagon(canvasContext, x, y, fill , color) {           
        var fill = fill || false;

        canvasContext.beginPath();
        canvasContext.strokeStyle = 'black';
        canvasContext.moveTo(x + hexRadius, y);
        canvasContext.lineTo(x + hexRectangleWidth, y + hexHeight);
        canvasContext.lineTo(x + hexRectangleWidth, y + hexHeight + sideLength);
        canvasContext.lineTo(x + hexRadius, y + hexRectangleHeight);
        canvasContext.lineTo(x, y + sideLength + hexHeight);
        canvasContext.lineTo(x, y + hexHeight);
        canvasContext.fillStyle = color;
         canvasContext.fill();
        canvasContext.closePath();

        if(fill) {
            canvasContext.fill();
        } else {
            canvasContext.stroke();
        }
    }
    function play(canvasContext, width, height, player1, player2) {
        var i = player2["move"][0][0] ;
        var l = (player2["move"]).length
        console.log(Math.trunc(player1["move"][5]/size));
        var m;
        for(m = 0; m<l; ++m) {      
            drawHexagon(
                ctx, 
                Math.trunc(player2["move"][m]- size*Math.trunc(player2["move"][m]/size))* hexRectangleWidth + ( Math.trunc(player2["move"][m]/size)* hexRadius), 
                Math.trunc(player2["move"][m]/size)  * (sideLength + hexHeight), 
                false,
                color1
                );


        }        for(m = 0; m<l; ++m) {     
            drawHexagon(
                ctx, 
                Math.trunc(player1["move"][m]- size*Math.trunc(player1["move"][m]/size))* hexRectangleWidth + ( Math.trunc(player1["move"][m]/size)* hexRadius), 
                Math.trunc(player1["move"][m]/size)  * (sideLength + hexHeight), 
                false,
                color2
                );


        }

    }

})();