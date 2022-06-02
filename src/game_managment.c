/**
 * @brief It read all game elements from a file.
 *
 * @file game_reader.c
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers, Ignacio Nunez
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/game_managment.h"
/*
STATUS game_add_space(Game *game, Space *space);
STATUS game_add_object(Game *game, Object *obj);
STATUS game_add_player(Game *game, Player *p);
STATUS game_add_enemy(Game *game, Enemy *e);
STATUS game_add_link(Game *game, Link *l);
Id game_get_space_id_at(Game *game, int position);
STATUS game_set_player_location(Game *game, Id player_id, Id space_id);
STATUS game_set_object_location(Game *game, Id obj_id, Id space_id);
STATUS game_set_enemy_location(Game *game, Id enemy_id, Id space_id);
*/
/**
 * Funciones privadas
 */
STATUS game_load_spaces(Game *game, char *filename);
STATUS game_load_objs(Game *game, char *filename);
STATUS game_load_players(Game *game, char *filename);
STATUS game_load_enemy(Game *game, char *filename);
STATUS game_load_link(Game *game, char *filename);
STATUS game_load_inventory(Game *game, char *filename);
STATUS game_managment_save(char *filename, Game* game);
STATUS game_managment_load(char *filename, Game *game);

GAME_IS_ELEMENT id_type(Id id);

/**
  Game_reader implementacion
*/

/** game_create_from_file  game_create_from_file initializes
 * all of game's members from the filename.dat
 */
STATUS game_create_from_file(Game *game, char *filename)
{

  if (game_create(game) == ERROR)
  {
    return ERROR;
  }

  if (game_load_spaces(game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_load_objs(game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_load_players(game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_load_enemy(game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_load_link(game, filename) == ERROR)
  {
    return ERROR;
  }

  
  if (game_load_inventory(game, filename) == ERROR)
  {
    return ERROR;
  }
  
  /* The player and the object are located in the first space */

  return OK;
}

STATUS game_managment_save(char *filename, Game* game)
{
  STATUS st = OK;

  st = game_save(filename, game);
  return st;
}

STATUS game_managment_load(char *filename, Game *game)
{
  STATUS st = OK;
  
  st = game_destroy_load(game);
  st = game_create_from_file(game, filename);
  return st;
}

/**
 * @brief Loads the spaces of the game
 * @author Modified by Nicolas Victorino
 *
 * @param game pointer to the game
 * @param filename pointer to the file from where spaces are being loaded
 * @return OK if everything goes right or ERROR if something goes wrong
 */
STATUS game_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char brief_description[WORD_SIZE] = "";
  char long_description[WORD_SIZE] = "";
  char *toks = NULL, *aux;
  char **gdesc = NULL;
  Id id = NO_ID;
  Floor floor;
  Light ls;
  BOOL fire;
  Space *space = NULL;
  STATUS status = OK;
  int i, j;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(brief_description, toks);
      toks = strtok(NULL, "|");
      strcpy(long_description, toks);
      toks = strtok(NULL, "|");
      ls = atol(toks);

      gdesc = space_create_gdesc();
      if (gdesc == NULL)
      {
        return ERROR;
      }

      for (i = 0; i < TAM_GDESC_Y; i++)
      {
        aux = strtok(NULL, "|");
        for (j = 0; j < strlen(aux) && j < TAM_GDESC_X; j++)
        {
          gdesc[i][j] = aux[j];
        }
      }

      toks = strtok(NULL, "|");
      floor = atoi(toks);

      toks = strtok(NULL, "|");
      if (atoi(toks) == 1)
      {
        fire = TRUE;
      }
      else
      {
        fire = FALSE;
      }
      

#ifdef DEBUG
      // printf("Leido: %ld|%s|%s\n", id, name, description);
#endif
      space = space_create(id);
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_brief_description(space, brief_description);
        space_set_long_description(space, long_description);
        space_set_gdesc(space, gdesc);
        space_set_light_status(space, ls);
        space_set_floor(space, floor);
        space_set_fire(space, fire);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * @brief Loads the objects of the game
 * @author Miguel Soto
 *
 * @param game pointer to game
 * @param filename pointer to the file's name
 * @return OK if everything goes right or ERROR if something goes wrong
 */
STATUS game_load_objs(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, pos = NO_ID;
  Object *obj = NULL;
  BOOL movable, illuminate, turnedon;
  Id dependency, open;
  STATUS status = OK;
  Light light_visible = -1;
  int crit = 0;
  int durability = 0;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  /*Error control*/
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      pos = atol(toks);
      toks = strtok(NULL, "|");
      movable = atoi(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      illuminate = atoi(toks);
      toks = strtok(NULL, "|");
      turnedon = atoi(toks);
      toks = strtok(NULL, "|");
      light_visible = atoi(toks);
      toks = strtok(NULL, "|");
      crit = atoi(toks);
      toks = strtok(NULL, "|");
      durability = atoi(toks);


#ifdef DEBUG
      // printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      obj = obj_create(id);
      if (obj != NULL)
      {
        obj_set_name(obj, name);
        obj_set_description(obj, description);
        obj_set_location(obj, pos);
        object_set_movable(obj, movable);
        object_set_dependency(obj, dependency);
        object_set_open(obj, open);
        object_set_illuminate(obj, illuminate);
        object_set_turnedon(obj, turnedon);
        object_set_light_visible(obj,light_visible);
        object_set_crit(obj, crit);
        object_set_durability(obj, durability);
        
        /*Error control*/
        if (pos != -1)
        {
          if (space_add_objectid(game_get_space(game, pos), id) == ERROR)
          {
            return ERROR;
          }
        }
        game_add_object(game, obj);
      }
    } 
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * @brief Loads the player into the game
 * @author Nicolas Victorino
 *
 * @param game pointer to game
 * @param filename pointer to the file from where it is going to load the player
 * @return OK if everything is right ERROR if something went wrong
 */
STATUS game_load_players(Game *game, char *filename)
{
  int i, j;
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  int objects, health;
  Player *player = NULL;
  STATUS status = OK;
  int crit = 0, base_dmg = 0;
  char *aux, **gdesc = NULL;

  /*Error control*/
  if (!filename)
  {
    return ERROR;
  }

  /*Error control*/
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  /*
  * While the loop reads information in the current line from the file:
  "hormiguero.dat", it divides that line in smaller tokens.
  * Each token has a piece of information, in the following order:
  * ID of the player, name, Id of the object that the player has
  * (NO_ID if it has no object), and location.
  */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atol(toks);
      toks = strtok(NULL, "|");
      objects = atol(toks);
      toks = strtok(NULL, "|");
      crit = atol(toks);
      toks = strtok(NULL, "|");
      base_dmg = atol(toks);
      
      gdesc = player_create_gdesc();
      if (gdesc == NULL)
      {
        return ERROR;
      }

      for (i = 0; i < PLAYER_GDESC_Y; i++)
      {
        aux = strtok(NULL, "|");
        for (j = 0; j < strlen(aux) && j < PLAYER_GDESC_X; j++)
        {
          gdesc[i][j] = aux[j];
        }
      }

      /*If debug is being used, it will print all the information from
        the current player that is being loaded*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld\n", id, name, object, location);
#endif

      /*Defines a private variable called "player" and saves a pointer to player with the given id in it*/
      player = player_create(id);

      /*Error control, and in case everything is fine, it saves the
        information gotten in the prior loop in the newly created player*/
      if (player != NULL)
      {
        player_set_name(player, name);
        player_set_max_inventory(player, objects);
        player_set_location(player, location);
        player_set_health(player, health);
        player_set_crit(player, crit);
        player_set_baseDmg(player, base_dmg);
        player_set_gdesc(player, gdesc);
        game_add_player(game, player);
      }
    }
  }

  /*Error control, if it has given an error at any moment while using the file,
  ferror while make the if condition be true.
  This will change the private status variable declared at the beggining
  of the function from OK to ERROR. */
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * @brief Loads the enemy into the game
 * @author Nicolas Victorino
 *
 * @param game pointer to game
 * @param filename pointer to the file from where it is going to load the enemy
 * @return OK if everything is right ERROR if something went wrong
 */
STATUS game_load_enemy(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  int health;
  Enemy *enemy = NULL;
  STATUS status = OK;
  int crit = 0, base_dmg = 0;
  char *aux, **gdesc = NULL;
  int i, j;

  /*Error control*/
  if (!filename)
  {
    return ERROR;
  }

  /*Error control*/
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  /*
   * While the loop reads information in the current line from the file:
   * "hormiguero.dat", it divides that line in smaller tokens.
   * Each token has a piece of information, in the following order:
   * ID of the enemy, name, and location.
   */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#e:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atol(toks);
      toks = strtok(NULL, "|");
      crit = atol(toks);
      toks = strtok(NULL, "|");
      base_dmg = atol(toks);

      gdesc = enemy_create_gdesc();
      if (gdesc == NULL)
      {
        return ERROR;
      }

      for (i = 0; i < ENEMY_GDESC_Y; i++)
      {
        aux = strtok(NULL, "|");
        for (j = 0; j < strlen(aux) && j < ENEMY_GDESC_X; j++)
        {
          gdesc[i][j] = aux[j];
        }
      }
      /*If debug is being used, it will print all the information
      from the current enemy that is being loaded*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, location);
#endif

      /*Defines a private variable called "enemy" and saves
      a pointer to enemy with the given id in it*/
      enemy = enemy_create(id);

      /*Error control, and in case everything is fine, it saves
      the information gotten in the prior loop in the newly created enemy*/
      if (enemy != NULL)
      {
        enemy_set_name(enemy, name);
        enemy_set_location(enemy, location);
        enemy_set_health(enemy, health);
        enemy_set_crit(enemy, crit);
        enemy_set_baseDmg(enemy, base_dmg);
        enemy_set_gdesc(enemy, gdesc);
        game_add_enemy(game, enemy);
      }
    }
  }

  /*Error control, if it has given an error at any moment
  while using the file, ferror while make the if condition be true.
   This will change the private status variable declared at
   the beggining of the function from OK to ERROR. */
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * @brief Loads the links into the game
 * @author Nicolas Victorino
 *
 * @param game pointer to game
 * @param filename pointer to the file from where it is going to load the enemy
 * @return OK if everything is right ERROR if something went wrong
 */
STATUS game_load_link(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, id_start = NO_ID, id_dest = NO_ID;
  DIRECTION dir = ND;
  LINK_STATUS status = CLOSE;
  Link *link = NULL;
  STATUS st = OK;

  /*Error control*/
  if (!filename)
  {
    return ERROR;
  }

  /*Error control*/
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  /*
  * While the loop reads information in the current line from the file:
  "map.dat", it divides that line in smaller tokens.
  * Each token has a piece of information, in the following order:
  * ID of the link, name, and location.
  */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_start = atol(toks);
      toks = strtok(NULL, "|");
      id_dest = atol(toks);

      toks = strtok(NULL, "|");
      switch (atoi(toks))
      {
      case 0:
        dir = N;
        break;

      case 1:
        dir = S;
        break;

      case 2:
        dir = E;
        break;

      case 3:
        dir = W;
        break;

      case 4:
        dir = U;
        break;

      case 5:
        dir = D;
        break; 

      default:
        dir = ND;
        break;
      }

      toks = strtok(NULL, "|");
      switch (atoi(toks))
      {
      case 1:
        status = OPEN_L;
        break;

      default:
        status = CLOSE;
        break;
      }

      /*If debug is being used, it will print all the information
      from the current link that is being loaded*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, id_start, id_end, dir, status);
#endif

      /*Defines a private variable called "link" and saves a
      pointer to player with the given id in it*/
      link = link_create(id);

      /*Error control, and in case everything is fine, it saves
      the information gotten in the prior loop in the newly created link*/
      if (link != NULL)
      {
        link_set_name(link, name);
        link_set_start(link, id_start);
        link_set_destination(link, id_dest);
        link_set_direction(link, dir);
        link_set_status(link, status);
        space_set_link(game_get_space(game, id_start), id, dir);
        game_add_link(game, link);
      }
    }
  }

  /*Error control, if it has given an error at any moment
   while using the file, ferror while make the if condition be true.
   This will change the private status variable declared
   at the beggining of the function from OK to ERROR. */
  if (ferror(file))
  {
    st = ERROR;
  }

  fclose(file);

  return st;
}

STATUS game_load_inventory(Game *game, char *filename)
{
 FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, id_player = NO_ID;
  STATUS status = OK;

  /*Error control*/
  if (!filename)
  {
    return ERROR;
  }
  /*Error control*/
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  /*
   * While the loop reads information in the current line from the file:
   * "hormiguero.dat", it divides that line in smaller tokens.
   * Each token has a piece of information, in the following order:
   * ID of the object and id of the player.
   */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#i:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      id_player = atol(toks);

      /*If debug is being used, it will print all the information
      from the current enemy that is being loaded*/
#ifdef DEBUG
      printf("Leido: %ld|%ld\n", id, id_player);
#endif

      /*Adds the object to the given player*/
      obj_set_location(game_get_object(game, id), player_get_location(game_get_player(game, id_player)));
      inventory_add_object(player_get_inventory(game_get_player(game, id_player)), id);
    }
  }

  /*Error control, if it has given an error at any moment
  while using the file, ferror while make the if condition be true.
   This will change the private status variable declared at
   the beggining of the function from OK to ERROR. */
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * @brief It indicates which element of the game has the target id
 * @author Miguel Soto
 *
 * @param id target id 
 * @return game elements with the target id
 */
GAME_IS_ELEMENT id_type(Id id)
{
  int first_digit, digits;

  /*Error control*/
  if (id < 0)
  {
    return '\0';
  }

  digits = (int)log10(id);

  first_digit = (int)(id / pow(10, digits));

  if (first_digit == FD_ID_SPACE)
  {
    return IS_SPACE;
  }
  else if (first_digit == FD_ID_PLAYER)
  {
    return IS_PLAYER;
  }
  else if (first_digit == FD_ID_OBJ)
  {
    return IS_OBJECT;
  }
  else if (first_digit == FD_ID_ENEMY)
  {
    return IS_ENEMY;
  }
  /*Error control*/
  else
  {
    return '\0';
  }
}
