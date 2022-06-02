/** 
 * @brief It implements the enemy interface.
 * 
 * @file enemy.h
 * @author Antonio Van-Oers, Ignacio Nunez, Nicolas VIctorino and Miguel Soto
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

#define ENEMY_LEN_NAME 60  /*!< Enemy's name length */
#define ENEMY_GDESC_Y 3 /*!< Establish the maximun number of litednes ENEMY's graphic description (gdesc) will have  */
#define ENEMY_GDESC_X 6 /*!< Establish the maximun number of characters each line of ENEMY's graphic description (gdesc) will have */

/**
 * @brief Enemy
 *
 * This structure stores all info that each enemy has
 */
typedef struct _Enemy Enemy;


/**
 * @brief Creates a new enemy.
 * @author Antonio Van-Oers 
 *
 * enemy_create allocates memory for a new enemy and initializes all its members .
 * @param id new enemy's identification number.
 * @return a new enemy, initialized, or NULL in case of error.
 */
Enemy *enemy_create(Id id);

/**
 * @brief It destroys an enemy
 * @author Antonio Van-Oers 
 * 
 * enemy_destroy frees the previous memory allocation for an enemy
 * @param enemy a pointer to the enemy that must be destroyed.
 * @return OK, if everything goes well o ERROR, if there was some mistake.
 */
STATUS enemy_destroy(Enemy *enemy);

/**
 * @brief It gets an enemy's id
 * @author Antonio Van-Oers
 * 
 * @param enemy a pointer to a certain enemy
 * @return enemy id, or NULL if there was some mistake.
 */
Id enemy_get_id(Enemy *enemy);

/**
 * @brief Tests whether the id is from an enemy or not
 * @author Miguel Soto
 * 
 * @param id to be tested
 * @return OK, if it is indeed from an enemy, ERROR if it is not or anything goes wrong. 
 */
STATUS enemy_test_id(Id id);

/**
 * @brief It gets an enemy's name
 * @author Antonio Van-Oers
 * 
 * @param enemy a pointer to a certain enemy.
 
 * @return a string with the enemy's name, or NULL if anything goes wrong.
 */
const char *enemy_get_name(Enemy *enemy);

/**
 * @brief It gets an enemy's location
 * @author Antonio Van-Oers
 * 
 * @param enemy a pointer to a certain enemy
 * @return enemy->location, enemy's location id or NO_ID if anything goes wrong.
 */
Id enemy_get_location(Enemy *enemy);

/**
 * @brief It gets an enemy's health
 * @author Antonio Van-Oers
 * 
 * @param enemy a pointer to a certain enemy
 * @return enemy->health, enemy's remaining health
 * and -1 if anything goes wrong.
 */
int enemy_get_health(Enemy *enemy);

/**
 * @brief It sets an enemy's health
 * @author Antonio Van-Oers
 * 
 * enemy_set_health sets an enemy's helath to the value indicated.
 * @param enemy a pointer to a certain enemy.
 * @param health an integer with the amount of health.
 * return OK, if everything goes well o ERROR, if there was some mistake.
 */
STATUS enemy_set_health(Enemy *enemy, int health);

/**
 * @brief It sets an enemy's location.
 * @author Antonio Van-Oers
 * 
 * @param enemy a pointer to a certain enemy
 * @param location is an enemy's location id.
 *return OK, if everything goes well o ERROR, if there was some mistake.
 */
STATUS enemy_set_location(Enemy *enemy, Id location);

/**
 * @brief It sets an enemy's name
 * @author Antonio Van-Oers
 * 
 * @param enemy a pointer to a certain enemy
 * @param name un string with the name for the enemy
 * return OK, if everything goes well o ERROR, if there was some mistake.
 */
STATUS enemy_set_name(Enemy *enemy, char *name);

/**
 * @brief Prints the info on the enemy's interface
 * @author Antonio Van-Oers
 * 
 * @param enemy a pointer to a certain enemy
 * @return OK, if everything goes well o ERROR, if there was some mistake.
 */
STATUS enemy_print(Enemy *enemy);

/** 
 * @brief enemy_print  Prints the info on the enemy's interface in the save file
 * @author Nicolas Victorino
 * 
 * @param a pointer to the enemy we want to print
 * @return OK, if everything goes well o ERROR, if there was some mistake.
 */
STATUS enemy_print_save(char *filename, Enemy *enemy);

/**
 * @brief Gets the crit_damage of a Enemy
 * @author Antonio Van-Oers Luis
 *  
 * @param enemy a pointer to target Enemy
 * @return the crit chance that an object gives
 */
int enemy_get_crit(Enemy *enemy);

/**
 * @brief Sets the crit_damage of a Enemy
 * @author Antonio Van-Oers Luis
 *  
 * @param enemy a pointer to target Enemy
 * @param crit chance in a scale from 0 to 10 
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS enemy_set_crit(Enemy *enemy, int crit);

/**
 * @brief Gets the crit_damage of a Enemy
 * @author Antonio Van-Oers Luis
 *  
 * @param enemy a pointer to target Enemy
 * @return the crit chance that an object gives
 */
int enemy_get_baseDmg(Enemy *enemy);

/**
 * @brief Sets the crit_damage of a Enemy
 * @author Antonio Van-Oers Luis
 *  
 * @param enemy a pointer to target Enemy
 * @param crit chance in a scale from 0 to 10 
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS enemy_set_baseDmg(Enemy *enemy, int base_dmg); 

/**
 * @brief It alloc memory for the enemy_gdesc
 * @author Miguel Soto
 *
 * @return double pointer to char to the newgdesc or NULL if there has been an error
 */
char **enemy_create_gdesc();

/**
 * @brief It frees memory for the enemy_gdesc
 * @author Miguel Soto
 *
 * @param gdesc pointer to the array of pointers to the gdesc field
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_destroy_gdesc(char **gdesc);

/**
 * @brief It sets the graphic description of a enemy
 * @author Miguel Soto
 *
 * @param s a pointer to enemy
 * @param newgdesc a double char array with the graphical description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_set_gdesc(Enemy *s, char **newgdesc);

/**
 * @brief It gets the graphic description from a enemy
 * @author Miguel Soto
 *
 * @param s a pointer to enemy
 * @return a double char array with the graphical description, or NULL if there was some error.
 */
char **enemy_get_gdesc(Enemy *s);

#endif
