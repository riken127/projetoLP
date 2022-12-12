//Macro and Library definition
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clients.h"
#include "production.h"
#include "products.h"
#define MSG_MAIN_MENU  "[1] - User.\n[2] - Admin."
#define MSG_ADMIN_MENU  "[1] - Clients Management.\n[2] - Products Management.\n[3] - Production Management."
#define MAX_CLIENTS 20



void adminMenu(Customer customer[], int *contCustomers, int curentID) {
    int option;

    do {
        option = menuRead(MSG_ADMIN_MENU, 0, 3);

        switch (option) {
            case 0:
                break;
            case 1:
                customerManagementMenu(customer, &(*contCustomers), curentID);
                break;
            case 2:
                break;
            case 3:
                break;
        }
    } while (option != 0);
}
/*
 * This menu is divided into three sub-menus, it loops until the integer [option] given by the user is equal to zero.
*/
void mainMenu(Customer customer[], int *contCustomers, int curentID) {
    int option;

    do {
        option = menuRead(MSG_MAIN_MENU, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:

                break;
            case 2:
                adminMenu(customer, &(*contCustomers), curentID);
                break;
        }
    } while (option != 0);
}
/*
 * This is the main menu, it's divided in two sides, the customer side, and the admin side, it loops until the integer
 * [option] given by the user is equal to zero.
 */
int main(int argc, char** argv) {

    int contCustomers = 0, curentID = 0;
    Customer customer[MAX_CLIENTS];

    mainMenu(customer, &contCustomers, curentID);

    return (EXIT_SUCCESS);
}

/*
 * This is the main function, this is all the structs are instantiated, here the main menu is invoked.
 */
