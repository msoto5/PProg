/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Miguel Soto, Antonio Van-Oers, Nicolas Victorino and Ignacio Nunez
 * @version 2.0
 * @date 02-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/space.h"

#define MAX_LINKS_SPACE 6   /*!< Establish the maximun of links per space. This number is related to the number of the different existing direction (declared in types.h)*/

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
  Id id;                             /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];          /*!< Name of the space */
  char brief_description[WORD_SIZE]; /*!< Brief description of the space*/
  char long_description[WORD_SIZE];  /*!< Detailed description of the space*/
  Id link[MAX_LINKS_SPACE];          /*!< Id from links between space with this space as origin */
  Set *objects;                      /*!< Conjunto de ids de los objetos que se encuentran en el espacio */
  char **gdesc;                      /*!< Array de 5 strings de 9 caracteres */
  Light ls;                          /*!< Status of light (Brief for Light Status) */
  Floor floor;                       /*!< Floor level of the space*/
  BOOL fire;                         /*!< If TRUE, torches can be turnon. If FALSE, torches cannot illuminate*/
} ;

/**
 * Private functions
 */
int _dir2i(DIRECTION dir);

/**
 * @brief Given a direction returns position of links array
 * @author Miguel Soto
 *
 * LINK ARRAY INDEXES:
 * (NORTH) link[0];
 * (EAST) link[1];
 * (SOUTH) link[2];
 * (WEST) link[3];
 *
 * @param dir direccion
 * @return index input in link array
 */
int _dir2i(DIRECTION dir)
{
  int n;

  if (dir == N)
  {
    n = 0;
  }
  else if (dir == E)
  {
    n = 1;
  }
  else if (dir == S)
  {
    n = 2;
  }
  else if (dir == W)
  {
    n = 3;
  }
  else if (dir == U)
  {
    n = 4;
  } 
  else if (dir == D)
  {
    n = 5;
  }
  else
  {
    n = -1;
  }

  return n;
}

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space *space_create(Id id)
{
  Space *newSpace = NULL;
  int i;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newSpace = (Space *)malloc(sizeof(Space));
  if (newSpace == NULL)
  {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->brief_description[0] = '\0';
  newSpace->long_description[0] = '\0';
  for (i = 0; i < 6; i++)
  {
    newSpace->link[i] = NO_ID;
  }
  newSpace->objects = set_create();
  newSpace->gdesc = NULL;
  newSpace->ls = UNKNOWN_LIGHT;
  newSpace->floor = UNKNOWN_FLOOR;
  newSpace->fire = FALSE;

  return newSpace;
}

/** space_destroy frees the previous memory allocation
 *  for a space
 */
STATUS space_destroy(Space *space)
{
  int i;

  /* Error control */
  if (!space)
  {
    return ERROR;
  }

  for (i = 0; i < 6; i++)
  {
    space->link[i] = NO_ID;
  }

  if (space->objects)
  {
    if (!set_destroy(space->objects))
    {
      return ERROR;
    }
    space->objects = NULL;
  }

  if (space->gdesc)
  {
    if (space_destroy_gdesc(space->gdesc) == ERROR)
    {
      /*printf("ERROR liberando memoria gdesc\n");*/
      return ERROR;
    }
  }

  free(space);
  space = NULL;
  return OK;
}

/** It gets the id of a space
 */
Id space_get_id(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

/**
 * Checks if the id reciven corresponds with a space
 */
STATUS space_test_id(Id id)
{
  int first_digit, digits;

  /*Error control*/
  if (id < 0)
  {
    return ERROR;
  }

  /* Calculates the total number of digits -1*/
  digits = (int)log10(id);

  /* Obtaines first digit*/
  first_digit = (int)(id / pow(10, digits));

  if (first_digit == FD_ID_SPACE)
  {
    return OK;
  }
  else
  {
    return ERROR;
  }
}

/** It sets the name of a space
 */
STATUS space_set_name(Space *space, char *name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (strlen(name) >= WORD_SIZE)
  {
    strncpy(space->name, name, WORD_SIZE);
  }
  else
  {
    strcpy(space->name, name);
  }
  return OK;
}

/** It gets the name of a space
 */
const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

/** space_get_description returns the brief description of a space.
 */
const char *space_get_brief_description(Space *space)
{
  /*CONTROL ERRORS*/
  if (!space)
  {
    return NULL;
  }

  return space->brief_description;
}

/** space_set_description set a new description for an space.
 */
STATUS space_set_brief_description(Space *space, char *brief_description)
{
  /* CONTROL ERROR */
  if (!space || !brief_description)
  {
    return ERROR;
  }

  if (!strcpy(space->brief_description, brief_description))
  {
    /*CONTROL ERROR*/
    return ERROR;
  }

  return OK;
}

/** space_get_long_description returns the detailed description of a space.
 */
const char *space_get_long_description(Space *space)
{
  /*CONTROL ERRORS*/
  if (!space)
  {
    return NULL;
  }

  return space->long_description;
}

/** space_set_long_description set a new detailed description for an space.
 */
STATUS space_set_long_description(Space *space, char *long_description)
{
  /* CONTROL ERROR */
  if (!space || !long_description)
  {
    return ERROR;
  }

  if (!strcpy(space->long_description, long_description))
  {
    /*CONTROL ERROR*/
    return ERROR;
  }

  return OK;
}

/**
 * It sets the link of the space in an specific direction
 */
STATUS space_set_link(Space *space, Id link, DIRECTION dir)
{
  int n = _dir2i(dir);

  if (!space || !link || dir == ND)
  {
    return ERROR;
  }

  if (n < 0)
  {
    return ERROR;
  }

  space->link[n] = link;
  return OK;
}

/**
 * It gets link's id that starts in this space with an specific direction
 */
Id space_get_link(Space *space, DIRECTION dir)
{
  int n = _dir2i(dir);

  if (!space || dir == ND)
  {
    return -1;
  }

  if (n < 0)
  {
    return -1;
  }

  return space->link[n];
}

/**
 * It add an object id in the space's set of objects
 */
STATUS space_add_objectid(Space *s, Id id)
{
  /* Error control*/
  if (!s || !id)
  {
    return ERROR;
  }

  if (!set_add(s->objects, id))
  {
    return ERROR;
  }

  return OK;
}

/**
 * It deletes an object id in the space's set of objects
 */
STATUS space_del_objectid(Space *s, Id id)
{
  /* Error control*/
  if (!s || !id)
  {
    return ERROR;
  }

  if (!set_del_id(s->objects, id))
  {
    return ERROR;
  }

  return OK;
}

/**
 * It gets a pointer to the set of objects in a space
 */
Set *space_get_objects(Space *s)
{
  /* Error control*/
  if (!s)
  {
    return NULL;
  }
  return s->objects;
}

/**
 * It gets a pointer to the id array of a set of objects that are in that space
 */
Id *space_get_objects_ids(Space *s)
{
  /* Error control*/
  if (!s)
  {
    return NULL;
  }

  return set_get_ids(space_get_objects(s));
}

/**
 * It sets the graphic description of a spaces.
 */
BOOL space_has_object(Space *s, Id id)
{
  Id *ids = NULL;
  BOOL b = FALSE;
  int i;

  /* Error control*/
  if (!s)
  {
    return FALSE;
  }

  ids = set_get_ids(s->objects);
  if (ids == NULL)
  {
    return FALSE;
  }

  for (i = 0; (i < set_get_nids(s->objects)) && (b == FALSE); i++)
  {
    if (*(ids + i) == id)
    {
      b = TRUE;
    }
  }

  return b;
}

char **space_create_gdesc()
{
  char **newgdesc = NULL;
  int i, j;

  newgdesc = (char **)malloc((TAM_GDESC_Y + 1) * sizeof(char *));
  if (!newgdesc)
  {
    return NULL;
  }
  for (i = 0; i < (TAM_GDESC_Y + 1); i++)
  {
    newgdesc[i] = NULL;
    newgdesc[i] = (char *)malloc((TAM_GDESC_X + 2) * sizeof(char));
    if (!newgdesc[i])
    {
      return NULL;
    }

    for (j = 0; j < (TAM_GDESC_X + 2); j++)
    {
      newgdesc[i][j] = '\0';
    }
  }

  return newgdesc;
}

STATUS space_destroy_gdesc(char **gdesc)
{
  int i;

  /* Error control*/
  if (!gdesc)
  {
    return ERROR;
  }

  if (gdesc)
  {
    for (i = TAM_GDESC_Y; i >= 0; i--)
    {
      if (gdesc[i])
      {
        free(gdesc[i]);
        gdesc[i] = NULL;
      }
    }

    free(gdesc);
    gdesc = NULL;
  }

  return OK;
}

/**
 * It gets the graphic description from a space.
 */
STATUS space_set_gdesc(Space *s, char **newgdesc)
{
  /* Error control*/
  if (!s || !newgdesc)
  {
    return ERROR;
  }

  s->gdesc = newgdesc;

  return OK;
}

char **space_get_gdesc(Space *s)
{
  /* Error control*/
  if (!s)
  {
    return NULL;
  }

  return s->gdesc;
}

/** It prints the space information
 */
STATUS space_print(Space *space)
{
  Id idaux = NO_ID;
  int nobj, i, j;
  Light ls;

  /* Error Control */
  if (!space)
  {
    return ERROR;
  }

  /* 1. Print the id, the name and the floor of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)", space->id, space->name);
  if (space->floor == DUNGEON)
  {
    fprintf(stdout, "; Floor: DUNGEON\n");
  } else if (space->floor == FLOOR_0)
  {
    fprintf(stdout, "; Floor: FLOOR_0\n");
  } else if (space->floor == ALCOVE)
  {
    fprintf(stdout, "; Floor: ALCOVE\n");
  }

  /* 2. For each direction, print its link */
  idaux = space_get_link(space, N);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_link(space, S);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_link(space, E);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_link(space, W);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  nobj = set_get_nids(space_get_objects(space));
  if (nobj > 0)
  {
    fprintf(stdout, "---> %d objects in the space.\n", nobj);
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
  }

  /* 4. Print if the space has light or not */
  ls = space_get_light_status(space);
  if (ls == BRIGHT)
  {
    fprintf(stdout, "---> The space is bright\n");
  }
  else
  {
    fprintf(stdout, "---> The space is dark\n");
  }

  /* 5. Print gdesc*/
  printf("=> Gdesc:\n");
  for (i = 0; i < TAM_GDESC_Y && space->gdesc[i]; i++)
  {
    for (j = 0; j < TAM_GDESC_X && space->gdesc[i][j]; j++)
    {
      printf("%c", space->gdesc[i][j]);
    }
    printf("\n");
    if (j != TAM_GDESC_X)
    {
      printf("ERROR IMPRIMIENDO space->gdesc[%d][%d] = NULL\n", i, j);
    }
  }

  return OK;
}

Id space_get_id_dest_by_link (Link *l)
{
  /*Error control*/
  if (!l)
  return -1;

  return (Id)link_get_destination(l);

}

STATUS space_set_light_status (Space *space, Light ls)
{

  if (! space ) {
    return ERROR;
  } 

  if (ls == -1)
  {
    space->ls = UNKNOWN_LIGHT;
  } else if (ls == 0)
  {
    space->ls = DARK;
  } else if (ls == 1)
  {
    space->ls = BRIGHT;
  }

  return OK;
}

Light space_get_light_status (Space *space)
{

  if (!space) {
    return UNKNOWN_LIGHT;
  }

  return space->ls;
}

/** It prints the space information in the save file
 */
STATUS space_print_save(char *filename, Space *space)
{
  int i = 0, j = 0;
  FILE *file = NULL;

  file = fopen(filename, "a");

 /* Error control */
  if (!space || !file)
  {
    return ERROR;
  }

  fprintf(file, "#s:%ld|%s|%s|%s|%d|", space->id, space->name, space->brief_description, space->long_description, space->ls);

  for (i = 0; i < TAM_GDESC_Y && space->gdesc[i]; i++)
  {
    for (j = 0; j < TAM_GDESC_X && space->gdesc[i][j]; j++)
    {
      fprintf(file, "%c", space->gdesc[i][j]);
    }
    fprintf(file, "|");
  }

  fprintf(file, "%d|%d|\n", space->floor, space->fire); 

  fclose(file);

  return OK;
}

Floor space_get_floor(Space* space)
{
  if (!space)
  {
    return UNKNOWN_FLOOR;
  }

  return space->floor;
}

STATUS space_set_floor(Space* space, Floor floor)
{
  if (!space || (floor != DUNGEON && floor != FLOOR_0 && floor != ALCOVE))
  {
    return ERROR;
  }

  space->floor = floor;
  return OK;
}

/**
 * It gets if the space has fire in it, so some objects can turn on.
 */
BOOL space_get_fire(Space *s)
{
  if (!s)
  {
    return FALSE;
  }
  
  return s->fire;
}

/**
 * It sets if there is fire in the space
 */
STATUS space_set_fire(Space *s, BOOL fire)
{
  if (!s)
  {
    return ERROR;
  }
  
  s->fire = fire;
  return OK;
}
