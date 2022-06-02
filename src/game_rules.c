/**
 * @brief It implements features of the game
 *
 * @file game_rules.c
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers, Ignacio Nunez
 * @version 1.0
 * @date 25-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "../include/game_rules.h"
#include "../include/types.h"

/*Private functions*/
int random();

/*Generates a random event by 
    percentages and returns it*/
R_Event game_rules_get_event(){
    int magic;

    magic = random();

    if(magic >= EVENT_FIVE){
        return SPAWN;
    }
    if(magic >= EVENT_FOUR){
        return DAYNIGHT;
    }
    if(magic >= EVENT_THREE){
        return SLIME;
    }
    if(magic >= EVENT_TWO){
        return TRAP;
    }
    if(magic >= EVENT_ONE){
        return MOVE_OBJ;
    }

    return NOTHING;
}

/*Returns TRUE in porcentage of num*/
int random(){

    int rand_num;

    rand_num = rand() % 100;

    return rand_num;
}
