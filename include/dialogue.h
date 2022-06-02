/**
 * @brief It implements the dialogue interpreter interface
 *
 * @file dialogue.h
 * @author Nicolas VIctorino, Antonio Van-Oers, Ignacio Nunez and Miguel Soto
 * @version 3.0
 * @date 27-04-2022
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "types.h"
#include "object.h"
#include "space.h"
#include "enemy.h"
 
#define COMMAND_SIZE 36
#define EVENT_SIZE 7
#define ERROR_SIZE 18

typedef enum _enum_command_dialogue{
    DC_ERROR = 0,               /*!< Error command dialogue*/
    DC_EXIT,                    /*!< Exit command dialogue*/
    DC_TAKE,                    /*!< Take command dialogue*/
    DC_DROP,                    /*!< Drop command dialogue*/
    DC_ATTACK_MISSED,           /*!< Attack missed command dialogue*/
    DC_ATTACK_HIT,              /*!< Attack hit command dialogue*/
    DC_ATTACK_CRITICAL,         /*!< Critical attack command dialogue*/
    DC_MOVE_N,                  /*!< Move north command dialogue*/
    DC_MOVE_E,                  /*!< Move east command dialogue*/
    DC_MOVE_S,                  /*!< Move south command dialogue*/
    DC_MOVE_W,                  /*!< Move west command dialogue*/
    DC_MOVE_U,                  /*!< Move up command dialogue*/
    DC_MOVE_D,                  /*!< Move down command dialogue*/
    DC_INSPECT_S,               /*!< Inspect object command dialogue*/
    DC_INSPECT_O,               /*!< Inspect space command dialogue*/
    DC_SAVE,                    /*!< Save command dialogue*/   
    DC_LOAD,                    /*!< Load command dialogue*/
    DC_USE_BED,                 /*!< USE_BED command dialogue*/
    DC_USE_APPLE,                /*!< USE_APPLE command dialogue*/
    DC_USE_ELIXIR,               /*!< USE_ELIXIR command dialogue*/
    DC_USE_ARMOR,                /*!< USE_ARMOR command dialogue*/
    DC_USE_HOOK,                 /*!< USE_HOOK command dialogue*/
    DC_BREAD,                    /*!< BREAD command dialogue*/
    DC_UNKNOWN,                  /*!< UNKNOWN command dialogue*/
    DC_PUZZLE,                   /*!< PUZZLE command dialogue*/
    DC_OPEN,                     /*!< OPEN command dialogue*/
    DC_HIM,                      /*!< HIM command dialogue*/
    DC_BOSS,                      /*!< BOSS  command dialogue*/
    DC_SBROKE,                    /*!< SBROKE  command dialogue*/
    DC_TON,                       /*!< Turnon  command dialogue*/
    DC_TOFF,                      /*!< Turnoff  command dialogue*/
    DC_START,                     /*!< Starting  command dialogue*/
    DC_END,                       /*!< ENDGAME  command dialogue*/
    DC_GOVER,                      /*!< GAME OVER  command dialogue*/
    DC_TAKE_S,                     /*!< TAKE Sun_Sword command dialogue*/
    DC_TAKE_M                      /*!< TAKE Moon_armor  command dialogue*/

}DC_Enum;

typedef enum _enum_event_dialogue{
    DE_NOTHING = 0,             /*!< Nothing event dialogue*/
    DE_MOVEOBJ,                 /*!< Move objetc event dialogue*/
    DE_TRAP,                    /*!< Trap event dialogue*/
    DE_SLIME,                   /*!< Slime event dialogue*/
    DE_NIGHT,                   /*!< Night event dialogue*/
    DE_DAY,                     /*!< Day event dialogue*/
    DE_SPAWN                    /*!< Spawn event dialogue*/
}DE_Enum;

typedef enum _enum_error_dialogue{
    E_ERROR = 0,               /*!< Error command dialogue*/
    E_EXIT,                    /*!< Exit command dialogue*/
    E_TAKE,                    /*!< Take command dialogue*/
    E_DROP,                    /*!< Drop command dialogue*/
    E_ATTACK,                   /*!< Attack command dialogue*/
    E_MOVE_N,                  /*!< Move north command dialogue*/
    E_MOVE_E,                  /*!< Move east command dialogue*/
    E_MOVE_S,                  /*!< Move south command dialogue*/
    E_MOVE_W,                  /*!< Move west command dialogue*/
    E_MOVE_U,                  /*!< Move up command dialogue*/
    E_MOVE_D,                  /*!< Move down command dialogue*/
    E_INSPECT,                  /*!< Inspect object command dialogue*/
    E_SAVE,                    /*!< Save command dialogue*/   
    E_LOAD,                    /*!< Load command dialogue*/
    E_USE,                      /*!< USE_BED command dialogue*/
    E_OPEN,                     /*!< OPEN command dialogue*/
    E_TON,                       /*!< Turnon  command dialogue*/
    E_TOFF                      /*!< Turnoff  command dialogue*/

}E_Enum;

typedef struct _Dialogue Dialogue;

/**
 * @brief Function to create a dialogue struct
 * @author Ignacio Nunnez
 * 
 * @return Pointer to the new dialogue, or NULL if something went wrong
 */
Dialogue *dialogue_create();

/**
 * @brief Function to free a given dialogue
 * 
 * @author Nicolas Victorino
 * @param d pointer to the dialogue
 * @return ERROR if something went wrong
 */
STATUS dialogue_destroy(Dialogue *d);

/**
 * @brief Resets the dialogue
 * @author Ignacio Nunnez
 * 
 * @param dialogue pointer to the dialogue
 * @return ERROR if something went wrong 
 */
STATUS dialogue_reset(Dialogue *dialogue);

/**
 * @brief Gets the dialogue information after executing a command
 * @author Ignacio Nunnez
 * 
 * @param dialogue pointer to the dialogue
 * @return Pointer to the command dialogue char 
 */
char *dialogue_get_command(Dialogue *dialogue);

/**
 * @brief Sets the dialogue information after executing a command
 * 
 * @param dialogue pointer to the dialogue
 * @param condition condition to set the new command dialogue
 * @return ERROR if something went wrong 
 */
STATUS dialogue_set_command(Dialogue *dialogue, DC_Enum condition, Space *current_loc, Object *obj, Enemy *enemy);

/**
 * @brief Gets the dialogue information after executing an event
 * @author Ignacio Nunnez
 * 
 * @param dialogue pointer to the dialogue
 * @return Pointer to the event dialogue char 
 */
char *dialogue_get_event(Dialogue *dialogue);
 
/**
 * @brief Sets the dialogue information after executing an event
 * 
 * @param dialogue pointer to the dialogue 
 * @param condition condition to set the new event dialogue
 * @return ERROR if something went wrong 
 */
STATUS dialogue_set_event(Dialogue *dialogue, DE_Enum condition);

/**
 * @brief Gets the dialogue information after executing a command
 * @author Antonio Van-Oers
 * 
 * @param dialogue pointer to the dialogue
 * @return Pointer to the command dialogue char 
 */
char *dialogue_get_error(Dialogue *dialogue);

/**
 * @brief Sets the dialogue information after executing a command
 * 
 * @param dialogue pointer to the dialogue
 * @param condition condition to set the new command dialogue
 * @return ERROR if something went wrong 
 */
STATUS dialogue_set_error(Dialogue *dialogue, E_Enum condition, Space *current_loc, Object *obj, Enemy *enemy);


#endif
