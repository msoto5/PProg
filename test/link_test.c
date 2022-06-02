#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "test.h"
#include "../include/link.h"
#include "link_test.h"

#define MAX_TESTS 30  /*!< It defines the maximun tests in this file */
#define FD_ID_LINK 5 /*!< It defines the a valid link id, first digit must be 5 */

/**
 * @brief Main function for Link unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 */
int main(int argc, char **argv)
{

  int test = 0;
  int all = 1, i;

  if (argc < 2)
  {
    printf("Running all test for module Link:\n");
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
  if (all || test == i) test1_link_create();
  i++;
  if (all || test == i) test2_link_create();
  i++;

  if (all || test == i) test1_link_destroy();
  i++;
  if (all || test == i) test2_link_destroy();
  i++;

  if (all || test == i) test1_link_get_id();
  i++;
  if (all || test == i) test2_link_get_id();
  i++;

  if (all || test == i) test1_link_set_name();
  i++;
  if (all || test == i) test2_link_set_name();
  i++;
  if (all || test == i) test3_link_set_name();
  i++;

  if (all || test == i) test1_link_get_name();
  i++;
  if (all || test == i) test2_link_get_name();
  i++;

  if (all || test == i) test1_link_set_start();
  i++;
  if (all || test == i) test2_link_set_start();
  i++;

  if (all || test == i) test1_link_get_start();
  i++;
  if (all || test == i) test2_link_get_start();
  i++;

  if (all || test == i) test1_link_set_destination();
  i++;
  if (all || test == i) test2_link_set_destination();
  i++;

  if (all || test == i) test1_link_get_destination();
  i++;
  if (all || test == i) test2_link_get_destination();
  i++;

  if (all || test == i) test1_link_set_direction();
  i++;
  if (all || test == i) test2_link_set_direction();
  i++;

  if (all || test == i) test1_link_get_direction();
  i++;
  if (all || test == i) test2_link_get_direction();
  i++;

  if (all || test == i) test1_link_set_status();
  i++;
  if (all || test == i) test2_link_set_status();
  i++;

  if (all || test == i) test1_link_get_status();
  i++;
  if (all || test == i) test2_link_get_status();
  i++;

  if (all || test == i) test1_link_print();
  i++;
  
  PRINT_PASSED_PERCENTAGE;

  return 0;
}
/* link_create */
void test1_link_create()
{
  int result;
  Link *link = NULL;
  Id link_id = FD_ID_LINK*10 + 1;
  link = link_create(link_id);
  result = link != NULL;
  PRINT_TEST_RESULT(result);
  link_destroy(link);
}
void test2_link_create()
{
  Link *link = NULL;
  Id link_id = FD_ID_LINK*10 + 1;
  link = link_create(link_id);
  PRINT_TEST_RESULT(link_get_id(link) == link_id);
  link_destroy(link);
}

/* link_destroy*/
void test1_link_destroy()
{
  Link *link = NULL;
  Id link_id = FD_ID_LINK*10 + 1;
  link = link_create(link_id);
  PRINT_TEST_RESULT(link_destroy(link) == OK);
}
void test2_link_destroy()
{
  Link *link = NULL;
  PRINT_TEST_RESULT(link_destroy(link) == ERROR);
}


/*  link_get_id*/
void test1_link_get_id()
{
  Link *link = NULL;
  Id link_id = FD_ID_LINK*10 + 1;
  link = link_create(link_id);
  PRINT_TEST_RESULT(link_get_id(link) == link_id);
  link_destroy(link);
}
void test2_link_get_id()
{
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_id(link) == NO_ID);
}

/* link_set_name*/
void test1_link_set_name()
{
  Link *link;
  Id link_id = FD_ID_LINK*10 + 1;
  link = link_create(link_id);
  PRINT_TEST_RESULT(link_set_name(link, "hola") == OK);
  link_destroy(link);
}
void test2_link_set_name()
{
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_name(link, "hola") == ERROR);
}
void test3_link_set_name()
{
  Link *link;
  Id link_id = FD_ID_LINK*10 + 1;
  link = link_create(link_id);
  PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
  link_destroy(link);
}

/* link_get_name */
void test1_link_get_name()
{
  Link *link = NULL;
  link = link_create(1);
  link_set_name(link, "adios");
  PRINT_TEST_RESULT(strcmp(link_get_name(link), "adios") == 0);
  link_destroy(link);
}
void test2_link_get_name()
{
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_name(link) == NULL);
}

void test1_link_set_start(){
Link *link = NULL;
link = link_create(1);
PRINT_TEST_RESULT(link_set_start(link,11) == OK);
link_destroy(link);

}

void test2_link_set_start(){
Link *link = NULL;
PRINT_TEST_RESULT(link_set_start(link, NO_ID) == ERROR);
}


void test1_link_get_start(){
Link *link = NULL;
link = link_create(1);
link_set_start(link, 11);
PRINT_TEST_RESULT(link_get_start(link) == 11);
link_destroy(link);

}

void test2_link_get_start(){
Link *link = NULL;
PRINT_TEST_RESULT(link_get_start(link) == NO_ID);

}

void test1_link_set_destination(){
Link *link = NULL;
link = link_create(1);
PRINT_TEST_RESULT(link_set_destination(link, 11)== OK);
link_destroy(link);

}

void test2_link_set_destination(){
Link *link = NULL;
PRINT_TEST_RESULT(link_set_destination(link,NO_ID) == ERROR);

}

void test1_link_get_destination(){
Link *link = NULL;
link = link_create(1);
link_set_destination(link, 11);
PRINT_TEST_RESULT(link_get_destination(link) == 11);
link_destroy(link);

}

void test2_link_get_destination(){
Link *link = NULL;
PRINT_TEST_RESULT(link_get_destination(link) == NO_ID);

}

void test1_link_set_direction(){
Link *link = NULL;
link = link_create(1);
PRINT_TEST_RESULT(link_set_direction(link, 'N') == OK);
link_destroy(link);

}

void test2_link_set_direction(){
Link *link = NULL;
PRINT_TEST_RESULT(link_set_destination(link,ND) == ERROR);

}

void test1_link_get_direction(){
Link *link = NULL;
link = link_create(1);
link_set_direction(link, 'N');
PRINT_TEST_RESULT(link_get_direction(link) == 'N');
link_destroy(link);

}

void test2_link_get_direction(){
Link *link = NULL;
PRINT_TEST_RESULT(link_get_direction(link) == ND);

}

void test1_link_set_status(){
Link *link = NULL;
link = link_create(1);
PRINT_TEST_RESULT(link_set_status(link, OPEN_L) == OK);
link_destroy(link);

}

void test2_link_set_status(){
Link *link = NULL;
PRINT_TEST_RESULT(link_set_status(link, INT_MAX) == ERROR);
}

void test1_link_get_status(){
Link *link = NULL;
link = link_create(1);
link_set_status(link, OPEN_L);
PRINT_TEST_RESULT(link_get_status(link) == OPEN_L);
link_destroy(link);

}

void test2_link_get_status(){
Link *link = NULL;
PRINT_TEST_RESULT(link_get_status(link) == CLOSE);

}

void test1_link_print(){
Link *link = NULL;
PRINT_TEST_RESULT(link_print(link) == -1);

}



