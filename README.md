Project Hex   
=====================

![alt text](doc/logo.png| width=100)


About
-------------------
C implementation of Hex Game


Authors
-------------------
Olivier Nguyen, Hicham Zghari, Augustin Gaucher, Imad Boudroua.


Compilation
-------------------
1- make

2- ./install/server install/fichier1.so install/fichier2.so

    options:

    -p1 print graph on terminal

    -m8 graphe de taille 8 

    -tc graph carré

    -th hexagonal

    -tt triangular

    perfect example:

    ./install/server -p1 -m8 install/bloker.so install/minimax.so 


Generate documentation
-------------------

make doc



test sources
-------------------

make test

./insall/alltests

visualisation of the game with html (not improved but works fine)
-------------------

1- ./install/server -m8 install/fichier1.so install/fichier2.so

2- make show    (opens game.html)

visualisation of the game in terminal (works great)
-------------------

1- ./install/server -p1 -m8 install/fichier1.so install/fichier2.so

