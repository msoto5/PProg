/** 
 * @brief It implements the dialogue interpreter module.
 * 
 * 
 * @file dialogue.c
 * @author Miguel Soto, Nicolas Victorino, Ignacio Nunez and Antonio Van-Oers
 * @version 3.0 
 * @date 27-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dialogue.h"

char matrix_command[COMMAND_SIZE][WORD_SIZE] =
{ " ",                                                                      /*!< DC_ERROR*/
  "Exiting game...",                                                        /*!< DC_EXIT*/   
  "You picked *",                                                           /*!< DC_TAKE*/      
  "You dropped *",                                                          /*!< DC_DROP*/      
  "You missed and * hit you . ",                                            /*!< DC_ATTACK_MISSED*/ 
  "You hit * . ",                                                           /*!< DC_ATTACK_HIT*/    
  "It was a critical hit from *!",                                                 /*!< DC_ATTACK_CRITICAL*/
  "You moved North, you are now in the *",                                  /*!< DC_MOVE_N*/  
  "You moved East, you are now in the *",                                   /*!< DC_MOVE_E*/   
  "You moved South, you are now in the *",                                  /*!< DC_MOVE_S*/  
  "You moved West, you are now in the *",                                   /*!< DC_MOVE_W*/ 
  "You moved Up, you are now in the *",                                     /*!< DC_MOVE_U*/     
  "You moved Down, you are now in the *",                                   /*!< DC_MOVE_D*/
  "You look around and found that the *",                                   /*!< DC_INSPECT_space*/ 
  "After a closer look, it * ",                                                /*!< DC_INSPECT_obj*/ 
  "Save completed successfully",                                            /*!< DC_SAVE*/
  "Loading game... Successful",                                             /*!< DC_MLOAD*/
  "You slept for a while, you should check the time ",                      /*!< DC_USE_BED*/
  "You used an apple, you recovered health",                                /*!< DC_USE_APPLE*/
  "You used an elixir, you recovered health",                               /*!< DC_USE_ELIXIR*/
  "You used armor, max health increased",                                   /*!< DC_USE_ARMOR*/
  "You used the hook, looks like you found a key!",                         /*!< DC_USE_HOOK*/
  "You dropped the crumbs close to your cellmate, he thanked you for that and     mentioned he left the key for a hidden door in an unreachable place so that no one will ever use it",     /*!< DC_BREAD*/
  "What's with me, what am I even thinking?",                               /*!< DC_UNKNOWN*/
  "Looks like the three candles activated a mechanism, a huge shelf slides to the side, revealing the opening to a Bedroom",                                                            /*!< DC_PUZZLE*/
  "You opened a door ",                                                     /*!< DC_OPEN*/
  "How dare you attack your creator? It was me who touched you, who Blessed you, no help for you this time. ALSO, have your punishment, little human -YOU WERE ATTACKED BY HIM, leaving you wounded",    /*!< DC_HIM*/
  "So here you are, seeking a final battle. Pathetic that you believe his promises, HE will abandon you, once again, like every other time. If not His, you will suffer the Dusk wrath", /*!< DC_BOSS*/ 
  "Your Sword broke",
  "You turned * on ",
  "You turned * off ",
  "After being knocked out, you found yourself in a Cell, a hungry cellmate is asking you for anything he could get, although you could attack him, you'd rather spare him, not evil apparently ",
  "Well here I am son, congrats for destroying the last remain of evil in this land, here, I'll end your pain - HE said while unraveling a sword and beheading you - Peace, at last  ",
  "You were slained by an enemy, you ask for a miracle so you can finish your quest, HE will bring you back next time ",
  "As soon as you took the Sun_Sword, the Moon_Armor dissapeared, you should inspect it, you feel a lot more powerful yielding it ",
  "As soon as you took the Moon_Armor, the  Sun_Sword dissapeared, you should inspect it, you feel a lot stronger wearing it "
};

char matrix_event[EVENT_SIZE][WORD_SIZE] =
{ "All seems ok",                                                           /*!< DE_NOTHING*/
  "This object was not here, someone moved it...",                          /*!< DE_MOVEOBJ*/
  "Be carefull! You stepped on spikes and lost 1 HP",                       /*!< DE_TRAP*/
  "A rat suddenly appeared, and it is attacking you!",                      /*!< DE_SLIME*/
  "Time seems to fly here. Darkness came and Night is upon us.",            /*!< DE_NIGHT*/
  "You can see the sun rising, it is daytime again",                        /*!< DE_DAY*/
  "You got lost and got back where you started"                             /*!< DE_SPAWN*/
};

char matrix_error[ERROR_SIZE][WORD_SIZE] =
{ " ",                                                                      /*!< E_ERROR*/
  "Error exiting game...",                                                        /*!< E_EXIT*/   
  "You can't take that * (if it is a key, it might be unreachable)",                                                           /*!< E_TAKE*/      
  "You can't drop that * ",                                                          /*!< E_DROP*/      
  "You can't attack now . ",                                            /*!< E_ATTACK */ 
  "You can't move North, you remain in the *",                                  /*!< E_MOVE_N*/  
  "You can't move East, you remain in the *",                                   /*!< E_MOVE_E*/   
  "You can't move South, you remain in the *",                                  /*!< E_MOVE_S*/  
  "You can't move West, you remain in the *",                                   /*!< E_MOVE_W*/ 
  "You can't move Up, you remain in the *",                                     /*!< E_MOVE_U*/     
  "You can't move Down, you remain in the *",                                   /*!< E_MOVE_D*/
  "You couldn't inpect that",                                   /*!< E_INSPECT*/ 
  "Couldn't save the game",                                            /*!< E_SAVE*/
  "Loading game... ERROR",                                             /*!< E_MLOAD*/
  "You cant use this now ",                                           /*!< E_USE*/
  "You couldn't open it, wrong key? maybe wrong door? ",                    /*!< E_OPEN*/
  "You couldn't turn * on ",                                             /*!< E_TON*/
  "You couldn't turn * off "                                             /*!< E_TOFF*/
};

struct _Dialogue
{
    char *command;      /*!< Command´s dialogue*/
    char *event;        /*!< Event´s dialogue*/
    char *error;         /*!< Error´s dialogue*/
};

/**
 * @brief Function that substitutes the * on each default dialogue by specific modifiers
 * 
 * @param str given command string
 * @param arg Given argument
 * @return Modified command
 */
char *strmod(char *str, const char *arg);


char *strmod(char *str, const char *arg) {
    char *res;
    int k = 0;
    int i;

    if(!str){
        return NULL;
    }

    if(arg == NULL){
        arg = " ";
    }

    res = (char *) malloc(strlen(str)+strlen(arg)+1);
    for (i=0; i<strlen(str); i++) {
        if (str[i] != '*') 
            res[k++] = str[i];
        else {
            strcpy(res+k, arg);
            k += strlen(arg);
        }
    }
    res[k] = 0;
    return res;
}


/** Function to create a dialogue struct
*/
Dialogue *dialogue_create()
{
    Dialogue *new_dialogue = NULL;

    new_dialogue = (Dialogue*) malloc(sizeof(Dialogue));

    /* Error control */
    if (new_dialogue == NULL)
    {
        return NULL;
    }

    new_dialogue->command = NULL;
    new_dialogue->event = NULL;
    new_dialogue->error = NULL;
    
    return new_dialogue;

}

/** Function to free a given dialogue structure
*/
STATUS dialogue_destroy(Dialogue *d)
{
    /*Error control*/
    if (!d)
    return ERROR;

    if(d->command != NULL){
        free(d->command);
    }
    if(d->error != NULL){
        free(d->error);
    }

    free(d);

    return OK;
}

/** Resets the dialogue
*/
STATUS dialogue_reset(Dialogue *dialogue){
    
    /*Error Control*/
    if(dialogue == NULL){
        return ERROR;
    }

    if(dialogue->command != NULL){
        free(dialogue->command);
    }
    if(dialogue->error != NULL){
        free(dialogue->error);
    }

    dialogue->command = strmod(matrix_command[DC_ERROR], " ");
    dialogue->event = matrix_event[DE_NOTHING];
    dialogue->error = strmod(matrix_error[E_ERROR], " ");

    return OK;
}

/** Gets the dialogue information after executing a command
*/
char *dialogue_get_command(Dialogue *dialogue)
{
    /*Error control */
    if(dialogue == NULL){
        return NULL;
    }

    return dialogue->command;
}

/** Sets the dialogue information after executing a command
*/
STATUS dialogue_set_command(Dialogue *dialogue, DC_Enum condition, Space *current_loc, Object *obj, Enemy *enemy)
{
    /*Error control*/
    if(dialogue == NULL){
        return ERROR;
    }
  
    if(dialogue->command!=NULL){
        free(dialogue->command);
    }

     if (condition == DC_TAKE || condition == DC_DROP || condition == DC_TON || condition == DC_TOFF){
        if(obj == NULL)
        {
            dialogue->command = strmod(matrix_command[DC_PUZZLE], " ");   
        }
        else
        {
            dialogue->command = strmod(matrix_command[condition], obj_get_name(obj) );
        }
         
     }

     else if (condition == DC_MOVE_N || condition == DC_MOVE_E || condition == DC_MOVE_S || condition == DC_MOVE_W || condition == DC_MOVE_U || condition == DC_MOVE_D){
        
         dialogue->command = strmod(matrix_command[condition], space_get_name(current_loc));
     }

     else if (condition == DC_ATTACK_HIT || condition == DC_ATTACK_MISSED || condition == DC_ATTACK_CRITICAL ){
        
         dialogue->command = strmod(matrix_command[condition], enemy_get_name(enemy));
     }

     else if (condition == DC_INSPECT_O){
         dialogue->command = strmod(matrix_command[condition], obj_get_description(obj));
     }

     else if (condition == DC_INSPECT_S){
         dialogue->command = strmod(matrix_command[condition], space_get_long_description(current_loc));
     }
     
     else
     {
        dialogue->command = strmod(matrix_command[condition], " ");      
     }
   
    if(dialogue->command == NULL){
        return ERROR;
    }

    return OK;
}
/**                     
                 
    DC_OPEN,                   
                       
    **/

/** Gets the dialogue information after executing an event
*/
char *dialogue_get_event(Dialogue *dialogue)
{
    /*Error control */
    if(dialogue == NULL){
        return NULL;
    }

    return dialogue->event;
}

/** Sets the dialogue information after executing an event
*/
STATUS dialogue_set_event(Dialogue *dialogue, DE_Enum condition)
{
    /*Error control*/
    if(dialogue == NULL){
        return ERROR;
    }

    dialogue->event = matrix_event[condition];

    return OK;
}

char *dialogue_get_error(Dialogue *dialogue)
{
    /*Error control */
    if(dialogue == NULL){
        return NULL;
    }

    return dialogue->error;
}

STATUS dialogue_set_error(Dialogue *dialogue, E_Enum condition, Space *current_loc, Object *obj, Enemy *enemy)
{
    /*Error control*/
    if(dialogue == NULL){
        return ERROR;
    }
  
    if(dialogue->error!=NULL){
        free(dialogue->error);
    }

     if (condition == E_TAKE || condition == E_DROP || condition == E_TON || condition == E_TOFF){
        
            dialogue->error = strmod(matrix_error[condition], obj_get_name(obj) );
        }
     else if (condition == E_MOVE_N || condition == E_MOVE_E || condition == E_MOVE_S || condition == E_MOVE_W || condition == E_MOVE_U || condition == E_MOVE_D){
        
         dialogue->error = strmod(matrix_error[condition], space_get_name(current_loc));
     }

     else
     {
        dialogue->error = strmod(matrix_error[condition], " ");      
     }
   
    if(dialogue->error == NULL){
        return ERROR;
    }

    return OK;
}
