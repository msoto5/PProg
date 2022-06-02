/** 
 * @brief It declares the tests for the enemy module
 * 
 * @file enemy_test.h
 * @author Antonio Van-Oers Luis
 * @version 2.0 
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#ifndef enemy_TEST_H
#define enemy_TEST_H

/**
 * @test Test enemy creation
 * @pre enemy ID 
 * @post Non NULL pointer to enemy 
 */
void test1_enemy_create();
/**
 * @test Test enemy creation
 * @pre enemy ID 
 * @post enemy_ID == Supplied enemy Id
 */
void test2_enemy_create();


/**
 * @test Test free enemy
 * @pre pointer to enemy
 * @post pointer to enemy = NULL
 */
void test1_enemy_destroy();
/**
 * @test Test free enemy
 * @pre pointer to enemy = NULL
 * @post Output == ERROR
 */
void test2_enemy_destroy();

/**
 * @test Test enemy id_type
 * @pre negative id
 * @post Output == ERROR
 */
void test1_enemy_test_id();

/**
 * @test Test enemy id_type
 * @pre id that is not from an enemy
 * @post Output == ERROR
 */
void test2_enemy_test_id();

/**
 * @test Test enemy id_type
 * @pre id that matches enemy id requirements
 * @post Output == OK
 */
void test3_enemy_test_id();


/**
 * @test Test function for getting enemy id
 * @pre enemy id = 4
 * @post Output==4
 */
void test1_enemy_get_id();

/**
 * @test Test function for getting enemy id
 * @pre pointer to enemy = NULL
 * @post Output==NO_ID
 */
void test2_enemy_get_id();


/**
 * @test Test function for enemy_name setting
 * @pre String with enemy name
 * @post Ouput==OK 
 */
void test1_enemy_set_name();

/**
 * @test Test function for enemy_name setting
 * @pre pointer to enemy = NULL 
 * @post Output==ERROR
 */
void test2_enemy_set_name();

/**
 * @test Test function for enemy_name setting
 * @pre pointer to enemy_name = NULL (point to enemy = NON NULL) 
 * @post Output==ERROR
 */
void test3_enemy_set_name();


/**
 * @test Test function for getting enemy_name
 * @pre string with enemy name = "adios" (pointer to enemy != NULL)
 * @post Output=="adios"
 */
void test1_enemy_get_name();

/**
 * @test Test function for getting enemy_name
 * @pre pointer to enemy = NULL
 * @post Output==NULL
 */
void test2_enemy_get_name();


/**
 * @test Test getting enemy location
 * @pre having set the enemy on the space id 11
 * @post Output == 11
 */
void test1_enemy_get_location();

/**
 * @test Test getting enemy location
 * @pre pointer to enemy = NULL
 * @post Output==NO_ID
 */
void test2_enemy_get_location();

/**
 * @test Test getting enemy health
 * @pre having set the enemy health to 3
 * @post Output == 3
 */
void test1_enemy_get_health();

/**
 * @test Test setting enemy health
 * @pre pointer to enemy = NULL
 * @post Output==NULL
 */
void test2_enemy_get_health();

/**
 * @test Test setting enemy health
 * @pre having set the enemy health to 3
 * @post Output == OK
 */
void test1_enemy_set_health();

/**
 * @test Test getting enemy health
 * @pre having set the enemy health to -1
 * @post Output==ERROR
 */
void test2_enemy_set_health();

/**
 * @test Test getting enemy health
 * @pre pointer to enemy = NULL
 * @post Output==ERROR
 */
void test3_enemy_set_health();

/**
 * @test Test setting enemy location
 * @pre having set the enemy location to a valid id (11)
 * @post Output == OK
 */
void test1_enemy_set_location();

/**
 * @test Test setting enemy location
 * @pre pointer to enemy = NULL
 * @post Output==NULL
 */
void test2_enemy_set_location();

/**
 * @test Test getting enemy health
 * @pre having set the enemy health to 3
 * @post Output == 3
 */
void test1_enemy_get_crit();

/**
 * @test Test setting enemy health
 * @pre pointer to enemy = NULL
 * @post Output==NULL
 */
void test2_enemy_get_crit();

/**
 * @test Test setting enemy health
 * @pre having set the enemy health to 3
 * @post Output == OK
 */
void test1_enemy_set_crit();

/**
 * @test Test getting enemy health
 * @pre having set the enemy health to -1
 * @post Output==ERROR
 */
void test2_enemy_set_crit();

/**
 * @test Test getting enemy health
 * @pre having set the enemy health to 3
 * @post Output == 3
 */
void test1_enemy_get_baseDmg();

/**
 * @test Test setting enemy health
 * @pre pointer to enemy = NULL
 * @post Output==NULL
 */
void test2_enemy_get_baseDmg();

/**
 * @test Test setting enemy health
 * @pre having set the enemy health to 3
 * @post Output == OK
 */
void test1_enemy_set_baseDmg();

/**
 * @test Test getting enemy health
 * @pre having set the enemy health to -1
 * @post Output==ERROR
 */
void test2_enemy_set_baseDmg();

#endif
