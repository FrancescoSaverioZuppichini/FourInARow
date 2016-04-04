//
//  main.c
//  SP_EX1_GRADED_CORRECT
//
//  Created by Francesco  on 31/03/16.
//  Copyright © 2016 Francesco Saverio Zuppichini. All rights reserved.
//

#include "game.h"

int main(int argc, const char * argv[]) {
    /* setup the game */
    if(!game_setup(argc,argv)){
        /* something wrong happened in the setup */
        return 1;
    }
    /* now the game starts */
    while (!next_move());
    /* free the memory and say bye to players */
    free_all();
    return 0;
}