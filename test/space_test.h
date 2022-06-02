/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Miguel Soto, Ignacio Nunez, Nicolas Victorino and Antonio Van-Oers
 * @version 2.0 
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();
/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();


/**
 * @test Test free space
 * @pre pointer to space
 * @post pointer to space = NULL
 */
void test1_space_destroy();
/**
 * @test Test free space
 * @pre pointer to space = NULL
 * @post Output == ERROR
 */
void test2_space_destroy();


/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();
/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();
/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for space link setting
 * @pre ND (Not defined direction)
 * @post Output==ERROR
 */
void test1_space_set_link();

/**
 * @test Test function for space_north setting
 * @pre Id from the north space (pointer to space != NULL)
 * @post Output==OK
 */
void test1_space_set_link_north();
/**
 * @test Test function for space_north setting
 * @pre pointer to space = NULL (Id from north space correct)
 * @post Output==ERROR
 */
void test2_space_set_link_north();
/**
 * @test Test function for space_north setting
 * @pre Id = NO_ID (pointer to space != NULL)
 * @post Output==ERROR
 */
void test3_space_set_link_north();



/**
 * @test Test function for space_south setting
 * @pre Id from the south space (pointer to space != NULL)
 * @post Output==OK
 */
void test1_space_set_link_south();
/**
 * @test Test function for space_south setting
 * @pre pointer to space = NULL (Id from south space correct)
 * @post Output==ERROR
 */
void test2_space_set_link_south();
/**
 * @test Test function for space_south setting
 * @pre Id = NO_ID (pointer to space != NULL)
 * @post Output==ERROR
 */
void test3_space_set_link_south();



/**
 * @test Test function for space_east setting
 * @pre Id from the east space (pointer to space != NULL)
 * @post Output==OK
 */
void test1_space_set_link_east();
/**
 * @test Test function for space_east setting
 * @pre pointer to space = NULL (Id from east space correct)
 * @post Output==ERROR
 */
void test2_space_set_link_east();
/**
 * @test Test function for space_east setting
 * @pre Id = NO_ID (pointer to space != NULL)
 * @post Output==ERROR
 */
void test3_space_set_link_east();



/**
 * @test Test function for space_west setting
 * @pre Id from the west space (pointer to space != NULL)
 * @post Output==OK
 */
void test1_space_set_link_west();
/**
 * @test Test function for space_west setting
 * @pre pointer to space = NULL (Id from west space correct)
 * @post Output==ERROR
 */
void test2_space_set_link_west();
/**
 * @test Test function for space_west setting
 * @pre Id = NO_ID (pointer to space != NULL)
 * @post Output==ERROR
 */
void test3_space_set_link_west();



/**
 * @test Test function for getting space id
 * @pre Space id = 5
 * @post Output==5
 */
void test1_space_get_id();
/**
 * @test Test function for getting space id
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_id();


/**
 * @test Test function for adding object to space setting
 * @pre Id from Object (pointer to space != NULL)
 * @post Output==OK
 */
void test1_space_add_object();
/**
 * @test Test function for adding object to space setting
 * @pre pointer to space = NULL (Id from Object correct)
 * @post Output==ERROR
 */
void test2_space_add_object();
/**
 * @test Test function for adding object to space setting
 * @pre Id = NO_ID (pointer to space != NULL)
 * @post Output==ERROR
 */
void test3_space_add_object();


/**
 * @test Test function for deleting object to space setting
 * @pre Id from Object (pointer to space != NULL)
 * @post Output==OK
 */
void test1_space_del_object();
/**
 * @test Test function for deleting object to space setting
 * @pre Id from Object not in space (pointer to space != NULL)
 * @post Output==ERROR
 */
void test2_space_del_object();
/**
 * @test Test function for deleting object to space setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test3_space_del_object();


/**
 * @test Test function for checking if space has object
 * @pre Id from Object not in space (pointer to space != NULL)
 * @post Output==FALSE
 */
void test1_space_get_object();
/**
 * @test Test function for checking if space has object
 * @pre Id from Object in space (pointer to space != NULL)
 * @post Output==TRUE
 */
void test2_space_get_object();
/**
 * @test Test function for checking if space has object
 * @pre pointer to space = NULL
 * @post Output==FALSE
 */
void test3_space_get_object();


/**
 * @test Test function for getting space_name
 * @pre string with space name = "adios" (pointer to space != NULL)
 * @post Output=="adios"
 */
void test1_space_get_name();
/**
 * @test Test function for getting space_name
 * @pre pointer to space = NULL
 * @post Output==NULL
 */
void test2_space_get_name();


/**
 * @test Test function for getting space link
 * @pre ND (Not defined direction)
 * @post Output==NO_ID
 */
void test1_space_get_link();
/**
 * @test Test function for getting space_north
 * @pre pointer to space != NULL (space_north = 4)
 * @post Output==4
 */
void test1_space_get_link_north();
/**
 * @test Test function for getting space_north
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_link_north();


/**
 * @test Test function for getting space_south
 * @pre pointer to space != NULL (space_south = 4)
 * @post Output==FALSE
 */
void test1_space_get_link_south();
/**
 * @test Test function for getting space_south
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_link_south();


/**
 * @test Test function for getting space_east
 * @pre pointer to space != NULL (space_east = 4)
 * @post Output==FALSE
 */
void test1_space_get_link_east();
/**
 * @test Test function for getting space_east
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_link_east();


/**
 * @test Test function for getting space_west
 * @pre pointer to space != NULL (space_west = 4)
 * @post Output==FALSE
 */
void test1_space_get_link_west();
/**
 * @test Test function for getting space_west
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_link_west();


/**
 * @test Test function for setting space_gdesc
 * @pre pointer to space != NULL
 * @post Output==OK
 */
void test1_space_set_gdesc();
/**
 * @test Test function for setting space_gdesc
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test function for setting space_gdesc
 * @pre pointer to space != NULL (char **gdesc = NULL)
 * @post Output==ERROR
 */
void test3_space_set_gdesc();


/**
 * @test Test function for getting space_gdesc
 * @pre pointer to space != NULL
 * @post Output==gdesc
 */
void test1_space_get_gdesc();

/**
 * @test Test function for getting space_gdesc
 * @pre pointer to space = NULL
 * @post Output==NULL
 */
void test2_space_get_gdesc();


/**
 * @test Test function setting light status
 * @pre pointer to space != NULL
 * @post Output==OK
 */
void test1_space_set_light_status();
/**
 * @test Test function for setting light status
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_light_status();


/**
 * @test Test function for getting light status
 * @pre pointer to space != NULL
 * @post Output==BRIGHT
 */
void test1_space_get_light_status();
/**
 * @test Test function for getting light status
 * @pre pointer to space = NULL
 * @post Output==UNKNOWN_LIGHT
 */
void test2_space_get_light_status();



/**
 * @test Test function setting floor status
 * @pre pointer to space != NULL
 * @post Output==OK
 */
void test1_space_set_floor();
/**
 * @test Test function for setting floor status
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_floor();


/**
 * @test Test function for getting floor status
 * @pre pointer to space != NULL
 * @post Output==DUNGEON
 */
void test1_space_get_floor();
/**
 * @test Test function for getting floor status
 * @pre pointer to space = NULL
 * @post Output==UNKNOWN_FLOOR
 */
void test2_space_get_floor();

#endif
