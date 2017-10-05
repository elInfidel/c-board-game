#include "game.h"
#include "string.h"

void playGame()
{
  GameState state;
  Player player;
  Cell board[BOARD_HEIGHT][BOARD_WIDTH];
  char tokenArray[MAX_TOKENS][TOKEN_LENGTH];

  /* Initialize game play */
  initialiseBoard(board);
  displayCommands();
  displayBoard(board, NULL);
  clearGameStateFlags(&state);

  load(board, tokenArray, &state);

  if(state.gameShouldExit != TRUE)
    init(&player, board, tokenArray, &state);
  else return;

  if(state.gameShouldExit != TRUE)
    play(&player, board, tokenArray, &state);
  else return;
}

void load(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state)
{
  /* Load game board state */
  state->loadAvailable = state->quitAvailable = TRUE;
  do
  {
    displayCommandsWithState(state);

    do
    {
      readCommand(tokens);
    } while(validateCommand(tokens, state) == FALSE);

    if(executeCommand(NULL, board, tokens, state) == LOAD)
      state->readyToContinue = TRUE;

    displayBoard(board, NULL);

  } while(state->readyToContinue == FALSE);
  clearGameStateFlags(state);
}

void init(Player* player,
Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state)
{
  /* Set relevant flags */
  state->loadAvailable = state->initAvailable = state->quitAvailable = TRUE;
  do
  {
    GameCommand cmd;
    displayCommandsWithState(state);

    do
    {
      readCommand(tokens);
    } while(validateCommand(tokens, state) == FALSE);

    cmd = executeCommand(player, board, tokens, state);

    if(cmd == QUIT)
      return;
    else if (cmd == INIT)
      state->readyToContinue = TRUE;

    displayBoard(board, player);

  } while(state->readyToContinue == FALSE);
  clearGameStateFlags(state);
}

void play(Player* player,
Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state)
{
  /* Set relevant flags */
  state->movementAvailable = state->quitAvailable = TRUE;
  do
  {
    GameCommand cmd;
    displayCommandsWithState(state);

    do
    {
      readCommand(tokens);
    } while(validateCommand(tokens, state) == FALSE);

    cmd = executeCommand(player, board, tokens, state);

    if(cmd == QUIT)
    {
      printf("Total player moves: %d\n\n", player->moves);
      return;
    }
    else if (cmd == INIT)
      state->readyToContinue = TRUE;

    displayBoard(board, player);
  } while(state->readyToContinue == FALSE);
  clearGameStateFlags(state);
}

void readCommand(char tokens[MAX_TOKENS][TOKEN_LENGTH])
{
  int i;
  /* Storage for input and split tokens from input*/
  char input[INPUT_LENGTH];
  char* curToken;

  /* Clear existing data in token buffer before reading*/
  /* If we don't do this pressing enter with no chosen command will read last
     input.*/
  for(i = 0; i < MAX_TOKENS; ++i)
  {
    tokens[i][0] = '\0';
  }

  /* Grab input */
  printf("\nInput a command:\n");
  fgets(input, sizeof(input), stdin);

  /* buffer overflow handling */
  if(input[strlen(input) - 1] != '\n')
    readRestOfLine();

  /* remove newline */
  input[strlen(input)-1] = 0;

  /*Tokenize command*/
  curToken = strtok (input, TOKEN_DELIMS);
  for(i = 0; i < MAX_TOKENS && curToken != NULL; ++i)
  {
    strcpy(tokens[i], curToken); /* TODO handle curTokenlen > TOKEN_LENGTH*/
    curToken = strtok (NULL, TOKEN_DELIMS);
  }
}

/*TODO: This function is a catastrophic mess, refactor!!!!! */
Boolean validateCommand(char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state)
{
  char* args = tokens[INPUT_ARG_INDEX];
  int x, y;
  GameCommand cmd = extractCommandType(tokens);

  /* Checks if a command is available and if so checks any args associated */
  /* Will return TRUE if a command is valid alongside its args based on state */
  switch(cmd)
  {
    case LOAD:
      if(state->loadAvailable == FALSE)
      {
        displayInvalidInputMsg(state);
        return FALSE;
      }

      if(strcmp(args, BOARD_ONE_TEXT) == 0) return TRUE;
      else if(strcmp(args, BOARD_TWO_TEXT) == 0) return TRUE;
      else
      {
        displayInvalidInputMsg(state);
        return FALSE;
      }
      break;
    case INIT:
      if(state->initAvailable == FALSE)
      {
        displayInvalidInputMsg(state);
        return FALSE;
      }
      /* Using offsets to go further into argument list */
      /* Check x,y args are valid */
      if(isdigit(*tokens[INPUT_ARG_INDEX]) == FALSE ||
         isdigit(*tokens[INPUT_ARG_INDEX + 1]) == FALSE)
      {
        displayInvalidInputMsg(state);
        return FALSE;
      }

      x = atoi(tokens[INPUT_ARG_INDEX]);
      y = atoi(tokens[INPUT_ARG_INDEX + 1]);
      if(x < 0 || x >= BOARD_WIDTH ||
         y < 0 || y >= BOARD_HEIGHT)
         return FALSE;

      /* Check valid direction */
      if((strcmp(tokens[INPUT_ARG_INDEX + 2], DIRECTION_NORTH) == 0) ||
        (strcmp(tokens[INPUT_ARG_INDEX + 2], DIRECTION_EAST ) == 0) ||
        (strcmp(tokens[INPUT_ARG_INDEX + 2], DIRECTION_SOUTH) == 0) ||
        (strcmp(tokens[INPUT_ARG_INDEX + 2], DIRECTION_WEST ) == 0))
        return TRUE;
      else
      {
        displayInvalidInputMsg(state);
        return FALSE;
      }
    case MOVE_FORWARD:
    case MOVE_LEFT:
    case MOVE_RIGHT:
      if(state->movementAvailable == FALSE)
      {
        displayInvalidInputMsg(state);
        return FALSE;
      }
      return TRUE;
    case QUIT:
      if(state->quitAvailable == FALSE) return FALSE;
      return TRUE;
    case NONE:
      displayInvalidInputMsg(state);
      return FALSE;
  }

  displayInvalidInputMsg(state);
  return FALSE;
}

GameCommand executeCommand(Player* player,
Cell board[BOARD_HEIGHT][BOARD_WIDTH],
char tokens[MAX_TOKENS][TOKEN_LENGTH], GameState* state)
{
  char* args = tokens[INPUT_ARG_INDEX];
  /* data used in switch*/
  int boardNum = 0;
  Position pos;
  Direction dir;
  PlayerMove playerMove;

  GameCommand cmd = extractCommandType(tokens);

  /* call relative functionality to command in valid */
  switch(cmd)
  {
    case LOAD:
      boardNum = atoi(args);
      if(boardNum == 1) {
        loadBoard(board, BOARD_1); return LOAD;
      }
      if(boardNum == 2) {
        loadBoard(board, BOARD_2); return LOAD;
      }
      return NONE;
    case INIT:
      pos.x = atoi(tokens[INPUT_ARG_INDEX]);
      pos.y = atoi(tokens[INPUT_ARG_INDEX+1]);


      if(strcmp(tokens[INPUT_ARG_INDEX+2], DIRECTION_NORTH) == 0) dir = NORTH;
      if(strcmp(tokens[INPUT_ARG_INDEX+2], DIRECTION_EAST) == 0) dir = EAST;
      if(strcmp(tokens[INPUT_ARG_INDEX+2], DIRECTION_SOUTH) == 0) dir = SOUTH;
      if(strcmp(tokens[INPUT_ARG_INDEX+2], DIRECTION_WEST) == 0) dir = WEST;

      if(placePlayer(board, pos) == TRUE)
      {
        initialisePlayer(player, &pos, dir);
        return INIT;
      }
      else
      {
        printf(PLAYER_INIT_FAIL);
        return NONE;
      }
    case MOVE_FORWARD:
      playerMove = movePlayerForward(board, player);
      if(playerMove == CELL_BLOCKED)
      {
        printf(INFO_ROAD_BLOCKED);
        return NONE;
      }
      else if(playerMove == OUTSIDE_BOUNDS)
      {
        printf(INFO_EDGE_OF_BOARD);
        return NONE;
      }

      return MOVE_FORWARD;
    case MOVE_LEFT:
      turnDirection(player, TURN_LEFT); return MOVE_LEFT;
    case MOVE_RIGHT:
      turnDirection(player, TURN_RIGHT); return MOVE_RIGHT;
    case QUIT:
      state->gameShouldExit = TRUE; return QUIT;
    default:
      return NONE;
  }

  /*
  * If we don't call a command then we can assume the command was invalid
  * and we return NONE to symbolise that.
  */
  return NONE;
}

GameCommand extractCommandType(char tokens[MAX_TOKENS][TOKEN_LENGTH])
{
  char* command = tokens[INPUT_COMMAND_INDEX];

  /* Attempt to match the command */
  if(strcmp(command, COMMAND_LOAD) == 0)
  {
    return LOAD;
  }
  else if(strcmp(command, COMMAND_INIT) == 0)
  {
    return INIT;
  }
  else if((strcmp(command, COMMAND_FORWARD) == 0) ||
  (strcmp(command, COMMAND_FORWARD_SHORTCUT) == 0))
  {
    return MOVE_FORWARD;
  }
  else if((strcmp(command, COMMAND_TURN_LEFT) == 0) ||
  (strcmp(command, COMMAND_TURN_LEFT_SHORTCUT) == 0))
  {
    return MOVE_LEFT;
  }
  else if((strcmp(command, COMMAND_TURN_RIGHT) == 0)||
  (strcmp(command, COMMAND_TURN_RIGHT_SHORTCUT) == 0))
  {
    return MOVE_RIGHT;
  }
  else if(strcmp(command, COMMAND_QUIT) == 0)
  {
    return QUIT;
  }

  return NONE;
}

void displayInvalidInputMsg(GameState* state)
{
  printf(INFO_INVALID_COMMAND);
  displayCommandsWithState(state);
}

void displayCommands()
{
  printf("\nYou can use the following commands to play the game:\n");

  printf(INFO_LOAD);
  printf(INFO_INIT);
  printf(INFO_MOVEMENT);
  printf(INFO_QUIT);

  printf("\n");
}

void displayCommandsWithState(GameState* state)
{
  printf("\nYour currently available commands are:\n\n");

  if(state->loadAvailable == TRUE)
    printf(INFO_LOAD);

  if(state->initAvailable == TRUE)
    printf(INFO_INIT);

  if(state->movementAvailable == TRUE)
    printf(INFO_MOVEMENT);

  if(state->quitAvailable == TRUE)
    printf(INFO_QUIT);

  printf("\n");
}

void clearGameStateFlags(GameState* state)
{
  state->loadAvailable = FALSE;
  state->initAvailable = FALSE;
  state->movementAvailable = FALSE;
  state->quitAvailable = FALSE;
  state->readyToContinue = FALSE;
  state->gameShouldExit = FALSE;
}
