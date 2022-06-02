
/**
* @brief It implements enemy module in the ant game
*
* @file inventory.c
* @author Ignacio Nunnez, Antonio Van-Oers, Nicolas Victorino and Miguel Soto
* @version 3.0
* @date 19-03-2022
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/inventory.h"

/**
 * @brief Inventory
 *
 * This struct stores all the 
 * informaction of an inventory.
 */
struct _Inventory {
  Set* objects;	/*!< Set of objects included in invetory */
  int max_objs; /*!< Defines the maximun objects of the inventory */
};

/** inventory_create allocates memory for a new inventory
  *  and initializes its members
  */
Inventory* inventory_create() {
  Inventory *newInventory = NULL;

  newInventory = (Inventory *) malloc(sizeof (Inventory));
  if (newInventory == NULL) {
    return NULL;
  }

  /* Initialization of an empty inventory*/
  newInventory->objects = set_create();
  newInventory->max_objs = 0;

  return newInventory;
}

/** inventory_destroy frees the previous memory allocation 
  *  for an inventory
  */
STATUS inventory_destroy(Inventory* inventory) {
  
  /* Error control */
  if (!inventory) {
    return ERROR;
  }

	set_destroy(inventory->objects);
	free(inventory);

  return OK;
}

/** It gets the set of objects
 *  of an inventory
  */
Set *inventory_get_objects(Inventory* inventory) {
  
  /* Error control */
  if (!inventory) {
    return NULL;
  }

  return inventory->objects;
}

/** It sets the objects of an player
  */
STATUS inventory_set_objects(Inventory* inventory, Set* set) {

	/*ERROR CONTROL*/
	if(!inventory || !set){
		return ERROR;
	}

  set_destroy(inventory->objects);

	inventory->objects = set;
	return OK;
}

/** Sets the maximum number of objects an inventory can store
 */
STATUS inventory_set_maxObjs(Inventory* inventory, int num)
{
  if (!inventory || num <= 0)
  {
    return ERROR;
  }

  inventory->max_objs = num;
  return OK;
}

/** Gets the maximum number of objects an inventory can store
 */
int inventory_get_maxObjs(Inventory *inventory)
{
  if (!inventory)
  {
    return NO_ID;
  }

  return inventory->max_objs;
}

/* It adds an object to the inventory if possible
	*/
STATUS inventory_add_object(Inventory* inventory, Id object) {

	/*CONTROL ERROR*/
	if(!inventory || !object){
		return ERROR;
	}

	if(set_get_nids(inventory->objects) >= inventory->max_objs){
		return ERROR;
	}

	set_add(inventory->objects, object);

	return OK;
	
}

/* It tells if an inventory has an id or not
*/
BOOL inventory_has_id(Inventory* inventory, Id object){
  
  /*CONTROL ERROR*/
  if(!inventory || object == NO_ID){
    return FALSE;
  }

  if(set_idInSet(inventory->objects, object) == TRUE)
  return TRUE;

  return FALSE;
}

/* It removes an object of the inventory
	*/
STATUS inventory_remove_object(Inventory* inventory, Id object) {

	/*CONTROL ERROR*/
	if(!inventory || !object){
		return ERROR;
	}

	if(set_del_id(inventory->objects, object) == OK){
		return OK;
	}

	return ERROR;
	
}

/** It prints the enemy information
  */
STATUS inventory_print(Inventory* inventory) {

  /* Error Control */
  if (!inventory) {
    return ERROR;
  }

  /* 1. Prints the Set of the inventory*/
	fprintf(stdout, "Set of objects:\n");
  set_print(inventory->objects);

  return OK;
}

/** It prints the enemy information in the save file
  */
STATUS inventory_print_save(char *filename, Inventory* inventory, Id player) {
  
  int i = 0;
  Id id = NO_ID;
  FILE *file = NULL;

  file = fopen(filename, "a");

 /* Error control */
  if (!inventory || !file)
  {
    return ERROR;
  }

  for (i = 0; i < set_get_nids(inventory->objects); i++) {
    id = set_get_ids_by_number(inventory->objects, i);

    if (id != NO_ID)
    {
      fprintf(file, "#i:%ld|%ld|\n", id, player);
    } else {
      break;
    }
  }

  fclose(file);
  return OK;
}
