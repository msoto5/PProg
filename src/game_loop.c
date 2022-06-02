/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers and Ignacio Nunez
 * @version 2.0
 * @date 03-04-2022
 * @copyright GNU Public License
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/graphic_engine.h"
#include "../include/game.h"
#include "../include/command.h"
#include "../include/game_managment.h"

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game *game, Graphic_engine *gengine, char *flog_name, char *fcmd_name);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);
void print_syntaxinfo(char *argv[]);

/**
 * @brief Main funcion of the game 
 * @author Miguel Soto && Nicolas Victorino
 *
 * Checks if the value of argc and argv are right to decide if it initializes the game and actives the cleanup
 * @param argc an integer that checks how many arguments the user has introduced
 * @param argv a string that contains the arguments the player has introduced
 * @return 0 if the game executes correctly 1 if the user hasnt used the right game_data_file 
 */
int main(int argc, char *argv[])
{
  Game *game = NULL;
  Graphic_engine *gengine;
  /* Used to able to save commands in log */
  char *wlog_name = NULL, *cmdf_name = NULL;
  int i; /* Used in loops */

  /*Necessary for random features*/
  srand(time(NULL));
  
  /* Alloc game's struct in memory */
  game = game_alloc2();
  if (!game)
  {
    fprintf(stderr, "ERROR allocating game's memory\n");
    return 1;
  }

  /* Check arguments in execution command */
  if (argc < 2) /* Incorrect syntax */
  {
    print_syntaxinfo(argv);
    return 1;
  }
  else if (argc == 2)
  {
    /*Loads game and waits for player interaction*/
    if (!game_loop_init(game, &gengine, argv[1]))
    {
      game_loop_run(game, gengine, NULL, NULL);
      game_loop_cleanup(game, gengine);
    }
  }
  else if (argc > 2)
  {
    /*Loads game from a file*/
    wlog_name = NULL;
    cmdf_name = NULL;
    if (argc == 3)
    {
      fprintf(stderr, "\nWrong syntax. Argument %s unidentified.\n", argv[2]);
      print_syntaxinfo(argv);
      return 1;
    }
    
    for (i = 2; i < (argc - 1); i++)
    {
      printf("argv[%d] = %s\n", i, argv[i]);
      if (strcmp(argv[i], "-l\0") == 0)
      {
        i++;
        wlog_name = argv[(i)];
      }
      else if (strcmp(argv[i], "<\0") == 0)
      {
        i++;
        cmdf_name = argv[i];
      }
      else
      {
        fprintf(stderr, "\nWrong syntax. Argument %s unidentified.\n", argv[i]);
        print_syntaxinfo(argv);
        return 1;
      }
    }

    if (!game_loop_init(game, &gengine, argv[1]))
    {
      game_loop_run(game, gengine, wlog_name, cmdf_name);
      game_loop_cleanup(game, gengine);
    }
  }

  return 0;
}

/**
 * @brief Initializes the game
 * @author Profesores PPROG
 *
 * @param game Pointer to the game type struct that contains the information of the enemies, player, object, links spaces and the last command 
 * @param gengine doble pointer to access the graphic engine
 * @param file_name is a pointer to the name of the file from which the game is initialized
 * @return 0 if the game initializes correctly 1 if there has been an error
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
  /*Error control(Creates game)*/
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  /*Error control(Creates graphic engine)*/
  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

/**
 * @brief Executes the game
 * @author Miguel Soto && Nicolas Victorino
 *
 * Cheks in a loop if the last command is not exit or if the game has not ended, to keep executing the game
 * @param game Pointer to the game type struct that contains the information of the enemies, player, object, links spaces and the last command 
 * @param gengine pointer to the graphi engine
 * @param flog_name string name from file where to write every command executed. It has to be NULL if a log file is not wanted.
 * @param fcmd_name string name from file where to get every command to be executed. It has to be NULL if a command file is not used.
 */
void game_loop_run(Game *game, Graphic_engine *gengine, char *flog_name, char *fcmd_name)
{
  T_Command command = NO_CMD;
  char arg1[MAX_ARG], arg2[MAX_ARG], input[MAX_ARG];
  int st = 5, wlog = 0, rcmd = 0;
  FILE *flog = NULL, *fcmd = NULL;
  T_Command last_cmd;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  /*Cheks if the game has been initialized with the flag -l, that outputs a log with the commands used during the execution of the game*/
  if (flog_name)
  {
    wlog = 1;
    flog = fopen(flog_name, "w");
    /*Error control*/
    if (!flog)
    {
      fprintf(stderr, "There was an error opening log_file.\n");
      return;
    }
  }

  /*Checks if the game has been initialized with the flag <, that loads a list of commands to the game from a given file*/
  if (fcmd_name)
  {
    rcmd = 1;
    fcmd = fopen(fcmd_name, "r");
    /*Error control*/
    if (!fcmd)
    {
      fprintf(stderr, "There was an error opening cmd_file.\n");
      return;
    }
  }

  for (; (command != EXIT) /*&& !game_is_over(game)*/;)
  {
    graphic_engine_paint_game(gengine, game, st);

    if (rcmd == 1)
    {
      if (fgets(input, MAX_ARG, fcmd))
      {
        command = command_get_file_input(input, arg1);
      }
      else
      {
        /* If there  is an error at the beggining of the execution is here, so it exits the game*/
        command = EXIT;
      }
    }
    else
    {
      command = command_get_user_input(arg1, arg2);
    }

    st = game_update(game, command, arg1, arg2);

    /*Cheks if the game is working in "log-mode" and if true it prints the commands in the output file*/
    if (wlog == 1)
    {
      last_cmd = game_get_last_command(game);
      if (st == 0)
      {
        if ( last_cmd == 1 || last_cmd == 2 || last_cmd == 3 || last_cmd == 4 || last_cmd == 5 ) {
          fprintf(flog, " %s (%s): ERROR\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
        } else {
          fprintf(flog, " %s (%s) %s: ERROR\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], arg1);
        }
      }
      else if (st == 1)
      {
        if ( last_cmd == 1 || last_cmd == 2 || last_cmd == 3 || last_cmd == 4 || last_cmd == 5 ) {
          fprintf(flog, " %s (%s): OK\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
        } else {
          fprintf(flog, " %s (%s) %s: OK\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], arg1);
        }
      }
      else
      {
        fprintf(flog, " %s (%s)\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
      }
    }
  }

  fprintf(stdout, "\n");

  /*Closes flog (output of "log-mode")*/
  if (flog)
  {
    fclose(flog);
    flog = NULL;
  }

  /*Closes command file (input of "<-mode")*/
  if (fcmd)
  {
    fclose(fcmd);
    fcmd = NULL;
  }

  return;
}


/**
 * @brief Ends and cleans the game
 * @author Profesores PPROG
 *
 * After the game has stopped, it destroys the game and the graphic engine to clean those processes
 * @param game Pointer to the game type struct that contains the information of the enemies, player, object, links spaces and the last command
 * @param gengine pointer to the graphic engine
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
}

/**
 * @brief Prints syntax info when running the  program.
 * @author Miguel Soto
 *
 * @param argv Arguments from the command used to execute program.
 */
void print_syntaxinfo(char *argv[])
{
  fprintf(stderr, "\nUse: %s <game_data_file>.\n", argv[0]);
  fprintf(stderr, "If you want to save inserted commands use the flag \"-l\" with the file name\n");
  fprintf(stderr, "Also, if you want to execute commands from a file use \"<\" with the file name\n \n");
  fprintf(stderr, "\tGlobal syntax: %s <game_data_file> [-l <log_file>] [< <command_file>]\n", argv[0]);
  fprintf(stderr, "\tArguments between [ ] are optional.\n \n");
}
