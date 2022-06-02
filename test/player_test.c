/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Profesores Pprog
 * @version 3.0
 * @date 30-03-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 48 /*!< It defines the maximun tests in this file */

/**
 * @brief Main function for player unit tests.
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
    printf("Running all test for module player:\n");
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
  if (all || test == i) test1_player_create();
  i++;
  if (all || test == i) test2_player_create();
  i++;
	if (all || test == i) test3_player_create();
  i++;

  if (all || test == i) test1_player_destroy();
  i++;
  if (all || test == i) test2_player_destroy();
  i++;

	if (all || test == i) test1_player_get_id();
  i++;
  if (all || test == i) test2_player_get_id();
  i++;

  if (all || test == i) test1_player_test_id();
  i++;
  if (all || test == i) test2_player_test_id();
  i++;
  if (all || test == i) test3_player_test_id();
  i++;

  if (all || test == i) test1_player_set_name();
  i++;
  if (all || test == i) test2_player_set_name();
  i++;

  if (all || test == i) test1_player_get_name();
  i++;
  if (all || test == i) test2_player_get_name();
  i++;
  if (all || test == i) test3_player_get_name();
  i++;

  if (all || test == i) test1_player_set_location();
  i++;
  if (all || test == i) test2_player_set_location();
  i++;


  if (all || test == i) test1_player_get_location();
  i++;
  if (all || test == i) test2_player_get_location();
  i++;
  if (all || test == i) test3_player_get_location();
  i++;

	if (all || test == i) test1_player_get_inventory();
  i++;
  if (all || test == i) test2_player_get_inventory();
  i++;

  if (all || test == i) test1_player_set_health();
  i++;
  if (all || test == i) test2_player_set_health();
  i++;

  if (all || test == i) test1_player_set_max_health();
  i++;
  if (all || test == i) test2_player_set_max_health();
  i++;

	if (all || test == i) test1_player_get_health();
  i++;
  if (all || test == i) test2_player_get_health();
  i++;
  if (all || test == i) test3_player_get_health();
  i++;

	if (all || test == i) test1_player_set_max_inventory();
  i++;
  if (all || test == i) test2_player_set_max_inventory();
  i++;

	if (all || test == i) test1_player_add_object();
  i++;
  if (all || test == i) test2_player_add_object();
  i++;
  if (all || test == i) test3_player_add_object();
  i++;

	if (all || test == i) test1_player_del_object();
  i++;
  if (all || test == i) test2_player_del_object();
  i++;
  if (all || test == i) test3_player_del_object();
  i++;

	if (all || test == i) test1_player_has_object();
  i++;
  if (all || test == i) test2_player_has_object();
  i++;
  if (all || test == i) test3_player_has_object();
  i++;

  if (all || test == i) test1_player_get_crit();
  i++;
  if (all || test == i) test2_player_get_crit();
  i++;

  if (all || test == i) test1_player_set_crit();
  i++;
  if (all || test == i) test2_player_set_crit();
  i++;

  if (all || test == i) test1_player_get_baseDmg();
  i++;
  if (all || test == i) test2_player_get_baseDmg();
  i++;

  if (all || test == i) test1_player_set_baseDmg();
  i++;
  if (all || test == i) test2_player_set_baseDmg();
  i++;

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/* player_create */
void test1_player_create()
{
  int result;
  Player *p;
  p = player_create(25);
  result = p != NULL;
  PRINT_TEST_RESULT(result);
  player_destroy(p);
}
void test2_player_create()
{
  Player *s = NULL;
  s = player_create(24);
  PRINT_TEST_RESULT(s != NULL);
  player_destroy(s);
}

void test3_player_create()
{
  Player *s = NULL;
  s = player_create(NO_ID);
  PRINT_TEST_RESULT(s == NULL);
}

/* player_destroy */
void test1_player_destroy()
{
  Player *p = NULL;
  p = player_create(24);
  PRINT_TEST_RESULT(player_destroy(p) == OK);
}
void test2_player_destroy()
{
  Player *p = NULL;
  PRINT_TEST_RESULT(player_destroy(p) == ERROR);
}

/*player_get_id */
void test1_player_get_id()
{
  Player *p = NULL;
  p = player_create(24);
  PRINT_TEST_RESULT(player_get_id(p) == 24);
  player_destroy(p);
} 

void test2_player_get_id()
{
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}

/*player_get_objects*/
void test1_player_test_id()
{
  Player *p = NULL;
  p = player_create(24);
  PRINT_TEST_RESULT(player_test_id(24) == OK);
  player_destroy(p);
}
  
void test2_player_test_id()
{
  Player *p = NULL;
  p = player_create(33);
  PRINT_TEST_RESULT(player_test_id(33)==ERROR);
	player_destroy(p);
}

void test3_player_test_id()
{
  PRINT_TEST_RESULT(player_test_id(10)==ERROR);
}
  
/*player_set_name */
void  test1_player_set_name()
{
  Player *p = NULL;
  p = player_create(23);
	PRINT_TEST_RESULT(player_set_name(p, "Carlos")==OK);
	player_destroy(p);
}
 
void  test2_player_set_name()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_set_name(p, "Carlos")==ERROR);
}

/*player_get_name */
void   test1_player_get_name()
{
	Player *p = NULL;
  p = player_create(24);
  player_set_name(p, "Carlos");
	PRINT_TEST_RESULT(strcmp(player_get_name(p), "Carlos") == 0);
	player_destroy(p);
}

void   test2_player_get_name()
{
  Player *p = NULL;
  p = player_create(24);
  player_set_name(p, "Carlos");
	PRINT_TEST_RESULT(strcmp(player_get_name(p), "Alberto") != 0);
	player_destroy(p);
}

void   test3_player_get_name()
{
	Player *s = NULL;
	PRINT_TEST_RESULT(player_get_name(s)==NULL);
}

/*player_set_location */
void  test1_player_set_location()
{
  Player *p = NULL;
  p = player_create(23);
	PRINT_TEST_RESULT(player_set_location(p, 12)==OK);
	player_destroy(p);
}
 
void  test2_player_set_location()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_set_location(p, 12)==ERROR);
}

/*player_get_location */
void   test1_player_get_location()
{
	Player *p = NULL;
  p = player_create(24);
  player_set_location(p, 12);
	PRINT_TEST_RESULT(player_get_location(p) == 12);
	player_destroy(p);
}

void   test2_player_get_location()
{
  Player *p = NULL;
  p = player_create(24);
  player_set_location(p, 12);
	PRINT_TEST_RESULT(player_get_location(p) != 13);
	player_destroy(p);
}

void   test3_player_get_location()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_get_location(p)==NO_ID);
}
  
/* player_get_inventory */
void test1_player_get_inventory()
{
  Player *p = NULL;
  p = player_create(24);
  PRINT_TEST_RESULT(player_get_inventory(p) != NULL);
  player_destroy(p);
}

void test2_player_get_inventory()
{
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_inventory(p) == NULL);
}

/*player_set_health */
void  test1_player_set_health()
{
  Player *p = NULL;
  p = player_create(23);
  player_set_max_health(p, 20);
	PRINT_TEST_RESULT(player_set_health(p, 12)==OK);
	player_destroy(p);
}
 
void  test2_player_set_health()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_set_health(p, 12)==ERROR);
}

/*player_set_max_health */
void  test1_player_set_max_health()
{
  Player *p = NULL;
  p = player_create(23);
	PRINT_TEST_RESULT(player_set_max_health(p, 20)==OK);
	player_destroy(p);
}
 
void  test2_player_set_max_health()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_set_max_health(p, 20)==ERROR);
}

/*player_get_location */
void   test1_player_get_health()
{
	Player *p = NULL;
  p = player_create(24);
  player_set_max_health(p, 20);
  player_set_health(p, 12);
	PRINT_TEST_RESULT(player_get_health(p) == 12);
	player_destroy(p);
}

void   test2_player_get_health()
{
  Player *p = NULL;
  p = player_create(24);
  player_set_health(p, 12);
	PRINT_TEST_RESULT(player_get_health(p) != 13);
	player_destroy(p);
}

void   test3_player_get_health()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_get_health(p) == -1);
}

/* player_remove_object */
void test1_player_set_max_inventory()
{
  Player *p = NULL;
  p = player_create(24);
  PRINT_TEST_RESULT(player_set_max_inventory(p, 5) == OK);
  player_destroy(p);
}

void test2_player_set_max_inventory()
{
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_max_inventory(p, 5) == ERROR);
}

/* player_add_object */
void test1_player_add_object()
{
  Player *p = NULL;
  Object *o = NULL;
  p = player_create(24);
	o = obj_create(31);
  player_set_max_inventory(p, 5);
  PRINT_TEST_RESULT( player_add_object(p, o) == OK);
  player_destroy(p);
	obj_destroy(o);
}

void test2_player_add_object()
{
  Player *p = NULL;
  Object *o = NULL;
  p = player_create(24);
  player_set_max_inventory(p, 5);
  PRINT_TEST_RESULT( player_add_object(p, o) == ERROR);
  player_destroy(p);
}

void test3_player_add_object()
{
  Player *p = NULL;
	Object *o = NULL;
  player_set_max_inventory(p, 5);
  PRINT_TEST_RESULT( player_add_object(p, o) == ERROR);
}

/* player_del_object */
void test1_player_del_object()
{
  Player *p = NULL;
  Object *o = NULL;
  Id id;
  p = player_create(24);
	o = obj_create(31);
  player_set_max_inventory(p, 5);
	player_add_object(p, o);
	id = obj_get_id(o);
  PRINT_TEST_RESULT( player_del_object(p, id) == OK);
  player_destroy(p);
	obj_destroy(o);
}

void test2_player_del_object()
{
  Player *p = NULL;
	Object *o = NULL;  
  Id id;
  p = player_create(24);
  player_set_max_inventory(p, 5);
	player_add_object(p, o);
	id = obj_get_id(o);
  PRINT_TEST_RESULT( player_del_object(p, id) == ERROR);
  player_destroy(p);
}

void test3_player_del_object()
{
  Player *p = NULL;
	Object *o = NULL;
  player_set_max_inventory(p, 5);
  PRINT_TEST_RESULT( player_add_object(p, o) == ERROR);
}

/* player_has_object */
void test1_player_has_object()
{
  Player *p = NULL;
  Object *o = NULL;
  Id id;
  p = player_create(24);
	o = obj_create(31);
  player_set_max_inventory(p, 5);
	player_add_object(p, o);
	id = obj_get_id(o);
  PRINT_TEST_RESULT( player_has_object(p, id) == TRUE);
  player_destroy(p);
	obj_destroy(o);
}

void test2_player_has_object()
{
  Player *p = NULL;
  Object *o = NULL;
  Id id;
  p = player_create(24);
  player_set_max_inventory(p, 5);
	player_add_object(p, o);
	id = obj_get_id(o);
  PRINT_TEST_RESULT( player_has_object(p, id) == FALSE);
  player_destroy(p);
}

void test3_player_has_object()
{
  Player *p = NULL;
  player_set_max_inventory(p, 5);
  PRINT_TEST_RESULT( player_has_object(p, NO_ID) == FALSE);
}

/*player_get_crit */
void  test1_player_get_crit()
{
  Player *s;
  s = player_create(4);
	player_set_crit(s, 3);
	PRINT_TEST_RESULT(player_get_crit(s)==3);
	player_destroy(s);
}
 
void  test2_player_get_crit()
{
	Player *s = NULL;
  s = NULL;
	PRINT_TEST_RESULT(player_get_crit(s)==(0));
}

/*player_set_crit */
void   test1_player_set_crit()
{
	Player *s;
  s = player_create(4);
	PRINT_TEST_RESULT(player_set_crit(s, 3)==OK);
	player_destroy(s);
}

void   test2_player_set_crit()
{
	Player *s = NULL;
	PRINT_TEST_RESULT(player_set_crit(s, -1)==ERROR);
}
  
/*player_get_baseDmg */
void  test1_player_get_baseDmg()
{
  Player *s;
  s = player_create(4);
	player_set_baseDmg(s, 3);
	PRINT_TEST_RESULT(player_get_baseDmg(s)==3);
	player_destroy(s);
}
 
void  test2_player_get_baseDmg()
{
	Player *s = NULL;
  s = NULL;
	PRINT_TEST_RESULT(player_get_baseDmg(s)==(0));
}

/*player_set_baseDmg */
void   test1_player_set_baseDmg()
{
	Player *s;
  s = player_create(4);
	PRINT_TEST_RESULT(player_set_baseDmg(s, 3)==OK);
	player_destroy(s);
}

void   test2_player_set_baseDmg()
{
	Player *s = NULL;
	PRINT_TEST_RESULT(player_set_baseDmg(s, -1)==ERROR);
}