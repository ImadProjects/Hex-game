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