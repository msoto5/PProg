/** 
 * @brief Implements the object's interface
 * 
 * @file object.h
 * @author Miguel Soto, Antonio Van-Oers, Ignacio Nunez and Nicolas Victorino
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#define OBJ_NAME_LEN 40   /*!< Establish maximun length of object's name */

typedef struct _Object Object;  /*!< It defines the object structure, which can be taken or dropped by the player */


/**
 * @brief Creates a new object
 * @author Miguel Soto
 *
 * obj_create allocates memory for a new object and initializes all its members
 * @param id is the target object's id
 * @return a new object (type Object) initialized, or NULL if anything goes wrong.
 */
Object *obj_create(Id id);

/**
 * @brief Destroys an object
 * @author Miguel Soto
 * 
 * obj_destroy frees the previously allocated memory for an object
 * @param obj is a pointer to the target object.
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_destroy(Object *obj);

/**
 * @brief Tests whether the designated id is from an object or not
 * @author Miguel Soto
 * 
 * @param id is the target object's id
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_test_id(Id id);

/**
 * @brief  Gets an object's id
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @return object's id, or NULL if anything goes wrong.
 */
Id obj_get_id(Object *obj);

/**
 * @brief Gets an object's name 
 * @author Miguel Soto
 *
 * @param obj is a pointer to the target object.
 * @return a string with the object's name, or NULL if anything goes wrong.
 */
const char *obj_get_name(Object *obj);

/**
 * @brief Sets an object's name
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @param name a string containing the new object's name
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_set_name(Object *obj, char *name);

/**
 * @brief Gets the description of a given object
 * @author Ignacio Nunnez
 * 
 * description_get_name returns the descrption of the objetc(obj).
 * @param obj pointer to given object
 * @return char string with the description of the object, or NULL if there was an error
 */
const char *obj_get_description(Object *obj);

/**
 * @brief Sets the description of a given object
 * @author Miguel Soto
 * 
 * obj_set_descripcion sets the description of the object (obj).
 * @param obj pointer to given object
 * @param description string with the new description of the object
 * @return OK, if everything is right ERROR, if there was a mistake
 */
STATUS obj_set_description(Object *obj, char *descripcion);

/**
 * @brief Gets an object's position
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @return space's id where the object is located.
 */
Id obj_get_location(Object *obj);

/**
 * @brief Sets an object's position
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @param id is the target object's id
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong. 
 */
STATUS obj_set_location(Object *obj, Id id);

/**
 * @brief Prints the info regarding an object 
 * @author Miguel Soto and Nicolas Victorino
 *  
 * obj_print prints an object's name and id
 * @param obj is a pointer to the target object.
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_print(Object *obj);

/**
 * @brief Sets the movable condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object @param cond new value of the condition
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_movable(Object *obj, BOOL cond);

/**
 * @brief Sets the dependency condition of an object, assigining it the id of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object @param id id of the object the has dependency with the given
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_dependency(Object *obj, Id id);

/**
 * @brief Sets the open condition of an object, assigining it the id of an space
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object @param id id of the space that can be opened by the given object
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_open(Object *obj, Id id);

/**
 * @brief Sets the illuminate condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object @param cond new value of the condition
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_illuminate(Object *obj, BOOL cond);

/**
 * @brief Sets the turned on condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object @param cond new value of the condition
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_turnedon(Object *obj, BOOL cond);

/**
 * @brief Gets the movable condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object
 * @return TRUE if object is movable, FALSE if not
 */
BOOL object_get_movable(Object *obj);

/**
 * @brief Gets the dependency condition of an object, in the form of an Id
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object
 * @return Id of the object that is dependent of the given one, NO_ID if no object has dependency
 */
Id object_get_dependency(Object *obj);

/**
 * @brief Gets the open condition of an object, in the form of an Id
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object
 * @return Id of the space that is opened by the given object, NO_ID if the object doesnt open any space
 */
Id object_get_open(Object *obj);

/**
 * @brief Gets the illuminate condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object
 * @return TRUE if object con illuminate, FALSE if not
 */
BOOL object_get_illuminate(Object *obj);

/**
 * @brief Gets the turned on condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object
 * @return TRUE if object is turned on (can illuminate), FALSE if not
 */
BOOL object_get_turnedon(Object *obj);

/** @brief obj_print_save prints the information of an object in the save file
 *  @author Nicolas Victorino
 * 
 *  @param obj pointer to the object we want to print
 *  @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_print_save(char *filename, Object *obj);

/**
 * @brief Sets the light_visible condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object @param light new value of the condition
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_light_visible(Object *obj, Light light);

/**
 * @brief Gets the light_visible condition of an object
 * @author Nicolas Victorino
 *  
 * @param obj is a pointer to the target object
 * @return Light when the object is visible, -1 if error
 */
Light object_get_light_visible(Object *obj);

/** 
 * @brief Return true if the object is visible
 * @author Nicolas Victorino
 * 
 * @param obj_id id of the object @param time Day time @param ls Light status of the space
 * @return True if visible
*/
BOOL obj_is_visible(Object *obj, Light ls);

/**
 * @brief Gets the type of an object (apple, bed...)
 * 
 * @author Nicolas Victorino
 * @param id 
 * @return Object type or UNKOWN_TYPE if error
 */
Obj_type obj_get_type(Id id);

/**
 * @brief Gets the crit_damage of an object
 * @author Antonio Van-Oers Luis
 *  
 * @param obj is a pointer to the target object
 * @return the crit chance that an object gives
 */
int object_get_crit(Object *obj);

/**
 * @brief Sets the crit_damage of an object
 * @author Antonio Van-Oers Luis
 *  
 * @param obj is a pointer to the target object
 * @param crit crit chance
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_crit(Object *obj, int crit);

/**
 * @brief Gets the durability of an object
 * @author Antonio Van-Oers Luis
 *  
 * @param obj is a pointer to the target object
 * @return the durability that an object gives
 */
int object_get_durability(Object *obj);

/**
 * @brief Sets the durability of an object
 * @author Antonio Van-Oers Luis
 *  
 * @param obj is a pointer to the target object
 * @param dur durability points
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS object_set_durability(Object *obj, int dur);

/**
 * @brief Tells if an item is broken (0 durability)
 * @author Antonio Van-Oers Luis
 *  
 * @param obj is a pointer to the target object
 * @return True if it is indeed broken and FALSE in case it isn't
 */
BOOL object_isBroken(Object *obj);

#endif

