/** 
 * @brief It implements the set interface.
 * 
 * @file set.h
 * @author Miguel Soto, Nicolas Victorino, Ignacio Nunez and Antonio Van-Oers.
 * @version 3.0
 * @date 04-04-2022 
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"

typedef struct _Set Set;  /*!< It defines the set structure, making it easier to manage any kind of data sets */

/**
 * @brief Allocates memory for a new set
 * @author Miguel Soto
 * 
 * set_create Allocates memory for a new set and 
 * has all its members initialized
 *  
 * @return a pointer to an initialized set or NULL if anything went wrong
 */
Set *set_create();

/**
 * @brief Frees the previously allocated memory for a set
 * @author Miguel Soto
 * 
 * set_destroy Frees the previously allocated memory for a set and all 
 * of its members
 * 
 * @param s a pointer to target set
 * @return OK if everything goes well, or ERROR if anything doesn't.
 */
STATUS set_destroy(Set *s);

/**
 * @brief It adds a new id to a set
 * @author Miguel Soto
 * 
 *set_add increases the number of ids in the set 
 * and stores the newest in the last position
 * 
 * @param s a pointer to target set
 * @param id target id to be assigned to a set
 * @return OK if everything goes well, or ERROR if anything doesn't.
 */
STATUS set_add(Set *s, Id id);

/**
 * @brief Removes a certain id from the set
 * @author Miguel Soto
 * 
 * set_del_id searches for the indicated id on a set
 * and has it removed
 * 
 * @param s a pointer to target set
 * @param id target id to be removed from a set
 * @return OK if everything goes well, or ERROR if anything doesn't.
 */
STATUS set_del_id(Set *s, Id id);

/**
 * @brief Removes an id from the set, position wise
 * @author Miguel Soto
 * 
 * set_del_pos Removes an id from the set by a position based search
 * 
 * @param s a pointer to target set
 * @param pos the position of the target id to be removed
 * @return OK if everything goes well, or ERROR if anything doesn't. 
 */
STATUS set_del_pos(Set *s, int pos);

/**
 * @brief Gets the amount of ids in a set
 * @author Miguel Soto
 * 
 * @param s a pointer to target set
 * @return int with the amount of ids in a set. 
 * -1 if anything goes wrong.
 */
int set_get_nids(Set *s);

/**
 * @brief gets the array containing all ids from a set
 * @author Miguel Soto
 * 
 * @param s a pointer to target set
 * @return a pointer to the array containing all ids from a set
 */
Id *set_get_ids(Set *s);

/**
  * @brief Finds if a id is in a set or not
  * @author Nicolas Victorino
  *
  * @param set a pointer to the given set
  * @param id the id we want to find
  * @return TRUE if the set contains the id, FALSE in opposite case
  */
BOOL set_idInSet (Set* set, Id id);

/**
 * @brief Tests whether the set is well defined or not
 * @author Miguel Soto
 * 
 * Tests made:
 * - s is not NULL
 * - That there is no id == NO_ID
 * - correct amount of ids
 * - That the id_num > 0
 * 
 * @param s a pointer to target set
 * @return OK if everything goes well, or ERROR if anything doesn't. 
 */
STATUS set_test(Set *s);

/**
 * @brief Prints all info regarding set
 * 
 * @param s a pointer to target set
 * @return number of printed characters
 */
int set_print(Set *s);

/**
 * @brief Gets an object id determined by a given number
 * 
 * @author Nicolas Victorino
 * 
 * @param set a pointer to target set 
 * @param n the number that determines the id that is returned
 * @return id of the object
 */
Id set_get_ids_by_number(Set* set, int n);

#endif
