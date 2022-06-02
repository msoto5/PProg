/**
 * @brief It tests dialogue module
 *
 * @file dialogue_test.c
 * @author Ignacio Nunnez
 * @version 3.0
 * @date 07-05-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dialogue.h"
#include "dialogue_test.h"
#include "test.h"

#define MAX_TESTS 14  /*!< It defines the maximun tests in this file */

int main(int argc, char **argv)
{

  int test = 0;
  int all = 1, i;

  if (argc < 2)
  {
    printf("Running all test for module dialogue:\n");
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
  if (all || test == i) test1_dialogue_create();
  i++;
  if (all || test == i) test2_dialogue_create();
  i++;

  if (all || test == i) test1_dialogue_destroy();
  i++;
  if (all || test == i) test2_dialogue_destroy();
  i++;

  if (all || test == i) test1_dialogue_reset();
  i++;
  if (all || test == i) test2_dialogue_reset();
  i++;

	if (all || test == i) test1_dialogue_get_command();
  i++;
  if (all || test == i) test2_dialogue_get_command();
  i++;

  if (all || test == i) test1_dialogue_get_event();
  i++;
  if (all || test == i) test2_dialogue_get_event();
  i++;

  if (all || test == i) test1_dialogue_get_error();
  i++;
  if (all || test == i) test2_dialogue_get_error();
  i++;  

  if (all || test == i) test1_dialogue_set_command();
  i++;
  if (all || test == i) test2_dialogue_set_command();
  i++;
  
  if (all || test == i) test1_dialogue_set_event();
  i++;
  if (all || test == i) test2_dialogue_set_event();
  i++;
  
  if (all || test == i) test1_dialogue_set_error();
  i++;
  if (all || test == i) test2_dialogue_set_error();
  i++;

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/*dialogue_create*/
void test1_dialogue_create(){
	int result;
  Dialogue *d;
  d = dialogue_create();
  result = d != NULL;
  PRINT_TEST_RESULT(result);
  dialogue_destroy(d);
}

void test2_dialogue_create()
{
  Dialogue *d = NULL;
  d = dialogue_create();
  PRINT_TEST_RESULT(d != NULL);
  dialogue_destroy(d);
}

/* inventory_destroy */
void test1_dialogue_destroy()
{
  Dialogue *d = NULL;
  d = dialogue_create();
  PRINT_TEST_RESULT(dialogue_destroy(d) == OK);
}

void test2_dialogue_destroy()
{
  Dialogue *d = NULL;
  PRINT_TEST_RESULT(dialogue_destroy(d) == ERROR);
}

/* dialogue_destroy */
void test1_dialogue_reset()
{
	Dialogue *d = NULL;
	d = dialogue_create();
	PRINT_TEST_RESULT(dialogue_reset(d) == OK);
	dialogue_destroy(d);
}

void test2_dialogue_reset()
{
	Dialogue *d = NULL;
	PRINT_TEST_RESULT(dialogue_reset(d) == ERROR);
}

/*dialogue_get_command*/
void test1_dialogue_get_command()
{
  Dialogue *d = NULL;
  Enemy *e = NULL;
	int condition = 4;

  d = dialogue_create();
  e = enemy_create(4);
  enemy_set_name(e, "Hola");

	dialogue_set_command(d, condition, NULL, NULL, e);
  PRINT_TEST_RESULT(dialogue_get_command(d) != NULL);
  dialogue_destroy(d);
  enemy_destroy(e);
}
  
void test2_dialogue_get_command()
{
  Dialogue *d = NULL;
	PRINT_TEST_RESULT(dialogue_get_command(d)==NULL);
}

/*dialogue_get_event*/
void test1_dialogue_get_event()
{
  Dialogue *d = NULL;
	int condition = 4;
  d = dialogue_create();

	dialogue_set_event(d, condition);
  PRINT_TEST_RESULT(dialogue_get_event(d) != NULL);
  dialogue_destroy(d);
}
  
void test2_dialogue_get_event()
{
  Dialogue *d = NULL;
	PRINT_TEST_RESULT(dialogue_get_event(d)==NULL);
}

/*dialogue_get_error*/
void test1_dialogue_get_error()
{
  Dialogue *d = NULL;
	int condition = 4;
  d = dialogue_create();

	dialogue_set_error(d, condition, NULL, NULL, NULL);
  PRINT_TEST_RESULT(dialogue_get_error(d) != NULL);
  dialogue_destroy(d);
}
  
void test2_dialogue_get_error()
{
  Dialogue *d = NULL;
	PRINT_TEST_RESULT(dialogue_get_error(d)==NULL);
}

/*dialogue_set_command*/
void test1_dialogue_set_command()
{
	Dialogue *d = NULL;
  Enemy *e = NULL;
  int condition = 4;
  
  d = dialogue_create();
  e = enemy_create(4);
  enemy_set_name(e, "Hola");

  PRINT_TEST_RESULT(dialogue_set_command(d, condition, NULL, NULL, e) == OK);
  dialogue_destroy(d);
  enemy_destroy(e);
}

void test2_dialogue_set_command()
{
	Dialogue *d = NULL;
	int condition = 4;
	PRINT_TEST_RESULT(dialogue_set_command(d, condition, NULL, NULL, NULL)==ERROR);
}

/*dialogue_set_event*/

void test1_dialogue_set_event()
{
	Dialogue *d = NULL;
  int condition = 4;

	d = dialogue_create();

	PRINT_TEST_RESULT(dialogue_set_event(d, condition) == OK);
  dialogue_destroy(d);
}

void test2_dialogue_set_event()
{
	Dialogue *d = NULL;
	int condition = 4;
	PRINT_TEST_RESULT(dialogue_set_event(d, condition)==ERROR);
}

/*dialogue_set_error*/
void test1_dialogue_set_error()
{
	Dialogue *d = NULL;
	int condition = 4;
  d = dialogue_create();

  PRINT_TEST_RESULT(dialogue_set_error(d, condition, NULL, NULL, NULL) == OK);
  dialogue_destroy(d);
}

void test2_dialogue_set_error()
{
	Dialogue *d = NULL;
	int condition = 4;
	PRINT_TEST_RESULT(dialogue_set_error(d, condition, NULL, NULL, NULL)==ERROR);
}
