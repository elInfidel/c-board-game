#include "carboard.h"
#include "game.h"

int main()
{
    /**
     * Here's the main function. You can write the "main menu" loop/code
     * here or you can make separate functions - up to you.
     */
    showMainMenu();

    printf("\n Good bye! \n\n");

    return EXIT_SUCCESS;
}

void showMainMenu()
{
  while(!programShouldEnd)
  {
    printf("\nWelcome to Car Board\n");
    printf("--------------------\n");
    printf("%d. Play game\n", OPTION_PLAY_GAME);
    printf("%d. Show student's information\n", OPTION_SHOW_STUDENT_INFO);
    printf("%d. Quit\n", OPTION_QUIT);
    printf("\n");
    printf("Please enter your choice: ");
    processMenuInput();
  }
}

/* Potential stack overflow? Probably not a big deal. */
void processMenuInput()
{
  char input[1 + EXTRA_SPACES];
  int inputInt;

  /* Grab input */
  fgets(input, sizeof(input), stdin);
  inputInt = atoi(input);

  /* Check buffer overflow */
  if(input[1] != '\n')
    readRestOfLine();

  /* Validate Input */
  if(inputInt != OPTION_PLAY_GAME
    && inputInt != OPTION_SHOW_STUDENT_INFO
    && inputInt != OPTION_QUIT)
  {
    printf("\nPlease enter your choice: ");
    processMenuInput();
  }
  else
  {
    switch(inputInt)
    {
      case OPTION_PLAY_GAME:
        playGame();
        break;
      case OPTION_SHOW_STUDENT_INFO:
        showStudentInformation();
        break;
      case OPTION_QUIT:
        programShouldEnd = TRUE;
        break;
    }
  }

}

void showStudentInformation()
{
  /** Print student info based on defined info in carboard.h */
  printf("\n-------------------------\n");
  printf("Name: %s\n", STUDENT_NAME);
  printf("No: %s\n", STUDENT_ID);
  printf("Email: %s\n", STUDENT_EMAIL);
  printf("-------------------------\n\n");
}
