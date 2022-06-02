/** 
 * @brief It declares the tests for the test module
 * 
 * @file set_test.h
 * @author Profesores Pprog y Miguel Soto
 * @version 2.0 
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test set creation
 * @pre pointer to set = NULL
 * @post Non NULL pointer to set 
 */
void test1_set_create();


/**
 * @test Test free set
 * @pre pointer to set
 * @post pointer to set = NULL
 */
void test1_set_destroy();
/**
 * @test Test free set
 * @pre pointer to set = NULL
 * @post Output == ERROR
 */
void test2_set_destroy();


/**
 * @test Test function for adding an id
 * @pre pointer to set and id correct
 * @post Ouput==OK 
 */
void test1_set_add();
/**
 * @test Test function for adding an id
 * @pre pointer to set = NULL
 * @post Output==ERROR
 */
void test2_set_add();
/**
 * @test Test function for adding an id
 * @pre id = NO_ID 
 * @post Output==ERROR
 */
void test3_set_add();


/**
 * @test Test function for adding an id
 * @pre pointer to set and id correct
 * @post Ouput==OK 
 */
void test1_set_del_id();
/**
 * @test Test function for adding an id
 * @pre pointer to set = NULL
 * @post Output==ERROR
 */
void test2_set_del_id();
/**
 * @test Test function for adding an id
 * @pre id = NO_ID 
 * @post Output==ERROR
 */
void test3_set_del_id();

/**
 * @test Test function for getting the number of ids in set
 * @pre added 1 id
 * @post Output==1
 */
void test1_set_get_nids();
/**
 * @test Test function for getting the number of ids in set
 * @pre pointer to set = NULL
 * @post Output==-1
 */
void test2_set_get_nids();


/**
 * @test Test function for getting ids from set
 * @pre added 1 id
 * @post Output!=NULL
 */
void test1_set_get_ids();
/**
 * @test Test function for getting ids from set
 * @pre pointer to set = NULL
 * @post Output==NULL
 */
void test2_set_get_ids();

#endif
