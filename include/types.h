/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers, Ignacio Nunez
 * @version 2.0
 * @date 02-04-2022
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000    /*!< Establish the length for some strings */
#define NO_ID -1          /*!< Establish a non-defined id and its value is -1*/
#define MAX_ARG 20        /*!< Establish a length of command input arguments */
#define NUM_ARG 2         /*!< Establish the number or arguments in an input command */

#define FD_ID_SPACE 1  /*!< First digit of a space. */
#define FD_ID_PLAYER 2 /*!< First digit of a player. */
#define FD_ID_OBJ 3    /*!< First digit of an object. */
#define FD_ID_ENEMY 4  /*!< First digit of an enemy. */

/**
 * @brief Ids
 */
typedef long Id;

/**
 * @brief Booleans (TRUE or FALSE)
 */
typedef enum
{
  FALSE,
  TRUE
} BOOL;

/**
 * @brief Status (OK or ERROR)
 */
typedef enum
{
  ERROR = 0,
  OK = 1
} STATUS;

/**
 * @brief Link's and space's directions (N, S, E, W or ND (not-defined))
 */
typedef enum
{
  ND = -1, /* !< Short for Not Defined */
  N,       /* !< Short for North */
  S,       /* !< Short for South */
  E,       /* !< Short for East */
  W,       /* !< Short for West */
  U,       /* !< Short for Up */
  D        /* !< Short for Down */
} DIRECTION;

/**
 * @brief Luminosity status of a space (DARK, BRIGHT)
 */
typedef enum
{
  UNKNOWN_LIGHT = -1,   /* !< Light status not defined*/
  DARK,      /* !< Dark status of a space */
  BRIGHT         /* !< Bright status of a space */
} Light;

/**
 * @brief Day-Night status
 */
typedef enum 
{
  DAY,    /*!< Day time*/
  NIGHT   /*!< Night time*/
} Time;

/**
 * @brief Type of an object
 */
typedef enum
{
  UNKNOWN_TYPE = -1,  /*!< Unknown object type*/
  APPLE,              /*!< Apple object type*/
  ELIXIR,             /*!< Elixir object type*/
  ARMOR,              /*!< Armor object type*/
  HOOK,               /*!< Hook object type*/
  BED,                /*!< Bed object type*/
  BREAD_CRUMBS        /*!< Bread_crumbs object type*/
} Obj_type;

/**
 * @brief Floor on which a space is
 */
typedef enum {
  UNKNOWN_FLOOR = -2,
  DUNGEON,       /*!< Dungeon floor*/
  FLOOR_0,            /*!< Initial floor*/
  ALCOVE              /*!< Alcove floor*/
} Floor;

#endif
