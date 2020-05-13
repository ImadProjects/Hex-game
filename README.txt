Welcome to our Hex project !

Three stategies were implemented during this project, a random strategy, a blocking strategy, a minimax strategy and a Kirchhoff strategy.

vrandom.so is our random player
bloker.so is our blocking player
aresistance.so is our resistance (Kirchhoff) player.
minimax.so is our minimax player

To compile our code use the command "make"

To compile tests use "make test"

To run tests afterwards use "./install/alltests"

To generate a game use the command : ".install/server -m [M] -t [T] ./install/player1.so ./install/player2.so"
-m allows the manipulation of the size of the board
-t allows the manipulation of the form of the board. Use "h" for hexagonal, "c" for square, "t" for triangle
