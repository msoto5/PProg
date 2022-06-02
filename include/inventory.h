/**
* @brief It defines inventory module
*
* @file inventory.h
* @author Ignacio Nunnez
* @version 1.2
* @date 19/03/2022
* @copyright Free use
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"
#include "object.h"

typedef struct _Inventory Inventory; /*!< It defines the inventory structure, used by the player to store the items */

/**
  * @brief It creates a new inventory
  * @author Ignacio Nunnez
  *
  * inventory_create allocates memory for a new inventory
  *  and initializes its members
  * @return a new inventory, initialized
  */
Inventory* inventory_create();

/**
  * @brief It destroys an inventory
  * @author Ignacio Nunnez
  *
  * inventory_destroy frees the previous memory allocation 
  * for an inventory
  * @param inventory a pointer to the inventory that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_destroy(Inventory* inventory);

/**
  * @brief It gets the set of an inventory
  * @author Ignacio Nunnez
  * 
  * @param inventory a pointer to the inventory  
  * @return the set of objects of the inventory
  */
Set *inventory_get_objects(Inventory* inventory);

/**
  * @brief It sets the objects of an inventory
  * @author Ignacio Nunnez
  * 
  * @param inventory a pointer to the inventory
  * @param set a pointer to the set for the inventory
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS inventory_set_objects(Inventory* inventory, Set* set);

/**
  * @brief It sets the maximum number of objects an inventory can store
  * @author Nicolas Victorino
  * 
  * @param inventory a pointer to the inventory
  * @param num number that is going to be the new maximum
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS inventory_set_maxObjs(Inventory* inventory, int num);

/**
  * @brief It gets the maximum number of objects an inventory can store
  * @author Nicolas Victorino
  * 
  * @param inventory a pointer to the inventory
  * @return -1 if something went wrong, or the number of objects it can store
  */
int inventory_get_maxObjs(Inventory *inventory);

/**
  * @brief It adds an objects to the inventory
  * @author Ignacio Nunnez
  * 
  * @param inventory a pointer to the inventory
  * @param object the id of a the new object
  * @return OK, if everything goes well or ERROR if there was some mistake
  * it can return ERROR if the inventory is full
  */
STATUS inventory_add_object(Inventory* inventory, Id object);

/**
  * @brief It removes an objects of the inventory
  * @author Ignacio Nunnez
  * 
  * @param inventory a pointer to the inventory
  * @param object the id of a the object
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_remove_object(Inventory* inventory, Id object);

/**
  * @brief It tells if an inventory has an object
  * @author Ignacio Nunnez
  * 
  * @param inventory a pointer to the inventory
  * @param object the id of a the object
  * @return TRUE, if the inventory has it or FALSE if not
  */
BOOL inventory_has_id(Inventory* inventory, Id object);

/**
  * @brief It prints the inventory information
  * @author Ignacio Nunnez
  *
  * This fucntion shows the id, name, location and health of the enemy.
  * @param inventory a pointer to the inventory
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_print(Inventory* inventory);

/**
  * @brief It prints the inventory information in the save file
  * @author Nicolas Victorino
  *
  * @param inventory a pointer to the inventory we want to print
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS inventory_print_save(char *filename, Inventory* inventory, Id player);

#endif
