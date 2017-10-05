#include "player.h"

void initialisePlayer(Player * player, Position * position, Direction direction)
{
    if(player == NULL || position == NULL) return;

    player->position = *position;
    player->direction = direction;
    player->moves = 0;
}

void turnDirection(Player * player, TurnDirection turnDirection)
{
    if(player == NULL) return;

    /* Determine new direction TODO: Could be improved?? */
    switch(player->direction)
    {
      case NORTH:
        if(turnDirection == TURN_RIGHT)
          player->direction = EAST;
        else
          player->direction = WEST;
        break;
      case EAST:
        if(turnDirection == TURN_RIGHT)
          player->direction = SOUTH;
        else
          player->direction = NORTH;
        break;
      case SOUTH:
        if(turnDirection == TURN_RIGHT)
          player->direction = WEST;
        else
          player->direction = EAST;
        break;
      case WEST:
        if(turnDirection == TURN_RIGHT)
          player->direction = NORTH;
        else
          player->direction = SOUTH;
        break;
    }
}

Position getNextForwardPosition(const Player * player)
{
    Position position;
    position.x = 0;
    position.y = 0;

    if(player == NULL) return position;

    position.x = player->position.x;
    position.y = player->position.y;

    /* Find position forward of current. */
    switch(player->direction)
    {
      case NORTH: position.y--; break;
      case EAST:  position.x++; break;
      case SOUTH: position.y++; break;
      case WEST:  position.x--; break;
    }

    return position;
}

void updatePosition(Player * player, Position position)
{
    if(player == NULL) return;

    player->position = position;
    player->moves++;
}

void displayDirection(Direction direction)
{
    switch(direction)
    {
      case NORTH:
        printf(DIRECTION_ARROW_OUTPUT_NORTH);
        break;
      case EAST:
        printf(DIRECTION_ARROW_OUTPUT_EAST);
        break;
      case SOUTH:
        printf(DIRECTION_ARROW_OUTPUT_SOUTH);
        break;
      case WEST:
        printf(DIRECTION_ARROW_OUTPUT_WEST);
        break;
    }
}
