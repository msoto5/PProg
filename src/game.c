/**
 * @brief It implements the game module and all the associated calls
 * for each command
 *
 * @file game.c
 * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "../include/game.h"
#include "../include/game_managment.h"

/**
 * @brief Game
 * 
 * This struct stores all the information of a space.
 */
struct _Game
{
  Player *player[MAX_PLAYERS]; /*!< Pointer to player's array */
  Object *object[MAX_OBJS];    /*!< Pointer to object's array */
  Enemy *enemy[MAX_ENEMYS];    /*!< Pointer to enemy's array */
  Space *spaces[MAX_SPACES];   /*!< Pointer to space's array */
  Link *links[MAX_LINKS];      /*!< Pointer to link's array */
  char *inspection;            /*!< Long description for inspect space */
  Time day_time;               /*!< Time cycle of the game */
  T_Command last_cmd;          /*!< Last command input */
  R_Event last_event;          /*!< Last event */
  Dialogue *dialogue;          /*!< Text to print*/
} ;

/**
   Private functions
*/
int game_command_unknown(Game *game, char *arg);
void game_get_new_event(Game *game);
STATUS game_command_exit(Game *game, char *arg);
STATUS game_command_take(Game *game, char *arg);
STATUS game_command_drop(Game *game, char *arg);
STATUS game_command_attack(Game *game, char *arg);
STATUS game_command_move(Game *game, char *arg);
STATUS game_command_movement(Game *game, DIRECTION dir);
STATUS game_command_inspect(Game *game, char *arg);
STATUS game_command_save(Game *game, char *arg);
STATUS game_command_load(Game *game, char *arg);
STATUS game_command_turnon(Game *game, char *arg);
STATUS game_command_turnoff(Game *game, char *arg);
STATUS game_command_open(Game *game, char *link_name, char *obj_name);
STATUS game_command_use(Game *game, char *arg);
STATUS game_event_move(Game *game);
STATUS game_event_trap(Game *game);
STATUS game_event_slime(Game *game);
STATUS game_event_daynight(Game *game);
STATUS game_event_spawn(Game *game);

/**
 * Game interface implementation
 */

/** game_create allocs memory for some necessary game's members
 */
STATUS game_alloc(Game *game)
{
  Id id_player = 21, id_enemy = 41;
  int i = 0;

  if (!game)
  {
    fprintf(stderr, "Error saving memory for game (game_alloc)");
    return ERROR;
  }

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->player[i] = player_create(id_player);
    if (!game->player[i])
    {
      return ERROR;
    }
  }

  for (i = 0; i < MAX_ENEMYS; i++)
  {
    game->enemy[i] = enemy_create(id_enemy);
    if (!game->enemy[i])
    {
      return ERROR;
    }
  }

  game->inspection = " ";
  game->dialogue = dialogue_create();
  return OK;
}

/** game_create initializes all necessary game's members
 * to a empty value
 */
STATUS game_create(Game *game)
{
  int i = 0;

  /* Error control*/
  if (game == NULL)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJS; i++)
  {
    game->object[i] = NULL;
  }

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->player[i] = NULL;
  }

  for (i = 0; i < MAX_ENEMYS; i++)
  {
    game->enemy[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    game->links[i] = NULL;
  }

  game->day_time = DAY;
  game->last_cmd = NO_CMD;
  
  return OK;
}

/** game_destroy frees/destroys all of game's members
 * calling space_destroy for each one of them
 */
STATUS game_destroy(Game *game)
{
  int i = 0;

  /* Error control*/
  if (game == NULL)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    obj_destroy(game->object[i]);
    game->object[i] = NULL;
  }

  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    player_destroy(game->player[i]);
    game->player[i] = NULL;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    enemy_destroy(game->enemy[i]);
    game->enemy[i] = NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    link_destroy(game->links[i]);
    game->links[i] = NULL;
  }

  dialogue_destroy(game->dialogue);

  free(game);
  game = NULL;

  return OK;
}

/**
 * It adds one space (space) to game's struct.
 */
STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  /* Error control*/
  if (game == NULL)
  {
    return ERROR;
  }

  /* Error control*/
  if (space == NULL)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
  }

  /* Error control*/
  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

/**
 * Adds objects to the game
 */
STATUS game_add_object(Game *game, Object *obj)
{
  int i = 0;

  /* Error control*/
  if (!game || !obj)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
  }

  /* Error control*/
  if (i >= MAX_OBJS)
  {
    return ERROR;
  }

  game->object[i] = obj;

  return OK;
}

/**
 * It adds a player to game struct.
 */
STATUS game_add_player(Game *game, Player *p)
{
  int i = 0;

  /* Error control*/
  if (!game || !p)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
  }

  if (i >= MAX_PLAYERS)
  /* Error control*/
  {
    return ERROR;
  }

  game->player[i] = p;

  return OK;
}

/**
 * Adds all game's enemies
 */
STATUS game_add_enemy(Game *game, Enemy *e)
{
    int i = 0;

  /* Error control*/
  if (!game || !e)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
  }

  /* Error control*/
  if (i >= MAX_ENEMYS)
  {
    return ERROR;
  }

  game->enemy[i] = e;

  return OK;
}

/**
 * Adds all game's links
 */
STATUS game_add_link(Game *game, Link *l)
{
  int i = 0;

  /* Error control*/
  if (!game || !l)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
  }

  /* Error control*/
  if (i >= MAX_LINKS)
  {
    return ERROR;
  }

  game->links[i] = l;

  return OK;
}

/**
 * game_get_space_id_at Checks if the spaces are within the appropiate range, output will be No_ID
 * whenever it is located outside this range or its id if it belongs to the game
 */
Id game_get_space_id_at(Game *game, int position)
{
  /* Error control*/
  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/** Gets game's space with target id
 */
Space *game_get_space(Game *game, Id id)
{
  int i;

  /* Error control*/
  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

/** Sets the day time of the game
 */
STATUS game_set_time(Game *game, Time time)
{
  int i = 0;
  Space *s = NULL;
  Id id = NO_ID;

  if (!game || (time != DAY && time != NIGHT))
  {
    return ERROR;
  }

  game->day_time = time;

  if (time == NIGHT)
  {
    for (i = 0; i < MAX_SPACES; i++)
    {
      s = game->spaces[i];
      id = space_get_id(s);

      if (s != NULL)
      {
        if (id != 121 && id != 125)
        {
          if (space_set_light_status(s, DARK) == ERROR)
          {
            return ERROR;
          }
        } 
      }
    } 
  } else 
  {
    for (i = 0; i < MAX_SPACES; i++)
    {
      s = game->spaces[i];
      id = space_get_id(s);

      if (s != NULL)
      {
        if (id != 121 && id != 125)
        {
          if (space_set_light_status(s, BRIGHT) == ERROR)
          {
            return ERROR;
          }
        } 
      }
    }
  }  
  return OK;

}

/** Gets if it is day or night
 */
Time game_get_time(Game *game)
{
  if (!game)
  {
    return -1;
  }

  return game->day_time;
}


/**
 * Gets a game's object with target id
 */
Object *game_get_object(Game *game, Id id)
{
  int i;

  /* Error control*/
  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    if (id == obj_get_id(game->object[i]))
    {
      return game->object[i];
    }
  }

  return NULL;
}

/**
 * @brief Finds an object with the same name. Case is ignore.
 * @author Nicolas Victorino
 * 
 * @param game pointer to game struct
 * @param name string with obj_name
 * @return pointer to object with name name.
 */
Object *game_get_object_byName(Game *game, char *name)
{
  int i;

  /* Error control*/
  if (!game || name == NULL)
  {
    return NULL;
  }

  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    if (strcasecmp(name, obj_get_name(game->object[i])) == 0)
    {
      return game->object[i];
    }
  }

  return NULL;
}

/**
 * @brief Finds a link with the same name. Case is ignore.
 * @author Miguel Soto
 * 
 * @param game pointer to game struct.
 * @param name string with link's name.
 * @return pointer to link with name name.
 */
Link *game_get_link_byName(Game *game, char *name)
{
  int i;

  /* Error control*/
  if (!game || name == NULL)
  {
    return NULL;
  }

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (strcasecmp(name, link_get_name(game->links[i])) == 0)
    {
      return game->links[i];
    }
  }

  return NULL;
}

Enemy *game_get_enemyWithPlayer(Game *game, Id player_loc){

  int i;

  if (!game || player_loc == NO_ID){
    return NULL;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    if (player_loc == enemy_get_location(game->enemy[i]))
    {
      return game->enemy[i];
    }
  }

  return NULL;

}

/**
 * Finds an enemy with the same name. Case is ignore.
 */
Enemy *game_get_enemy_byName(Game *game, char *name)
{
  int i;

  /* Error control*/
  if (!game || name == NULL)
  {
    return NULL;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    if (strcasecmp(name, enemy_get_name(game->enemy[i])) == 0)
    {
      return game->enemy[i];
    }
  }

  return NULL;
}

/**
 * Gets a game's palyer with target id
 */
Player *game_get_player(Game *game, Id id)
{
  int i;

  /* Error control*/
  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    if (id == player_get_id(game->player[i]))
    {
      return game->player[i];
    }
  }

  return NULL;
}

/**
 * Gets a game's enemy with target id
 */
Enemy *game_get_enemy(Game *game, Id id)
{
  int i;

  /* Error control*/
  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    if (id == enemy_get_id(game->enemy[i]))
    {
      return game->enemy[i];
    }
  }

  return NULL;
}

/**
 * returns long description that is on screen
 */
char *game_get_inspection(Game *game)
{
  /* Error control*/
  if (!game)
  {
    return NULL;
  }

  return game->inspection;
}

/**
 * Gets a game's link with target id
 */
Link *game_get_link(Game *game, Id id)
{
  int i;

  /* Error control*/
  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (id == link_get_id(game->links[i]))
    {
      return game->links[i];
    }
  }

  return NULL;
}

/**
 * Sets the player's location to target id
 */
STATUS game_set_player_location(Game *game, Id player_id, Id space_id)
{
  Player *p = NULL;

  /* Error control*/
  if (!game || player_id == NO_ID || space_id == NO_ID)
  {
    return ERROR;
  }

  p = game_get_player(game, player_id);
  if (!p)
  {
    return ERROR;
  }

  /* Error control*/
  if (player_set_location(p, space_id) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

/**
 * Sets the object's location to target id
 */
STATUS game_set_object_location(Game *game, Id obj_id, Id space_id)
{
  Object *o = NULL;

  /* Error control*/
  if (!game || obj_id == NO_ID)
  {
    return ERROR;
  }

  o = game_get_object(game, obj_id);
  /* Error control*/
  if (!o)
  {
    return ERROR;
  }

  /* Error control*/
  if (obj_set_location(o, space_id) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

/**
 * Sets the enemy's location to target id
 */
STATUS game_set_enemy_location(Game *game, Id enemy_id, Id space_id)
{
    Enemy *e = NULL;

  /* Error control*/
  if (!game || enemy_id == NO_ID || space_id == NO_ID)
  {
    return ERROR;
  }

  e = game_get_enemy(game, enemy_id);
  /* Error control*/
  if (!e)
  {
    return ERROR;
  }

  return enemy_set_location(game->enemy[MAX_PLAYERS - 1], space_id);
}

/** Gets an player's position
 */
Id game_get_player_location(Game *game, Id player_id)
{
  Player *p = NULL;

  /* Error control*/
  if (!game || player_id == NO_ID)
  {
    return NO_ID;
  }

  p = game_get_player(game, player_id);
  /* Error control*/
  if (!p)
  {
    return NO_ID;
  }

  return player_get_location(p);
}

/** Gets an enemy's position
 */
Id game_get_enemy_location(Game *game, Id enemy_id)
{
  Enemy *e = NULL;

  /* Error control*/
  if (!game || enemy_id == NO_ID)
  {
    return NO_ID;
  }

  e = game_get_enemy(game, enemy_id);
  /* Error control*/
  if (!e)
  {
    return NO_ID;
  }

  return enemy_get_location(e);
}

/** Gets an object's position
 */
Id game_get_object_location(Game *game, Id obj_id)
{
    Object *o = NULL;

  /* Error control*/
  if (!game || obj_id == NO_ID)
  {
    return NO_ID;
  }

  o = game_get_object(game, obj_id);
  /* Error control*/
  if (!o)
  {
    return NO_ID;
  }

  return obj_get_location(o);
}

/**
 * It get if link is open or close giving an space and a specific direction
 */
LINK_STATUS game_get_connection_status(Game *game, Id act_spaceid, DIRECTION dir)
{
  Id link_id = -1;
  Space *s = NULL;
  LINK_STATUS linkst = CLOSE;

  /* Error control */
  if (!game || act_spaceid == NO_ID || dir == ND)
  {
    return CLOSE;
  }

  s = game_get_space(game, act_spaceid);
  /* Error control*/
  if (!s)
  {
    return CLOSE;
  }

  link_id = space_get_link(s, dir);
  /* Error control*/
  if (link_id < 0)
  {
    return CLOSE;
  }

  linkst = link_get_status(game_get_link(game, link_id));

  return linkst;
}

/**
 * It get id from the space destination of a link
 */
Id game_get_connection(Game *game, Id act_spaceid, DIRECTION dir)
{
  Id link_id = -1, dest_id = -1;
  Space *s = NULL;

  /* Error control */
  if (!game || act_spaceid == NO_ID || dir == ND)
  {
    return CLOSE;
  }

  s = game_get_space(game, act_spaceid);

  /* Error control */
  if (!s)
  {
    return CLOSE;
  }

  link_id = space_get_link(s, dir);
  /* Error control */
  if (link_id < 0)
  {
    return CLOSE;
  }

  dest_id = link_get_destination(game_get_link(game, link_id));

  return dest_id;
}

/*Functions for the new event
(just a continuation of game_update)*/
void game_get_new_event(Game *game){

  R_Event new_event = 0;
  STATUS st = ERROR;

  new_event = game_rules_get_event();
  game->last_event = new_event;

  switch(new_event)
  {
    case MOVE_OBJ:
      st = game_event_move(game);
      break;

    case TRAP:
      st = game_event_trap(game);
      break;

    case SLIME:
      st = game_event_slime(game);
      break;

    case DAYNIGHT:
      st = game_event_daynight(game);
      break;

    case SPAWN:
      st = game_event_spawn(game);
      break;

    default:
      break;
  }

  if(st == ERROR){
    game->last_event = NOTHING;
  }

  return;
}


/** game_update updates cmd whenever something is typed in, this is where
 * every known case gets interpreted as the various actions on the game,
 * any other input would be considered unknown
 */
int game_update(Game *game, T_Command cmd, char *arg1, char *arg2)
{
  int st = 0;
  
  if(!game){
    return 0;
  }
  
  game->last_cmd = cmd;
  game->inspection = 0;
  dialogue_reset(game->dialogue);
  
  if (update_game_over(game) == TRUE)
  {
    game_is_over(game);
  }

  switch (cmd)
  {
  case UNKNOWN:
    st = game_command_unknown(game, arg1);
    break;

  case EXIT:
    st = (int)game_command_exit(game, arg1);
    break;

  case TAKE:
    st = (int)game_command_take(game, arg1);
    break;

  case DROP:
    st = (int)game_command_drop(game, arg1);
    break;

  case ATTACK:
    st = (int)game_command_attack(game, arg1);
    break;

  case MOVE:
    st = (int)game_command_move(game, arg1);
    break;

  case INSPECT:
    st = (int)game_command_inspect(game, arg1);
    break;

  case SAVE:
    st = (int)game_command_save(game, arg1);
    break;

  case LOAD:
    st = (int)game_command_load(game, arg1);
    break;
    
  case TURNON:
    st = (int)game_command_turnon(game, arg1);
    break;

  case TURNOFF:
    st = (int)game_command_turnoff(game, arg1);
    break;

  case OPEN:
    st = (int)game_command_open(game, arg1, arg2);
    break;

  case USE:
    st = (int)game_command_use(game, arg1);
    break;
      
  default:
    break;
  }

  game_update_object(game);
  game_update_enemy(game);
  game_update_time(game);
  game_update_ls(game);
  
  game_get_new_event(game);

  return st;
}


/* Gets the last event in the input
*/
R_Event game_get_last_event(Game *game){
  if(game == NULL){
    return -1;
  }
  
  return game->last_event;
}

/** Gets the last command in the input
 */
T_Command game_get_last_command(Game *game)
{
  if(game == NULL){
    return -1;
  }
  
  return game->last_cmd;
}

/**
 * game_print_data prints all game related relevant data
 */
void game_print_data(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Objects:\n");
  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    obj_print(game->object[i]);
  }

  printf("=> Players:\n");
  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    player_print(game->player[i]);
  }

  printf("=> Enemies:\n");
  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    enemy_print(game->enemy[i]);
  }
}

/** False is the output when called
 * meaning game has ended
 */
BOOL game_is_over(Game *game)
{
  if (player_get_health(game->player[MAX_PLAYERS - 1]) <= 0)
  {
    dialogue_set_command(game->dialogue, DC_GOVER, NULL, NULL, NULL);
    return TRUE;
  }

   if (enemy_get_health(game_get_enemy(game, 45)) <= 0)
  {
    dialogue_set_command(game->dialogue, DC_END, NULL, NULL, NULL);
    return TRUE;
  }

  return FALSE;
}

/**
 *Calls implementation for each action
 */

/**
 * @brief It executes UNKNOWN command in game.
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
int game_command_unknown(Game *game, char *arg)
{
  dialogue_set_command(game->dialogue, DC_UNKNOWN, NULL, NULL, NULL);
  return 5;
}

/**
 * @brief It executes EXIT command in game.
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_exit(Game *game, char *arg)
{
  dialogue_set_command(game->dialogue, DC_EXIT, NULL, NULL, NULL);
  return OK;
}

/**
 * @brief It executes TAKE command in game.
 * 
 * This command is for the player to take the object located
 * on the current position. It requires the name of the object for it
 * to be taken correctly
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_take(Game *game, char *arg)
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS - 1]);
  Id id_obj_taken = NO_ID, obj_loc = NO_ID;
  Object *obj_taken;
  Space *s = NULL;
  Object *o = NULL;
  STATUS st = OK;

  obj_taken = game_get_object_byName(game, arg);
  id_obj_taken = obj_get_id(obj_taken);
  
  /* Error control*/
  if(object_get_movable(obj_taken)==TRUE && obj_is_visible(obj_taken, space_get_light_status(game_get_space(game, player_location))) && id_obj_taken != 398){  
    /* Error control*/
    if (space_has_object(game_get_space(game, player_location), id_obj_taken) == TRUE && set_get_nids(inventory_get_objects(player_get_inventory(game->player[0]))) < inventory_get_maxObjs(player_get_inventory(game->player[0])))
    {
      s = game_get_space(game, player_location);
      o = game_get_object(game, id_obj_taken);
      obj_loc = game_get_object_location(game, id_obj_taken);
      
      /* Error control*/
      if (s == NULL)
      {
        dialogue_set_error(game->dialogue, E_TAKE, NULL, o, NULL);
        st = ERROR;
      }

      /* Error control*/
      if (o == NULL)
      {
        dialogue_set_error(game->dialogue, E_TAKE, NULL, o, NULL);
        st = ERROR;
      }

      /* Error control*/
      if (player_location != obj_loc)
      {
        dialogue_set_error(game->dialogue, E_TAKE, NULL, o, NULL);
        st = ERROR;
      }

      if (game_set_object_location(game, obj_get_id(o), NO_ID) == ERROR)
      /* Error control */
      {
        dialogue_set_error(game->dialogue, E_TAKE, NULL, o, NULL);
        st = ERROR;
      }

      /* Error control */
      if (player_add_object(game->player[MAX_PLAYERS - 1], o) == ERROR)
      {
        dialogue_set_error(game->dialogue, E_TAKE, NULL, o, NULL);
        st = ERROR;
      }
      /* Error control */
      if (space_del_objectid(s, id_obj_taken) == ERROR)
      {
        dialogue_set_error(game->dialogue, E_TAKE, NULL, o, NULL);
        st = ERROR;
      }
      
      if (id_obj_taken == 383)
      {
        dialogue_set_command(game->dialogue, DC_TAKE_M, NULL, NULL, NULL);
        player_set_max_health(game_get_player(game, 21), player_get_max_health(game_get_player(game, 21)) + 10);
        player_set_health(game_get_player(game, 21), player_get_health(game_get_player(game, 21)) + 10);
        return st;
      }

      if (id_obj_taken == 384)
      {
        dialogue_set_command(game->dialogue, DC_TAKE_S, NULL, NULL, NULL);
        player_set_baseDmg(game_get_player(game, 21), player_get_baseDmg(game_get_player(game, 21)) + 1);
        return st;
      }

      if (id_obj_taken == 380)
      {
        dialogue_set_command(game->dialogue, DC_TAKE, NULL, o, NULL);
        player_set_crit(game_get_player(game, 21), object_get_crit(obj_taken));
        return st;
      }
      
      dialogue_set_command(game->dialogue, DC_TAKE, NULL, o, NULL);
      return st;
    }
  }
  
  dialogue_set_error(game->dialogue, E_TAKE, NULL, o, NULL);
  st=ERROR;
  return st;
}

/**
 * @brief It executes DROP command in game.
 * 
 * This command is for dropping the object that carries the player
 * on the current position. It requires the name of the object to be dropped
 * to work correctly
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_drop(Game *game, char *arg)
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS - 1]);
  Id obj_id = NO_ID;
  Object *obj;
  STATUS st = OK;
  Space *s = NULL;
  Object *o = NULL;

  obj = game_get_object_byName(game, arg);
  obj_id = obj_get_id(obj);

  /* Error control */
  if (obj_id != obj_get_id(obj) || inventory_has_id(player_get_inventory(game->player[MAX_PLAYERS - 1]), obj_id) == FALSE)
  {
    dialogue_set_error(game->dialogue, E_DROP, NULL, o, NULL);
    st = ERROR;
  }

  /* Error control*/
  if (player_get_inventory(game->player[MAX_PLAYERS - 1]) == NULL)
  {
   dialogue_set_error(game->dialogue, E_DROP, NULL, o, NULL);
   st = ERROR;
  }

  s = game_get_space(game, player_location);
  /* Error control*/
  if (s == NULL)
  {
     dialogue_set_error(game->dialogue, E_DROP, NULL, o, NULL);
     st = ERROR;
  }

  o = game_get_object(game, obj_id);
  /* Error control*/
  if (o == NULL)
  {
     dialogue_set_error(game->dialogue, E_DROP, NULL, o, NULL);
    st = ERROR;
  }

  /* Error control */
  if (space_add_objectid(s, obj_get_id(o)) == ERROR)
  {
     dialogue_set_error(game->dialogue, E_DROP, NULL, o, NULL);
    st = ERROR;
  }

  /* Error control */
  if (game_set_object_location(game, obj_get_id(o), space_get_id(s)) == ERROR)
  {
     dialogue_set_error(game->dialogue, E_DROP, NULL, o, NULL);
    st = ERROR;
  }
  /* Error control */
  if (player_del_object(game->player[MAX_PLAYERS - 1], obj_id) == ERROR)
  {
     dialogue_set_error(game->dialogue, E_DROP, NULL, o, NULL);
    st = ERROR;
  }

  /* If the object is the ladder or Candle_1(Turnedon==TRUE and are dropped in the correct space, make them not movable) */
  if((obj_id == 397 && space_get_id(s) == 11) || (obj_id==394 && space_get_id(s)==13)){
    object_set_movable(obj, FALSE);

    if (obj_id == 397)
    {
      link_set_status(game_get_link(game, space_get_link(s, U)), OPEN_L);
    }
    /*Puzzle completed*/
    else 
    {
      link_set_status(game_get_link(game, 526), OPEN_L);
      dialogue_set_command(game->dialogue, DC_PUZZLE, NULL, NULL, NULL);
      return st;
    }

  }

  dialogue_set_command(game->dialogue, DC_DROP, NULL, o, NULL);
  return st;
}

/**
 * @brief It executes ATTACK command in game.
 * 
 * This command allows the player to engage in combat with an enemy.
 * The deciding factor is up to chance, a random number will determine
 * whether the player or the enemy won that round resulting in the loser
 * getting his health reduced by 1
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_attack(Game *game, char *arg)
{
  int rand_num = 0, rand_crit_player = 0, rand_crit_enemy = 0;
  Id player_loc = player_get_location(game->player[MAX_PLAYERS - 1]);
  Enemy *enemy = game_get_enemyWithPlayer(game, player_loc);
  Id enemy_loc = enemy_get_location(enemy);
  
  int player_crit = player_get_crit(game->player[MAX_PLAYERS - 1]);
  int player_baseDmg = player_get_baseDmg(game->player[MAX_PLAYERS - 1]);

  int enemy_crit = enemy_get_crit(enemy);
  int enemy_baseDmg = enemy_get_baseDmg(enemy);

  Object *Sword1 = game_get_object_byName(game, "Sword1");
  Object *Sword2 = game_get_object_byName(game, "Sword2");

  Id id_Sword1 = obj_get_id(Sword1) ;
  Id id_Sword2 = obj_get_id(Sword2) ;

  int hit_chance=5;
 

  srand(time(NULL));

  rand_num = rand() % 10;
  rand_crit_player = rand() % 10;
  rand_crit_enemy = rand() % 10;

  /* Error control */
  if(!enemy)
  {
     dialogue_set_error(game->dialogue, E_ATTACK, NULL, NULL, NULL);
    return ERROR;
  }

  /* Error control */
  if (enemy_get_health(enemy) == 0)
  {
    dialogue_set_error(game->dialogue, E_ATTACK, NULL, NULL, NULL);
    return ERROR;
  }

  /* Error control */
  if (player_loc == NO_ID || enemy_loc == NO_ID)
  {
    dialogue_set_error(game->dialogue, E_ATTACK, NULL, NULL, NULL);
    return ERROR;
  }

  /* Error control */
  if (player_loc != enemy_loc)
  {
    dialogue_set_error(game->dialogue, E_ATTACK, NULL, NULL, NULL);
    return ERROR;
  }


  /* Changing the base dmg if it is a crit from the player*/
  if(rand_crit_player < player_crit){
    player_baseDmg = player_baseDmg*2;
  }
  if(rand_crit_enemy < enemy_crit){
    enemy_baseDmg = enemy_baseDmg*2;
    dialogue_set_command(game->dialogue, DC_ATTACK_CRITICAL, NULL, NULL, NULL);
  }

/*Basically if a player has either sword, hit chance is increased, each attack removes one durability, after 3 attacks sword must be destroyed*/
if(player_has_object(game->player[MAX_PLAYERS - 1], id_Sword1))
  {
     hit_chance= hit_chance-2;
    object_set_durability(Sword1, (object_get_durability(Sword1)-1));
    if(object_get_durability(Sword1)<=0){
      inventory_remove_object(player_get_inventory(game->player[MAX_PLAYERS - 1]), id_Sword1);
      dialogue_set_command(game->dialogue, DC_SBROKE, NULL, NULL, NULL);
    }
  }
  else if(player_has_object(game->player[MAX_PLAYERS - 1], id_Sword2))
  {
    hit_chance= hit_chance-2;
    object_set_durability(Sword2, (object_get_durability(Sword2)-1));
     if(object_get_durability(Sword1)<=0){
      inventory_remove_object(player_get_inventory(game->player[MAX_PLAYERS - 1]), id_Sword2);
      dialogue_set_command(game->dialogue, DC_SBROKE, NULL, NULL, NULL);
      
    }
  }

  if(enemy_loc != 11){
  /*Player wins if rand_num es > 5, else, they lose a life as the enemy won that round*/
    if (rand_num > hit_chance)
    {
      enemy_set_health(enemy, (enemy_get_health(enemy) - player_baseDmg));
      dialogue_set_command(game->dialogue, DC_ATTACK_HIT, NULL, NULL, enemy);
       if (enemy_get_health(enemy) == 0 && enemy_loc==123)
      {
       dialogue_set_command(game->dialogue, DC_END, NULL, NULL, NULL);
      }
    }
    else
    {
      player_set_health(game->player[MAX_PLAYERS - 1], (player_get_health(game->player[MAX_PLAYERS - 1]) - enemy_baseDmg));
      dialogue_set_command(game->dialogue, DC_ATTACK_MISSED, NULL, NULL, enemy);
      if (player_get_health(game->player[MAX_PLAYERS - 1]) == 0)
      {
       dialogue_set_command(game->dialogue, DC_GOVER, NULL, NULL, NULL);
        game_is_over(game);
      }
      
    }

  }
  else{
    player_set_health(game->player[MAX_PLAYERS - 1], (player_get_health(game->player[MAX_PLAYERS - 1]) - enemy_baseDmg));
    dialogue_set_command(game->dialogue, DC_HIM, NULL, NULL, NULL);
    enemy_set_name(enemy, "HIM");
    if (player_get_health(game->player[MAX_PLAYERS - 1]) == 0)
      {
       dialogue_set_command(game->dialogue, DC_GOVER, NULL, NULL, NULL);
        game_is_over(game);
      }
  }



  

  return OK;
}


/**
 * @brief It executes MOVE command in game.
 * 
 * Another way to move, commands move n,s,e,w,u,d
 * to north, south, east, west, up or down respectively
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_move(Game *game, char *arg)
{
  char *west[2] = {"w", "West"};
  char *north[2] = {"n", "North"};
  char *south[2] = {"s", "South"};
  char *east[2] = {"e", "East"};
  char *up[2] = {"u", "Up"};
  char *down[2] = {"d", "Down"};
  STATUS st = ERROR;
  Space *s=NULL;


  if (strcasecmp(arg, west[0]) == 0 || strcasecmp(arg, west[1]) == 0)
  {
    /* Moving west */
    st = game_command_movement(game, W);
    s = game_get_space(game, player_get_location(game->player[MAX_PLAYERS-1]));
    dialogue_set_command(game->dialogue, DC_MOVE_W, s, NULL, NULL);

    if (st==ERROR){
      dialogue_set_error(game->dialogue, E_MOVE_W, s, NULL, NULL);
    }
  }
  else if (strcasecmp(arg, north[0]) == 0 || strcasecmp(arg, north[1]) == 0)
  {
    /* Moving north */
    st = game_command_movement(game, N);
    s = game_get_space(game, player_get_location(game->player[MAX_PLAYERS-1]));
    dialogue_set_command(game->dialogue, DC_MOVE_N, s, NULL, NULL);

     if (st==ERROR){
      dialogue_set_error(game->dialogue, E_MOVE_N, s, NULL, NULL);
    }
  }
  else if (strcasecmp(arg, south[0]) == 0 || strcasecmp(arg, south[1]) == 0)
  {
    /* Moving south */
    st = game_command_movement(game, S);
    s = game_get_space(game, player_get_location(game->player[MAX_PLAYERS-1]));
    if( player_get_location(game->player[MAX_PLAYERS-1])!=123){
      dialogue_set_command(game->dialogue, DC_MOVE_S, s, NULL, NULL);
    }
    else{
       dialogue_set_command(game->dialogue, DC_BOSS, NULL, NULL, NULL);
    }

    if (st==ERROR){
      dialogue_set_error(game->dialogue, E_MOVE_S, s, NULL, NULL);
    }
  }
  else if (strcasecmp(arg, east[0]) == 0 || strcasecmp(arg, east[1]) == 0)
  {
    /* Moving east */
    st = game_command_movement(game, E);
    s = game_get_space(game, player_get_location(game->player[MAX_PLAYERS-1]));
    dialogue_set_command(game->dialogue, DC_MOVE_E, s, NULL, NULL);

     if (st==ERROR){
      dialogue_set_error(game->dialogue, E_MOVE_E, s, NULL, NULL);
    }
  }
  else if (strcasecmp(arg, up[0]) == 0 || strcasecmp(arg, up[1]) == 0)
  {
    /* Moving up */
    st = game_command_movement(game, U);
    s = game_get_space(game, player_get_location(game->player[MAX_PLAYERS-1]));
    dialogue_set_command(game->dialogue, DC_MOVE_U, s, NULL, NULL);

     if (st==ERROR){
      dialogue_set_error(game->dialogue, E_MOVE_U, s, NULL, NULL);
    }
  }
  else if (strcasecmp(arg, down[0]) == 0 || strcasecmp(arg, down[1]) == 0)
  {
    /* Moving down */
    st = game_command_movement(game, D);
    s = game_get_space(game, player_get_location(game->player[MAX_PLAYERS-1]));
    dialogue_set_command(game->dialogue, DC_MOVE_D, s, NULL, NULL);

     if (st==ERROR){
      dialogue_set_error(game->dialogue, E_MOVE_D, s, NULL, NULL);
    }
  }
  else
  {
    st = ERROR;
  }

  return st;
}

/**
 * @brief It executes the movement from a move command in game.
 * @author Miguel Soto
 * 
 * @param game pointer to game struct
 * @param dir movement direction
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_movement(Game *game, DIRECTION dir)
{
  Id player_location = NO_ID, player_id = NO_ID;
  Space *s = NULL;
  Link *l = NULL;
  STATUS st = OK;
  if (!game || dir == ND)
  {
   st = ERROR;
  }

  player_location = player_get_location(game->player[MAX_PLAYERS - 1]);
  player_id = player_get_id(game->player[MAX_PLAYERS - 1]);
  if (player_location == NO_ID || player_id == NO_ID)
  {
    st = ERROR;
  }
  
  s = game_get_space(game, player_location);
  if (!s)
  {
    st = ERROR;
  }
  
  l = game_get_link(game, space_get_link(s, dir));
  if (!l)
  {
    st = ERROR;
  }
  
  if (link_get_status(l) == OPEN_L)
  {
    game_set_player_location(game, player_id, link_get_destination(l));
    return st;
  }
  else
  {
    /* Link is closed */
    st = ERROR;
    return st;
  }
}


/**
 * @brief It executes INSPECT command in game.
 * 
 * Changes the description of game to the one user wanted
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_inspect(Game *game, char *arg)
{
  Object *obj = game_get_object_byName(game, arg);
  STATUS st = OK;

  /*SPACE CASE*/
  if (strcmp(arg, "space") == 0 || strcmp(arg, "s") == 0)
  {
    if(space_get_light_status(game_get_space(game, player_get_location(game->player[MAX_PLAYERS - 1]))) == BRIGHT){
      dialogue_set_command(game->dialogue, DC_INSPECT_S,game_get_space(game, player_get_location(game->player[MAX_PLAYERS - 1])) , NULL, NULL);
      game->inspection = (char *)space_get_long_description(game_get_space(game, player_get_location(game->player[MAX_PLAYERS - 1])));
    }
    else{
      dialogue_set_error(game->dialogue, E_INSPECT, NULL, NULL, NULL);
    
      game->inspection = "El lugar esta muy oscuro, no puedes ver nada";
    }
    
    return st;
  }

  /*OBJECT CASE*/
  else
  {
    if (arg == NULL)
    {
      dialogue_set_error(game->dialogue, E_INSPECT, NULL, NULL, NULL);
      game->inspection = " ";
      st = ERROR;
    }

    if (obj == NULL)
    {
      dialogue_set_error(game->dialogue, E_INSPECT, NULL, NULL, NULL);
      game->inspection = " ";
      st = ERROR;
    }
    if (player_has_object(game->player[0], obj_get_id(obj)) == FALSE && player_get_location(game->player[0]) != obj_get_location(obj))
    {
       dialogue_set_error(game->dialogue, E_INSPECT, NULL, NULL, NULL);
      st = ERROR;
    }
    game->inspection = (char *)obj_get_description(obj);
    dialogue_set_command(game->dialogue, DC_INSPECT_O, NULL, obj, NULL);
    return st;
  }
  return st;
}

/**
 * @brief It executes SAVE command in game.
 * 
 * Creates a file with the info of the game
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_save(Game* game, char *arg){
  dialogue_set_command(game->dialogue, DC_SAVE, NULL, NULL, NULL);
  return game_managment_save(arg, game);
}

/**
 * @brief It executes LOAD command in game.
 * 
 * Generates a new game throught a file 
 * 
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_load(Game* game, char *arg){
  STATUS st = OK;
  if(strcasecmp(arg, "savedata.dat") != 0 && strcasecmp(arg, "hormiguero.dat") != 0){
    dialogue_set_error(game->dialogue, E_LOAD, NULL, NULL, NULL);
    st = ERROR;
  }

 st = game_managment_load(arg, game);
 dialogue_set_command(game->dialogue, DC_LOAD, NULL, NULL, NULL);
 return st;
}

/**
 * @brief It executes TURNON command in game
 * @author Miguel Soto
 *
 * It turn on an object so it iluminates.
 *
 * @param game pointer to game struct.
 * @param arg string with command argument.
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_turnon(Game *game, char *arg)
{
  Object *obj = NULL;
  Id player_loc = NO_ID;

  printf("**\nEntrando en turnon\n");
  if (!game || !arg)
  {
    dialogue_set_error(game->dialogue, E_TON, NULL, NULL, NULL);
    return ERROR;
  }

  printf("Getting obj\n");
  obj = game_get_object_byName(game, arg);
  if (!obj)
  {
    dialogue_set_error(game->dialogue, E_TON, NULL, NULL, NULL);
    printf("ERROR Obj is NULL\n**\n");
    return ERROR;
  }

  player_loc = player_get_location(game->player[0]);
  if (player_loc == NO_ID)
  {
    dialogue_set_error(game->dialogue, E_TON, NULL, NULL, NULL);
    return ERROR;
  }
  
  if (player_has_object(game->player[MAX_PLAYERS-1], obj_get_id(obj)) == FALSE)
  {
    dialogue_set_error(game->dialogue, E_TON, NULL, NULL, NULL);
    return ERROR;
  }
  printf("Checking obj properties\n");
  if (object_get_illuminate(obj) == FALSE || object_get_turnedon(obj) == TRUE)
  {
    dialogue_set_error(game->dialogue, E_TON, NULL, NULL, NULL);
    /* Object has not iluminate attribute or object is already iluminated*/
    printf("ERROR object properties\n**\n");
    return ERROR;
  }
  else if (space_get_fire(game_get_space(game, player_loc)) == FALSE)
  {
    dialogue_set_error(game->dialogue, E_TON, NULL, NULL, NULL);
    printf("There is no fire in space\n");
    return ERROR;
  }
  
  dialogue_set_command(game->dialogue, DC_TON, NULL, obj, NULL);
  printf("Calling object_set_turnon");
  return object_set_turnedon(obj, TRUE);
}

/**
 * @brief It executes TURN OFF command in game
 * @author Miguel Soto
 *
 * It turn off an object so it stop to iluminate.
 *
 * @param game pointer to game struct.
 * @param arg string with command argument.
 * @return OK if everything goes well or ERROR if there was any mistake .
 */
STATUS game_command_turnoff(Game *game, char *arg)
{
  Object *obj = NULL;

  printf("**\nEntrando en turnon\n");
  if (!game || !arg)
  {
    dialogue_set_error(game->dialogue, E_TOFF, NULL, NULL, NULL);
    return ERROR;
  }

  printf("Getting obj\n");
  obj = game_get_object_byName(game, arg);
  if (!obj)
  {
    dialogue_set_error(game->dialogue, E_TOFF, NULL, NULL, NULL);
    printf("ERROR Obj es NULL\n**\n");
    return ERROR;
  }

  if (player_has_object(game->player[MAX_PLAYERS-1], obj_get_id(obj)) == FALSE)
  {
    dialogue_set_error(game->dialogue, E_TOFF, NULL, NULL, NULL);
    return ERROR;
  }
  printf("Checking obj properties\n");
  if (object_get_illuminate(obj) == FALSE || object_get_turnedon(obj) == FALSE)
  {
    dialogue_set_error(game->dialogue, E_TOFF, NULL, NULL, NULL);
    /* Object has not iluminate attribute or object is already not iluminated*/
    printf("ERROR object properties\n**\n");
    return ERROR;
  }

  dialogue_set_command(game->dialogue, DC_TOFF, NULL, obj, NULL);
  printf("Calling object_set_turnon FALSE object properties\n**\n");
  return object_set_turnedon(obj, FALSE);
}

/**
 * @brief It executes OPEN command in game
 * @author Miguel Soto
 * 
 * It opens a link with an object.
 * 
 * @param game pointer to game struct.
 * @param link_name string with link name that is about to be open.
 * @param obj_name string with object name that opens link.
 * @return OK if everything goes well or ERROR if there was any mistake .
 */
STATUS game_command_open(Game *game, char *link_name, char *obj_name)
{
  Link *l = NULL;
  Object *obj = NULL;
  Id obj_open_link = NO_ID;

  if (!game || !link_name || !obj_name)
  {
    dialogue_set_error(game->dialogue, E_OPEN, NULL, NULL, NULL);
    return ERROR;
  }  

  l = game_get_link_byName(game, link_name);
  obj = game_get_object_byName(game, obj_name);
  if (!l || !obj)
  {
    dialogue_set_error(game->dialogue, E_OPEN, NULL, NULL, NULL);
    return ERROR;
  }

  if (link_get_status(l) == OPEN_L || player_has_object(game->player[0], obj_get_id(obj)) == FALSE)
  {
    /* Link is already open */
    dialogue_set_error(game->dialogue, E_OPEN, NULL, NULL, NULL);
    return ERROR;
  }

  obj_open_link = object_get_open(obj);

  if (link_get_id(l) == obj_open_link && player_get_location(game->player[0]) == link_get_start(l))
  {
    dialogue_set_command(game->dialogue, DC_OPEN, game_get_space(game,player_get_location(game->player[MAX_PLAYERS - 1])), NULL, NULL) ;
    inventory_remove_object(player_get_inventory(game->player[0]),obj_get_id(obj));
    obj_set_location(obj, -1);
    return link_set_status(l, OPEN_L);
  }

  dialogue_set_error(game->dialogue, E_OPEN, NULL, NULL, NULL);
  return ERROR;
}

/**
 * @brief It executes USE command in game.
 *
 * Uses a given object
 *
 * @param game pointer to game struct
 * @param arg string with command argument
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_command_use(Game *game, char *arg)
{
  Object *obj = NULL;
  Id id = NO_ID;
  Obj_type type = UNKNOWN_TYPE;
  Player *player = NULL;
  STATUS st = OK;

  printf("**\nEntrando use\n");

  if (!game || !arg)
  {
    dialogue_set_error(game->dialogue, E_USE, NULL, NULL, NULL);
    st = ERROR;
    return st;
  }

  obj = game_get_object_byName(game, arg);
  printf("Getting obj\n");

  if (obj == NULL)
  {
    dialogue_set_error(game->dialogue, E_USE, NULL, NULL, NULL);
    printf("Obj es NULL\n**\n");
    st = ERROR;
    return st;
  }

  printf("Gettin id & player\n");
  id = obj_get_id(obj);
  player = game_get_player(game, 21);
  
  
  if (id == NO_ID || !player)
  {
    dialogue_set_error(game->dialogue, E_USE, NULL, NULL, NULL);
    printf("Id obj es NO_ID or player == NULL\n**\n");
    st = ERROR;
    return st;
  }

  printf("Viendo tipo object\n");
  type = obj_get_type(id);

  printf("Viendo si el player tiene el objeto\n");
  if (type != BED)
  {
    if (inventory_has_id(player_get_inventory(player), id) == FALSE)
    {
      dialogue_set_error(game->dialogue, E_USE, NULL, NULL, NULL);
      printf("No tiene el objeto\n**\n");
      st = ERROR;
      return st;
    }
  }
  else if (type == BED)
  {
    if (space_has_object(game_get_space(game, player_get_location(player)), id) == FALSE)
    {
      dialogue_set_error(game->dialogue, E_USE, NULL, NULL, NULL);
      printf("No tiene el objeto\n**\n");
      st = ERROR;
      return st;
    }
  }


  if (type == APPLE && st == OK) /*Case apples*/
  {
    printf("Es manzana\n");
    st = inventory_remove_object(player_get_inventory(player), id);
    st = player_set_health(player, player_get_health(player) + 1);

    st = obj_set_location(game_get_object(game, id), -1);
    dialogue_set_command(game->dialogue, DC_USE_APPLE, NULL, NULL, NULL);

    return st;
  }
  else if (type == ELIXIR && st == OK) /*Case elixir*/
  {
    printf("Es elixir\n");
    st = inventory_remove_object(player_get_inventory(player), id);
    st = player_set_health(player, player_get_health(player) + 2);

    st = obj_set_location(game_get_object(game, id), -1);
    dialogue_set_command(game->dialogue, DC_USE_APPLE, NULL, NULL, NULL);

    return st;
  }
  else if (type == ARMOR && st == OK) /*Case armour*/
  {
    printf("Es armadura\n");
    st = inventory_remove_object(player_get_inventory(player), id);
    st = player_set_max_health(player, player_get_max_health(player) + 1);

    st = obj_set_location(game_get_object(game, id), -1);
    dialogue_set_command(game->dialogue, DC_USE_ARMOR, NULL, NULL, NULL);

    return st;
  }
  else if (type == HOOK && st == OK) /*Case hook*/
  {
    printf("Es hook\n");
    st = inventory_remove_object(player_get_inventory(player), id);
    if (player_get_location(player) == 125)
    {
      st = obj_set_location(game_get_object(game, 398), -1);
      st = inventory_add_object(player_get_inventory(player), 398);

      st = obj_set_location(game_get_object(game, id), -1);
      dialogue_set_command(game->dialogue, DC_USE_HOOK, NULL, NULL, NULL);

      return st;
    }
  }
  else if (type == BED && st == OK) /*Case bed*/
  {
    printf("Es cama\n");
    /*st = set_del_id(space_get_objects(game_get_space(game, player_get_location(player))), id);*/
    if (game_get_time(game) == DAY)
    {
      st = game_set_time(game, NIGHT);
    }
    else
    {
      st = game_set_time(game, DAY);
    }

    dialogue_set_command(game->dialogue, DC_USE_BED, NULL, NULL, NULL);

    return st;
  } else if (type == BREAD_CRUMBS)
  {
    if (player_get_location(player) == 11) 
    {
      dialogue_set_command(game->dialogue, DC_BREAD, NULL, NULL, NULL);
      st = inventory_remove_object(player_get_inventory(player), id);
      return st;
    }
    else 
    {
      st = ERROR;
      return st;
    }
  }

  dialogue_set_error(game->dialogue, E_USE, NULL, NULL, NULL);
  printf("No es ninguno: %d", (int) type);
  st = ERROR;
  return st;  
}
/**
 * @brief It executes MOVE event
 * 
 * Apple or Elixir will appear on the player's room 
 * 
 * @param game pointer to game struct
 * @return OK if event happens, ERROR if not
 */
STATUS game_event_move(Game *game){
  
  Object *elixir;
  Id id, current_id, elixir_loc;
  Space *current_location, *elixir_space;


  if(game->day_time == DAY || game->last_cmd != MOVE){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR;
  }

  elixir = game_get_object_byName(game, "Elixir4");

  if(elixir == NULL || obj_get_location(elixir) == -1){
    elixir = game_get_object_byName(game, "Elixir6");
    if(elixir == NULL || obj_get_location(elixir) == -1){
      dialogue_set_event(game->dialogue, DE_NOTHING);
      return ERROR;
    }
  }

  current_id = player_get_location(game->player[MAX_PLAYERS - 1]);
  current_location = game_get_space(game, current_id);
  elixir_loc = obj_get_location(elixir);
  elixir_space = game_get_space(game, elixir_loc);

  id = obj_get_id(elixir);

  if(space_del_objectid(elixir_space, id) == ERROR){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR; 
  }

  if(space_add_objectid(current_location, id)==ERROR){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR; 
  }

  if(obj_set_location(elixir, current_id)){
    dialogue_set_event(game->dialogue, DE_MOVEOBJ);
    return ERROR; 
  }

  dialogue_set_event(game->dialogue, DE_MOVEOBJ);
  return OK; 
}

/**
 * @brief It executes TRAP event
 * 
 * Player losses 1 HP
 * 
 * @param game pointer to game struct
 * @return OK if event happens, ERROR if not
 */
STATUS game_event_trap(Game *game){

  /*Events only Occurs at Night*/
  if(game->day_time == DAY|| game->last_cmd != MOVE){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR;
  }

  /*Player losses one of HP*/
  player_set_health(game->player[MAX_PLAYERS - 1], (player_get_health(game->player[MAX_PLAYERS - 1]) - 1));

  dialogue_set_event(game->dialogue, DE_TRAP);
  return OK;
}

/**
 * @brief It executes SLIME event
 * 
 * An slime appear on the players location 
 * 
 * @param game pointer to game struct
 * @return OK if event happens, ERROR if not
 */
STATUS game_event_slime(Game *game){
  
  Enemy *slime = game_get_enemy_byName(game, "Rat1");
  Id slime_loc = enemy_get_location(slime);
  
    if(slime == NULL){
    slime = game_get_enemy_byName(game, "Rat2");
  }
  /*Events only Occurs at Night*/
  if(game->day_time == DAY|| game->last_cmd == ATTACK){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR;
  }

  /*In case slime is already dead*/
  if(slime_loc == -1){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR;
  }

  /*Sets the enemy on players location*/
  enemy_set_location(slime, player_get_location(game->player[MAX_PLAYERS - 1]));

  dialogue_set_event(game->dialogue, DE_SLIME);
  return OK;
}

/**
 * @brief It executes DAYNIGHT event
 * 
 * Changes day to night and night to day 
 * 
 * @param game pointer to game struct
 * @return OK if event happens, ERROR if not
 */
STATUS game_event_daynight(Game *game){

  if(game_get_time(game) == DAY){
    dialogue_set_event(game->dialogue, DE_NIGHT);
    game_set_time(game, NIGHT);
  }
  else if(game_get_time(game) == NIGHT){
    dialogue_set_event(game->dialogue, DE_DAY);
    game_set_time(game, DAY);
  }

  return OK;
}

/**
 * @brief It executes SPAWN event
 * 
 * Player tps to entrance
 * 
 * @param game pointer to game struct
 * @return OK if event happens, ERROR if not
 */
STATUS game_event_spawn(Game *game){

  /*Events only Occurs at Night*/
  if(game->day_time == DAY || game->last_cmd != MOVE){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR;
  }
  
  /*You cannot get lost while attacking*/
  if(game->last_cmd == ATTACK){
    dialogue_set_event(game->dialogue, DE_NOTHING);
    return ERROR;
  }

  /*Sets player to the initial room*/
  player_set_location(game->player[0], SPACE_INITIAL);

  dialogue_set_event(game->dialogue, DE_SPAWN);
  return OK;
}

/*Function that gets the enemy id based on the position it is located in the enemy array located in the game structure */
Id game_get_enemy_id(Game *game, int num)
{

  /* Error control */
  if (!game || num < 0 || num > MAX_ENEMYS - 1)
  {
    return NO_ID;
  }

  return (Id)enemy_get_id(game->enemy[num]);
}

Id game_get_player_id(Game *game)
{

  /* Error control */
  if (!game)
  {
    return NO_ID;
  }

  return (Id)player_get_id(game->player[MAX_PLAYERS - 1]);
}

/** 
 * Function that gets the object id based on the position it is located in 
 * the object array located in the game structure 
 */
Id game_get_object_id(Game *game, int num)
{

  /* Error control */
  if (!game || num < 0 || num > MAX_ENEMYS - 1)
  {
    return NO_ID;
  }

  return (Id)obj_get_id(game->object[num]);
}

Game *game_alloc2()
{

  Game *game = NULL;

  game = (Game *)malloc(sizeof(Game));

  /* Error control */
  if (!game)
  {
    fprintf(stderr, "Error saving memory for game(game_create)");
    return NULL;
  }
  game->inspection = "\0";
  game->day_time = DAY;
  game->last_event = NOTHING;
  game->dialogue = dialogue_create();

  return game;
}
STATUS game_save(char *filename, Game* game)
{
 int i = 0;
 Inventory *player_inventory = player_get_inventory(game_get_player(game, 21));
 FILE *file = NULL;
 file = fopen("savedata.dat", "w");
 fclose(file);

  /*Spaces*/
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print_save("savedata.dat", game->spaces[i]);
  }

  /*Objects*/
  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    obj_print_save("savedata.dat", game->object[i]);
  }

  /*Players*/
  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    player_print_save("savedata.dat", game->player[i]);
  }

  /*Enemies*/
  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    enemy_print_save("savedata.dat", game->enemy[i]);
  }

  /*Links*/
  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    link_print_save("savedata.dat", game->links[i]);
  }

  /*Inventory*/

  inventory_print_save("savedata.dat", player_inventory, 21);

  return OK;
}

Dialogue *game_get_dialogue(Game *game)
{
  if (!game)
  {
    return NULL;
  }

  return game->dialogue;
}

STATUS game_update_ls(Game *game)
{
  int i = 0;
  Inventory *in = NULL;
  Player *p = NULL;
  Object *o = NULL;
  Space *s = NULL;

  if (!game)
  {
    return ERROR;
  }

  p = game_get_player(game, 21);
  in = player_get_inventory(p);
  s = game_get_space(game, player_get_location(p));

  if (!p || !in || !s)
  {
    return ERROR;
  }

  if (space_get_light_status(s) == DARK)
  {
    for (i = 0; i < set_get_nids(inventory_get_objects(in)); i++)
    {
      o = game_get_object(game,set_get_ids_by_number(inventory_get_objects(in), i));

      if (o != NULL)
      {
        if (object_get_turnedon(o) == TRUE)
        {
          if (space_set_light_status(s, BRIGHT) == ERROR)
          {
            return ERROR;
          }
          break;
        }
      }
    }
  }

  return OK;
}

STATUS game_update_time(Game *game)
{
  int i = 0;
  Space *s = NULL;
  Id id = NO_ID;
  Time time;

  if (!game)
  {
    return ERROR;
  }

  time = game_get_time(game);

  for (i = 0; i < MAX_SPACES; i++)
  {
    if ((s = game->spaces[i]) != NULL && (id = space_get_id(s)) != NO_ID)
    {
      if (id != 121 && id != 125)
      {
        if (time == NIGHT)
        {
          if (space_set_light_status(s, DARK) == ERROR)
          {
            return ERROR;
          }
        } else 
        {
          if (space_set_light_status(s, BRIGHT) == ERROR)
          {
            return ERROR;
          }          
        }

      } 
    }
  }   
  return OK;
}

STATUS game_update_object(Game *game)
{
  Enemy *e1 = NULL, *e2 = NULL;
  Object *key1 = NULL, *key2 = NULL;

  if (!game)
  {
    return ERROR;
  }

  e1 = game_get_enemy(game, 42);
  e2 = game_get_enemy(game, 43);
  key1 = game_get_object(game, 399);
  key2 = game_get_object(game, 385);

  if (!e1 || !e2 || !key1 || !key2)
  {
    return ERROR;
  }

  if (enemy_get_health(e1) <= 0 && space_has_object(game_get_space(game, 127), obj_get_id(key1)) == FALSE && enemy_get_location(e1) != NO_ID)
  {
    obj_set_location(key1, 127);
    space_add_objectid(game_get_space(game, 127), obj_get_id(key1));
    enemy_set_health(e1, -1);
    enemy_set_location(e1, -1);
  }

    if (enemy_get_health(e2) <= 0 && space_has_object(game_get_space(game, 126), obj_get_id(key2)) == FALSE && enemy_get_location(e2) != NO_ID)
  {
    obj_set_location(key2, 126);
    space_add_objectid(game_get_space(game, 126), obj_get_id(key2));
    enemy_set_health(e2, -1);
    enemy_set_location(e2, -1);
  }
  
  if (object_get_durability(game_get_object(game, 392)) <= 0)
  {
    inventory_remove_object(player_get_inventory(game_get_player(game, 21)), 392);
    obj_set_location(game_get_object(game, 392), NO_ID);
  }

  if (object_get_durability(game_get_object(game, 393)) <= 0)
  {
    inventory_remove_object(player_get_inventory(game_get_player(game, 21)), 393);
    obj_set_location(game_get_object(game, 393), NO_ID);
  }

  return OK;
}

STATUS game_update_enemy(Game *game)
{
  int i = 0;
  Enemy *e = NULL;

  if (!game)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_ENEMYS; i++)
  {
    e = game->enemy[i];

    if (e)
    {
      if (enemy_get_health(e) <= 0 && enemy_get_location(e) != -1)
      {
        enemy_set_health(e, -1);
        enemy_set_location(e, -1);
      }
    }
  }
  return OK;
}

STATUS game_destroy_load(Game *game)
{
   int i = 0;

   if (!game)
   {
     return ERROR;
   } 

  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    obj_destroy(game->object[i]);
    game->object[i] = NULL;
  }

  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    player_destroy(game->player[i]);
    game->player[i] = NULL;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    enemy_destroy(game->enemy[i]);
    game->enemy[i] = NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    link_destroy(game->links[i]);
    game->links[i] = NULL;
  }

  /*dialogue_destroy(game->dialogue);*/

  return OK;
}

Enemy *game_get_enemy_in_space(Game *game, Id space)
{
  int i;

  if (!game || space == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i]; i++)
  {
    if (enemy_get_location(game->enemy[i]) == space)
    {
      return game->enemy[i];
    }
  }

  return NULL;
}

BOOL update_game_over(Game *game)
{
  if (!game)
  {
    return FALSE;
  }

  if (player_get_health(game_get_player(game, 21)) <= 0)
  {
    return TRUE;
  } else
  {
    return FALSE;
  }
}
