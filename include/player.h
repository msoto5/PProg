/** 
 * @brief Implements the player's interface
 * 
 * @file player.h
 * @author Antonio Van-Oers, Nicolas Victorino, Ignacio Nunez and Miguel Soto
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "object.h"
#include "inventory.h"

#define PLAYER_NAME_LEN 60   /*!< Establish player's name length */
#define PLAYER_GDESC_Y 3 /*!< Establish the maximun number of litednes player's graphic description (gdesc) will have  */
#define PLAYER_GDESC_X 4 /*!< Establish the maximun number of characters each line of player's graphic description (gdesc) will have */

typedef struct _Player Player; /*!< It defines the player structure, it can move, attack or take and drop objects */

/**
 * @brief Creates a new player.
 * @author Antonio Van-Oers 
 *
 * player_create player_create allocates memory for a new player
 * and initializes all its members
 * @param id is the target player's id
 * @return a new, initialized player, or NULL if anything goes wrong.
 */
Player *player_create(Id id);

/**
 * @brief Frees all of a player's allocated memory
 * @author Antonio Van-Oers 
 * 
 * player_destroy frees all previously allocated
 * memory for a player
 * @param player a pointer to target player
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_destroy(Player *player);

/**
 * @brief Gets a player's id
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @return player's id if everything goes well, or NULL if anything goes wrong.
 */
Id player_get_id(Player *player);

/**
 * @brief Tests whether an id is from a player or not
 * @author Miguel Soto
 * 
 *@param id is the target id
 * @return OK, if everything goes well, or ERROR if anything goes wrong.
 */
STATUS player_test_id(Id id);

/**
 * @brief Gets a player's name
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @return a string with the plyer's name, or NULL if anything goes wrong.
 */
const char *player_get_name(Player *player);

/**
 * @brief Gets a player's location
 * @author Antonio Van-Oers
 * 
 * player_get_location obtiene la localizacion de un jugador (player).
 * @param player a pointer to target player
 * @return player->location, player's location id or NO_ID if anything goes wrong
 */
Id player_get_location(Player *player);

/**
 * @brief Gets a player's array of objects
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @return player->inventory, an inventory type variable from the 
 * player or NULL if anything goes wrong.
 */
Inventory *player_get_inventory(Player *player);

/**
 * @brief Gets a player's health.
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @return player->health, the remainig health on the 
 * target player or -1 if anything goes wrong.
 */
int player_get_health(Player *player);

/**
 * @brief Sets a player's health to the assigned value.
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @param health indicates the amount of health to be given to the player
 * @return OK if everything goes well or ERROR if anything goes wrong.
 */
STATUS player_set_health(Player *player, int health);

/**
 * @brief Assigns an object to a player
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @param object the object about to be added to the player's belongings
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_add_object(Player *player, Object *object);

/**
 * @brief Removes an object from a player's inventory
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @param id_obj id to the object about to be removed from the player's belongings
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_del_object(Player *player, Id id_obj);


/**
 * @brief Assigns the maximum number of objects available in the inventory
 * @author Nicolas Victorino
 * 
 * @param player a pointer to target player
 * @param num new maximum number of objects the player can have
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_set_max_inventory(Player* player, int num);
/**
 * @brief Sets a player's location
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @param location is the space's id on which the player is located
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_set_location(Player *player, Id location);

/**
 * @brief Sets the player's new name
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @param name a string with the new name for the player
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_set_name(Player *player, char *name);

/**
 * @brief If a player has an object or not
 * @author Ignacio Nunnez
 * 
 * @param player a pointer to target player
 * @param obj_id id of the object to find
 * @return TRUE if player has it, FALSE if not or there was a mistake
 */
BOOL player_has_object(Player *player, Id obj_id);

/**
 * @brief Prints all player related info in a string
 * @author Antonio Van-Oers
 * 
 * @param player a pointer to target player
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_print(Player *player);

/**
 * @brief Prints all player related information in the save file
 * @author Nicolas Victorino
 * 
 * @param player a pointer to target player
 * @return OK, if the task was successfully completed or ERROR, if anything goes wrong.
 */
STATUS player_print_save(char *filename, Player *player);

/**
 * @brief 
 * 
 * @author Nicolas Victorino
 * @param player Given player
 * @param health New max health
 * @return ERROR if something went wrong 
 */
STATUS player_set_max_health(Player *player, int health);

/**
 * @brief Gets players max health
 * 
 * @author Nicolas Victorino
 * @param player Given player
 * @return -1 if error
 */
int player_get_max_health(Player *player);

/**
 * @brief Gets the crit_damage of a player
 * @author Antonio Van-Oers Luis
 *  
 * @param player a pointer to target player
 * @return the crit chance that an object gives
 */
int player_get_crit(Player *player);

/**
 * @brief Sets the crit_damage of a player
 * @author Antonio Van-Oers Luis
 *  
 * @param player a pointer to target player
 * @param crit chance in a scale from 0 to 10 
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS player_set_crit(Player *player, int crit);

/**
 * @brief Gets the crit_damage of a player
 * @author Antonio Van-Oers Luis
 *  
 * @param player a pointer to target player
 * @return the crit chance that an object gives
 */
int player_get_baseDmg(Player *player);

/**
 * @brief Sets the crit_damage of a player
 * @author Antonio Van-Oers Luis
 *  
 * @param player a pointer to target player
 * @param crit chance in a scale from 0 to 10 
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS player_set_baseDmg(Player *player, int base_dmg);

/**
 * @brief It alloc memory for the player_gdesc
 * @author Miguel Soto
 *
 * @return double pointer to char to the newgdesc or NULL if there has been an error
 */
char **player_create_gdesc();

/**
 * @brief It frees memory for the player_gdesc
 * @author Miguel Soto
 *
 * @param gdesc pointer to the array of pointers to the gdesc field
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_destroy_gdesc(char **gdesc);

/**
 * @brief It sets the graphic description of a player
 * @author Miguel Soto
 *
 * @param s a pointer to player
 * @param newgdesc a double char array with the graphical description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_set_gdesc(Player *p, char **newgdesc);

/**
 * @brief It gets the graphic description from a player
 * @author Miguel Soto
 *
 * @param s a pointer to player
 * @return a double char array with the graphical description, or NULL if there was some error.
 */
char **player_get_gdesc(Player *p);

#endif
