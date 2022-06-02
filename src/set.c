/** 
 * @brief Implements the necessary functions to work with sets
 * 
 * @file set.c
 * @author Miguel Soto, Nicolas Victorino, Ignacio Nunez and Antonio Van-Oers
 * @version 2.0
 * @date 08-03-2022 
 * @copyright GNU Public License
 */

#include "../include/set.h"

/**
 * @brief Set
 * 
 * This struct stores a set of ids and the number of ids stored.
 */
struct _Set
{
    Id *ids;            /*!< Ids array */
    int n_ids;          /*!< Number of ids stored*/
};

/**
 * set_create Allocates memory for a new set and 
 * has all its members initialized
 */
Set *set_create()
{
    Set *new_set = NULL;    

    new_set = (Set *) malloc(sizeof(Set));
    if (!new_set)
    {
        return NULL;
    }
    
    new_set->ids = NULL;
    new_set->n_ids = 0;

    return new_set;
}

/**
 * set_destroy Frees the previously allocated memory for a set and all 
 * of its members
 */
STATUS set_destroy(Set *s)
{
    /*Error control*/
    if (!s)
    {
        return ERROR;
    }
    
    if (s->ids)
    {
        free(s->ids);
    }
    
    free(s);
    s = NULL;
    
    return OK;
}

/**
 * set_add increases the number of ids in the set 
 * and stores the newest in the last position
 */
STATUS set_add(Set *s, Id id)
{
    Id *aux = NULL;

    /*Error control*/
    if (!s || id == NO_ID)
    {
        return ERROR;
    }
    
    /* increasing the number of ids*/
    aux = (Id *) realloc(s->ids, (s->n_ids + 1) * sizeof(Id));
    if (!aux)
    {
        return ERROR;
    }
    s->n_ids++;
    s->ids = aux;
    aux = NULL;

    s->ids[s->n_ids-1] = id;

    return OK;
}

/**
 * et_del_id searches for the indicated id on a set
 * and has it removed
 */
STATUS set_del_id(Set *s, Id id)
{
    int i, k;
    Id *aux = NULL;
    
    /*Error control*/
    if (!s || id == NO_ID || s->n_ids == 0)
    {
        return ERROR;
    }
    
    for (i = 0, k = 0; i < s->n_ids && k == 0; i++)
    {
        if (s->ids[i] == id)
        {
            s->ids[i] = s->ids[s->n_ids-1];

            /*Error control*/
            aux = (Id *) realloc(s->ids, (s->n_ids) * sizeof(Id));
            if (!aux)
            {
                return ERROR;
            }
            s->n_ids--;

            s->ids = aux;
            aux = NULL;

            k = 1;
        }
    }

    if (k == 1)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

/**
 * set_del_pos Removes an id from the set by a position based search
 */
STATUS set_del_pos(Set *s, int pos)
{
    Id *aux = NULL;

    /*Error control*/
    if (!s || pos < 0 || pos >= s->n_ids || s->n_ids == 0)
    {
        printf("aa\n");
        return ERROR;
    }

    /*Error control*/
    if (s->ids[pos] == NO_ID)
    {
        printf("aaa\n");
        return ERROR;
    }
    
    s->ids[pos] = s->ids[s->n_ids-1];
    
    aux = (Id *) realloc(s->ids, s->n_ids * sizeof(Id));
    if (!aux)
    {
        return ERROR;
    }
    s->n_ids--;
    s->ids = aux;
    aux = NULL;

    return OK;
}

/**
 * Gets the amount of ids in a set
 */
int set_get_nids(Set *s)
{
    /*Error control*/
    if (!s)
    {
        return -1;
    }
    
    return s->n_ids;
}

/**
 * Gets the array containing all ids from a set
 */
Id *set_get_ids(Set *s)
{
    /*Error control*/
    if (!s)
    {
        return NULL;
    }
    
    return s->ids;
}

/**
 * Tests whether the set is well defined or not
 */
STATUS set_test(Set *s)
{
    int i, size_s;

    /*Error control*/
    if (!s || s->n_ids < 0)
    {
        return ERROR;
    }
    
    /* Testing correct amount of ids*/
    if (s->n_ids > 0)
    {
        size_s = (int) sizeof(s->ids) / sizeof(Id);
        if (size_s != s->n_ids)
        {
            return ERROR;
        }
        
    }
    
    /* Testing that there is no id == NO_ID*/
    for (i = 0; i < s->n_ids; i++)
    {
        if (s->ids[i] == NO_ID)
        {
            return ERROR;
        }
        
    }
    
    return OK;
}

/*Function that tells if an object is or not in a set*/
BOOL set_idInSet (Set* set, Id id)
{
    int i = 0; 

    /*Error control*/
    if ((!set) || (!id)) {
        return FALSE;
    }


    /*Checks the position where the id coincides*/
    while (i < set->n_ids) {
        if(set->ids[i]==id){
            break;
        }
        i++;
    }

    /*If it has not located the position, it reaches MAX_IDS and returns ERROR*/
    if ( i == set->n_ids) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * Prints all info regarding set
 */
int set_print(Set *s)
{
    int i, n;

    /*Error control*/
    for (i = 0, n = 0; i < s->n_ids; i++)
    {
        n += fprintf(stdout, "Id %d : %ld\n", i, s->ids[i]);
    }
    
    return n;
}

Id set_get_ids_by_number(Set* set, int n)
{
    /*Error control*/
    if (!set || n < 0 || n > set->n_ids + 1)
    return -1;

    return set->ids[n];
}
