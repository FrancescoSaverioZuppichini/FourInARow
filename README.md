# FourInARow [![Build Status](https://travis-ci.org/FrancescoSaverioZuppichini/FourInARow.svg?branch=master)](https://travis-ci.org/FrancescoSaverioZuppichini/FourInARow)
## C implementation of the famous *four in a row* game
#### *By Francesco Saverio Zuppichini*

###How to play
Clone the folder, from the terminal *cd* into it and then run:

```
gcc fourinarow.c game.c -o fourinarow 
```
Then in oder to play just run the program

```
./fourinarow 
```

###Players and table size
To create a custom game just run the program with the follows arguments


```
./fourinarow -p <playersNamesAsSingleChar> -s <RowXColumns>
```

####Example 
If we want to create a game with three players *a*,*b*,*c* in a table of *6* rows and *8* column we need to run:


```
./fourinarow -p abc -s 6x8
```

Without any arguments the games will start with two players *a* , *b* and a table of size *7x6*