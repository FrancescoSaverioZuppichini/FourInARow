//
//  game.h
//  SP_EX1_GRADED_CORRECT
//
//  Created by Francesco  on 31/03/16.
//  Copyright © 2016 Francesco Saverio Zuppichini. All rights reserved.
//

#ifndef game_h
#define game_h

/* It makes more sense to return 1 as correct output and 0 as incorrect ouput. Why you may ask?
 In c language program the number 1 is interpreted as true and 0 as false, thus checking condition in a condition flow will
 result more readible and less confusing. 8*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_MOVE 2
#define MIN_STRING_LEN 5
#define PARSE_ERR "Error in parsing user's input"
#define NO_PARAM "Error in reading user's comand line"
#define NEW_LINE (putchar('\n'))
#define KINDLY "Please, input your move (just a column): "
/* this macro will trigger the show_table comand */
#define SHOW_TABLE "show"

struct state {
    /* the 2D array that represent the table */
    char **table;
};

struct move {
    /* The player that did the move */
    char player;
    int row;
    int column;
};
/* This structure is passed almost everywhere in the functions, it holds everything we need to know about the current game */
struct game{
    /* The game's players */
    char *players;
    /* the winner of the game */
    char winner;
    /* the state of the game */
    struct state state;
    /* why i have it if i don't use it?
     this can be usefull for future implementation since
     we are keeping track of every move
     */
    struct move *moves;
    /* pointer to the players stack */
    int current_player;
    /* usefull informations about the game */
    int rows;
    int columns;
    /* this is the strlen of the comand line parameter rowXcolumn
     we will use it to do a first check on the user's input
     */
    int max_input;
    
};
/* This function setup a game, it checks the inputs and stores the player and creates a table*/
int game_setup(int argc, const char *argv[],struct game *myGame);
/* This function asks for a new move and update the game. It return 1 if a new move can be asked, 0 if the game is finished */
int next_move(struct game *myGame);
/* This function free all the memory and say bye */
void free_all(struct game *myGame);


#endif /* game_h */
