/** 
 * @brief It implements the command interpreter module.
 * 
 * It scans the cmd searching for key words introduced by the user in order to interpret and clasify the commands
 * as unknown, exit, up, down, left, right attack, take, drop, move or inspect depending on what string is typed.
 * 
 * @file command.c
 * @author Miguel Soto, Nicolas Victorino, Ignacio Nunez and Antonio Van-Oers
 * @version 3.0 
 * @date 05-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "../include/command.h"

#define CMD_LENGHT 30 /*!< It defines the maximun lenght from an input command */

/**
 * @brief Two dimensional string array where commands names are included. When reading commands case sensitivity is off.
 */
char *cmd_to_str[N_CMD]
[N_CMDT] = {{"", "No command"},    /*!< At the beginning, there is no commands */
      {"", "Unknown"},             /*!< If an empty or unknown string is received, it is interpreted as Unknown */
      {"e", "Exit"},               /*!< If an "e" or "exit" is received, it is interpreted as Exit */
      {"t", "Take"},               /*!< If a "t" or "take" is received, it is interpreted as Take */
      {"d", "Drop"},               /*!< If a "d" or "drop" is received, it is interpreted as Drop */
      {"a", "Attack"},             /*!< If a "a" or "attack" is received, it is interpreted as Attack */
      {"m", "Move"},               /*!< If a "m" or "move" is received, it is interpreted as move */
      {"i", "Inspect"},            /*!< If an "i" or "inspect" is received, it is interpreted as inspect */
      {"s", "Save"},               /*!< If a "s" or "save" is received, it is interpreted as Save */
      {"l", "Load"},               /*!< If a "l" or "load" is received, it is interpreted as Load */
      {"ton", "Turnon"},           /*!< If a "ton" or "Turnon" is received, it is interpreted as Turnon */
      {"toff", "Turnoff"},         /*!< If a "toff" or "Turnoff" is received, it is interpreted as Turnoff */
      {"o", "Open"},               /*!< If an "o" or "Open" is received, it is interpreted as Open */
      {"u", "Use"}                 /*!< If an "u" or "Use" is received, it is interpreted as Use */
      };

/**
 * Funciones privadas
 */
void print_syntax_command(T_Command cmd);

/**It scans the cmd searching for key words introduced by the user 
  *in order to interpret and clasify the info
  */
T_Command command_get_user_input(char *arg1, char *arg2)
{
  T_Command cmd = NO_CMD; 
  char input[CMD_LENGHT] = "", aux[CMD_LENGHT] = "\0";
  int i = UNKNOWN - NO_CMD + 1;
  
  /* Error control*/
  if (!arg1 || !arg2)
  {
    return NO_CMD;
  }
  
  if (scanf("%s", input) > 0)
  {
    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD)     /*!< Condition to continue reading */
    {
      if (!strcasecmp(input, cmd_to_str[i][CMDS]) || !strcasecmp(input, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;                   /*!< If any differences are detected between CMDS, CMDL and the input, cmd is modified */
        if (cmd == TAKE || cmd == DROP || cmd == MOVE || cmd == INSPECT || cmd == LOAD || cmd == TURNON || cmd == TURNOFF || cmd == USE)
        {
          if (scanf("%s", arg1) < 0)
          {
            print_syntax_command(cmd);
          }
        }
        else if (cmd == OPEN)
        {
          if (scanf("%s %s %s", arg1, aux, arg2) != 3)
          {
            print_syntax_command(cmd);
          }

          strncat(aux, "\0", 1);
          if (strcasecmp("with\0", aux) != 0)
          {
            print_syntax_command(cmd);
            return UNKNOWN;
          }
        }
      }
      else                                  /*!< In any other case, continue reading >! */
      {
        i++;                                 
      }
    }
  }
  
  return cmd;
}

T_Command command_get_file_input(char *command, char *arg) 
{
  T_Command cmd = NO_CMD; 
  char input[CMD_LENGHT] = "";
  int i = UNKNOWN - NO_CMD + 1, j = 0, z = 0;
  
  /* Error control*/
  if (!arg)
  {
    return NO_CMD;
  }
  
  if (command != NULL)
  {
    cmd = UNKNOWN;
    for (j = 0; command[j] != ' '; j++) { /*Reads first part of command*/
      input[j] = command[j];
    }
    input[j] = '\0';
    while (cmd == UNKNOWN && i < N_CMD)     /*!< Condition to continue reading */
    {
      if (!strcasecmp(input, cmd_to_str[i][CMDS]) || !strcasecmp(input, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;                   /*!< If any differences are detected between CMDS, CMDL and the input, cmd is modified */
        if (cmd == TAKE || cmd == DROP || cmd == MOVE || cmd == INSPECT)
        {
          for (j++, z = 0; command[j] != ' '; j++, z++) { /*Reads the second argument of command and saves it in arg*/ 
            arg[z] = command[j];
          } 
          arg[z] = '\0';
          if (arg == NULL)
          {
            fprintf(stdout, "Comando incorrecto. Los comandos TAKE DROP INSPECT MOVE USE OPEN necesitan un argumento mas como el nombre del objeto .\n");
          }
        }
        /*
        else if (cmd == OPEN)
        {
          if (scanf("%s %s %s", arg[0], arg[1], arg[2]) != 3)
          {
            print_syntax_command(cmd);
          }
          if (strcasecmp("with\0", arg[1]) != 0)
          {
            print_syntax_command(cmd);
            return UNKNOWN;
          }
        }
        */
      }
      else                                  /*!< In any other case, continue reading >! */
      {
        i++;
      }
    }
  }
  
  return cmd;
}

/**
 * @brief Print syntax information of a given command
 * @author Miguel Soto
 * 
 * @param cmd command type you need to print syntax information
 */
void print_syntax_command(T_Command cmd)
{
  switch (cmd)
  {
  case TAKE:
    fprintf(stdout, "ERROR: Incorrect command syntax. Command take needs an argument with the object name the player will take.\n");
    fprintf(stdout, "Command TAKE syntax: t <obj_name> or take <obj_name>\n");
    break;
  case DROP:
    fprintf(stdout, "ERROR: Incorrect command syntax. Command drop needs an argument with the object name the player will drop.\n");
    fprintf(stdout, "Command DROP syntax: d <obj_name> or drop <obj_name>\n");
    break;
  case MOVE:
    fprintf(stdout, "ERROR: Incorrect command syntax. Command move needs an argument with the direction you want to travel through.\n");
    fprintf(stdout, "Command MOVE syntax: m <direction> or move <direction>.\n");
    fprintf(stdout, "<direction> can be N (North), S (South), E (East), W (West), U (Up) or D (Down).\n");
    break;
  case INSPECT:
    fprintf(stdout, "ERROR: Incorrect command syntax. Command inspect needs an argument with an space or object name you want to read larger description.\n");
    fprintf(stdout, "Command INSPECT syntax: i <arg> or inspect <arg>\n");
    break;
  case SAVE:
    fprintf(stdout, "ERROR: Incorrect command syntax.\n");
    fprintf(stdout, "Command SAVE syntax: s <obj_name> or save <obj_name>\n");
    break;
  case LOAD:
    fprintf(stdout, "ERROR: Incorrect command syntax.\n");
    fprintf(stdout, "Command LOAD syntax: l <obj_name> or load <obj_name>\n");
    break;
  case TURNON:
    fprintf(stdout, "ERROR: Incorrect command syntax. Command turnon needs an argument with the object name you want to iluminate.\n");
    fprintf(stdout, "Command TURNON syntax: ton <obj_name> or turnon <obj_name>\n");
    break;
  case TURNOFF:
    fprintf(stdout, "ERROR: Incorrect command syntax. Command turnoff needs an argument with the object name you want to stop lighting.\n");
    fprintf(stdout, "Command TURNOFF syntax: ton <obj_name> or turnoff <obj_name>\n");
    break;
  case OPEN:
    fprintf(stdout, "ERROR: Incorrect command syntax. Command open needs 2 arguments: one with the link name you want to open and one with the object name with which player opens link.\n");
    fprintf(stdout, "Command OPEN syntax: o <link_name> with <obj> or open <link_name> with <obj>\n");
    break;
  default:
    break;
  }
}
