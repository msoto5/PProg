/**
 * @brief It defines features of the game
 *
 * @file game_rules.h
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers, Ignacio Nunez
 * @version 1.0
 * @date 25-04-2022
 * @copyright GNU Public License
 */

#define EVENT_CERO 0
#define EVENT_ONE 75
#define EVENT_TWO 80
#define EVENT_THREE 85
#define EVENT_FOUR 93
#define EVENT_FIVE 95

typedef enum rules_Event
{
  NOTHING = EVENT_CERO,
  MOVE_OBJ = EVENT_ONE,
  TRAP = EVENT_TWO,
  SLIME = EVENT_THREE,
  DAYNIGHT = EVENT_FOUR,
  SPAWN = EVENT_FIVE
} R_Event;

/**
 * @brief Obtains the Event for the game
 * @author Ignacio Nunnez
 *
 * It generates a random number and according to some percentages
 * return the event for the inmediate game
 *
 * @return R_Event, most cases will be NOTHING
 */
R_Event game_rules_get_event();
