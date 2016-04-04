#Assignment 1 System Programming Graded
## Francesco Saverio Zuppichini

###Preambula
I spoke with luca scibona about the input part, so maybe, you will find a similar approach.


My signature is a little bit different, since we need other information more then the *struct state* i decided to create a *struct game* that contains the *struct state*, the players and so on. I know that some people just put them in the *state* but from my point of view there doesn't below to the state. So in the signature i used *struct game ...* instead of *struct state ...* since i can access to the state from *game->state* and then i can use the general information about the match. I hope that you appreciate my good intentions to improve my implementation

   I strongly suggest you to read the comments in the header for a general overview, and, for a deeper understanding of the code, the source file. 
   
###Error handling
One of my aiming was error handling. Is really foundamental that the user is allowed to write only what we are aspecting. Below you can find a list of the checked erros in my implementation.

* Argument line parameters
	* correct number
	* presence of the separators *-p* and *-s*
	* at leas one player
	* correct format of the table size
		* there is a 'x'
		* there are two numbers *before* and *after* the x
			* the numbers must be real number (48 < x < 57)
	* memory error after malloc
* game input parameters
	* in the size of the table
	* in a empty cell
	* in can be only a number or 'show'
	* check for EOF

###Replay mode
As you can notice in my code there is a commented function with a TODO, this is why in the first developing i thought that was a good idea to add an array of moves so, in a future, i can write the replay move. Why i do that? Since it's easy to comment it out now but it's harded to modify it later. Thus an array with all the moves can always be usefull.

###Conclusion
####Pros
* error handling
* tons of comments
* good division in functions 


####Cons
* in my opinion keep every thing in a file is very confusing (but you have your really good reason to ask to do it )
* some inconsistency in coding style (due to the fact that i'm still developing mine)

Further informatitions can be found at https://github.com/FrancescoSaverioZuppichini/FourInARow