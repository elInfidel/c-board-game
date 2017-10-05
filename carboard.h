#ifndef CARBOARD_H
#define CARBOARD_H

#include "helpers.h"
#include "game.h"

/* Student details for use in student information menu. */
#define STUDENT_NAME "Liam"
#define STUDENT_ID "sxxxxxxx"
#define STUDENT_EMAIL "sxxxxxxx@student.rmit.edu.au"

/* Values representing options the user may select on the main menu. */
#define OPTION_PLAY_GAME 1
#define OPTION_SHOW_STUDENT_INFO 2
#define OPTION_QUIT 3

/* True when the user opts to quit via menu. */
int programShouldEnd = FALSE;

/*
* Displays main menu to the users allowing them to choose between
* between playing the game, showing their student information or quiting.
*/
void showMainMenu();

/*
* Listens for input from the user, expects one of the following defined inputs
* - OPTION_PLAY_GAME
* - OPTION_SHOW_STUDENT_INFO
* - OPTION_QUIT
*
* If the user inputs an invalid option, they will be notified and told to try
* again.
*/
void processMenuInput();

/**
 * Main menu option 2 - show your student information as per the specification.
 *
 * You should change the defines above related to student information and use
 * them when printing.
 */
void showStudentInformation();

#endif
