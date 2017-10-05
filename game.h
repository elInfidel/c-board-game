#ifndef GAME_H
#define GAME_H

#include "helpers.h"
#include "board.h"
#include "player.h"

/* Defines for commands/args the user is expected to input. */
#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_FORWARD "forward"
#define COMMAND_FORWARD_SHORTCUT "f"
#define COMMAND_TURN_LEFT "turn_left"
#define COMMAND_TURN_LEFT_SHORTCUT "l"
#define COMMAND_TURN_RIGHT "turn_right"
#define COMMAND_TURN_RIGHT_SHORTCUT "r"
#define COMMAND_QUIT "quit"

#define DIRECTION_NORTH "north"
#define DIRECTION_EAST "east"
#define DIRECTION_SOUTH "south"
#define DIRECTION_WEST "west"

#define BOARD_ONE_TEXT "1"
#define BOARD_TWO_TEXT "2"

/* State related information structure */
typedef struct gameState
{
  /* Set to TRUE when the relevant command should be available */
  Boolean loadAvailable;
  Boolean initAvailable;
  Boolean movementAvailable;
  Boolean quitAvailable;
  /* Set to TRUE when the game should progress to next stage */
  Boolean readyToContinue;
  /* Set to TRUE when quit has been selected */
  Boolean gameShouldExit;
} GameState ;

/* Contains commands */
typedef enum gameCommand
{
  LOAD = 0,
  INIT,
  MOVE_FORWARD,
  MOVE_LEFT,
  MOVE_RIGHT,
  QUIT,
  NONE
} GameCommand;

/* Defines for input related functionality */
#define INPUT_LENGTH 50 + EXTRA_SPACES

#define MAX_TOKENS 10
#define TOKEN_LENGTH 30 + EXTRA_SPACES
#define TOKEN_DELIMS ", "

#define INPUT_COMMAND_INDEX 0
#define INPUT_ARG_INDEX 1

/* Defines for commonly used game text */
#define INFO_LOAD "load <g>\n\
   g: number of the game board to load\n"

#define INFO_INIT "init <x>,<y>,<direction>\n\
   x: horizontal position of the car on the board (between 0 & 9)\n\
   y: vertical position of the car on the board (between 0 & 9)\n\
   direction: direction of the car's movement (north, east, south, west)\n"

#define INFO_MOVEMENT "forward (or f)\n\
turn_left (or l)\n\
turn_right (or r)\n"

#define INFO_QUIT "quit\n"

#define INFO_INVALID_COMMAND "\nInvalid Command!\n"

#define INFO_EDGE_OF_BOARD "\nThe car is at the edge of the board and cannot\
 move further in that direction\n"

#define INFO_ROAD_BLOCKED "\nERROR: cannot move forward because the road is\
 blocked. \n"

 #define PLAYER_INIT_FAIL "\nERROR: cannot place player here, the tile is\
  blocked. \n"

/**
 * Main menu option 1 - play the game as per the specification.
 *
 * This function makes all the calls to board & player and handles interaction
 * with the user (reading input from the console, error checking, etc...).
 *
 * It should be possible to break this function down into smaller functions -
 * but this is up to you to decide and is entirely your own design. You can
 * place the additional functions in this header file if you want.
 *
 * Note that if you don't break this function up it could become pretty big...
 */
void playGame();

/*
 * The 3 functions below hold the code for each of the 3 major stages
 * of gameplay.
 */
void load(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state);

void init(Player* player,
Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state);

void play(Player* player,
Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state);

/**
 * Listens for and extracts expected commands/args from input. storing them as
 * individual tokens within the token array.
 */
void readCommand(char tokens[MAX_TOKENS][TOKEN_LENGTH]);

/**
 * Returns TRUE when a valid command and all of its required args exists
 * within tokens and the command is currently set active in state.
 */
Boolean validateCommand(char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state);

/**
 * Executes the command/args inside the token array on the game using the
 * passed in player and board. Returns an enum type GameCommand with the
 * successfully executed command if any, otherwise will return NONE.
 *
 * NOTE: The tokens array should be run through validateTokens() func before
 * calling this func to verify that the command is valid.
 */
GameCommand executeCommand(Player* player,
Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state);

/*
 * Returns the type of the command contained with the tokens array.
 */
GameCommand extractCommandType(char tokens[MAX_TOKENS][TOKEN_LENGTH]);

/*
 * Displays the invalid input error message to the user and shows them
 * what valid commands they could have put in.
 */
void displayInvalidInputMsg(GameState* state);

/**
 * Displays all available commands/args to the player.
 */
void displayCommands();

/**
 * Displays all commands set to be available in the passed in game state.
 */
void displayCommandsWithState(GameState* state);

/**
 * Clears a passed in game state struct setting all flags to default.
 */
void clearGameStateFlags(GameState* state);

#endif
