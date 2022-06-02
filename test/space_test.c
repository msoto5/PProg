/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Ignacio Nunez, Miguel Soto, Antonio Van-Oers and Nicolas Victorino
 * @version 3.0
 * @date 04-04-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 46 /*!< It defines the maximun tests in this file */

/**
 * @brief Main function for SPACE unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

  int test = 0;
  int all = 1, i;

  if (argc < 2)
  {
    printf("Running all test for module Space:\n");
  }
  else
  {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS)
    {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  i = 1;
  if (all || test == i) test1_space_create();
  i++;
  if (all || test == i) test2_space_create();
  i++;

  if (all || test == i) test1_space_destroy();
  i++;
  if (all || test == i) test2_space_destroy();
  i++;

  if (all || test == i) test1_space_set_name();
  i++;
  if (all || test == i) test2_space_set_name();
  i++;
  if (all || test == i) test3_space_set_name();
  i++;

  if (all || test == i) test1_space_set_link();
  i++;
  if (all || test == i) test1_space_set_link_north();
  i++;
  if (all || test == i) test2_space_set_link_north();
  i++;
  if (all || test == i) test1_space_set_link_south();
  i++;
  if (all || test == i) test2_space_set_link_south();
  i++;
  if (all || test == i) test1_space_set_link_east();
  i++;
  if (all || test == i) test2_space_set_link_east();
  i++;
  if (all || test == i) test1_space_set_link_west();
  i++;
  if (all || test == i) test2_space_set_link_west();
  i++;


  if (all || test == i) test1_space_add_object();
  i++;
  if (all || test == i) test2_space_add_object();
  i++;

  if (all || test == i) test1_space_del_object();
  i++;
  if (all || test == i) test2_space_del_object();
  i++;
  if (all || test == i) test3_space_del_object();
  i++;

  if (all || test == i) test1_space_get_object();
  i++;
  if (all || test == i) test2_space_get_object();
  i++;
  if (all || test == i) test3_space_get_object();
  i++;

  if (all || test == i) test1_space_get_link();
  i++;
  if (all || test == i) test1_space_get_link_north();
  i++;
  if (all || test == i) test2_space_get_link_north();
  i++;
  if (all || test == i) test1_space_get_link_south();
  i++;
  if (all || test == i) test2_space_get_link_south();
  i++;
  if (all || test == i) test1_space_get_link_east();
  i++;
  if (all || test == i) test2_space_get_link_east();
  i++;
  if (all || test == i) test1_space_get_link_west();
  i++;
  if (all || test == i) test2_space_get_link_west();
  i++;

  if (all || test == i) test1_space_get_id();
  i++;
  if (all || test == i) test2_space_get_id();
  i++;

  if (all || test == i) test2_space_get_id();
  i++;
  if (all || test == i) test2_space_get_id();
  i++;

  if (all || test == i) test1_space_set_gdesc();
  i++;
  if (all || test == i) test2_space_set_gdesc();
  i++;


  if (all || test == i) test1_space_get_gdesc();
  i++;
  if (all || test == i) test2_space_get_gdesc();
  i++;


  if (all || test == i) test1_space_set_light_status();
  i++;
  if (all || test == i) test2_space_set_light_status();
  i++;


  if (all || test == i) test1_space_get_light_status();
  i++;
  if (all || test == i) test2_space_get_light_status();
  i++;



  if (all || test == i) test1_space_set_floor();
  i++;
  if (all || test == i) test2_space_set_floor();
  i++;


  if (all || test == i) test1_space_get_floor();
  i++;
  if (all || test == i) test2_space_get_floor();
  i++;


  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/*  space_create */
void test1_space_create()
{
  int result;
  Space *s;
  s = space_create(5);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}
void test2_space_create()
{
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

/*  space_destroy*/
void test1_space_destroy()
{
  Space *s = NULL;
  s = space_create(1);
  PRINT_TEST_RESULT(space_destroy(s) == OK);
}
void test2_space_destroy()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_destroy(s) == ERROR);
}

/*  space_set_name*/
void test1_space_set_name()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}
void test2_space_set_name()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}
void test3_space_set_name()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

/*  space_set_link */
void test1_space_set_link()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, 4, ND) == ERROR);
  space_destroy(s);
}

void test1_space_set_link_north()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, 4, N) == OK);
  space_destroy(s);
}
void test2_space_set_link_north()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_link(s, 4, N) == ERROR);
}
void test3_space_set_link_north()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, NO_ID, N) == ERROR);
}

void test1_space_set_link_south()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, 4, S) == OK);
  space_destroy(s);
}
void test2_space_set_link_south()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_link(s, 4, S) == ERROR);
}
void test3_space_set_link_south()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, NO_ID, S) == ERROR);
}

void test1_space_set_link_east()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, 4, E) == OK);
  space_destroy(s);
}
void test2_space_set_link_east()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_link(s, 4, E) == ERROR);
}
void test3_space_set_link_east()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, NO_ID, E) == ERROR);
}

void test1_space_set_link_west()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, 4, W) == OK);
  space_destroy(s);
}
void test2_space_set_link_west()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_link(s, 4, W) == ERROR);
}
void test3_space_set_link_west()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_link(s, NO_ID, W) == ERROR);
}

/*  space_get_id*/
void test1_space_get_id()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_get_id(s) == 5);
  space_destroy(s);
}
void test2_space_get_id()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/*  space_add_object*/
void test1_space_add_object()
{
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_objectid(s, 31) == OK);
  space_destroy(s);
}
void test2_space_add_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_objectid(s, 31) == ERROR);
}
void test3_space_add_object()
{
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_objectid(s, NO_ID) == ERROR);
  space_destroy(s);
}

/*  space_del_object*/
void test1_space_del_object()
{
  Space *s;
  s = space_create(1);
  space_add_objectid(s, 31);
  PRINT_TEST_RESULT(space_del_objectid(s, 31) == OK);
  space_destroy(s);
}
void test2_space_del_object()
{
  Space *s = NULL;
  s = space_create(1);
  space_add_objectid(s, 31);
  PRINT_TEST_RESULT(space_del_objectid(s, 32) == ERROR);
  space_destroy(s);
}
void test3_space_del_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_del_objectid(s, 31) == ERROR);
}

/*  space_get_object*/
void test1_space_get_object()
{
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_has_object(s, 31) == FALSE);
  space_destroy(s);
}
void test2_space_get_object()
{
  Space *s;
  s = space_create(1);
  space_add_objectid(s, 31);
  PRINT_TEST_RESULT(space_has_object(s, 31) == TRUE);
  space_destroy(s);
}
void test3_space_get_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_object(s, 31) == FALSE);
}

/*  space_get_name*/
void test1_space_get_name()
{
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}
void test2_space_get_name()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}


/*  space_get_link*/
void test1_space_get_link()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_get_link(s, ND) == NO_ID);
  space_destroy(s);
}

void test1_space_get_link_north()
{
  Space *s;
  s = space_create(5);
  space_set_link(s, 4, N);
  PRINT_TEST_RESULT(space_get_link(s, N) == 4);
  space_destroy(s);
}
void test2_space_get_link_north()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_link(s, N) == NO_ID);
}

void test1_space_get_link_south()
{
  Space *s;
  s = space_create(5);
  space_set_link(s, 2, S);
  PRINT_TEST_RESULT(space_get_link(s, S) == 2);
  space_destroy(s);
}
void test2_space_get_link_south()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_link(s, S) == NO_ID);
}

void test1_space_get_link_east()
{
  Space *s;
  s = space_create(5);
  space_set_link(s, 1, E);
  PRINT_TEST_RESULT(space_get_link(s, E) == 1);
  space_destroy(s);
}
void test2_space_get_link_east()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_link(s, E) == NO_ID);
}

void test1_space_get_link_west()
{
  Space *s;
  s = space_create(5);
  space_set_link(s, 6, W);
  PRINT_TEST_RESULT(space_get_link(s, W) == 6);
  space_destroy(s);
}
void test2_space_get_link_west()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_link(s, W) == NO_ID);
}

/*  space_set_gdesc*/
void test1_space_set_gdesc()
{
  Space *s = NULL;
  char **gdesc;
  s = space_create(5);
  gdesc = space_create_gdesc();
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
  space_destroy(s);
}
void test2_space_set_gdesc()
{
  Space *s = NULL;
  char *gdesc[TAM_GDESC_X] = {"123456789", "123456789", "123456789", "123456789", "123456789"};
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
}
void test3_space_set_gdesc()
{
  Space *s = NULL;
  char **gdesc = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
  space_destroy(s);
}

/*  space_get_desc*/
void test1_space_get_gdesc()
{
  Space *s = NULL;
  char **gdesc;
  s = space_create(5);
  gdesc = space_create_gdesc();
  
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
  space_destroy(s);
}
void test2_space_get_gdesc()
{
  Space *s = NULL;  
  PRINT_TEST_RESULT(space_get_gdesc(s) == NULL);
}

/* space_set_light_status*/
void test1_space_set_light_status()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_light_status(s, BRIGHT) == OK);
  space_destroy(s);
}
void test2_space_set_light_status()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_light_status(s, DARK) == ERROR);
}

/* space_get_light_status*/
void test1_space_get_light_status()
{
  Space *s;
  s = space_create(5);
  space_set_light_status(s, DARK);
  PRINT_TEST_RESULT(space_get_light_status(s) == DARK);
  space_destroy(s);
}
void test2_space_get_light_status()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_light_status(s) == UNKNOWN_LIGHT);
}


/* space_set_floor*/
void test1_space_set_floor()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_floor(s, DUNGEON) == OK);
  space_destroy(s);
}
void test2_space_set_floor()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_floor(s, DUNGEON) == ERROR);
}

/* space_get_floor*/
void test1_space_get_floor()
{
  Space *s;
  s = space_create(5);
  space_set_floor(s, DUNGEON);
  PRINT_TEST_RESULT(space_get_floor(s) == DUNGEON);
  space_destroy(s);
}
void test2_space_get_floor()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_floor(s) == UNKNOWN_FLOOR);
}
