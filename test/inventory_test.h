  /**
 * @brief It tests inventory module
 *
 * @file inventory_test.h
 * @author Ignacio NUnnez
 * @version 3.0
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#ifndef ENEMY_TEST_H
#define ENEMY_TEST_H

/**
 * @test Test inventory creation
 * @pre inventory pointer 
 * @post non NULL pointer 
 */
void test1_inventory_create();

/**
 * @test Test inventory creation
 * @pre inventory pointer 
 * @post NULL pointer
 */
void test2_inventory_create();

/**
 * @test Test inventory free
 * @pre inventory pointer 
 * @post alocated-memory' pointer
 */
void test1_inventory_destroy();

/**
 * @test Test inventory free
 * @pre inventory pointer 
 * @post non-alocated-memory' pointer
 */
void test2_inventory_destroy();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @pre set pointer
 * @post output == OK
 */
void test1_inventory_set_objects();

/**
 * @test Test inventory
 * @pre inventory NULL pointer
 * @pre set pointer
 * @post output == ERROR
 */
void test2_inventory_set_objects();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @pre set NULL pointer
 * @post output == ERROR
 */
void test3_inventory_set_objects();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @pre set pointer
 * @post non NULL pointer
 */
void test1_inventory_get_objects();

/**
 * @test Test inventory
 * @pre inventory NULL pointer
 * @post NULL pointer
 */
void test2_inventory_get_objects();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == OK
 */
void test1_inventory_set_maxObjs();

/**
 * @test Test inventory
 * @pre inventory NULL pointer
 * @post output == ERROR
 */
void test2_inventory_set_maxObjs();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post specific int
 */
void test1_inventory_get_maxObjs();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post non specific int
 */
void test2_inventory_get_maxObjs();

/**
 * @test Test inventory
 * @pre inventory NULL pointer
 * @post NO_ID
 */
void test3_inventory_get_maxObjs();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == OK
 */
void test1_inventory_add_object();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == ERROR
 */
void test2_inventory_add_object();

/**
 * @test Test inventory
 * @pre inventory NULL pointer
 * @post output == ERROR
 */
void test3_inventory_add_object();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == OK
 */
void test1_inventory_remove_object();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == ERROR
 */
void test2_inventory_remove_object();

/**
 * @test Test inventory
 * @pre inventory NULL pointer
 * @post output == ERROR
 */
void test3_inventory_remove_object();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == TRUE
 */
void test1_inventory_has_id();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == FALSE
 */
void test2_inventory_has_id();

/**
 * @test Test inventory
 * @pre inventory pointer
 * @post output == FALSE
 */
void test3_inventory_has_id();

#endif
