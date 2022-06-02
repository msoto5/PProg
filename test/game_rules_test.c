/**
 * @brief It tests game_rules module
 *
 * @file game_rules_test.c
 * @author Ignacio Nunnez
 * @version 3.0
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game_rules.h"
#include "game_rules_test.h"
#include "test.h"

#define NUMBER_TEST 1000  /*!< It defines the number of tests in this file */

int main(int argc, char **argv)
{	
	int test;

	if(argc > 1)
	{
		test = atoi(argv[1]);
	}
	else{
		test = NUMBER_TEST;
	}

	test1_game_rules_get_event(test);

	PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_game_rules_get_event(int test)
{
	int i;
	float e0, e1, e2, e3, e4, e5;
	R_Event event;

	srand(time(NULL));

	fprintf(stdout, "Porcentages of happening for every event: \n");
  	fprintf(stdout, "Event nº0 (No event): %d%%\n", EVENT_ONE);
  	fprintf(stdout, "Event nº1: %d%%\n", 100 - EVENT_ONE);
  	fprintf(stdout, "Event nº2: %d%%\n", EVENT_TWO - EVENT_ONE);
  	fprintf(stdout, "Event nº3: %d%%\n", EVENT_THREE - EVENT_TWO);
  	fprintf(stdout, "Event nº4: %d%%\n", EVENT_FOUR - EVENT_THREE);
  	fprintf(stdout, "Event nº4: %d%%\n", EVENT_FIVE - EVENT_FOUR);

	for(e0=0, e1=0, e2=0, e3=0, e4=0, e5=0, i=0 ; i < test ; i++)
	{
		event = game_rules_get_event();
		PRINT_TEST_RESULT(event < -1);
		fprintf(stdout, "Random event for test %d: ", i+1);

		if(event == EVENT_CERO){
			fprintf(stdout, "Event 0\n");
			e0++;
		}
		else if(event == EVENT_ONE){
			fprintf(stdout, "Event 1\n");
			e1++;
		}
		else if(event == EVENT_TWO){
			fprintf(stdout, "Event 2\n");
			e2++;
		}
		else if(event == EVENT_THREE){
			fprintf(stdout, "Event 3\n");
			e3++;
		}
		else if(event == EVENT_FOUR){
			fprintf(stdout, "Event 4\n");
			e4++;
		}
		else if(event == EVENT_FIVE){
			fprintf(stdout, "Event 5\n");
			e5++;
		}
	}

	fprintf(stdout, "FINAL RESULTS:\n");
	fprintf(stdout, "Event 0 - Porcentage expected: %d%% --> Porcentage obtained: %.2f%%\n", EVENT_ONE, (e0*100)/test);
	fprintf(stdout, "Event 1 - Porcentage expected: %d%% --> Porcentage obtained: %.2f%%\n", EVENT_TWO - EVENT_ONE, (e1*100)/test);
	fprintf(stdout, "Event 2 - Porcentage expected: %d%% --> Porcentage obtained: %.2f%%\n", EVENT_THREE - EVENT_TWO, (e2*100)/test);
	fprintf(stdout, "Event 3 - Porcentage expected: %d%% --> Porcentage obtained: %.2f%%\n", EVENT_FOUR - EVENT_THREE, (e3*100)/test);
	fprintf(stdout, "Event 4 - Porcentage expected: %d%% --> Porcentage obtained: %.2f%%\n", EVENT_FIVE - EVENT_FOUR, (e4*100)/test);
	fprintf(stdout, "Event 5 - Porcentage expected: %d%% --> Porcentage obtained: %.2f%%\n", 100 - EVENT_FIVE, (e5*100)/test);

}