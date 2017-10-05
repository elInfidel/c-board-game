#ifndef BOARD_H
#define BOARD_H

#include "helpers.h"
#include "player.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

typedef enum cell
{
	EMPTY,
	BLOCKED,
	PLAYER
} Cell;

#define EMPTY_OUTPUT " "
#define BLOCKED_OUTPUT "*"

Cell BOARD_1[BOARD_HEIGHT][BOARD_WIDTH];
Cell BOARD_2[BOARD_HEIGHT][BOARD_WIDTH];

typedef enum playerMove
{
    PLAYER_MOVED,
    CELL_BLOCKED,
    OUTSIDE_BOUNDS
} PlayerMove;

/**
 * Initialise the board - set all the cells in the board to EMPTY.
 */
void initialiseBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH]);

/**
 * Load the board - set all the cells in board to those present in boardToLoad.
 */
void loadBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
               Cell boardToLoad[BOARD_HEIGHT][BOARD_WIDTH]);

/**
 * Try to place the PLAYER cell at the provided position.
 *
 * Note that if the position is outside the bounds of the board or if the cell
 * at the provided position is BLOCKED then you should return FALSE.
 *
 * Return TRUE when the cell at the position is successfully set to PLAYER.
 */
Boolean placePlayer(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Position position);

/**
 * Try to move the player forward - note the player has a current direction and
 * position.
 *
 * You should call "getNextForwardPosition(...)" to get the position as if the
 * player did move.
 *
 * If this new position is outside the bounds of the board return
 * OUTSIDE_BOUNDS. If the new position is on-top of a BLOCKED cell then
 * return CELL_BLOCKED.
 *
 * Note that if either of these error cases occur then the board cells and
 * player position are not modified.
 *
 * Lastly if the new position is EMPTY then remove PLAYER from the current
 * player's position on the board (set cell to EMPTY) and set the new position
 * to PLAYER. And call "updatePosition(...)" to update the player's position
 * then return PLAYER_MOVED.
 */
PlayerMove movePlayerForward(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
                             Player * player);

/**
 * Display the board according to the specification. Take note when encountering
 * the PLAYER cell and that you should call "displayDirection(...)" function to
 * display the arrow. Here is an example output (without the player arrow):

| |0|1|2|3|4|5|6|7|8|9|
|0|*|*|*| | | | | | | |
|1| |*|*| | | | | | | |
|2| |*|*| | | | | | | |
|3| | | | |*| | | | | |
|4| | | | |*| | | | | |
|5| |*|*| | | | | | | |
|6| | | | |*| | | | | |
|7| |*|*| | | | | | | |
|8| |*|*| | | | | | | |
|9| |*|*| | | | | | | |

 */
void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player);

#endif
