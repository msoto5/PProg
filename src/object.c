  /**
 * @brief It implements the object module.
 *
 * @file object.c
 * @author Miguel Soto, Antonio Van-Oers, Nicolas Victorino & Ignacio Nunnez
 * @version 3.0
 * @date 02-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/object.h"

/**
 * @brief Object
 *
 * This structure saves the information of an object
 */
struct _Object
{
  Id id;                        /*!< Object's id */
  char name[OBJ_NAME_LEN];      /*!< Object name */
  char description[WORD_SIZE];  /*!< Object description */
  Id location;                  /*!< Object space location */
  BOOL movable;                 /*!< Movable condition of an object (FALSE by default)*/
  Id dependency;                /*!< Dependency condtion of an object (If and object is dependent of another it saves its id here, if not NO_ID) */
  Id open;                      /*!< Open condition of an object (If an object can open a certain space it saves the id here, if not NO_ID)*/
  BOOL illuminate;              /*!< Illuminate condition of an object (FALSE by default)*/
  BOOL turnedon;                /*!< Turned on condition of an object (FALSE by default)*/
  Light light_visible;          /*!< Tells the light conditions when the object is visible*/
  int Crit_dmg;                 /*!< Critical chance that the object adds to the one who carries it*/
  int Durability;               /*!< Durability points left(-1 if it is not breakable)*/
} ;

/** obj_create saves memory for a new object and initializes its parameters
 */
Object *obj_create(Id id)
{
  Object *new_obj = NULL;

  /* Control de errores */
  if (id == NO_ID)
  {
    return NULL;
  }

  new_obj = (Object *)malloc(sizeof(Object));
  if (new_obj == NULL)
  {
    return NULL;
  }

  /* Initialization of the object*/
  new_obj->id = id;
  new_obj->name[0] = '\0';
  new_obj->description[0] = '\0';
  new_obj->movable = FALSE;
  new_obj->dependency = NO_ID;
  new_obj->open = NO_ID;
  new_obj->illuminate = FALSE;
  new_obj->turnedon = FALSE;

  return new_obj;
}

/** obj_destroy free the memory previously saved of an object
 */
STATUS obj_destroy(Object *obj)
{
  /* Error control */
  if (!obj)
  {
    return ERROR;
  }

  free(obj);
  obj = NULL;
  return OK;
}

/**
 * Checks if the received id corresponds to an object
 */
STATUS obj_test_id(Id id)
{
  int first_digit, digits;

  /* Error control*/
  if (id < 0)
  {
    return ERROR;
  }

  /* Calculates the total number of digits -1 */
  digits = (int)log10(id);

  /* Obtaines the first digit */
  first_digit = (int)(id / pow(10, digits));

  if (first_digit == FD_ID_OBJ)
  {
    return OK;
  }
  else
  {
    return ERROR;
  }
}

/** obj_get_id returns the id of an object (obj).
 */
Id obj_get_id(Object *obj)
{
  /*Error control*/
  if (!obj)
  {
    return NO_ID;
  }

  return obj->id;
}

/** obj_get_name returns the name of an object
 */
const char *obj_get_name(Object *obj)
{
  /* Error control */
  if (!obj)
  {
    return NULL;
  }

  return obj->name;
}

/** obj_set_name sets the name of an object(obj).
 */
STATUS obj_set_name(Object *obj, char *name)
{
  /* Error control */
  if (!obj || !name)
  {
    return ERROR;
  }

  if (strlen(name) >= OBJ_NAME_LEN)
  {
    strncpy(obj->name, name, OBJ_NAME_LEN);
  }
  else
  {
    strcpy(obj->name, name);
  }

  return OK;
}

/** obj_get_description returns the description of an object.
 */
const char *obj_get_description(Object *obj)
{
  /*CONTROL ERRORS*/
  if (!obj)
  {
    return NULL;
  }

  return obj->description;
}

/** obj_set_description set a new description for an object.
 */
STATUS obj_set_description(Object *obj, char *description)
{
  /* CONTROL ERROR */
  if (!obj || !description)
  {
    return ERROR;
  }

  if (!strcpy(obj->description, description))
  {
    /*CONTROL ERROR*/
    return ERROR;
  }

  return OK;
}

Id obj_get_location(Object *obj)
{
  /* Control de errores */
  if (!obj)
  {
    return NO_ID;
  }

  return obj->location;
}

STATUS obj_set_location(Object *obj, Id id)
{
  /* Control de errores */
  if (!obj)
  {
    return ERROR;
  }

  obj->location = id;
  return OK;
}

/** obj_print prints the information of an object (obj).
 */
STATUS obj_print(Object *obj)
{
  /* Error control */
  if (!obj)
  {
    return ERROR;
  }

  /*General information*/
  fprintf(stdout, "--> Object (Id: %ld; Name: %s; Location: %ld;\nDescription: %s)\n", obj->id, obj->name, obj->location, obj->description);

  /*Movable condition*/
  if (obj->movable == TRUE)
  {
    fprintf(stdout, "Movable: TRUE");
  } else {
    fprintf(stdout, "Movable: FALSE");
  }

  /*Dependency condition*/
  if (obj->dependency == NO_ID)
  {
    fprintf(stdout, "Depenency: NO_ID");
  } else {
    fprintf(stdout, "Dependency: %ld", obj->dependency);
  }

  /*Open condition*/
  if (obj->open == NO_ID)
  {
    fprintf(stdout, "Open: NO_ID");
  } else {
    fprintf(stdout, "Open: %ld", obj->open);
  }

  /*Illuminate condition*/
  if (obj->illuminate == TRUE)
  {
    fprintf(stdout, "Illuminate: TRUE");
  } else {
    fprintf(stdout, "Illuminate: FALSE");
  }

  /*Turned on condition*/
  if (obj->turnedon == TRUE)
  {
    fprintf(stdout, "Turned on: TRUE");
  } else {
    fprintf(stdout, "Turned on: FALSE");
  }
  return OK;
}

/** Sets the movable condition of an object
 */
STATUS object_set_movable(Object *obj, BOOL cond)
{
  if (!obj || (cond != TRUE && cond != FALSE))
  {
    return ERROR;
  }

  if (cond == FALSE)
  {
    obj->movable = FALSE;
  } else if (cond == TRUE)
  {
    obj->movable = TRUE;
  }

  return OK;
}

/** Sets the dependency condition of an object
 */
STATUS object_set_dependency(Object *obj, Id id)
{
  if (!obj)
  {
    return ERROR;
  }

  obj->dependency = id;

  return OK;
}

/** Sets the open condition of an object
 */
STATUS object_set_open(Object *obj, Id id)
{
  if (!obj)
  {
    return ERROR;
  }

  obj->open = id;

  return OK;
}

/** Sets the illuminate condition of an object
 */
STATUS object_set_illuminate(Object *obj, BOOL cond)
{
  if (!obj)
  {
    return ERROR;
  }

  obj->illuminate = cond;

  return OK;
}

/** Sets the turnedon condition of an object
 */
STATUS object_set_turnedon(Object *obj, BOOL cond)
{
  if (!obj)
  {
    return ERROR;
  }

  obj->turnedon = cond;

  return OK;
}

/** Gets the movable condition of an object
 */
BOOL object_get_movable(Object *obj)
{
  if (!obj)
  {
    return FALSE;
  }

  return obj->movable;
}

/** Gets the dependency condition of an object
 */
Id object_get_dependency(Object *obj)
{
  if (!obj)
  {
    return NO_ID;
  }

  return obj->dependency;
}

/** Gets the open condition of an object
 */
Id object_get_open(Object *obj)
{
  if (!obj)
  {
    return NO_ID;
  }

  return obj->open;
}

/** Gets the illuminate condition of an object
 */
BOOL object_get_illuminate(Object *obj)
{
  if (!obj)
  {
    return FALSE;
  }

  return obj->illuminate;
}

/** Gets the turnedon condition of an object
 */
BOOL object_get_turnedon(Object *obj)
{
  if (!obj)
  {
    return FALSE;
  }

  return obj->turnedon;
}

/** Set the time when an object is visible
*/
STATUS object_set_light_visible(Object *obj, Light light)
{
  if (!obj || (light != BRIGHT && light != DARK))
  {
    return ERROR;
  }

  obj->light_visible = light;
  return OK;
}

/** Gets the time when an object is visible 
*/
Light object_get_light_visible(Object *obj)
{
  if (!obj)
  {
    return -1;
  }

  return obj->light_visible;
}

/** obj_print_save prints the information of an object in the save file
 */
STATUS obj_print_save(char *filename, Object *obj)
{

  FILE *file = NULL;

  file = fopen(filename, "a");

 /* Error control */
  if (!obj || !file)
  {
    return ERROR;
  }
  fprintf(file, "#o:%ld|%s|%s|%ld|%d|%ld|%ld|%d|%d|%d|%d|%d|\n", obj->id, obj->name, obj->description, obj->location, obj->movable, obj->dependency, obj->open, obj->illuminate, obj->turnedon, obj->light_visible, obj->Crit_dmg, obj->Durability);

  fclose(file);

  return OK;
}

/** Return true if the object is visible
*/
BOOL obj_is_visible(Object *obj, Light ls)
{
  if (obj == NULL || ls == UNKNOWN_LIGHT)
  {
    return ERROR;
  }

  if (object_get_light_visible(obj) == ls)
  {
    return TRUE;
  } else {
    return FALSE;
  }
}

/** Gets the type (apple, elixir, bed, armour...) of an object
 */
Obj_type obj_get_type(Id id)
{

  /*Error control*/
  if (id < 300 || id > 400)
  {
    return UNKNOWN_TYPE;
  }

  if (id - 310 < 0 && id - 310 >= -10) 
  {
    return APPLE;
  } else if (id - 320 < 0 && id - 320 >= -10)
  {
    return ELIXIR;
  } else if (id - 330 < 0 && id - 330 >= -10)
  {
    return ARMOR;
  } else if (id - 340 < 0 && id - 340 >= -10)
  {
    return HOOK;
  } else if (id - 350 < 0 && id - 350 >= -10)
  {
    return BED;
  } else if (id - 360 < 0 && id - 360 >= -10) 
  {
    return BREAD_CRUMBS;
  } else
  {
    return UNKNOWN_TYPE;
  }


}

/** Gets the critical damage of an object
 */
int object_get_crit(Object *obj){
  if (!obj){
    return 0;
  }
  return obj->Crit_dmg;
}

/** Sets the critical damage of an object
 */
STATUS object_set_crit(Object *obj, int crit){
  if (!obj){
    return ERROR;
  }
 obj->Crit_dmg = crit;
 
 return OK;
}

/** Sets the durability of an object
 */
int object_get_durability(Object *obj){
  if (!obj){
    return 0;
  }
  return obj->Durability;
}

/** Gets the durability of an object
 */
STATUS object_set_durability(Object *obj, int dur){
  if (!obj){
    return ERROR;
  }
 obj->Durability = dur;
 
 return OK;
}

/** Checks if an object is broken
 */
BOOL object_isBroken(Object *obj){
  if (!obj){
    return TRUE;
  }
  if (object_get_durability(obj)==0){
    return TRUE;
  }
  return FALSE;
}
