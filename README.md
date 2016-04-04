# FourInARow
## C implementation of the famous *four in a row* game
#### *By Francesco Saverio Zuppichini*

###How to play
clone the folder, and go into it then run:

```
gcc fourinarow.c game.c -o fourinarow 
```
Then in oder to play

```
./fourinarow 
```

###Players and table size
In order to create a custom game just run with the follows arguments


```
./fourinarow -p <playersNamesAsSingleChar> -s <RowXColumns>
```

If we wanna to create a game with three players *a*,*b*,*c* in a table of *6* rows and *8* column we need to run:


```
./fourinarow -p abc -s 6x8
```
