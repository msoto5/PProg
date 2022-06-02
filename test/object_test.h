/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Profesores Pprog
 * @version 3.0
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H


/**
 * @test Test Object Creation
 * @pre Object ID 
 * @post Non NULL pointer to Object 
 */
void test1_obj_create();
/**
 * @test Test Object creation
 * @pre Object ID 
 * @post Object_ID == Supplied Object Id
 */
void test2_obj_create();


/**
 * @test Test free object
 * @pre pointer to object
 * @post pointer to object = NULL
 */
void test1_obj_destroy();
/**
 * @test Test free object
 * @pre pointer to object = NULL
 * @post Output == ERROR
 */
void test2_obj_destroy();

/**
 * @test Test object id classification
 * @pre Id = Object id
 * @post Output == OK
 */
void test1_obj_test_id();
/**
 * @test Test object id classification
 * @pre Id = Player id
 * @post Output == ERROR
 */
void test2_obj_test_id();


/**
 * @test Test function for getting Object id
 * @pre Object id = FD_ID_OBJ*10 + 1
 * @post Output==Object id
 */
void test1_obj_get_id();
/**
 * @test Test function for getting Object id
 * @pre pointer to Object = NULL
 * @post Output==NO_ID
 */
void test2_obj_get_id();


/**
 * @test Test function for object_name setting
 * @pre String with object name
 * @post Ouput==OK 
 */
void test1_obj_set_name();
/**
 * @test Test function for object_name setting
 * @pre pointer to object = NULL 
 * @post Output==ERROR
 */
void test2_obj_set_name();
/**
 * @test Test function for object_name setting
 * @pre pointer to object_name = NULL (point to object = NON NULL) 
 * @post Output==ERROR
 */
void test3_obj_set_name();


/**
 * @test Test function for getting Object_name
 * @pre string with Object name = "adios" (pointer to Object != NULL)
 * @post Output=="adios"
 */
void test1_obj_get_name();
/**
 * @test Test function for getting Object_name
 * @pre pointer to Object = NULL
 * @post Output==NULL
 */
void test2_obj_get_name();


/**
 * @test Test function for obj_location setting
 * @pre Id from the location object (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_location();
/**
 * @test Test function for object_location setting
 * @pre pointer to object = NULL (Id from location object correct)
 * @post Output==ERROR
 */
void test2_obj_set_location();
/**
 * @test Test function for object_location setting
 * @pre Id = NO_ID (pointer to object != NULL)
 * @post Output==ERROR
 */
void test3_obj_set_location();

/**
 * @test Test function for getting obj_location
 * @pre pointer to Object != NULL (obj_location = space_id)
 * @post Output==4
 */
void test1_obj_get_location();
/**
 * @test Test function for getting obj_location
 * @pre pointer to Object = NULL
 * @post Output==NO_ID
 */
void test2_obj_get_location();

/**
 * @test Test function for obj_movable setting
 * @pre Boolean (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_movable();

/**
 * @test Test function for object_movable setting
 * @pre Boolean (pointer to object == NULL)
 * @post Output==ERROR
 */
void test2_obj_set_movable();

/**
 * @test Test function for obj_dependency setting
 * @pre Id from object (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_dependency();

/**
 * @test Test function for object_dependency setting
 * @pre Id from object (pointer to object == NULL)
 * @post Output==ERROR
 */ 
void test2_obj_set_dependency();

/**
 * @test Test function for obj_open setting
 * @pre Id from object (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_open();

/**
 * @test Test function for object_open setting
 * @pre Id from object (pointer to object == NULL)
 * @post Output==ERROR
 */ 
void test2_obj_set_open();

/**
 * @test Test function for obj_illuminate setting
 * @pre Boolean (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_illuminate();

/**
 * @test Test function for object_illuminate setting
 * @pre Boolean (pointer to object == NULL)
 * @post Output==ERROR
 */ 
void test2_obj_set_illuminate();

/**
 * @test Test function for obj_turnedon setting
 * @pre Boolean (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_turnedon();

 /**
 * @test Test function for object_turnedon setting
 * @pre Boolean (pointer to object == NULL)
 * @post Output==ERROR
 */  
void test2_obj_set_turnedon();

/**
 * @test Test function for getting obj_movable
 * @pre pointer to Object != NULL
 * @post Output==TRUE
 */
void test1_obj_get_movable();

/**
 * @test Test function for getting obj_location
 * @pre pointer to Object = NULL
 * @post Output==FALSE
 */
void test2_obj_get_movable();

/**
 * @test Test function for getting obj_dependency
 * @pre pointer to Object != NULL
 * @post Output==Id_dependency
 */
void test1_obj_get_dependency();

 /**
 * @test Test function for getting obj_dependency
 * @pre pointer to Object = NULL
 * @post Output==NO_ID
 */ 
void test2_obj_get_dependency();

/**
 * @test Test function for getting obj_open
 * @pre pointer to Object != NULL 
 * @post Output == id_dependency
 */
void test1_obj_get_open();

 /**
 * @test Test function for getting obj_open
 * @pre pointer to Object = NULL
 * @post Output==NO_ID
 */ 
void test2_obj_get_open();

/**
 * @test Test function for getting obj_illuminate
 * @pre pointer to Object != NULL
 * @post Output==TRUE
 */
void test1_obj_get_illuminate();

 /**
 * @test Test function for getting obj_illuminate
 * @pre pointer to Object = NULL
 * @post Output==FALSE
 */ 
void test2_obj_get_illuminate();

/**
 * @test Test function for getting obj_turnedon
 * @pre pointer to Object != NULL
 * @post Output==TRUE
 */
void test1_obj_get_turnedon();

 /**
 * @test Test function for getting obj_turnedon
 * @pre pointer to Object = NULL
 * @post Output==FALSE
 */ 
void test2_obj_get_turnedon();

/**
 * @test Test function for obj_light_visible setting
 * @pre Boolean (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_light_visible();

/**
 * @test Test function for object_light_visible setting
 * @pre Boolean (pointer to object != NULL)
 * @post Output==ERROR
 */  
void test2_obj_set_light_visible();

/**
 * @test Test function for getting obj_light_visible
 * @pre pointer to Object != NULL (LIGHT)
 * @post Output==BRIGHT
 */
void test1_obj_get_light_visible();

/**
 * @test Test function for getting obj_location
 * @pre pointer to Object = NULL
 * @post Output==UNKNOW_LIGHT
 */  
void test2_obj_get_light_visible();

/**
 * @test Test function for knowing obj_visible 
 * @pre pointer to Object != NULL
 * @post Output==TRUE
 */
void test1_obj_is_visible();

/**
 * @test Test function for getting obj_location
 * @pre pointer to Object = NULL
 * @post Output==FALSE
 */   
void test2_obj_is_visible(); 

/**
 * @test Test function for getting obj_type
 * @pre pointer to Object != NULL (id for APPLE)
 * @post Output==APPLE
 */
void test1_obj_get_type();

/**
 * @test Test function for getting obj_location
 * @pre pointer to Object = NULL
 * @post Output==UNKNOW_TYPE
 */ 
void test2_obj_get_type();

/**
 * @test Test function for obj_crit setting
 * @pre int (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_crit();
  
/**
 * @test Test function for object_crit setting
 * @pre int (pointer to object = NULL)
 * @post Output==ERROR
 */  
void test2_obj_set_crit();

/**
 * @test Test function for getting obj_durability
 * @pre pointer to Object != NULL
 * @post Output==5
 */
void test1_obj_get_durability();

/**
 * @test Test function for getting obj_durability
 * @pre pointer to Object = NULL
 * @post Output==0
 */  
void test2_obj_get_durability();  

/**
 * @test Test function for obj_durability setting
 * @pre int (pointer to object != NULL)
 * @post Output==OK
 */
void test1_obj_set_durability();

/**
 * @test Test function for obj_durability setting
 * @pre int (pointer to object = NULL)
 * @post Output==ERROR
 */ 
void test2_obj_set_durability();

/**
 * @test Test function for knowing obj_visible 
 * @pre pointer to Object != NULL
 * @post Output==FALSE
 */
void test1_obj_isBroken();

/**
 * @test Test function for getting obj_location
 * @pre pointer to Object = NULL
 * @post Output==TRUE
 */   
void test2_obj_isBroken();

#endif
