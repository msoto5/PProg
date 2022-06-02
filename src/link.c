/**
 * @file link.c
 * @author Miguel Soto, Antonio Van-Oers, Nicolas VIctorino and Nacho
 * @brief It implements the link between spaces
 * @version 0.1
 * @date 2022-03-17
 *
 * @copyright Copyright (c) 2022
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/link.h"

/**
 * @brief Link
 * 
 * This struct stores all the information of a link between spaces.
 */
struct _Link
{
    Id id;                    /*!< Link's id */
    char name[LINK_NAME_LEN]; /*!< Link's name */
    Id start;   /*!< Id from the space where link starts*/
    Id destination;      /*!< Id to space destination */
    DIRECTION direction; /*!< Defines link's direction */
    LINK_STATUS status;  /*!< Wether link is OPEN or CLOSE */
};

/**
 * It allocs memory for a new link struct and initialize its members.
 */
Link *link_create(Id id)
{
    Link *l = NULL;
    int i;

    /* Error control */
    if (id == NO_ID)
    {
        return NULL;
    }

    /* Alloc memory for Link struct */
    l = (Link *)malloc(sizeof(Link));
    if (!l) /* Error control in malloc */
    {
        return NULL;
    }

    /* Initializing link's elements */
    l->id = id;
    for (i = 0; i < LINK_NAME_LEN; i++)
    {
        l->name[i] = '\0';
    }
    l->destination = NO_ID;
    l->direction = ND;
    l->status = CLOSE;

    /* Return initialize link */
    return l;
}

/**
 * It frees the memory of a link's struct.
 */
STATUS link_destroy(Link *link)
{
    /* Error control */
    if (!link)
    {
        return ERROR;
    }

    /* Free pointer to link */
    free(link);
    link = NULL;

    return OK;
}

/**
 * It gets link's id.
 */
Id link_get_id(Link *link)
{
    /* Error control */
    if (!link)
    {
        return NO_ID;
    }

    return link->id;
}

/**
 * It sets a name to a link.
 */
STATUS link_set_name(Link *link, char *name)
{
    /* Error control */
    if (!link || !name)
    {
        return ERROR;
    }

    if (strlen(name) >= LINK_NAME_LEN)
    {
        strncpy(link->name, name, LINK_NAME_LEN);
    }
    else
    {
        strcpy(link->name, name);
    }

    return OK;
}

/**
 * It gets link's name.
 */
char *link_get_name(Link *link)
{
    /* Error control */
    if (!link)
    {
        return NULL;
    }

    return link->name;
}

/** Sets the start of target link
 */
STATUS link_set_start(Link *link, Id id_space_start)
{
    /* Error control */
    if (!link || id_space_start < 0)
    {
        return ERROR;
    }

    link->start = id_space_start;
    return OK;
}

/** Gets a link's start
 */
Id link_get_start(Link *link)
{
    /* Error control */
    if (!link)
    {
        return NO_ID;
    }

    return link->start;
}

/** Sets the destination of target link
 */
STATUS link_set_destination(Link *link, Id id_space_dest)
{
    /* Error control */
    if (!link || id_space_dest < 0)
    {
        return ERROR;
    }

    link->destination = id_space_dest;
    return OK;
}

/** Gets a link's destination
 */
Id link_get_destination(Link *link)
{
    /* Error control */
    if (!link)
    {
        return NO_ID;
    }

    return link->destination;
}

/** Sets the direction of target link
 */
STATUS link_set_direction(Link *link, DIRECTION dir)
{

    /* Error control */
    if (!link || dir == ND)
    {
        return ERROR;
    }

    link->direction = dir;
    return OK;
}

/** Gets a link's direction
 */
DIRECTION link_get_direction(Link *link)
{
    /* Error control */
    if (!link)
    {
        return ND;
    }

    return link->direction;
}

/** Sets the status of target link
 */
STATUS link_set_status(Link *link, LINK_STATUS st)
{
    if (!link || (st != CLOSE && st != OPEN_L))
    {
        return ERROR;
    }

    link->status = st;
    return OK;
}

/** Gets a link's status
 */
LINK_STATUS link_get_status(Link *link)
{

    if (!link)
    {
        return CLOSE;
    }

    return link->status;
}

/**
 * It prints link and its elements for debugging porpuses.
 */
int link_print(Link *link)
{
    int n = 0;

    /* Error Control */
    if (!link)
    {
        return -1;
    }

    /* Printing in terminal link info */
    n = fprintf(stdout, "=> Link (Id: %ld):\n", link->id);
    n += fprintf(stdout, "- Name: %s\n", link->name);
    n += fprintf(stdout, "- Origen: %ld\n", link->start);
    n += fprintf(stdout, "- Destination: %ld\n", link->destination);

    /* Printing in terminal link's direction */
    n += fprintf(stdout, "- Direction: ");
    if (link->direction == N)
    {
        n += fprintf(stdout, "NORTH (N)\n");
    }
    else if (link->direction == E)
    {
        n += fprintf(stdout, "EAST (E)\n");
    }
    else if (link->direction == S)
    {
        n += fprintf(stdout, "SOUTH (S)\n");
    }
    else if (link->direction == W)
    {
        n += fprintf(stdout, "WEST (W)\n");
    }
    else if (link->direction == U)
    {
        n += fprintf(stdout, "UP (U)\n");
    }
    else if (link->direction == D)
    {
        n += fprintf(stdout, "DOWN (D)\n");
    }
    else
    {
        n += fprintf(stdout, "Not Defined (ND)\n");
    }

    /* Printing in terminal link's status */
    n += fprintf(stdout, "- Link_status: ");
    if (link->status == OPEN_L)
    {
        n += fprintf(stdout, "OPEN\n");
    }
    else
    {
        n += fprintf(stdout, "CLOSE\n");
    }

    fprintf(stdout, "\n");

    /* Return number of characters printed */
    return n;
}

STATUS link_print_save(char *filename, Link *link)
{
    FILE *file = NULL;

    file = fopen(filename, "a");

    /* Error control */
    if (!link || !file)
    {
        return ERROR;
    }

    fprintf(file, "#l:%ld|%s|%ld|%ld|%d|%d|\n", link->id, link->name, link->start, link->destination, link->direction, link->status);

    fclose(file);

    return OK;
}

