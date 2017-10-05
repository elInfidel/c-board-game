#include "board.h"

Cell BOARD_1[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

Cell BOARD_2[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

void initialiseBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int i, j;
    for(i = 0; i < BOARD_HEIGHT; ++i)
    {
      for(j = 0; j < BOARD_WIDTH; ++j)
      {
        board[i][j] = EMPTY;
      }
    }
}

void loadBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
               Cell boardToLoad[BOARD_HEIGHT][BOARD_WIDTH])
{
    int i, j;
    for(i = 0; i < BOARD_HEIGHT; ++i)
    {
      for(j = 0; j < BOARD_WIDTH; ++j)
      {
        board[i][j] = boardToLoad[i][j];
      }
    }
}

Boolean placePlayer(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Position position)
{
    /* Bounds check. */
    if((position.x < 0 || position.x > BOARD_WIDTH) &&
      (position.y < 0 || position.y > BOARD_HEIGHT))
      return FALSE;

    /* Blocked cell check. */
    if(board[position.x][position.y] == BLOCKED)
      return FALSE;

    /* Place player. */
    board[position.x][position.y] = PLAYER;
    return TRUE;
}

PlayerMove movePlayerForward(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
                             Player * player)
{
    Position newPosition = getNextForwardPosition(player);

    /* Check bounds. */
    if((newPosition.x < 0 || newPosition.x > BOARD_WIDTH - 1) ||
       (newPosition.y < 0 || newPosition.y > BOARD_HEIGHT - 1))
      return OUTSIDE_BOUNDS;

    /* Check blocked cell*/
    if(board[newPosition.y][newPosition.x] == BLOCKED)
      return CELL_BLOCKED;

    /*
    * Update player position -
    * We could assume the cell will be empty at this point however
    * we run the risk of a bug if new cell types are added later. So we check.
    */
    if(board[newPosition.y][newPosition.x] == EMPTY)
    {
      /*Clear current player pos cell & set new player pos cell*/
      board[player->position.y][player->position.x] = EMPTY;
      board[newPosition.y][newPosition.x] = PLAYER;
      updatePosition(player, newPosition);
    }

    return PLAYER_MOVED;
}

void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
    int i, j;

    /* Display board data*/
    printf("| |");
    for(i = 0; i < BOARD_WIDTH; ++i)
    {
      printf("%d|", i);
    }
    printf("\n");

    for(i = 0; i < BOARD_HEIGHT; ++i)
    {
      /* Display row index */
      printf("|%d|", i);

      /* Display board row data */
      for(j = 0; j < BOARD_WIDTH; ++j)
      {
        if(board[i][j] == PLAYER)
        {
          if(player != NULL)
          {
            displayDirection(player->direction);
            printf("|");
          }
        }
        else
        {
          const char* tile = (board[i][j] == BLOCKED)
          ? BLOCKED_OUTPUT : EMPTY_OUTPUT;

          printf("%s|", tile);
        }
      }

      /* Proceed to next row */
      printf("\n");
    }

    printf("\n");
}
