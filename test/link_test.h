/**
 * @brief It tests link module
 *
 * @file link_test.h
 * @author Profesores Pprog
 * @version 3.0
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test Link Creation
 * @pre Link ID 
 * @post Non NULL pointer to Link 
 */
void test1_link_create();
/**
 * @test Test Link creation
 * @pre Link ID 
 * @post Link_ID == Supplied Link Id
 */
void test2_link_create();


/**
 * @test Test free link
 * @pre pointer to link
 * @post pointer to link = NULL
 */
void test1_link_destroy();
/**
 * @test Test free link
 * @pre pointer to link = NULL
 * @post Output == ERROR
 */
void test2_link_destroy();


/**
 * @test Test function for getting Link id
 * @pre Link id = FD_ID_LINK*10 + 1
 * @post Output==Link id
 */
void test1_link_get_id();
/**
 * @test Test function for getting Link id
 * @pre pointer to Link = NULL
 * @post Output==NO_ID
 */
void test2_link_get_id();


/**
 * @test Test function for link_name setting
 * @pre String with link name
 * @post Ouput==OK 
 */
void test1_link_set_name();
/**
 * @test Test function for link_name setting
 * @pre pointer to link = NULL 
 * @post Output==ERROR
 */
void test2_link_set_name();
/**
 * @test Test function for link_name setting
 * @pre pointer to link_name = NULL (point to link = NON NULL) 
 * @post Output==ERROR
 */
void test3_link_set_name();


/**
 * @test Test function for getting Link_name
 * @pre string with Link name = "adios" (pointer to Link != NULL)
 * @post Output=="adios"
 */
void test1_link_get_name();
/**
 * @test Test function for getting Link_name
 * @pre pointer to Link = NULL
 * @post Output==NULL
 */
void test2_link_get_name();


/**
 * @test Test function for link_start setting
 * @pre Valid link and 11 as the initial id 
 * @post Output == OK
 */
void test1_link_set_start();

/**
 * @test Test function for link_start setting
 * @pre pointer to Link = NULL
 * @post Output == ERROR
 */
void test2_link_set_start();


/**
 * @test Test function for getting link_start
 * @pre Valid link and 11 as the initial id 
 * @post Output == 11
 */
void test1_link_get_start();

/**
 * @test Test function for getting link_satrt
 * @pre pointer to Link = NULL
 * @post Output == NO_ID
 */
void test2_link_get_start();


/**
 * @test Test function for link_destination setting
 * @pre Valid link and 11 as the initial id 
 * @post Output == OK
 */
void test1_link_set_destination();

/**
 * @test Test function for link_destination setting
 * @pre pointer to Link = NULL
 * @post Output == ERROR
 */
void test2_link_set_destination();


/**
 * @test Test function for getting link_destination
 * @pre Valid link and 11 as the initial id 
 * @post Output == 11
 */
void test1_link_get_destination();
/**
 * @test Test function for getting lik_destination
 * @pre pointer to Link = NULL
 * @post Output == NO_ID
 */
void test2_link_get_destination();


/**
 * @test Test function for link_direction setting
 * @pre Valid link and 'N' as the initial direction
 * @post Output == OK
 */
void test1_link_set_direction();

/**
 * @test Test function for link_direction setting
 * @pre pointer to Link = NULL
 * @post Output == ERROR
 */
void test2_link_set_direction();


/**
 * @test Test function for getting link_direction
 * @pre Valid link and 'N' as the initial direction
 * @post Output == 'N'
 */
void test1_link_get_direction();

/**
 * @test Test function for getting link_direction
 * @pre pointer to Link = NULL
 * @post Output == ND
 */
void test2_link_get_direction();


/**
 * @test Test function for link_status setting
 * @pre Valid link and OPEN as the initial status
 * @post Output == OK
 */
void test1_link_set_status();

/**
 * @test Test function for link status setting
 * @pre pointer to Link = NULL
 * @post Output == ERROR
 */
void test2_link_set_status();


/**
 * @test Test function for getting link_status
 * @pre @pre Valid link and OPEN as the initial status
 * @post Output == OPEN
 */
void test1_link_get_status();

/**
 * @test Test function for getting link_status
 * @pre pointer to Link = NULL
 * @post Output == CLOSE
 */
void test2_link_get_status();


/**
 * @test Test function for link_print
 * @pre pointer to Link = NULL
 * @post Output == -1
 */
void test1_link_print();


#endif
