/** 
 * @brief It defines the game interface
 * 
 * @file game.h
 * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "link.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "enemy.h"
#include "inventory.h"
#include "game_rules.h"
#include "dialogue.h"

#define MAX_LINKS 200  /*!< It established the maximun of links that can be in a game */
#define MAX_SPACES 100  /*!< It established the maximun of spaces that can be in a game */
#define MAX_ENEMYS 10   /*!< It established the maximun of enemies that can be in a game */
#define MAX_OBJS 100   /*!< It established the maximun of objects that can be in a game */
#define MAX_PLAYERS 1  /*!< It established the maximun of players that can be in a game */

/**
 * @brief Game's structucture
 *
 * Has all members necessary to create, start and play a game
 */
typedef struct _Game Game;

/**
  * @brief returns inspection' pointer
  * @author Antonio Van-Oers
  * 
  * @param game a pointer to game
  * @return inspection pointer (can be NULL)
  */
char *game_get_inspection(Game *game);

/**
 * @brief Allocs memory for some of game's members
 * @author Miguel Soto
 * 
 * @param game a pointer to game
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_alloc(Game *game);

/**
  * @brief initializes all necessary members to empty values
  * @author Nicolas Victorino
  * 
  * @param game a pointer to game
  * @return OK if everything goes well or ERROR if there was any mistake
  */
STATUS game_create(Game *game);

/**
  * @brief Checks if there was any update on the game cmd, whenever the user types something
  * @author Miguel Soto
  *
  * game_update updates cmd whenever something is typed in, this is where 
  * every known case gets interpreted as the various actions on the game, 
  * any other input would be considered unknown
  * 
  * @param game a pointer to game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @param cmd la variable tipo T_Command del interprete de comandos, varia segun el comando introducido por el usuario
  * @param arg1 string with input command argument.
  * @param arg2 string with input command second argument.
  * @return 0 if ERROR, 1 if OK, and 5 if OK but dont print condition
  */
int game_update(Game *game, T_Command cmd, char *arg1, char *arg2);

/**
  * @brief frees/destroys the game
  * @author Ignacio Nunez
  *
  * game_destroy frees/destroys all of game's spaces  
  * calling space_destroy for each one of them
  * @param game a pointer to game
  * @return OK if everything goes well or ERROR if there was any mistake
  */
STATUS game_destroy(Game *game);

/**
  * @brief Ends the game
  * @author Antonio Van-Oers
  *
  * False is the output when called, meaning game has ended
  * 
  * @param game a pointer to game
  * @return FALSE 
  */
BOOL game_is_over(Game *game);

/**
  * @brief  Prints all game related relevant data
  * @author Nicolas Victorino
  *
  * @param game a pointer to game
  */
void game_print_data(Game *game);

/**
  * @brief Gets a space via target id
  * @author Ignacio Nunez
  *
  * Checks wheter a space is on the game by comparing target id with each game's spaces' id
  * @param game a pointer to game  
  * @param id target space's id
  * @return a pointer to the space which has that id, or NULL if something went wrong
  * or the space doesn't belong to the game
  */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Sets the day time of the game
 * @author Nicolas Victorino
 * 
 * @param game 
 * @param time 
 * @return STATUS 
 */
STATUS game_set_time(Game *game, Time time);

/**
 * @brief Gets if it is day or night
 * @author Nicolas Victorino
 * 
 * @param game Given game
 * @return Day or night, -1 if error 
 */
Time game_get_time(Game *game);

/**
 * @brief Gets the last event
 * @author Ignacio Nunnez
 * 
 * @param game Given game
 * @return the event (most times NOTHING) 
 */
R_Event game_get_last_event(Game *game);

/**
 * @brief Gets an object via target id
 * @author Miguel Soto
 * 
 * Checks wheter an object is on the game by comparing target id with each game's objects' id
 * @param game a pointer to game
 * @param id target objec's id
 * @return a pointer to the object which has that id, or NULL if something went wrong
 * or the object doesn't belong to the game
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief Gets a player via target id
 * @author Miguel Soto
 * 
 * Checks wheter a player is on the game by comparing target id with each game's players' id
 * @param game a pointer to game
 * @param id target player's id
 * @return a pointer to the player which has that id, or NULL if something went wrong
 * or the player doesn't belong to the game
 */
Player *game_get_player(Game *game, Id id);

/**
 * @brief Gets an enemy via target id
 * @author Miguel Soto
 * 
 * Checks wheter an enemy is on the game by comparing target id with each game's enemies' id
 * @param game a pointer to game
 * @param id target enemy's id
 * @return a pointer to the enemy which has that id, or NULL if something went wrong
 * or the enemy doesn't belong to the game
 */
Enemy *game_get_enemy(Game *game, Id id);

/**
 * @brief Gets an enemy via target id
 * @author Miguel Soto
 * 
 * Checks wheter a link is on the game by comparing target id with each game's links' id
 * @param game a pointer to game
 * @param id target link's id
 * @return a pointer to the link which has that id, or NULL if something went wrong
 * or the link doesn't belong to the game
 */
Link *game_get_link(Game *game, Id id);

/**
  * @brief Gets a player's location via target id
  * @author Miguel Soto
  *
  * @param game a pointer to game
  * @param player_id targe player's id
  * @return player's location's id or NO_ID if something went wrong
  */
Id game_get_player_location(Game *game, Id player_id);

/**
  * @brief Gets an enemy's location via target id
  * @author Antonio Van-Oers Luis
  *
  * @param game a pointer to game
  * @param enemy_id target enemy's id
  * @return enemy's location's id or NO_ID if something went wrong
  */
Id game_get_enemy_location(Game *game, Id enemy_id);

/**
  * @brief Gets an objects's location via target id
  * @author Miguel Soto
  *
  * @param game a pointer to game
  * @param obj_id target object's id
  * @return object's location's id or NO_ID if something went wrong
  */
Id game_get_object_location(Game *game, Id obj_id);

/**
  * @brief Gets the last command input 
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  *
  * @param game a pointer to game
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
T_Command game_get_last_command(Game *game);

/**
 * @brief Function that gets the enemy id based on the position it is located in the enemy array located in the game structure
 * @author Nicolas Victorino
 * 
 * @param game  pointer to game @param num number of the enemy position in the array 
 * @return The id of the enemy, or in case it doesn't have one, NO_ID
 */
Id game_get_enemy_id(Game *game, int num);

/**
 * @brief Function that gets the player id 
 * @author Nicolas Victorino
 * 
 * @param game  pointer to game  
 * @return The id of the player, or in case it doesn't have one, NO_ID
 */
Id game_get_player_id(Game* game);

/**
 * @brief Function that gets the object id based on the position it is located in the object array located in the game structure
 * @author Nicolas Victorino
 * 
 * @param game  pointer to game @param num number of the object position in the array 
 * @return The id of the enemy, or in case it doesn't have one, NO_ID
 */
Id game_get_object_id(Game *game, int num);

/**
 * @brief Function that saves memory for the game in game_loop
 * @author Nicolas Victorino
 * 
 * @return A pointer to the game
 */
Game* game_alloc2();

/**
 * @brief It get if link is open or close giving an space and a specific direction
 * @author Miguel Soto
 * 
 * @param game pointer to game
 * @param act_spaceid id from space (normaly it would be actual player location)
 * @param dir link's direction
 * @return OPEN if link is open or CLOSE if link is close. In case of error, returns CLOSE 
 */
LINK_STATUS game_get_connection_status(Game *game, Id act_spaceid, DIRECTION dir);

/**
 * @brief It get id from the space destination of a link
 * @author Miguel Soto
 * 
 * @param game pointer to game
 * @param act_spaceid id from space (normaly it would be actual player location)
 * @param dir link's direction
 * @return Id from the space destination of a link
 */
Id game_get_connection(Game *game, Id act_spaceid, DIRECTION dir);


/**
 * @brief Adds spaces to the game.
 * @author Miguel Soto
 *
 * It adds one space (space) to game's struct.
 * @param game pointer to game.
 * @param space pointer to the target space.
 * @return OK if everything worked correctly and ERROR if there was any mistake.
 */
STATUS game_add_space(Game *game, Space *space);

/**
 * @brief Adds objects to the game
 * @author Miguel Soto
 *
 * @param game pointer to game
 * @param obj pointer to target object
 * @return OK if everything worked correctly and ERROR if there was any mistake
 */
STATUS game_add_object(Game *game, Object *obj);

/**
 * @brief Adds game's players.
 * @author Miguel Soto
 *
 * It adds a player to game struct.
 * @param game pointer to game.
 * @param p pointer to player to be added in game.
 * @return OK if everything worked correctly and ERROR if there was any mistake.
 */
STATUS game_add_player(Game *game, Player *p);

/**
 * @brief Adds all game's enemies
 * @author Miguel Soto
 *
 * @param game pointer to game
 * @param e pointer to enemy to be added in game
 * @return OK if everything worked correctly and ERROR if there was any mistake
 */
STATUS game_add_enemy(Game *game, Enemy *e);

/**
 * @brief Adds all game's links
 * @author Miguel Soto
 *
 * @param game pointer to game
 * @param l pointer to target link
 * @return OK if everything worked correctly and ERROR if there was any mistake
 */
STATUS game_add_link(Game *game, Link *l);

/**
 * @brief Checks if the spaces are within the appropiate range
 * @author Profesores PProg
 *
 * game_get_space_id_at Checks if the spaces are within the appropiate range, output will be No_ID
 * whenever it is located outside this range or its id if it belongs to the game
 * @param game pointer to game
 * @param position integer that marks the position of the space to check
 * @return space_get_id(game->spaces[position]) output will be No_ID
 * whenever it is located outside this range or its id if it belongs to the game.
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief Sets the player's location to target id
 * @author Miguel Soto
 *
 * @param game pointer to game
 * @param player_id player id that location must be change
 * @param space_id space id where the player would be located
 * @return OK if everything worked correctly or ERROR if there was any mistake
 */
STATUS game_set_player_location(Game *game, Id player_id, Id space_id);

/**
 * @brief Sets the object's location to target id
 * @author Miguel Soto
 *
 * @param game pointer to game
 * @param obj_id object id that changes lcoation
 * @param space_id space id where the object would be located
 * @return OK if everything worked correctly or ERROR if there was any mistake
 */
STATUS game_set_object_location(Game *game, Id obj_id, Id space_id);

/**
 * @brief Sets the enemy's location to target id
 * @author Antonio Van-Oers
 *
 * @param game pointer to game
 * @param enemy_id enemy id that would change lcoation
 * @param space_id space id where the enemy would be located
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_set_enemy_location(Game *game, Id enemy_id, Id space_id);

/**
 * @brief Saves the information of the actual game in the save file
 * @author Nicolas Victorino
 *
 * @param game pointer to the game we want to save
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_save(char *filename, Game* game);

/**
 * @brief Returns a pointer to the structure dialogue
 * 
 * @param game Pointer to game
 * @return NULL in case of error
 */
Dialogue *game_get_dialogue(Game *game);

/** @brief Function that gets the enemy based on whether it is in the same player's location
 * @author Antonio Van-Oers 
 * 
 * @param game  pointer to game 
 * @param player_loc id of the player's location 
 * @return The enemy, or in case there is no enemy with the player, NULL
 */
Enemy *game_get_enemyWithPlayer(Game *game, Id player_loc); 

/**
 * @brief Checks if space is dark and player has a turnedon object, and then changes the light status of the space
 * @author Nicolas Victorino
 * 
 * @param game Pointer to the game
 * @return ERROR if something went wrong 
 */
STATUS game_update_ls(Game *game);

/**
 * @brief Checks if it is night time and sets all the rooms to dark
 * @author Nicolas Victorino
 * 
 * @param game pointer to game
 * @return ERROR if something went wrong
 */
STATUS game_update_time(Game *game);

/**
 * @brief Checks whether an object should be dropped on a space or not depending on the enemies health
 * @author Nicolas Victorino
 * 
 * @param game Pointer to game
 * @return ERROR if something went wrong 
 */
STATUS game_update_object(Game *game);

/**
 * @brief Checks whether an enemy has 0 health and then changes its location to -1
 * @author Nicolas Victorino
 * 
 * @param game pointer to game
 * @return ERROR if something went wrong
 */
STATUS game_update_enemy(Game *game);

/**
 * @brief Frees all the memory allocated in the game structure
 * @author Nicolas Victorino
 * 
 * @param game pointer to the game 
 * @return ERROR if something went wrong 
 */
STATUS game_destroy_load(Game *game);


/**
 * @brief Gets the enemy that is in space location
 * 
 * @param game pointer to game
 * @param space space id
 * @return pointer to enemy in that sapce. NULL in case of error.
 */
Enemy *game_get_enemy_in_space(Game *game, Id space);

/**
 * @brief Function to check if player is alive
 * @author Nicolas Victorino
 * 
 * @param game pointer to game
 * @return TRUE if player is dead 
 */
BOOL update_game_over(Game *game);

#endif
