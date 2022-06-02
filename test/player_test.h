  /**
 * @brief It tests player module
 *
 * @file player_test.h
 * @author Ignacio Nunnez
 * @version 3.0
 * @date 31-03-2021
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test player
 * @pre allocated-memory' player pointer
 * @post non-NULL pointer
 */
void test1_player_create();

/**
 * @test Test player
 * @pre allocated-memory' player pointer
 * @post non-NULL pointer
 */
void test2_player_create();

/**
 * @test Test player
 * @pre player pointer
 * @post NULL pointer
 */
void test3_player_create();

/**
 * @test Test player
 * @pre allocated-memory' player pointer
 * @post output == OK
 */
void test1_player_destroy();

/**
 * @test Test player
 * @pre non-allocated-memory' player pointer
 * @post output == ERROR
 */
void test2_player_destroy();

/**
 * @test Test player
 * @pre	player pointer
 * @post specific int
 */
void test1_player_get_id();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @post NO_ID 
 */
void test2_player_get_id();

/**
 * @test Test player
 * @pre	specific int
 * @post output = OK
 */
void test1_player_test_id();

/**
 * @test Test player
 * @pre	specific int
 * @post output = ERROR
 */
void test2_player_test_id();

/**
 * @test Test player
 * @pre	specific int
 * @post output = ERROR
 */
void test3_player_test_id();

/**
 * @test Test player
 * @pre	player pointer
 * @pre specfic string
 * @post output = OK
 */
void test1_player_set_name();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @pre specfic string
 * @post output = ERROR
 */
void test2_player_set_name();

/**
 * @test Test player
 * @pre	player pointer
 * @pre specfic string
 * @post output = OK
 */
void test1_player_get_name();

/**
 * @test Test player
 * @pre	player pointer
 * @pre specfic string
 * @post output = ERROR
 */
void test2_player_get_name();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @pre specfic string
 * @post output = ERROR
 */
void test3_player_get_name();

/**
 * @test Test player
 * @pre	player pointer
 * @post output = OK
 */
void test1_player_set_location();

/**
 * @test Test player
 * @pre	player pointer
 * @post output = ERROR
 */
void test2_player_set_location();

/**
 * @test Test player
 * @pre	player pointer
 * @post specific ID
 */
void test1_player_get_location();

/**
 * @test Test player
 * @pre	player pointer
 * @post specific ID
 */
void test2_player_get_location();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @post NO_ID
 */
void test3_player_get_location();

/**
 * @test Test player
 * @pre	player pointer
 * @post non-NULL pointer
 */
void test1_player_get_inventory();

/**
 * @test Test player
 * @pre	non-allocated player pointer
 * @post NULL pointer
 */
void test2_player_get_inventory();

/**
 * @test Test player
 * @pre	player pointer
 * @post output = OK
 */
void test1_player_set_health();

/**
 * @test Test player
 * @pre	player pointer
 * @post output = ERROR
 */
void test2_player_set_health();

/**
 * @test Test player
 * @pre	player pointer
 * @post output = OK
 */
void test1_player_set_max_health();

/**
 * @test Test player
 * @pre	player pointer
 * @post output = ERROR
 */
void test2_player_set_max_health();

/**
 * @test Test player
 * @pre	player pointer
 * @post specific ID
 */
void test1_player_get_health();

/**
 * @test Test player
 * @pre	player pointer
 * @post specific ID
 */
void test2_player_get_health();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @post NO_ID
 */
void test3_player_get_health();

/**
 * @test Test player
 * @pre	player pointer
 * @post output = OK
 */
void test1_player_set_max_inventory();

/**
 * @test Test player
 * @pre	non-allocated-memory player pointer
 * @post output = ERROR
 */
void test2_player_set_max_inventory();

/**
 * @test Test player
 * @pre	player pointer
 * @pre object pointer
 * @post output = OK
 */
void test1_player_add_object();

/**
 * @test Test player
 * @pre	player pointer
 * @pre NULL object pointer
 * @post output = ERROR
 */
void test2_player_add_object();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @pre object pointer
 * @post output = ERROR
 */
void test3_player_add_object();

/**
 * @test Test player
 * @pre	player pointer
 * @pre object pointer
 * @post output = OK
 */
void test1_player_del_object();

/**
 * @test Test player
 * @pre	player pointer
 * @pre NULL object pointer
 * @post output = ERROR
 */
void test2_player_del_object();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @pre object pointer
 * @post output = ERROR
 */
void test3_player_del_object();

/**
 * @test Test player
 * @pre	player pointer
 * @pre object pointer
 * @post output = TRUE
 */
void test1_player_has_object();

/**
 * @test Test player
 * @pre	player pointer
 * @pre NULL object pointer
 * @post output = FALSE
 */
void test2_player_has_object();

/**
 * @test Test player
 * @pre	NULL player pointer
 * @pre object pointer
 * @post output = FALSE
 */
void test3_player_has_object();

/**
 * @test Test getting player health
 * @pre having set the player health to 3
 * @post Output == 3
 */
void test1_player_get_crit();

/**
 * @test Test setting player health
 * @pre pointer to player = NULL
 * @post Output==NULL
 */
void test2_player_get_crit();

/**
 * @test Test setting player health
 * @pre having set the player health to 3
 * @post Output == OK
 */
void test1_player_set_crit();

/**
 * @test Test getting player health
 * @pre having set the player health to -1
 * @post Output==ERROR
 */
void test2_player_set_crit();

/**
 * @test Test getting player health
 * @pre having set the player health to 3
 * @post Output == 3
 */
void test1_player_get_baseDmg();

/**
 * @test Test setting player health
 * @pre pointer to player = NULL
 * @post Output==NULL
 */
void test2_player_get_baseDmg();

/**
 * @test Test setting player health
 * @pre having set the player health to 3
 * @post Output == OK
 */
void test1_player_set_baseDmg();

/**
 * @test Test getting player health
 * @pre having set the player health to -1
 * @post Output==ERROR
 */
void test2_player_set_baseDmg();

#endif