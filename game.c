//
//  game.c
//  SP_EX1_GRADED_CORRECT
//
//  Created by Francesco  on 31/03/16.
//  Copyright © 2016 Francesco Saverio Zuppichini. All rights reserved.
//

#include "game.h"

/* This global variable holds all the data about the current game
 look at the header for more informations about game */
struct game myGame;

void free_all(){
    /* free all memory */
    free(myGame.moves);
    free(myGame.players);
    free(myGame.state.table);
    /* we are kind :) */
    NEW_LINE;
    puts("Bye and thank you for playing :)");
    
}

/* This function check if the input is indeed a numerical input */
int my_atoi(const char *to_convert){
    int i,n;
    
    n = 0;
    /* we don't need to check the sign */
    for (i = 0; to_convert[i] != '\0'; i++) {
        /* we must accepct only numerical input */
        if (to_convert[i] < '0' || to_convert[i] > '9') {
            /* this will raise an error in the called function */
            n = - 1;
            break;
        }
        /* convert the ascii char */
        n = (to_convert[i] - '0') + 10*n;
    }
        
    return  n;
}

/* This function parses a string input in a form of <rowXcolumn> (e.g "5x5").
 The signature doens't need any 'struct game' thus we can use it for further implementations */
int parse_rowXcolumn(char *rowXcolumn, int *r, int *c){
    /* will holds the strtok returns */
    char *temp;
    /* now we break the string and we convert each sub-string in int */
    temp = strtok(rowXcolumn,"x");
    if( temp == NULL){
        /* no memory! */
        return 1;
    }
    /* everything okay */
    *r = my_atoi(temp);
    
    temp = strtok(NULL,"x");
    
    if(temp == NULL){
        return 1;
    };
    /* let's convert the string in int */
    *c = my_atoi(temp);
    
    /* check for incorrect numbers */
    if (*r <= 0 ||  *c <= 0) {
        return 0;
    }
    
    return 1;
}


int parse_and_set_rowXcolumn(char *info){
    int rows;
    int columns;
    /* check the inputs */
    if(!parse_rowXcolumn(info,&rows,&columns)){
        puts(NO_PARAM);
        return 0;
    };
    /* update the game's dimensions */
    myGame.rows = rows;
    myGame.columns = columns;
    /* everything ok! */
    return 1;
    
}

/* This function initiliazed the table as a 2D array of empty space */
void initiliaze_table(){
    int i,j;
    
    for (i = 0; i < myGame.rows; i++) {
        for (j = 0; j < myGame.columns; j++) {
            myGame.state.table[i][j] = ' ';
        }
    }
    
}
/* check if the table is too small */
int is_big_enough(){
// TODO find the correct formulat to do that
//    return myGame.rows * myGame.columns >= 4 * strlen(myGame.players) ;
    return 1;
}

int create_table(){
    int i;
    
    /* allocate memory for the 2d array */
    myGame.state.table = malloc(myGame.rows * sizeof(*myGame.state.table));
    
    if(myGame.state.table == NULL){
        return 0;
    }
    
    /* allocate memory for the columns */
    for (i = 0; i < myGame.rows; i++) {
        myGame.state.table[i] = malloc(myGame.columns * sizeof(char));
    }
    
    /* initialize the table with empty space */
    initiliaze_table();
    return 1;
}

/* This function setup the table */
int  setup_table(char *info){
    
    /* this is used to check valid players' moves */
    myGame.max_input = (int) strlen(info);
    /* check and set the info into myGame */
    if(!parse_and_set_rowXcolumn(info))
        return 0;
    /* check is the table is really playable */
    if(!is_big_enough()){
        puts("The table size is too small");
        return 0;
    }
    /* used myGame.rows and columns in order to create the 2D array*/
    if (!create_table())
        return 0;
    
    return 1;
}

/* This functiona allocates the momery and store the players name in game->players*/
int setup_players(const char *players){
    /* copy players in myGame */
    myGame.players = malloc(sizeof(char) * (int) strlen(players));
    strcpy(myGame.players,players);
    /* players acts like a stack with a pointer to the curr player */
    myGame.current_player = 0;
    /* initiliaze moves */
    myGame.moves = malloc(sizeof(struct move) * MIN_MOVE);
    
    return 1;
    
}

/* This function copy a string src into a string dst
 but it alloc new memory every time the string dst is full */
int copy_dynamically(char dst[], const char src[], int cap){
    int i;
    
    for (i = 0; i < strlen(src); i++) {
        
        if(i > cap){
            
            cap = i*2;
            dst = realloc(dst, sizeof(char) * cap);
            if (dst == NULL)
                return 0;
        }
        
        dst[i] = src[i];
    }
    dst[i] = '\0';
    
    return 1;
}

/* This function will do the dirty work for game_setup, it actually setup everything given the players and the table info*/
int inner_game_setup(const char *players, char *table_info){
    /* set up the game */
    if (!setup_players(players))
        return 0;
    if(!setup_table(table_info))
        return 0;

    return 1;
}
/* This function setups all the custom_game */
int custom_game(const char *argv[]){
    char *players;
    char *table_info;
    
    table_info = malloc(sizeof(char) * MIN_STRING_LEN);
    players = malloc(sizeof(char) * MIN_STRING_LEN);
    
    /* check if the delimiters exist */
    if (strcmp(argv[1], "-p") != 0) {
        puts(PARSE_ERR);
        return 0;
    }
    if(strcmp(argv[3], "-s") != 0){
        puts(PARSE_ERR);
        return 0;
    }
    /* copy the players' names */
    if(!copy_dynamically(players, argv[2],MIN_STRING_LEN))
        return 0;
    /* set up the game! */
    if(!copy_dynamically(table_info, argv[4],MIN_STRING_LEN))
        return 0;
    
    
    return inner_game_setup(players, table_info);
    
}

int default_game(){
    char players[] = "ab";
    char table_info[] = "7x6";
    
    
    /* parameters are hard coded */
    return inner_game_setup(players, table_info);
    
}

/* This function checks the argv and call the corresponding functions in order the create a game */
int game_setup(int argc, const char *argv[]){
    /* first check the number of argc, we need 5 since
     argv must be = to ["<filename>","-p","<players>","-s","<rowXcolumn>"]
     */
    switch (argc) {
        case 1:
            puts("Default game selected");
            return default_game();
            
        case 5:
            puts("Custom game selected");
            return custom_game(argv);
            
        default:
            puts("The number parameters is incorrect");
            return 0;
    }
    
}

/* This function will print the '-------' line */
void print_frame(){
    int i;
    
    for (i = 0; i < myGame.columns * 4; i++) {
        putchar('-');
    }
}

/* This function print the table for the game */
void game_print(){
    int i,j;
    
    NEW_LINE;
    print_frame();
    NEW_LINE;
    for (i = myGame.rows - 1; i >= 0; i--) {
        for (j = 0; j < myGame.columns ; j++) {
            printf("%c%c%c%c",'|',' ',myGame.state.table[i][j],' ');
        }
        printf("%c",'|');
        NEW_LINE;
        print_frame();
        NEW_LINE;
    }
    NEW_LINE;
    
}

/* This function finds the corresponding row of the last empty position in 'currColumn' */
int find_row(int currColumn){
    int i;
    /* scan down-top */
    for (i = 0 ; i < myGame.rows && myGame.state.table[i][currColumn - 1] != ' '  ; i++);
    /* +1 because the user starts to count from 1 not 0*/
    return i + 1;
    
}

/* This function stores the current move in the 2D array in game->state->table */
int store_move_in_table(char *currMoveString, struct move *currMove ){
    int currColumn;
    int currRow;
    
    /* no need to use my_atoi */
    currColumn = atoi(currMoveString);
    
    /* check for wrong dimensions */
    if (currColumn <= 0 || currColumn > myGame.columns) {
        return 0;
    }
    /* store the column */
    currMove->column = currColumn;
    /* let's find the row */
    currRow = find_row(currColumn);
    /* another check */
    if (currRow > myGame.rows) {
        return 0;
    }
    /* move valid, store the row */
    currMove->row = currRow;
    
    return 1;
}

void update_current_player(){
    /* point to the next one */
    myGame.current_player++;
    myGame.current_player %= strlen(myGame.players);
}

/* This function update the state of the game */
void game_update(struct move *currMove){
    /* store the player */
    currMove->player = myGame.players[myGame.current_player];
    update_current_player();
    /* update the state */
    myGame.state.table[currMove->row - 1][currMove->column - 1] = currMove->player;
    
}


/* This function will ALWAYS return 1 if the move is invalid */
int move_is_valid(struct move *currMove){
    /* we NEED a string since we can read "show" */
    char *currMoveString;
    
    currMoveString = malloc((myGame.max_input > strlen(SHOW_TABLE) ? myGame.max_input : strlen(SHOW_TABLE)) * sizeof(char));
    puts(KINDLY);
    
    if(scanf("%s",currMoveString) != 1){
        /* if we read EOF, free and bye bye */
        free_all();
        /* actually i don't like this forced exit(0) */
        exit(0);
    };
    /* check if the user inputed 'show' */
    if(strcmp(currMoveString, SHOW_TABLE) == 0){
        game_print();
        /* we should ask again after showed the table */
        return 0;
    };
    
    /* the move input is valid, now we check the numerical values*/
    return store_move_in_table(currMoveString,currMove);
}

/* This is not used for now */
int update_moves(struct move * currMove){
    static int idx = 0;
    static int cap = MIN_MOVE;
    
    if (idx >= cap) {
        /* we need more memory! */
        cap = idx * 2;
        myGame.moves = realloc(myGame.moves, cap *sizeof(struct move));
        if ( myGame.moves == NULL) {
            /* no more memory */
            return 1;
        }
    }
    /* update it */
    myGame.moves[idx] = *currMove;
    idx++;
    
    return 0;
    
}

/* check if there is a winner in the same column */
int check_down(struct move *currMove){
    int i,times;
    
    times = 0;
    for (i = currMove->row - 1;  i >= 0 && times<4; i--) {
        if (myGame.state.table[i][currMove->column - 1] != currMove->player) {
            return 0;
        }
        times++;
    }
    return times == 4 ? 1 : 0;
    
}

/* called by check_same_line this helper function will do the dirty work of checking the same line */
int check_inner_same_line(struct move *currMove, int bool_dx){
    int i,times;
    
    times = 0;
    for (i = currMove ->column - 1; i >= 0 && times<4; bool_dx ? i++ : i--) {
        if (myGame.state.table[currMove->row - 1][i] != currMove->player) {
            return 0;
        }
        times++;
    }
    
    return times == 4 ? 1 : 0;
}

/* check if there is a winner in the same line */
int check_same_line(struct move *currMove){
    int to_return;
    to_return = 0;
    
    to_return += check_inner_same_line(currMove,1);
    to_return += check_inner_same_line(currMove,0);
    
    return to_return;
    
}

/* called by check_same_line this helper function will do the dirty work of checking the diagonals */
int inner_check_diagonal(struct move *currMove, int bool_column){
    int i,j,times;
    
    times = 0;
    for (i = currMove ->row - 1, j = currMove->column - 1; i >= 0  && j>= 0 && times<4; i--, bool_column ? j++ : j--) {
        if (myGame.state.table[i][j] != currMove->player) {
            return 0;
        }
        times++;
    }
    return times == 4 ? 1 : 0;
    
}

/* check if there is a winner in the diagonal */
int check_diagonal(struct move *currMove){
    int to_return;
    
    to_return = 0;
    /* up diagonal */
    to_return += inner_check_diagonal(currMove, 1);
    /* down diagonal */
    to_return += inner_check_diagonal(currMove, 0);
    
    
    return to_return > 0  ? 1 : 0;
    
}

/* This function check if in the last row of the table there are any empty space */
int check_last_row(){
    int i;
    
    for (i = 0; i < myGame.columns && myGame.state.table[myGame.rows - 1][i] != ' '; i++){
        
    };
    
    return i == myGame.columns;
}

/* This function will search any winner move */
int is_finish(struct move *currMove){
    /* this flag will holds the result of every checks */
    int winner_flag;
    
    winner_flag = 0;
    winner_flag += check_down(currMove);
    winner_flag += check_same_line(currMove);
    winner_flag += check_diagonal(currMove);
    
    /* at this point the flag can have a value in [0...3]
     if it is > 0 it means that one of the check function returns 1
     thus there is a winner */
    if (winner_flag > 0) {
        /* set the winner */
        myGame.winner  = currMove->player;
        printf("The winner is: %c \n", myGame.winner);
        return 1;
    }
    /* check if it is tie */
    else if (check_last_row()){
        puts("Tie !");
        return 1;
    };
    /* no winner, the match can continue */
    return 0;
    
}

/* This function ask a moves, save it, apply it and return 0 if the game is finish (won or tie) */
int next_move(){
    struct move currMove;

    printf("Player: %c\n", myGame.players[myGame.current_player]);
    /* continue to ask until the move is correct */
    while(!move_is_valid(&currMove));
    game_update(&currMove);
    /* update the moves history */
//    TODO this can be used as history replay mode
//    if(update_moves(&currMove) !=0)
//        return 1;
    /* print the table */
    game_print();
    /* check if there is a winner or it is tie */
    return is_finish(&currMove);
}




