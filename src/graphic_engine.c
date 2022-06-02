/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Miguel Soto, Antonio Van-Oers, Nicolas Victorino and Ignacio Nunez
 * @version 3.0
 * @date 06-04-2022
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/graphic_engine.h"
#include "../include/libscreen.h"
#include "../include/command.h"
#include "../include/space.h"
#include "../include/types.h"
#include "../include/enemy.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/inventory.h"
#include "../include/set.h"

#define ROWS 44       /*!< Establish screen size in y dimension */
#define COLUMNS 120   /*!< Establish screen size in x dimension */
#define TAMCELL_X 19  /*!< Establish cell size per line */

/**
 * @brief Graphic engine
 *
 * This struct contains all pointer to the different areas shown in graphics
 */
struct _Graphic_engine
{
  Area *map;      /*!< graphic engine area of the game map */
  Area *descript; /*!< graphic engine area of the description */
  Area *banner;   /*!< graphic engine area of the banner */
  Area *help;     /*!< graphic engine area of help */
  Area *feedback;   /*!< graphic engine area of feedback */
  Area *dialogue; /*!< graphic engine area of dialoge */
  Area *events; /*!< graphic engine area of events */
};

/**
 * graphic_engine_create initializes game's members
 */
Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init(ROWS, COLUMNS);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
    return NULL;

  ge->map = screen_area_init(1, 1, 80, 25);
  ge->descript = screen_area_init(82, 1, 35, 34);
  ge->banner = screen_area_init(30, 27, 19, 1);
  ge->help = screen_area_init(1, 28, 80, 3);
  ge->feedback = screen_area_init(1, 32, 80, 3);
  ge->dialogue = screen_area_init(1, 36, 80, 7);
  ge->events = screen_area_init(82, 36, 35, 7);

  return ge;
}

/**
  * graphic_engine_destroy, using the function screen_area_destroy, 
  * destroys the map, banner, descript, help and feedback 
  * It also frees all the previosly alloc'd memory
  */
void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  screen_area_destroy(ge->dialogue);
  screen_area_destroy(ge->events);

  screen_destroy();
  free(ge);
}

/**
  * Prints the game on the screen, with all its components on the 
  * right position for the user to see the info needed to interact with it
  */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, int st)
{
  /* Variables declaration */
  Id id_act = NO_ID, id_up = NO_ID, id_down = NO_ID, id_left= NO_ID, id_right= NO_ID, aux_obj_id = NO_ID;
  Id player_loc = NO_ID, en_loc[MAX_ENEMYS] = {NO_ID};
  Inventory *player_inventory = NULL;
  int en_health[MAX_ENEMYS] = {0}, player_health = 0;
  Space *space_act = NULL;
  char obj = '\0', obj_l = '\0', obj_r = '\0';
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  char **gdesc = NULL, **gdesc_right = NULL, **gdesc_left = NULL, aux_gdesc[10][10];
  char **enemy_gdesc = NULL;
  char *description;
  char *en_name[MAX_ENEMYS];
  char *inspection, *dialogue, *events;
  char link_up = '\0', link_down = '\0', link_right = '\0', link_left = '\0';
  char *space_name, *space_name2, *space_name3, aux_name1[20] = "", aux_name2[20] = "", blank20[] = "                   ";
  Set *object_set = NULL, *object_set_r = NULL, *object_set_l = NULL;
  Enemy *enemy = NULL;

  /* setting all proper values for each variable */
  player_loc = game_get_player_location(game, 21);
  id_act = player_loc;
  player_inventory = player_get_inventory(game_get_player(game, game_get_player_id(game)));
  player_health = player_get_health(game_get_player(game, game_get_player_id(game)));
  description = (char*) space_get_brief_description(game_get_space(game, player_loc));
  inspection = game_get_inspection(game);

  for(i=0;i<MAX_ENEMYS;i++)
  { 
    /* Error Control */
    if (game_get_enemy(game, game_get_enemy_id(game, i))==NULL)
    {
      break;
    }
    en_health[i] = enemy_get_health(game_get_enemy(game, game_get_enemy_id(game, i)));
    en_name[i] = (char *)enemy_get_name(game_get_enemy(game, game_get_enemy_id(game, i)));
    en_loc[i] = game_get_enemy_location(game, game_get_enemy_id(game, i));
  }

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  
  if (id_act != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_up = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, N)));
    id_down = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, S)));
    id_left = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, W)));
    id_right = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, E)));

    object_set = space_get_objects(game_get_space(game, id_act));
    object_set_r = space_get_objects(game_get_space(game, id_right));
    object_set_l = space_get_objects(game_get_space(game, id_left));

    /* Space to the north of the current space */
    if (id_up != NO_ID)
    {
      obj = ' ';
      for(i = 0; i < set_get_nids(object_set); i++)
      {
        aux_obj_id = set_get_ids_by_number(object_set, i);
        
        if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_act))) ==  FALSE) 
        {
          obj = ' ';
        } else {
          obj = '*';              
          i = set_get_nids(object_set) + 1;
        }
      }

      space_name = (char *)space_get_name(game_get_space(game, id_up));
      strncat(space_name, blank20, 15 - strlen(space_name));
      sprintf(str, "  %.19s   | %s |", blank20, space_name);
      screen_area_puts(ge->map, str);

      sprintf(str, "  %.19s   |                 |", blank20);
      screen_area_puts(ge->map, str);
      sprintf(str, "  %.19s   |        %c        |", blank20, obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  %.19s   |                 |", blank20);
      screen_area_puts(ge->map, str);
      sprintf(str, "  %.19s   +-----------------+", blank20);
      screen_area_puts(ge->map, str);
      
      if (game_get_connection_status(game, id_act, N) == OPEN_L)
      {
        link_up = '^';
      }
      else
      {
        link_up = ' ';
      }

      if (game_get_connection_status(game, id_act, E) == OPEN_L)
      {
        link_right = '>';
      }
      else
      {
        link_right = ' ';
      }

      if (game_get_connection_status(game, id_act, W) == OPEN_L)
      {
        link_left = '<';
      }
      else
      {
        link_left = ' ';
      }

      sprintf(str, "  %.19s            %c", blank20, link_up);
      screen_area_puts(ge->map, str);
    }

    /* Current space */
    if (id_act != NO_ID)
    {
      if (id_up == NO_ID)
      {
        for (i = 0; i < 6; i++)
        {
          sprintf(str, " ");
          screen_area_puts(ge->map, str);
        }
      }
      
      obj = ' ';
      for(i = 0; i < set_get_nids(object_set); i++)
      {
        aux_obj_id = set_get_ids_by_number(object_set, i);

        if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_act))) ==  FALSE) 
        {
          obj = ' ';
        } else {
          obj = '*';              
          i = set_get_nids(object_set) + 1;
        }
      }
      

       /* Checks that there are no other spaces to the left or right */    
      if(id_left==NO_ID && id_right==NO_ID)  
      {
        sprintf(str, "  %.19s   +-----------------+", blank20);
        screen_area_puts(ge->map, str);

        space_name = (char *)space_get_name(game_get_space(game, id_act));
        strncat(space_name, blank20, 15 - strlen(space_name));
        sprintf(str, "  %.19s   | %s |", blank20, space_name);
        screen_area_puts(ge->map, str);

        sprintf(str, "  %.19s   |           gpp0^ | ", blank20);
        screen_area_puts(ge->map, str);

        sprintf(str, "  %.19s   |                 |", blank20);
        screen_area_puts(ge->map, str);

        gdesc = space_get_gdesc(game_get_space(game, id_act));
        enemy = NULL;
        enemy = game_get_enemy_in_space(game, id_act);
        if (enemy)
        {
          enemy_gdesc = enemy_get_gdesc(enemy);
        }
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          if (i < ENEMY_GDESC_Y && enemy)
          {
            sprintf(str, "  %.19s   | %s %s|", blank20, enemy_gdesc[i], gdesc[i]);
          }
          else if (enemy)
          {
            sprintf(str, "  %.19s   |        %s|", blank20, gdesc[i]);
          }
          else
          {
            sprintf(str, "  %.19s   |    %s    |", blank20, gdesc[i]);
          }
          
          screen_area_puts(ge->map, str);
        }
        
        sprintf(str, "  %.19s   |                 |", blank20);
        screen_area_puts(ge->map, str);
        
        sprintf(str, "  %.19s   |        %c        |", blank20, obj);
        screen_area_puts(ge->map, str);

        sprintf(str, "  %.19s   +-----------------+", blank20);
        screen_area_puts(ge->map, str);
      } 
      
      /* Checks that there is no space to the left but there is one to the right */    
      if (id_right != NO_ID && id_left == NO_ID)
      {  
        obj = ' ';
        for(i = 0; i < set_get_nids(object_set); i++)
        {
          aux_obj_id = set_get_ids_by_number(object_set, i);

          if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_act))) ==  FALSE) 
          {
            obj = ' ';
          } else {
            obj = '*';              
            i = set_get_nids(object_set) + 1;
          }
        }

        obj_r = ' ';
        for(i = 0; i < set_get_nids(object_set_r); i++)
        {
          aux_obj_id = set_get_ids_by_number(object_set_r, i);

          if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_right))) ==  FALSE) 
          {
            obj_r = ' ';
          } else {
            obj_r = '*';              
            i = set_get_nids(object_set_r) + 1;
          }
        }

        if (game_get_connection_status(game, id_act, E) == OPEN_L)
        {
          link_right = '>';
        }
        else
        {
          link_right = ' ';
        }

        if (game_get_connection_status(game, id_act, W) == OPEN_L)
        {
          link_left = '<';
        }
        else
        {
          link_left = ' ';
        }

        sprintf(str, "  %.19s   +-----------------+   +-----------------+", blank20);
        screen_area_puts(ge->map, str);

        space_name = (char *)space_get_name(game_get_space(game, id_act));
        strcpy(aux_name1, space_name);
        strncat(aux_name1, blank20, 15 - strlen(space_name));
        space_name2 = (char *)space_get_name(game_get_space(game, id_right));
        strcpy(aux_name2, space_name2);
        strncat(aux_name2, blank20, 15 - strlen(space_name2));
        if (id_right == 16 && game_get_time(game) == DAY)
        {
          strcpy(aux_name2, "¬¬¬¬¬¬¬ ");
        }
        sprintf(str, "  %.19s   | %s |   | %s |", blank20, space_name, aux_name2);
        screen_area_puts(ge->map, str);

        sprintf(str, "  %.19s   |           gpp0^ |   |                 |", blank20);
        screen_area_puts(ge->map, str);
        
        sprintf(str, "  %.19s   |                 |   |                 |", blank20);
        screen_area_puts(ge->map, str);

        gdesc = space_get_gdesc(game_get_space(game, id_act)); 
        gdesc_right = space_get_gdesc(game_get_space(game, id_right));
        enemy = NULL;
        enemy = game_get_enemy_in_space(game, id_act);
        if (enemy)
        {
          enemy_gdesc = enemy_get_gdesc(enemy);
        }
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          strcpy(aux_gdesc[i], gdesc_right[i]);
          if (id_right == 16 && game_get_time(game) == DAY)
          {
            strcpy(aux_gdesc[i], "¬¬¬¬ ");
          }
          if (i < ENEMY_GDESC_Y && enemy)
          {
            sprintf(str, "  %.19s   | %s %s|   |    %s    |", blank20, enemy_gdesc[i], gdesc[i], aux_gdesc[i]);
          }
          else if (enemy && i != 3)
          {
            sprintf(str, "  %.19s   |        %s|   |    %s    |", blank20, gdesc[i], aux_gdesc[i]);
          }
          else if (enemy)
          {
            sprintf(str, "  %.19s   |        %s| %c |    %s    |", blank20, gdesc[i], link_right, aux_gdesc[i]);
          }
          else if (i != 3) {
            sprintf(str, "  %.19s   |    %s    |   |    %s    |", blank20, gdesc[i], aux_gdesc[i]);
          } else {
            sprintf(str, "  %.19s   |    %s    | %c |    %s    |", blank20, gdesc[i], link_right, aux_gdesc[i]);
          }
          screen_area_puts(ge->map, str);
        }
        
        sprintf(str, "  %.19s   |                 |   |                 |", blank20);
        screen_area_puts(ge->map, str);
        sprintf(str, "  %.19s   |                 |   |                 |", blank20);
        screen_area_puts(ge->map, str);
        sprintf(str, "  %.19s   |        %c        |   |        %c        |", blank20, obj, obj_r);
        screen_area_puts(ge->map, str);
        sprintf(str, "  %.19s   +-----------------+   +-----------------+", blank20);
        screen_area_puts(ge->map, str);  
      }
      


      if (id_left != NO_ID && id_right == NO_ID)
      {
        obj = ' ';
        for(i = 0; i < set_get_nids(object_set); i++)
        {
          aux_obj_id = set_get_ids_by_number(object_set, i);
          
          if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_act))) ==  FALSE) 
          {
            obj = ' ';
          } else {
            obj = '*';              
            i = set_get_nids(object_set) + 1;
          }
        }
        obj_l = ' ';
        for(i = 0; i < set_get_nids(object_set_r); i++)
        {
          aux_obj_id = set_get_ids_by_number(object_set_r, i);
          
          if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_left))) ==  FALSE) 
          {
            obj_l = ' ';
          } else {
            obj_l = '*';              
            i = set_get_nids(object_set_r) + 1;
          }
        }

        if (game_get_connection_status(game, id_act, E) == OPEN_L)
        {
          link_right = '>';
        }
        else
        {
          link_right = ' ';
        }

        if (game_get_connection_status(game, id_act, W) == OPEN_L)
        {
          link_left = '<';
        }
        else
        {
          link_left = ' ';
        }

        sprintf(str, "  +-----------------+   +-----------------+");
        screen_area_puts(ge->map, str);

        space_name = (char *)space_get_name(game_get_space(game, id_act));
        strncat(space_name, blank20, 15 - strlen(space_name));
        space_name2 = (char *)space_get_name(game_get_space(game, id_left));
        strncat(space_name2, blank20, 15 - strlen(space_name2));
        /*
        if (id_right == 16 && game_get_time(game) == DAY)
        {
          strcpy(space_name2, "¬¬¬¬¬¬¬ ");
        }
        */
        sprintf(str, "  | %s |   | %s |", space_name2, space_name);
        screen_area_puts(ge->map, str);

        sprintf(str, "  |                 |   |           gpp0^ |");
        screen_area_puts(ge->map, str);
        
        sprintf(str, "  |                 |   |                 |");
        screen_area_puts(ge->map, str);

        gdesc = space_get_gdesc(game_get_space(game, id_act)); 
        gdesc_right = space_get_gdesc(game_get_space(game, id_left));
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          if (id_right == 16 && game_get_time(game) == DAY)
          {
            strcpy(gdesc_right[i], "¬¬¬¬ ");
          } 
          if (i != 3) {
            sprintf(str, "  |    %s    |   |    %s    |", gdesc_right[i], gdesc[i]);
            screen_area_puts(ge->map, str);
          } else {
            sprintf(str, "  |    %s    | %c |    %s    |", gdesc_right[i], link_right, gdesc[i]);
            screen_area_puts(ge->map, str);
          }
        }
        
        sprintf(str, "  |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |        %c        |   |        %c        |", obj_l, obj);
        screen_area_puts(ge->map, str);
        sprintf(str, "  +-----------------+   +-----------------+");
        screen_area_puts(ge->map, str);  
      }

      /* Checks that there are both spaces to the left and right */    
      if (id_left != NO_ID && id_right != NO_ID)
      {
        obj = ' ';
        for(i = 0; i < set_get_nids(object_set); i++)
        {
          aux_obj_id = set_get_ids_by_number(object_set, i);
          
          if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_act))) ==  FALSE) 
          {
            obj = ' ';
          } else {
            obj = '*';              
            i = set_get_nids(object_set) + 1;
          }
        }
        obj_r = ' ';
        for(i = 0; i < set_get_nids(object_set_r); i++)
        {
          aux_obj_id = set_get_ids_by_number(object_set_r, i);
          
          if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_right))) ==  FALSE) 
          {
            obj_r = ' ';
          } else {
            obj_r = '*';              
            i = set_get_nids(object_set_r) + 1;
          }
        }

        obj_l = ' ';
        for(i = 0; i < set_get_nids(object_set_l); i++)
        {
          aux_obj_id = set_get_ids_by_number(object_set_l, i);
          
          if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_left))) ==  FALSE) 
          {
            obj_l = ' ';
          } else {
            obj_l = '*';              
            i = set_get_nids(object_set_l) + 1;
          }
        }

        if (game_get_connection_status(game, id_act, E) == OPEN_L)
        {
          link_right = '>';
        }
        else
        {
          link_right = ' ';
        }

        if (game_get_connection_status(game, id_act, W) == OPEN_L)
        {
          link_left = '<';
        }
        else
        {
          link_left = ' ';
        }
        
        sprintf(str, "  +-----------------+   +-----------------+   +-----------------+");
        screen_area_puts(ge->map, str);

        space_name = (char *)space_get_name(game_get_space(game, id_left));
        strncat(space_name, blank20, 15 - strlen(space_name));
        space_name2 = (char *)space_get_name(game_get_space(game, id_act));
        strncat(space_name2, blank20, 15 - strlen(space_name2));
        space_name3 = (char *)space_get_name(game_get_space(game, id_right));
        strncat(space_name3, blank20, 15 - strlen(space_name3));
        sprintf(str, "  | %s |   | %s |   | %s |", space_name, space_name2, space_name3);
        screen_area_puts(ge->map, str);

        sprintf(str, "  |                 |   |           gpp0^ |   |                 |");
        screen_area_puts(ge->map, str);

        sprintf(str, "  |                 |   |                 |   |                 |");
        screen_area_puts(ge->map, str);
        gdesc = space_get_gdesc(game_get_space(game, id_act)); 
        gdesc_right = space_get_gdesc(game_get_space(game, id_right)); 
        gdesc_left = space_get_gdesc(game_get_space(game, id_left)); 
        enemy = NULL;
        enemy = game_get_enemy_in_space(game, id_act);
        if (enemy)
        {
          enemy_gdesc = enemy_get_gdesc(enemy);
        }
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          if (i < ENEMY_GDESC_Y && enemy)
          {
            sprintf(str, "  |    %s    |   | %s %s|   |    %s    |", gdesc_left[i], enemy_gdesc[i], gdesc[i], gdesc_right[i]);
          }
          else if (enemy && i != 3)
          {
            sprintf(str, "  |    %s    |   |        %s|   |    %s    |", gdesc_left[i], gdesc[i], gdesc_right[i]);
          }
          else if (enemy)
          {
            sprintf(str,  "  |    %s    | %c |        %s| %c |    %s    |", gdesc_left[i], link_left, gdesc[i], link_right, gdesc_right[i]);
          }
          else if (i != 3) {
            sprintf(str, "  |    %s    |   |    %s    |   |    %s    |", gdesc_left[i], gdesc[i], gdesc_right[i]);
          } else {
            sprintf(str, "  |    %s    | %c |    %s    | %c |    %s    |", gdesc_left[i], link_left, gdesc[i], link_right, gdesc_right[i]);
          }
          screen_area_puts(ge->map, str);
        }

        
        sprintf(str, "  |                 |   |                 |   |                 |");
        screen_area_puts(ge->map, str);

        sprintf(str, "  |         %c       |   |         %c       |   |         %c       |", obj_l, obj, obj_r);
        screen_area_puts(ge->map, str);  
        sprintf(str, "  +-----------------+   +-----------------+   +-----------------+");
        screen_area_puts(ge->map, str);
      }
    }

    /* Space to the south of the current space */
    if (id_down != NO_ID)
    {
      obj = ' ';
      for(i = 0; i < set_get_nids(object_set); i++)
      {
        aux_obj_id = set_get_ids_by_number(object_set, i);
        if (obj_is_visible(game_get_object(game, aux_obj_id), space_get_light_status(game_get_space(game, id_act))) ==  FALSE) 
        {
          obj = ' ';
        } else {
          obj = '*';              
          break;
        }
      }

      if (game_get_connection_status(game, id_act, S) == OPEN_L)
      {
        link_down = 'v';
      }
      else
      {
        link_down = ' ';
      }

      sprintf(str, "  %.19s            %c", blank20, link_down);
      screen_area_puts(ge->map, str);
      sprintf(str, "  %.19s   +-----------------+", blank20);
      screen_area_puts(ge->map, str);

      space_name = (char *)space_get_name(game_get_space(game, id_down));
      strncat(space_name, blank20, 15 - strlen(space_name));
      sprintf(str, "  %.19s   | %s |", blank20, space_name);
      screen_area_puts(ge->map, str);

      sprintf(str, "  %.19s   |                 |", blank20);
      screen_area_puts(ge->map, str);

      sprintf(str, "  %.19s   |        %c        |", blank20, obj);
      screen_area_puts(ge->map, str);

      sprintf(str, "  %.19s   |                 |", blank20);
      screen_area_puts(ge->map, str);
    }
  }
  
  /* Paint in the description area */
  screen_area_clear(ge->descript);
  
  if ((player_loc != NO_ID) && (en_loc[0] != NO_ID))
  {
    sprintf(str, "  Objects in space:");
    screen_area_puts(ge->descript, str);
    
    for(i=0;i< set_get_nids(space_get_objects(game_get_space(game, id_act)));i++)
    { 
      if (game_get_object(game,set_get_ids_by_number(space_get_objects(game_get_space(game, id_act)), i)) == NULL)
      {
        break;                     
      }

      if (obj_is_visible(game_get_object(game,set_get_ids_by_number(space_get_objects(game_get_space(game, id_act)), i)), space_get_light_status(game_get_space(game, id_act)))== TRUE) {
        sprintf(str, "  %s ", obj_get_name(game_get_object(game,set_get_ids_by_number(space_get_objects(game_get_space(game, id_act)), i))));
        screen_area_puts(ge->descript, str);
      }
    }

    sprintf(str, "   ") ;
    screen_area_puts(ge->descript, str);

    sprintf(str, "  PLAYER (gpp0^):");
    screen_area_puts(ge->descript, str);
    gdesc = player_get_gdesc(game_get_player(game, 21));
    sprintf(str, "  +--------+");
    screen_area_puts(ge->descript, str);
    for (i = 0; i < PLAYER_GDESC_Y; i++)
    {
      sprintf(str, "  |  %s  |", gdesc[i]);
      screen_area_puts(ge->descript, str);
    }
    sprintf(str, "  +--------+");
    screen_area_puts(ge->descript, str);

    sprintf(str, "  Player location:%d", (int)player_loc);
    screen_area_puts(ge->descript, str);
  
    if(player_inventory==NULL || set_get_nids(inventory_get_objects(player_inventory)) == 0)
    {
      sprintf(str, "  Player object: No object" );
      screen_area_puts(ge->descript, str);
    }
    else
    {
      sprintf(str, "  Player objects:"); 
      screen_area_puts(ge->descript, str);

    
      for (i = 0; i < set_get_nids(inventory_get_objects(player_inventory)); i++)
      {
        sprintf(str, "    %s", obj_get_name(game_get_object(game, set_get_ids_by_number(inventory_get_objects(player_inventory),i)))); 
        screen_area_puts(ge->descript, str);
      }
    }
    
    sprintf(str, "  Player health:%d", (int)player_health);
    screen_area_puts(ge->descript, str);

    
    sprintf(str, "   ") ;
    screen_area_puts(ge->descript, str);

    sprintf(str, "  Enemies in space:") ;
    screen_area_puts(ge->descript, str);
    for (i = 0; i < MAX_ENEMYS; i++) {
      if (en_loc[i] == id_act) {
        sprintf(str, "    Enemy name:%s", en_name[i]);
        screen_area_puts(ge->descript, str);
        sprintf(str, "    Enemy health:%d", (int)en_health[i]);
        screen_area_puts(ge->descript, str);
        sprintf(str, "   ") ;
        screen_area_puts(ge->descript, str);
      }
    }

    sprintf(str, "   ");
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Info:");
    screen_area_puts(ge->descript, str);
    sprintf(str, "  %s", description);
    screen_area_puts(ge->descript, str);

    sprintf(str, "   ");
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Descriptions:");
    screen_area_puts(ge->descript, str);
    if(inspection){
      sprintf(str, "  %s", inspection);
      screen_area_puts(ge->descript, str);
    }

    sprintf(str, "   ");
    screen_area_puts(ge->descript, str);
    for (i = 0; i < 6; i++)
    {
      if (link_get_status(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == CLOSE )
      {
        if (link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) != NULL)
        {
          sprintf(str, "  Closed links(for keys): ");
          screen_area_puts(ge->descript, str);

          break;
        }
      }
    }
    for (i = 0; i < 6; i++)
    {
      if (link_get_status(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == CLOSE )
      {
        if (link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) != NULL)
        {
          if (link_get_direction(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == 0)
          {
            sprintf(str, "    %s: NORTH", link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))));
            screen_area_puts(ge->descript, str);
          } 
          else if (link_get_direction(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == 1)
          {
            sprintf(str, "    %s:  SOUTH ", link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))));
            screen_area_puts(ge->descript, str);
          }
          else if (link_get_direction(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == 2)
          {
            sprintf(str, "    %s: EAST", link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))));
            screen_area_puts(ge->descript, str);
          }
          else if (link_get_direction(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == 3)
          {
            sprintf(str, "    %s: WEST", link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))));
            screen_area_puts(ge->descript, str);
          }
          else if (link_get_direction(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == 4)
          {
            sprintf(str, "    %s: UP", link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))));
            screen_area_puts(ge->descript, str);
          }
          else if (link_get_direction(game_get_link(game, space_get_link(game_get_space(game, id_act), i))) == 5)
          {
            sprintf(str, "    %s: DOWN", link_get_name(game_get_link(game, space_get_link(game_get_space(game, id_act), i))));
            screen_area_puts(ge->descript, str);
          }
        }
      }
    }
    
  if (game_get_time(game) == DAY)
  {
    sprintf(str, "  Time: DAY");
  } 
  else
  {
    sprintf(str, "  Time: NIGHT");
  }
  screen_area_puts(ge->descript, str);
    
  if (player_get_health(game_get_player(game, 21)) <= 0 || enemy_get_health(game_get_enemy(game, 45)) <= 0)
  {
    screen_area_clear(ge->descript);
    screen_area_clear(ge->map);
    for (i = 0; i < 12; i++)
    {
      sprintf(str, "             ");
      screen_area_puts(ge->map, str);
    }
    sprintf(str, "                                 GAME IS OVER");
    screen_area_puts(ge->map, str);
    sprintf(str, "                           Press e to exit the game");
    screen_area_puts(ge->map, str);
  }
    
    sprintf(str, "  ");
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, " Day-Night Dungeon "); 

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, "                         The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " m(MOVE), t(TAKE), d(DROP), a(ATTACK), i(INSPECT), e(EXIT), s(SAVE), l(LOAD)");
  screen_area_puts(ge->help, str);
  sprintf(str, "               o (OPEN), ton (TURNON), toff (TURNOFF), u(USE)");
  screen_area_puts(ge->help, str);
  /*
  sprintf(str, " Player object will be -1 as long as it doesn't carry one");
  screen_area_puts(ge->help, str);
  */

  /* Paint in the feedback area */
  last_cmd = game_get_last_command(game);
  if (st == 0)
  {
    sprintf(str, " %s (%s): ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  else if (st == 1)
  {
    sprintf(str, " %s (%s): OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  else
  {
    sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  
  screen_area_puts(ge->feedback, str);

/* prints the dialoge area */
screen_area_clear(ge->dialogue);

screen_area_puts(ge->dialogue, " Dialogue:");
dialogue = dialogue_get_error(game_get_dialogue(game));

if(dialogue == NULL){}
else if(strcmp(dialogue, " ") == 0){
  dialogue = dialogue_get_command(game_get_dialogue(game));
}

if (dialogue)
{
  sprintf(str, "  %s", dialogue);
  screen_area_puts(ge->dialogue, str);
}

/* prints the events area */
screen_area_clear(ge->events);

screen_area_puts(ge->events, " Events:");
events = dialogue_get_event(game_get_dialogue(game));
if (events)
{
  sprintf(str, "  %s", events);
  screen_area_puts(ge->events, str);
}


  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");

}
