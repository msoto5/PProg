/**
 * @file link.h
 * @author Miguel Soto, Antonio Van-Oers, Nicolas Victorino and Ignacio Nunez
 * @brief It defines the link functions between spaces
 * @version 3.0
 * @date 04-04-2022
 * 
 * @copyright Copyright (c) 2022
 */


#ifndef LINK_H 
#define LINK_H

#include "types.h"

#define LINK_NAME_LEN 40    /*!< Establish link's name length*/

/**
 * @brief Link status enum. A link can be either close or open.
 */
typedef enum
{
    CLOSE = 0,  /*!< Link status is close */
    OPEN_L = 1    /*!< Link status is open */
} LINK_STATUS;

typedef struct _Link Link; /*!< It defines the link structure that determines whether you can go from an space to another or not */

/**
 * @brief It allocs memory for a new link struct and initialize its members.
 * @author Miguel Soto
 * 
 * link_create allocs memory for a new link struct and initialize its members:
 * - direction = ND
 * - status = CLOSE
 * 
 * @param id The id of the new link.
 * @return a pointer to link, or NULL if there was some error.
 */
Link *link_create(Id id);

/**
 * @brief It frees the memory of a link's struct.
 * @author Miguel Soto
 * 
 * @param link a pointer to target link.a pointer to link that must be destroy
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
STATUS link_destroy(Link * link);

/**
 * @brief It gets link's id.
 * @author Miguel Soto
 * 
 *@param link a pointer to target link.a pointer to target link.
 * @return link's id or NO_ID if there was some error.
 */
Id link_get_id(Link *link);

/**
 * @brief It sets a name to a link.
 * @author Miguel Soto
 * 
 *@param link a pointer to target link.a pointer to target link.
 * @param name string with link's new name.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
STATUS link_set_name(Link *link, char *name);

/**
 * @brief It gets link's name.
 * @author Miguel Soto
 * 
 *@param link a pointer to target link.a pointer to target link.
 * @return string with link's name or NULL if there was some error.
 */
char *link_get_name(Link *link);

/**
 * @brief Sets the start of target link
 * @author Nicolas Victorino
 * 
 * @param link a pointer to target link.
 * @param id_space_start space's id from which the link
 * is coming from 
 * @return STATUS OK, if everything goes well or ERROR if there was some mistake.
 */
STATUS link_set_start(Link *link, Id id_space_start);

/**
 * @brief Gets a link's start
 * @author Nicolas Victorino
 * 
 * @param link a pointer to target link.
 * @return Id 
 */
Id link_get_start(Link *link);

/**
 * @brief Sets the destination of target link
 * @author Antonio Van-Oers
 * 
 * @param link a pointer to target link.
 * @param id_space_dest space's id to which the link
 * is heading to 
 * @return STATUS OK, if everything goes well or ERROR if there was some mistake.
 */
STATUS link_set_destination(Link *link, Id id_space_dest);

/**
 * @brief Gets a link's destination
 * @author Antonio Van-Oers
 * 
 * @param link a pointer to target link.
 * @return Id 
 */
Id link_get_destination(Link *link);

/**
 * @brief Sets the direction of target link
 * @author Antonio Van-Oers
 * 
 * @param link a pointer to target link.
 * @param dir new link's direction
 * @return STATUS OK, if everything goes well or ERROR if there was some mistake.
 */
STATUS link_set_direction(Link *link, DIRECTION dir);

/**
 * @brief Gets a link's direction
 * @author Antonio Van-Oers
 * 
 * @param link a pointer to target link.
 * @return link's direction 
 */
DIRECTION link_get_direction(Link *link);

/**
 * @brief Sets the status of target link
 * @author Antonio Van-Oers
 * 
 * @param link a pointer to target link.
 * @param st new link's status
 * @return STATUS OK, if everything goes well or ERROR if there was some mistake. 
 */
STATUS link_set_status(Link *link, LINK_STATUS st);

/**
 * @brief Gets a link's status
 * @author Antonio Van-Oers
 * 
 * @param link a pointer to target link.
 * @return LINK_STATUS link->status if everything goes well and CLOSE if something doesn't 
 */
LINK_STATUS link_get_status(Link *link);

/**
 * @brief It prints link and its elements for debugging porpuses.
 * @author MIguel Soto
 * 
 * @param link a ponter to link struct
 * @return the number of characters written or -1 in caseof error.
 */
int link_print(Link *link);

/**
 * @brief It prints link and its elements in the save file
 * @author Nicolas Victorino
 * 
 * @param link a ponter to link struct we want to save
 * @return STATUS OK, if everything goes well or ERROR if there was some mistake. 
 */
STATUS link_print_save(char *filename, Link *link);

#endif
