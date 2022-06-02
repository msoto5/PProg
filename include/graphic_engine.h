/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Miguel Soto, Nicolas VIctorino, Antonio Van-Oers and Ignacio Nunez
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

/**
 * @brief Graphic engine
 *
 * This structure contains all pointers and data from the needed resources
 * to work with the graphic engine and all its members, them being everything
 * the user sees printed in their screen
 *
 */
typedef struct _Graphic_engine Graphic_engine;

/**
  * @brief Creates the graphic engine 
  * @author Profesores PPROG
  *
  * graphic_engine_create initializes the gamescreen with specific screen dimensions,
  * allocs memory for a variable, ge, type Graphic_engine and it also initializes
  * each member in its position on said screen 
  * @return ge if everything goes well or NULL if something went wrong
  */
Graphic_engine *graphic_engine_create();

/**
  * @brief Destroys every member of the graphic engine
  * @author Profesores PPROG
  *
  * graphic_engine_destroy, using the function screen_area_destroy, 
  * destroys the map, banner, descript, help and feedback 
  * It also frees all the previosly alloc'd memory
  * @param ge pointer to the graphic engine
  */
void graphic_engine_destroy(Graphic_engine *ge);

/**
  * @brief Prints the game on the screen
  * @author Profesores PPROG
  *
  * Prints the game on the screen, with all its components on the 
  * right position for the user to see the info needed to interact with it
  * @param ge pointer to the graphic engine
  * @param game pointer to the already created game
  * @param st is a integer that indicates the status of the last command
  */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, int st);

/**
  * @brief Writes down the last inputted command
  * @author Profesores PPROG
  *
  * @param ge pointer to the graphic engine
  * @param str pointer to the introduced string
  */
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
