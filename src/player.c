/** 
 * @brief Implements the player's interface
 * 
 * @file player.c
 * @author Antonio Van-Oers, Ignacio Nunez, Miguel Soto and Nicolas Victorino
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/player.h"

/**
 * @brief Player
 *
 * This structure contains all relevant info 
 * and members of a player
 */
struct _Player
{
  Id id;	/*!< Player's id */
  char name[PLAYER_NAME_LEN];	/*!< Player's name */
  Inventory *inventory;		/*!< Player's inventory */
  Id location;		/*!< Id to player's player location */
  int health;		/*!< Player's health */
  int max_health; /*!< Max player´s health */
  int Crit_dmg;               /*!< Player's crit chance (scale 0 to 10) */
  int base_dmg;               /*!< Player's base damage */
  char **gdesc;   /*!< Graphic visualization player */
} ;

/** player_create allocates memory for a new player
 * and initializes all its members
 */
Player *player_create(Id id)
{
  Player *new_player = NULL;

  /*Error control */
  if (id == NO_ID)
  {
      return NULL;
  }

  new_player = (Player *) malloc(sizeof(Player));
	/*Error control */
  if (new_player == NULL)
  {
    return NULL;
  }
  
  /* Initializing all of player's members*/
  new_player->id = id;
  new_player->health = 3;
  new_player->name[0] = '\0';
  new_player->location = NO_ID;
  new_player->max_health = 10;
  new_player->inventory = inventory_create();
  new_player->gdesc = NULL;

  return new_player;
}

/** player_destroy frees all previously allocated
 * memory for a player
 */
STATUS player_destroy(Player *player)
{
	/*Error control */
  if (!player)
  {
    return ERROR;
  }
  
  if (player->inventory != NULL) {
    inventory_destroy(player->inventory);
    player->inventory = NULL;
  }
	
  if (player->gdesc)
  {
    player_destroy_gdesc(player->gdesc);
  }
  
  free(player);
  player = NULL;
  return OK;
}

/** player_get_id gets a player's id
 */
Id player_get_id(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NO_ID;
  }
  
  return player->id;
}

/**
 * Tests whether an id is from a player or not
 */
STATUS player_test_id(Id id)
{
  int first_digit, digits;

  /*Error control */
  if (id < 0)
  {
    return ERROR;
  }

  /* Figuring out how many digits - 1 are there 
  and which one is the first */
  digits = (int)log10(id); 

  first_digit = (int)(id / pow(10, digits));
  
  if (first_digit == FD_ID_PLAYER)
  {
    return OK;
  }
  else
  {
    return ERROR;
  }
}

/** player_get_name gets a player's name
 */
const char *player_get_name(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NULL;
  }
  
  return player->name;
}

/** player_get_location gets a player's location
 */
Id player_get_location(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NO_ID;
  }
  
  return player->location;
}

/** player_get_health gets a player's health.
 */
int player_get_health(Player *player)
{
	/*Error control */
  if (!player)
  {
    return -1;
  }
  
  return player->health;
}

/** player_set_health sets a player's health
 */
STATUS player_set_health(Player *player, int health)
{ 
	/*Error control */
  if (!player || health > player->max_health)
  {
    return ERROR; 
  }
  
  player->health = health;
  return OK;
}



/** player_set_location sets a player's location
 */
STATUS player_set_location(Player *player, Id location)
{
	/*Error control */
  if (!player)
  {
    return ERROR;
  }

  player->location = location;
  
  return OK;
}



/** player_set_object assigns an object to a player
 */
STATUS player_add_object(Player *player, Object *object)
{
	/*Error control */
  if (!player|| !object)
  {
    return ERROR;
  }
  
  inventory_add_object(player->inventory, obj_get_id(object));
  return OK;
}

/** Removes an object from a player's inventory
 */
STATUS player_del_object(Player *player, Id id_obj){
  /*Error control */
  if (!player || id_obj==NO_ID)
  {
    return ERROR;
  }
  
  inventory_remove_object(player->inventory, id_obj);
  return OK;
}

/** Gets a player's inventory 
 */
Inventory *player_get_inventory(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NULL;
  }
  
  return player->inventory;
}

/*Tells if a player has an object in his
inventory or not
  */
BOOL player_has_object(Player *player, Id obj_id){
  BOOL b;

  if(!player || obj_id == NO_ID){
    return FALSE;
  }
  
  b = inventory_has_id(player->inventory, obj_id);

  return b;
}


/** player_set_name sets the player's new name
 */
STATUS player_set_name(Player *player, char *name)
{
	/*Error control */
  if (!player || !name)
  {
    return ERROR;
  }
	
  if (strlen(name) >= PLAYER_NAME_LEN)
  {
    strncpy(player->name, name, PLAYER_NAME_LEN);
  }
  else
  {
    strcpy(player->name, name);
  }
  
  return OK;
}

/** player_print prints all player related info in a string
 */
STATUS player_print(Player *player)
{
 /*Error control */
  if (!player)
  {
      return ERROR;
  }
  
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  return OK;
}

STATUS player_set_max_inventory(Player* player, int num) 
{

  if (!player)
  {
    return ERROR;
  }

  inventory_set_maxObjs(player->inventory, num);
  return OK;
}

STATUS player_set_max_health(Player *player, int health)
{
  if (!player || health < 0)
  return ERROR;

  player->max_health = health;

  return OK;
}

int player_get_max_health(Player *player)
{
  if (!player)
  return -1;

  return player->max_health;
}

STATUS player_print_save(char *filename, Player *player)
{
  int i, j;
  FILE *file = NULL;

  file = fopen(filename, "a");

 /* Error control */
  if (!player || !file)
  {
    return ERROR;
  }

  fprintf(file, "#p:%ld|%s|%ld|%d|%d|%d|%d|", player->id, player->name, player->location, player->health, inventory_get_maxObjs(player->inventory), player->Crit_dmg, player->base_dmg);

  for (i = 0; i < PLAYER_GDESC_Y && player->gdesc[i]; i++)
  {
    for (j = 0; j < PLAYER_GDESC_X && player->gdesc[i][j]; j++)
    {
      fprintf(file, "%c", player->gdesc[i][j]);
    }
    fprintf(file, "|");
  }
  
  fprintf(file, "\n");
  
  fclose(file);

  return OK;
}

int player_get_crit(Player *player){
  if (!player){
    return 0;
  }
  return player->Crit_dmg;
}

STATUS player_set_crit(Player *player, int crit){
  if (!player){
    return ERROR;
  }
 player->Crit_dmg = crit;

 return OK;
}

int player_get_baseDmg(Player *player){
  if (!player){
    return 0;
  }
  return player->base_dmg;
}

STATUS player_set_baseDmg(Player *player, int base_dmg){
  if (!player){
    return ERROR;
  }
 player->base_dmg = base_dmg;

 return OK;
}

char **player_create_gdesc()
{
  char **newgdesc = NULL;
  int i, j;

  newgdesc = (char **)malloc((PLAYER_GDESC_Y + 1) * sizeof(char *));
  if (!newgdesc)
  {
    return NULL;
  }
  for (i = 0; i < (PLAYER_GDESC_Y + 1); i++)
  {
    newgdesc[i] = NULL;
    newgdesc[i] = (char *)malloc((PLAYER_GDESC_X + 2) * sizeof(char));
    if (!newgdesc[i])
    {
      return NULL;
    }

    for (j = 0; j < (PLAYER_GDESC_X + 2); j++)
    {
      newgdesc[i][j] = '\0';
    }
  }

  return newgdesc;
}

STATUS player_destroy_gdesc(char **gdesc)
{
  int i;

  /* Error control*/
  if (!gdesc)
  {
    return ERROR;
  }

  if (gdesc)
  {
    for (i = PLAYER_GDESC_Y; i >= 0; i--)
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
 * It gets the graphic description from a player.
 */
STATUS player_set_gdesc(Player *p, char **newgdesc)
{
  /* Error control*/
  if (!p || !newgdesc)
  {
    return ERROR;
  }

  p->gdesc = newgdesc;

  return OK;
}

char **player_get_gdesc(Player *p)
{
  /* Error control*/
  if (!p)
  {
    return NULL;
  }

  return p->gdesc;
}
