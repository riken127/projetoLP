//
// Created by r1ken on 19-01-2023.
//

#include "general.h"
#include <string.h>
#include <stdio.h>
/*
 * Bellow function checks if the given value
 * is between two values, if not, the cycle continues.
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