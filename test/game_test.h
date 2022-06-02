/** 
 * @brief It declares the tests for the game module
 * 
 * @file game_test.h
 * @author Ignacio NUnnez
 * @version 2.0 
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef GAME_TEST_H
#define GAME_TEST_H

/**
 * @test Test game allocation
 * @pre game pointer 
 * @post Non NULL pointer to game 
 */
void test1_game_alloc2();

/**
 * @test Test game destruction
 * @pre allocated game pointer
 * @post return OK 
 */
void test1_game_destroy();

/**
 * @test Test game destruction
 * @pre non-allocated game pointer
 * @post return ERROR 
 */
void test2_game_destroy();

/**
 * @test Test intialization of game members
 * @pre allocated game pointer 
 * @post return OK
 */
void test1_game_create();

/**
 * @test Test intialization of game members
 * @pre non-allocated game pointer 
 * @post return OK
 */
void test2_game_create();

/**
 * @test Test game update
 * @pre allocated game pointer 
 * @post return int different to 0
 */
void test1_game_update();

/**
 * @test Test game update
 * @pre non-allocated game pointer 
 * @post return int different to 0
 */
void test2_game_update();

/**
 * @test Test if game is over
 * @pre game with 0-HP-Player 
 * @post return TRUE
 */
void test1_game_is_over();

/**
 * @test Test if game is over
 * @pre game with 10-HP-Player 
 * @post return FALSE
 */
void test2_game_is_over();

/**
 * @test Test space getter
 * @pre game with new space 
 * @post return pointer different to NULL
 */
void test1_game_get_space();

/**
 * @test Test space getter
 * @pre game with new space but different ID
 * @post return pointer to NULL
 */
void test2_game_get_space();

/**
 * @test Test object getter
 * @pre game with new object 
 * @post return pointer different to NULL
 */
void test1_game_get_object();

/**
 * @test Test object getter
 * @pre game with new object but different ID
 * @post return pointer to NULL
 */
void test2_game_get_object();

/**
 * @test Test player getter
 * @pre game with new player 
 * @post return pointer different to NULL
 */
void test1_game_get_player();

/**
 * @test Test player getter
 * @pre game with new player but different ID
 * @post return pointer to NULL
 */
void test2_game_get_player();

/**
 * @test Test enemy getter
 * @pre game with new enemy 
 * @post return pointer different to NULL
 */
void test1_game_get_enemy();

/**
 * @test Test enemy getter
 * @pre game with new enemy but different ID
 * @post return pointer to NULL
 */
void test2_game_get_enemy();

/**
 * @test Test player location getter
 * @pre game with new player and with location 
 * @post return ID of the location
 */
void test1_game_get_player_location();

/**
 * @test Test player location getter
 * @pre game with NULL player
 * @post return NO_ID
 */
void test2_game_get_player_location();

/**
 * @test Test enemy location getter
 * @pre game with new enemy and with location 
 * @post return ID of the location
 */
void test1_game_get_enemy_location();

/**
 * @test Test enemy location getter
 * @pre game with NULL enemy
 * @post return NO_ID
 */
void test2_game_get_enemy_location();

/**
 * @test Test object location getter
 * @pre game with new object and with location 
 * @post return ID of the location
 */
void test1_game_get_object_location();

/**
 * @test Test object location getter
 * @pre game with NULL object
 * @post return NO_ID
 */
void test2_game_get_object_location();

/**
 * @test Test last_command getter
 * @pre game with new update
 * @post return specific command updated
 */
void test1_game_get_last_command();

/**
 * @test Test last_command getter
 * @pre game with new update
 * @post return specific command different 
 * to the updated
 */
void test2_game_get_last_command();

/**
 * @test Test enemy id getter
 * @pre game with new enemy 
 * @post return ID of the enemy
 */
void test1_game_get_enemy_id();

/**
 * @test Test enemy id getter
 * @pre game without enemy
 * @post return NO_ID
 */
void test2_game_get_enemy_id();

/**
 * @test Test player id getter
 * @pre game with new player 
 * @post return ID of the player
 */
void test1_game_get_player_id();

/**
 * @test Test player id getter
 * @pre game without player
 * @post return NO_ID
 */
void test2_game_get_player_id();

/**
 * @test Test object id getter
 * @pre game with new object 
 * @post return ID of the object
 */
void test1_game_get_object_id();

/**
 * @test Test object id getter
 * @pre game without object
 * @post return NO_ID
 */
void test2_game_get_object_id();

/**
 * @test Test connection status of a link
 * @pre game with an space and a link
 * on the space with specific direcction
 * @post return OPEN
 */
void test1_game_get_connection_status();

/**
 * @test Test connection status of a link
 * @pre game with an space and a link
 * on the space with specific direcction
 * but the function has incorrect ID
 * @post return CLOSE
 */
void test2_game_get_connection_status();

/**
 * @test Test connection id of a link
 * @pre game with an space and a link
 * on the space with specific direcction
 * @post return link-id
 */
void test1_game_get_connection();

/**
 * @test Test connection id of a link
 * @pre game with an space and a link
 * on the space with specific direcction
 * but the link hasn't destination and start
 * @post return CLOSE
 */
void test2_game_get_connection();

/**
 * @test Test game-description-member getter
 * @pre allocated game pointer 
 * @post return non-NULL pointer
 */
void test1_game_get_inspection();

/**
 * @test Test game time getter
 * @pre memory-allocated game 
 * @post return Day
 */
void test1_game_get_time();

/**
 * @test Test game time getter
 * @pre non-memory-allocated game 
 * @post return -1
 */
void test2_game_get_time();

/**
 * @test Test game time setter
 * @pre memory-allocated game 
 * @post return OK
 */
void test1_game_set_time();

/**
 * @test Test game time setter
 * @pre non-memory-allocated game 
 * @post return ERROR
*/
void test2_game_set_time();

/**
 * @test Test game last_event getter
 * @pre memory-allocated game 
 * @post return NOTHING
 */
void test1_game_get_last_event();

/**
 * @test Test game last_event getter
 * @pre non-memory-allocated game 
 * @post return -1
 */
void test2_game_get_last_event();

/**
 * @test Test game dialogue getter
 * @pre memory-allocated game 
 * @post return non NULL pointer
 */
void test1_game_get_dialogue();

/**
 * @test Test game dialogue getter
 * @pre non-memory-allocated game 
 * @post return NULL
 */
void test2_game_get_dialogue();

/**
 * @test Test game enemyWithPlayer getter
 * @pre memory-allocated game 
 * @post return non NULL pointer
 */
void test1_game_get_enemyWithPlayer();

/**
 * @test Test game enemyWithPlayer getter
 * @pre non-memory-allocated game 
 * @post return NULL
 */
void test2_game_get_enemyWithPlayer();

#endif
