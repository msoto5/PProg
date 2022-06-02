/** 
 * @brief It declares the tests for the dialogue module
 * 
 * @file dialogue_test.h
 * @author Ignacio Nunnez
 * @version 2.0 
 * @date 07-05-2022
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_TEST_H
#define DIALOGUE_TEST_H

/**
 * @test Test dialogue creation
 * @pre dialogue ID
 * @post Non NULL pointer to dialogue 
 */
void test1_dialogue_create();

/**
 * @test Test dialogue creation
 * @pre dialogue ID
 * @post dialogue_ID == Supplied dialogue Id
 */
void test2_dialogue_create();

/**
 * @test Test free dialogue
 * @pre pointer to dialogue
 * @post Output == OK
 */
void test1_dialogue_destroy();

/**
 * @test Test free enemy
 * @pre pointer to dialogue
 * @post Output == ERROR
 */
void test2_dialogue_destroy();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue
 * @post Output == OK
 */
void test1_dialogue_reset();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue = NULL
 * @post Output == ERROR
 */
void test2_dialogue_reset();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue
 * @post Non-NULL pointer
 */
void test1_dialogue_get_command();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue = NULL
 * @post NULL pointer
 */
void test2_dialogue_get_command();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue
 * @post Non-NULL pointer
 */
void test1_dialogue_get_event();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue = NULL
 * @post NULL pointer
 */
void test2_dialogue_get_event();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue
 * @post Non-NULL pointer
 */
void test1_dialogue_get_error();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue = NULL
 * @post NULL pointer
 */
void test2_dialogue_get_error();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue
 * @post output == OK
 */
void test1_dialogue_set_command();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue = NULL
 * @post output == ERROR
 */
void test2_dialogue_set_command();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue
 * @post output == OK
 */
void test1_dialogue_set_event();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue = NULL
 * @post output == ERROR
 */
void test2_dialogue_set_event();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue
 * @post output == OK
 */
void test1_dialogue_set_error();

/**
 * @test Test dialogue reset
 * @pre pointer to dialogue = NULL
 * @post output == ERROR
 */
void test2_dialogue_set_error();

#endif
