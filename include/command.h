/**
 * @brief It implements the command interpreter interface
 *
 * @file command.h
 * @author Nicolas VIctorino, Antonio Van-Oers, Ignacio Nunez and Miguel Soto
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2 /*!< It defines the number of ways each command can be call (the long and the short name). */
#define N_CMD 14 /*!< It defines the number of arguments. */

/**
 * @brief It defines the two ways to call a command, by its short name (CMDS) or by its long name (CMDL).
 */
typedef enum enum_CmdType
{
  CMDS,     /*!< Short for Command Short format. */
  CMDL      /*!< Short for Command Long format. */
} T_CmdType;

/**
 * @brief Command type enum (T_Command).
 *
 * Intitializes No_CMD to -1 and includes every possible interpretation for the input
 */
typedef enum enum_Command
{
  NO_CMD = -1,  /*!< There is no command or command type is ineffective. */
  UNKNOWN,      /*!< Command type is unknown. */
  EXIT,         /*!< Command type is to exit game. */
  TAKE,         /*!< Command type is to take object. Name of the objet must be included as a second argument. */
  DROP,         /*!< Command type is to drop object. Name of the objet must be included as a second argument. */
  ATTACK,       /*!< Command type is to attack an enemy. Id of the enemy must be included as a second argument. */
  MOVE,         /*!< Command type is to move player (direction specify in another argument). */
  INSPECT,      /*!< Command type is to inspect. */
  SAVE,         /*!< Command type is to save (name of the file as a second argument). */
  LOAD,         /*!< Command type is to load (name of the file as a second argument). */
  TURNON,       /*!< Command type is to turn on an object to iluminate space. */
  TURNOFF,      /*!< Command type is to turn off an object so it stops lighting a space. */
  OPEN,         /*!< Command type is to open a link with an object */
  USE           /*!< Command type is to use an object with the given id */
} T_Command;

/**
 * @brief Obtiene el input del usuario
 * @author Profesores PPROG
 *
 * It scans the cmd searching for key words introduced by the user
 * in order to interpret and clasify the info
 *
 * @return cmd, a T_Command type variable that changes its value depending on the input
 */
T_Command command_get_user_input();

/**
 * @brief Obtiene el input del usuario
 * @author Nicolas Victorino
 *
 * It scans the cmd searching for key words introduced by the file
 * in order to interpret and clasify the info.
 *
 * @return cmd, a T_Command type variable that changes its value depending on the input
 */
T_Command command_get_file_input(char *command, char *arg);

#endif
