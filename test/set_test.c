/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @author Miguel Soto
 * @version 3.0
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 33 /*!< It defines the maximun tests in this file */

/**
 * @brief Main function for set unit tests.
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
    printf("Running all test for module set:\n");
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
  if (all || test == i) test1_set_create();
  i++;

  if (all || test == i) test1_set_destroy();
  i++;
  if (all || test == i) test2_set_destroy();
  i++;

  if (all || test == i) test1_set_add();
  i++;
  if (all || test == i) test2_set_add();
  i++;
  if (all || test == i) test3_set_add();
  i++;

  if (all || test == i) test1_set_del_id();
  i++;
  if (all || test == i) test2_set_del_id();
  i++;
  if (all || test == i) test3_set_del_id();
  i++;

  if (all || test == i) test1_set_get_nids();
  i++;
  if (all || test == i) test2_set_get_nids();
  i++;

  if (all || test == i) test1_set_get_ids();
  i++;
  if (all || test == i) test2_set_get_ids();
  i++;

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/* set_create */
void test1_set_create()
{
  int result;
  Set *s = NULL;
  s = set_create(5);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  set_destroy(s);
}

/* set_destroy */
void test1_set_destroy()
{
  Set *s = NULL;
  s = set_create();
  PRINT_TEST_RESULT(set_destroy(s) == OK);
}
void test2_set_destroy()
{
  Set *s = NULL;
  PRINT_TEST_RESULT(set_destroy(s) == ERROR);
}

/* set_add */
void test1_set_add()
{
  Set *s = NULL;
  Id id = 31;
  s = set_create();
  PRINT_TEST_RESULT(set_add(s, id) == OK);
  set_destroy(s);
}
void test2_set_add()
{
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add(s, 31) == ERROR);
}
void test3_set_add()
{
  Set *s = NULL;
  s = set_create();
  PRINT_TEST_RESULT(set_add(s, NO_ID) == ERROR);
  set_destroy(s);
}

/* set_del_id */
void test1_set_del_id()
{
  Set *s = NULL;
  Id id = 31;
  s = set_create();
  set_add(s, id);
  PRINT_TEST_RESULT(set_del_id(s, id) == OK);
  set_destroy(s);
}
void test2_set_del_id()
{
  Set *s = NULL;
  Id id = 31;
  s = set_create();
  set_add(s, id);
  PRINT_TEST_RESULT(set_del_id(s, 30) == ERROR);
  set_destroy(s);
}
void test3_set_del_id()
{
  Set *s = NULL;
  s = set_create();
  PRINT_TEST_RESULT(set_del_id(s, NO_ID) == ERROR);
  set_destroy(s);
}

/* set_get_nids */
void test1_set_get_nids()
{
  Set *s = NULL;
  Id id = 31;
  s = set_create();
  set_add(s, id);
  PRINT_TEST_RESULT(set_get_nids(s) == 1);
  set_destroy(s);
}
void test2_set_get_nids()
{
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_nids(s) == -1);
}

/* set_get_id */
void test1_set_get_ids()
{
  Set *s = NULL;
  Id id = 31;
  s = set_create();
  set_add(s, id);
  PRINT_TEST_RESULT(set_get_ids(s) != NULL);
  set_destroy(s);
}
void test2_set_get_ids()
{
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_ids(s) == NULL);
}

