#ifndef PLAYER_H
#define PLAYER_H

#include "helpers.h"

typedef enum direction
{
  NORTH,
  EAST,
	SOUTH,
	WEST
} Direction;

typedef enum turnDirection
{
  TURN_LEFT,
  TURN_RIGHT
} TurnDirection;

typedef struct position
{
	int x;
	int y;
} Position;

typedef struct player
{
	Position position;
	Direction direction;
	unsigned moves;
} Player;

/**
 * Some predefined strings that should print out arrows on the terminal...
 */
#define DIRECTION_ARROW_OUTPUT_NORTH "\xe2\x86\x91"
#define DIRECTION_ARROW_OUTPUT_EAST "\xe2\x86\x92"
#define DIRECTION_ARROW_OUTPUT_SOUTH "\xe2\x86\x93"
#define DIRECTION_ARROW_OUTPUT_WEST "\xe2\x86\x90"

/**
 * Initialise the player - set the position, direction to the provided values
 * and set moves to 0.
 */
void initialisePlayer(Player * player, Position * position, Direction direction);

/**
 * Turn the player's direction according to the direction of the player and the
 * turn direction.
 *
 * Turn right has the following sequence:
 * North -> East
 * East -> South
 * South -> West
 * West -> North
 *
 * Turn left has the following sequence:
 * North -> West
 * West -> South
 * South -> East
 * East -> North
 */
void turnDirection(Player * player, TurnDirection turnDirection);

/**
 * Gets the new position as if the player moved forward from the player's
 * current position and direction.
 *
 * Note the new position can be outside the bounds of the board and could be on
 * a blocked cell. Also note that you should not modify the current position of
 * the player.
 */
Position getNextForwardPosition(const Player * player);

/**
 * Set the player's position to the provided position. Also increment the
 * moves count.
 */
void updatePosition(Player * player, Position position);

/**
 * Prints the direction arrow to the console - based upon the direction set
 * print one of the "DIRECTION_ARROW_OUTPUT_..." defines above.
 *
 * For example to print the north arrow:
 *     printf(DIRECTION_ARROW_OUTPUT_NORTH);
 */
void displayDirection(Direction direction);

#endif
