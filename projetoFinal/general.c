/**
 * 
 * @file general.c
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Source file general
 * 
 * Source file containing all the general functions.
 */
//library definition
#include "general.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Function below checks if the given value
 * is between two values, if not, the cycle continues.
 *
 * @param min Minimum value of the menu option.
 * @param max Maximum value of the menu option.
 * @param message[] Vector that hold the Menu message.
 * @return option Returns the option that the user has chosen.
 */

int menuRead(char message[], int min, int max) {
    int option = 0;
    char verify[MAX_VERIFY_CHARS] = "";
    do {
        do {
            puts(message);
            printf("\t\t\tInsert here - ");
            scanf("%s", verify);
            if (strcmp(verify, "0") == 0) {
                system("cls || clear");
                return option;
            }
            if (!(option = atoi(verify))) {
                errorMessage(MSG_ERROR_MESSAGE);
            }
        } while (!(option = atoi(verify)));

        system("cls || clear");
        if (option < min || option > max) {
            errorMessage(MSG_ERROR_MESSAGE);
        }
    } while (option < min || option > max);
    return option;
}
/**
 * Function below appears when an error appears, it receives the error message
 * as a parameter, and then waits for the user to press a key, if so, the screen
 * is cleaned and the function ends.
 *
 * @param message Vector which the error message is going to be stored.
 */
void errorMessage(const char message[]) {
    system("cls || clear");
    puts(message);
    pressAnyKeyToContinueFunction();
}
/**
 * Function below receives a message and depending on what the character that was
 * written the value that is returned is different.
 *
 * @param message[] Confirmation message.
 * @return 1 if the letter Y is pressed.
 * @return 2 if the letter N is pressed.
 */
int yesOrNoFunction(const char *message) {
    char option;
    do {
        printf("%s", message);
        scanf(" %c", &option);
    } while (option != 'y' && option != 'n' && option != 'Y' && option != 'N');
    switch (option) {
        case 'y':
        case 'Y':
            return 1;
            break;
        case 'n':
        case 'N':
            return 2;
            break;
        default:
            break;
    }
}

/**
 * These functions make it so when a function is over, the user can press any
 * key to continue with the program.
 * 
 * The function below this one works the same way, just that it is used to the lists.
 */

void pressAnyKeyToContinueFunction() {
    char any_key[20];

    printf("\n\t\t\t__________________________________");
    printf("\n\t\t\tPress any key to exit ");
    scanf("%s", any_key);
    system("cls || clear");
}
void pressAnyKeyToContinueFunctionListVersion() {
    char any_key[20];

    printf("\n\t\t\tPress any key to exit ");
    scanf("%s", any_key);
    system("cls || clear");
}