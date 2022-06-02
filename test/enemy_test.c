/**
 * @brief It tests enemy module
 *
 * @file enemy_test.c
 * @author Profesores Pprog
 * @version 3.0
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/enemy.h"
#include "enemy_test.h"
#include "test.h"

#define MAX_TESTS 41  /*!< It defines the maximun tests in this file */

/**
 * @brief Main function for enemy unit tests.
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
    printf("Running all test for module enemy:\n");
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
  if (all || test == i) test1_enemy_create();
  i++;
  if (all || test == i) test2_enemy_create();
  i++;

  if (all || test == i) test1_enemy_destroy();
  i++;
  if (all || test == i) test2_enemy_destroy();
  i++;

  if (all || test == i) test1_enemy_set_name();
  i++;
  if (all || test == i) test2_enemy_set_name();
  i++;
  if (all || test == i) test3_enemy_set_name();
  i++;

  if (all || test == i) test1_enemy_get_name();
  i++;
  if (all || test == i) test2_enemy_get_name();
  i++;

  if (all || test == i) test1_enemy_get_id();
  i++;
  if (all || test == i) test2_enemy_get_id();
  i++;

  if (all || test == i) test1_enemy_test_id();
  i++;
  if (all || test == i) test2_enemy_test_id();
  i++;
  if (all || test == i) test3_enemy_test_id();
  i++;


  if (all || test == i) test1_enemy_get_location();
  i++;
  if (all || test == i) test2_enemy_get_location();
  i++;

  if (all || test == i) test1_enemy_get_health();
  i++;
  if (all || test == i) test2_enemy_get_health();
  i++;

  if (all || test == i) test1_enemy_set_health();
  i++;
  if (all || test == i) test2_enemy_set_health();
  i++;
	if (all || test == i) test3_enemy_set_health();
  i++;
  
  if (all || test == i) test1_enemy_set_location();
  i++;
  if (all || test == i) test2_enemy_set_location();
  i++;

  if (all || test == i) test1_enemy_get_crit();
  i++;
  if (all || test == i) test2_enemy_get_crit();
  i++;

  if (all || test == i) test1_enemy_set_crit();
  i++;
  if (all || test == i) test2_enemy_set_crit();
  i++;

  if (all || test == i) test1_enemy_get_baseDmg();
  i++;
  if (all || test == i) test2_enemy_get_baseDmg();
  i++;

  if (all || test == i) test1_enemy_set_baseDmg();
  i++;
  if (all || test == i) test2_enemy_set_baseDmg();
  i++;

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/* enemy_create */
void test1_enemy_create()
{
  int result;
  Enemy *s;
  s = enemy_create(4);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  enemy_destroy(s);
}
void test2_enemy_create()
{
  Enemy *s;
  s = enemy_create(4);
  PRINT_TEST_RESULT(enemy_get_id(s) == 4);
  enemy_destroy(s);
}

/* enemy_destroy */
void test1_enemy_destroy()
{
  Enemy *s = NULL;
  s = enemy_create(4);
  PRINT_TEST_RESULT(enemy_destroy(s) == OK);
}
void test2_enemy_destroy()
{
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_destroy(s) == ERROR);
}

/* enemy_set_name */
void test1_enemy_set_name()
{
  Enemy *s;
  s = enemy_create(4);
  PRINT_TEST_RESULT(enemy_set_name(s, "hola") == OK);
  enemy_destroy(s);
}
void test2_enemy_set_name()
{
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_set_name(s, "hola") == ERROR);
}
void test3_enemy_set_name()
{
  Enemy *s;
  s = enemy_create(4);
  PRINT_TEST_RESULT(enemy_set_name(s, NULL) == ERROR);
  enemy_destroy(s);
}



/* enemy_get_id */
void test1_enemy_get_id()
{
  Enemy *s = NULL;
  s = enemy_create(4);
  PRINT_TEST_RESULT(enemy_get_id(s) == 4);
  enemy_destroy(s);
}
void test2_enemy_get_id()
{
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_get_id(s) == NO_ID);
}

/* enemy_get_name */
void test1_enemy_get_name()
{
  Enemy *s;
  s = enemy_create(4);
  enemy_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(enemy_get_name(s), "adios") == 0);
  enemy_destroy(s);
}
void test2_enemy_get_name()
{
  Enemy *s = NULL;
  PRINT_TEST_RESULT(enemy_get_name(s) == NULL);
}


/*enemy_test_id */
void test1_enemy_test_id()
{
  PRINT_TEST_RESULT(enemy_test_id(-1)==ERROR);
} 

void test2_enemy_test_id()
{
  PRINT_TEST_RESULT(enemy_test_id(1)==ERROR);
} 

void test3_enemy_test_id()
{
  PRINT_TEST_RESULT(enemy_test_id(42)==OK);
} 

/*enemy_get_location */
void test1_enemy_get_location()
{
  Enemy *s;
  s = enemy_create(4);
	enemy_set_location(s, 11);
	PRINT_TEST_RESULT(enemy_get_location(s)==11);
	enemy_destroy(s);
}
  
void test2_enemy_get_location()
{
  Enemy *s;
  s = NULL;
	PRINT_TEST_RESULT(enemy_get_location(s)==NO_ID);
}
  
/*enemy_get_health */
void  test1_enemy_get_health()
{
  Enemy *s;
  s = enemy_create(4);
	enemy_set_health(s, 3);
	PRINT_TEST_RESULT(enemy_get_health(s)==3);
	enemy_destroy(s);
}
 
void  test2_enemy_get_health()
{
	Enemy *s;
  s = NULL;
	PRINT_TEST_RESULT(enemy_get_health(s)==(-1));
}

/*enemy_set_health */
void   test1_enemy_set_health()
{
	Enemy *s;
  s = enemy_create(4);
	PRINT_TEST_RESULT(enemy_set_health(s, 3)==OK);
	enemy_destroy(s);
}

void   test2_enemy_set_health()
{
	Enemy *s;
  s = enemy_create(4);
	PRINT_TEST_RESULT(enemy_set_health(s, -1)==ERROR);
	enemy_destroy(s);
}
  
void  test3_enemy_set_health()
{
	Enemy *s;
  s = NULL;
	PRINT_TEST_RESULT(enemy_set_health(s,2)==ERROR);
}
 
/*enemy_set_location  */
void   test1_enemy_set_location()
{
	Enemy *s;
  s = enemy_create(4);
	PRINT_TEST_RESULT(enemy_set_location(s, 11)==OK);
	enemy_destroy(s);
}
  
void   test2_enemy_set_location()
{
	Enemy *s;
  s = NULL;
	PRINT_TEST_RESULT(enemy_set_location(s,2)==ERROR);
}
  
/*enemy_get_crit */
void  test1_enemy_get_crit()
{
  Enemy *s;
  s = enemy_create(4);
	enemy_set_crit(s, 3);
	PRINT_TEST_RESULT(enemy_get_crit(s)==3);
	enemy_destroy(s);
}
 
void  test2_enemy_get_crit()
{
	Enemy *s = NULL;
  s = NULL;
	PRINT_TEST_RESULT(enemy_get_crit(s)==(0));
}

/*enemy_set_crit */
void   test1_enemy_set_crit()
{
	Enemy *s;
  s = enemy_create(4);
	PRINT_TEST_RESULT(enemy_set_crit(s, 3)==OK);
	enemy_destroy(s);
}

void   test2_enemy_set_crit()
{
	Enemy *s = NULL;
	PRINT_TEST_RESULT(enemy_set_crit(s, -1)==ERROR);
}
  
/*enemy_get_baseDmg */
void  test1_enemy_get_baseDmg()
{
  Enemy *s;
  s = enemy_create(4);
	enemy_set_baseDmg(s, 3);
	PRINT_TEST_RESULT(enemy_get_baseDmg(s)==3);
	enemy_destroy(s);
}
 
void  test2_enemy_get_baseDmg()
{
	Enemy *s = NULL;
  s = NULL;
	PRINT_TEST_RESULT(enemy_get_baseDmg(s)==(0));
}

/*enemy_set_baseDmg */
void   test1_enemy_set_baseDmg()
{
	Enemy *s;
  s = enemy_create(4);
	PRINT_TEST_RESULT(enemy_set_baseDmg(s, 3)==OK);
	enemy_destroy(s);
}

void   test2_enemy_set_baseDmg()
{
	Enemy *s = NULL;
	PRINT_TEST_RESULT(enemy_set_baseDmg(s, -1)==ERROR);
}