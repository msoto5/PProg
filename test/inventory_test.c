/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @author Profesores Pprog
 * @version 3.0
 * @date 30-03-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 23 /*!< It defines the maximun tests in this file */

/**
 * @brief Main function for inventory unit tests.
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
    printf("Running all test for module inventory:\n");
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
  if (all || test == i) test1_inventory_create();
  i++;
  if (all || test == i) test2_inventory_create();
  i++;

  if (all || test == i) test1_inventory_destroy();
  i++;
  if (all || test == i) test2_inventory_destroy();
  i++;

  if (all || test == i) test1_inventory_set_objects();
  i++;
  if (all || test == i) test2_inventory_set_objects();
  i++;
  if (all || test == i) test3_inventory_set_objects();
  i++;

  if (all || test == i) test1_inventory_get_objects();
  i++;
  if (all || test == i) test2_inventory_get_objects();
  i++;

  if (all || test == i) test1_inventory_set_maxObjs();
  i++;
  if (all || test == i) test2_inventory_set_maxObjs();
  i++;

  if (all || test == i) test1_inventory_get_maxObjs();
  i++;
  if (all || test == i) test2_inventory_get_maxObjs();
  i++;
  if (all || test == i) test3_inventory_get_maxObjs();
  i++;


  if (all || test == i) test1_inventory_add_object();
  i++;
  if (all || test == i) test2_inventory_add_object();
  i++;
  if (all || test == i) test3_inventory_add_object();
  i++;

  if (all || test == i) test1_inventory_remove_object();
  i++;
  if (all || test == i) test2_inventory_remove_object();
  i++;
  if (all || test == i) test3_inventory_remove_object();
  i++;

  if (all || test == i) test1_inventory_has_id();
  i++;
  if (all || test == i) test2_inventory_has_id();
  i++;
	if (all || test == i) test3_inventory_has_id();
  i++;

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/* inventory_create */
void test1_inventory_create()
{
  int result;
  Inventory *v;
  v = inventory_create();
  result = v != NULL;
  PRINT_TEST_RESULT(result);
  inventory_destroy(v);
}
void test2_inventory_create()
{
  Inventory *s = NULL;
  s = inventory_create(4);
  PRINT_TEST_RESULT(s != NULL);
  inventory_destroy(s);
}

/* inventory_destroy */
void test1_inventory_destroy()
{
  Inventory *s = NULL;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_destroy(s) == OK);
}
void test2_inventory_destroy()
{
  Inventory *s = NULL;
  PRINT_TEST_RESULT(inventory_destroy(s) == ERROR);
}

/*inventory_set_objects */
void test1_inventory_set_objects()
{
  Inventory *s = NULL;
  Set *set;
  s = inventory_create(4);
  set = set_create();
  set_add(set, 80);
  PRINT_TEST_RESULT(inventory_set_objects(s, set) == OK);
  inventory_destroy(s);
} 

void test2_inventory_set_objects()
{
  Inventory *s = NULL;
  Set *set;
  set = set_create();
  set_add(set, 80);
  PRINT_TEST_RESULT(inventory_set_objects(s, set) == ERROR);
  set_destroy(set);
} 

void test3_inventory_set_objects()
{
  Inventory *s = NULL;
  Set *set = NULL;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_set_objects(s, set) == ERROR);
  inventory_destroy(s);
} 

/*inventory_get_objects*/
void test1_inventory_get_objects()
{
  Inventory *s = NULL;
  Set *set;
  s = inventory_create();

  set = set_create();
  set_add(set, 80);
	inventory_set_objects(s, set);
  PRINT_TEST_RESULT(inventory_get_objects(s) != NULL);
  inventory_destroy(s);
}
  
void test2_inventory_get_objects()
{
  Inventory *s = NULL;
	PRINT_TEST_RESULT(inventory_get_objects(s)==NULL);
}
  
/*inventory_set_maxObjs */
void  test1_inventory_set_maxObjs()
{
  Inventory *s = NULL;
  s = inventory_create();
	PRINT_TEST_RESULT(inventory_set_maxObjs(s, 10)==OK);
	inventory_destroy(s);
}
 
void  test2_inventory_set_maxObjs()
{
	Inventory *s = NULL;
  s = NULL;
	PRINT_TEST_RESULT(inventory_set_maxObjs(s, 10)==ERROR);
}

/*inventory_get_maxObjs */
void   test1_inventory_get_maxObjs()
{
	Inventory *s = NULL;
  s = inventory_create();
  inventory_set_maxObjs(s, 10);
	PRINT_TEST_RESULT(inventory_get_maxObjs(s)==10);
	inventory_destroy(s);
}

void   test2_inventory_get_maxObjs()
{
  Inventory *s = NULL;
  s = inventory_create();
  inventory_set_maxObjs(s, 10);
	PRINT_TEST_RESULT(inventory_get_maxObjs(s)!=7);
	inventory_destroy(s);
}

void   test3_inventory_get_maxObjs()
{
	Inventory *s = NULL;
  inventory_set_maxObjs(s, 10);
	PRINT_TEST_RESULT(inventory_get_maxObjs(s)==NO_ID);
}
  
/* inventory_add_object */
void test1_inventory_add_object()
{
  Inventory *s = NULL;
  s = inventory_create(4);
  inventory_set_maxObjs(s, 5);
  PRINT_TEST_RESULT(inventory_add_object(s, 9) == OK);
  inventory_destroy(s);
}

void test2_inventory_add_object()
{
  Inventory *s = NULL;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_add_object(s, 9) == ERROR);
  inventory_destroy(s);
}

void test3_inventory_add_object()
{
  Inventory *s = NULL;
  PRINT_TEST_RESULT(inventory_add_object(s, 9) == ERROR);
}

/* inventory_remove_object */
void test1_inventory_remove_object()
{
  Inventory *s = NULL;
  Id id = 9;
  s = inventory_create();
  inventory_set_maxObjs(s, 5);
  inventory_add_object(s, id);
  PRINT_TEST_RESULT(inventory_remove_object(s, id) == OK);
  inventory_destroy(s);
}

void test2_inventory_remove_object()
{
  Inventory *s = NULL;
  s = inventory_create(4);
  PRINT_TEST_RESULT(inventory_remove_object(s, 9) == ERROR);
  inventory_destroy(s);
}

void test3_inventory_remove_object()
{
  Inventory *s = NULL;
  PRINT_TEST_RESULT(inventory_remove_object(s, 9) == ERROR);
}

/* inventory_has_id */
void test1_inventory_has_id()
{
  Inventory *s = NULL;
  s = inventory_create(4);
  inventory_set_maxObjs(s, 5);
  inventory_add_object(s, 9);
  PRINT_TEST_RESULT(inventory_has_id(s, 9) == TRUE);
  inventory_destroy(s);
}

void test2_inventory_has_id()
{
  Inventory *s = NULL;
  s = inventory_create(4);
  inventory_add_object(s, 9);
  PRINT_TEST_RESULT(inventory_has_id(s, 8) == FALSE);
  inventory_destroy(s);
}

void test3_inventory_has_id()
{
  Inventory *s = NULL;
  PRINT_TEST_RESULT(inventory_has_id(s, 9) == FALSE);
}
