//
// Created by r1ken on 16-01-2023.
//

#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
//macro definition
#define MSG_MAIN_MENU "\n\t\t\t========= Main Menu =========\n\n\t\t\t[1] - User.\n\t\t\t[2] - Admin.\n\t\t\t[3] - Import.\n\t\t\t[4] - Export.\n\t\t\t[0] - Quit.\n\t\t\t_____________________________"
#define MSG_ADMIN_MENU                                                         \
  "\n\t\t\t=============== Admin Menu ===============\n\n\t\t\t[1] - Clients Management.\n\t\t\t[2] - Products & Materials Management.\n\t\t\t[3] - Production "   \
  "Management.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________________"
#define MSG_CLIENT_MENU                                                        \
  "\n\t\t\t========= Client Menu =========\n\n\t\t\t[1] - Do order.\n\t\t\t[2] - List orders.\n\t\t\t[0] - Quit.\n\t\t\t_______________________________"
#define MSG_IMPORT_MENU "\n\t\t\t========= Import Menu =========\n\n\t\t\t[1] - Clients.\n\t\t\t[2] - Products & Materials\n\t\t\t[3] - Orders.\n\t\t\t[0] - Quit.\n\t\t\t_______________________________"
#define MSG_EXPORT_MENU "\n\t\t\t========= Export Menu =========\n\n\t\t\t[1] - Clients.\n\t\t\t[2] - Products & Materials\n\t\t\t[3] - Orders.\n\t\t\t[0] - Quit.\n\t\t\t_______________________________"

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

/*
 * This menu is divided into three sub-menus, it loops until the integer
 * [option] given by the user is equal to zero.
 */
void adminMenu(Customers *customer, Orders **order,
        Products **product, Materials **material) {
    int option;

    do {
        option = menuRead(MSG_ADMIN_MENU, 0, 3);

        switch (option) {
            case 0:
                break;
            case 1:
                customerManagementMenu(customer, *order);
                break;
            case 2:
                productsMaterialsManagementMenu(*product, *material, *order);
                break;
            case 3:
                productionManagementMenu(order, material, product);
                break;
        }
    } while (option != 0);
}

/*
 * This menu loops until the integer
 * [option] given by the user is equal to zero.
 */
void clientMenu(Customers *customer, Products **product,
        Orders **order) {
    int option;

    do {
        option = menuRead(MSG_CLIENT_MENU, 0, 4);
        switch (option) {
            case 0:
                break;
            case 1:
                doOrder(*(&customer), *product, *order);
                break;
            case 2:
                listOrders(*order);
                break;
        }
    } while (option != 0);
}

void importMenu(Customers *customer, Orders **order,
        Products **product, Materials **material) {
    int option;

    do {
        option = menuRead(MSG_IMPORT_MENU, 0, 3);

        switch (option) {
            case 0:
                break;
            case 1:
                importCustomers(customer);
                break;
            case 2:
                loadProductMaterials(*product, *material);
                break;
            case 3:
                importOrders(*order);
                break;
        }
    } while (option != 0);
}

void exportMenu(Customers *customer, Orders **order,
        Products **product, Materials **material) {
    int option;

    do {
        option = menuRead(MSG_EXPORT_MENU, 0, 3);

        switch (option) {
            case 0:
                break;
            case 1:
                exportCustomers(customer);
                break;
            case 2:
                saveProductMaterials(*product, *material);
                break;
            case 3:
                exportOrders(*order);
                break;
        }
    } while (option != 0);
}

/*
 * This is the main menu, it's divided in two sides, the customer side, and the
 * admin side, it loops until the integer [option] given by the user is equal to
 * zero.
 */
void mainMenu(Customers *customer, Products **product,
        Orders **order, Materials **material) {
    int option;
    do {
        option = menuRead(MSG_MAIN_MENU, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                clientMenu(*(&customer), *(&product), *(&order));
                break;
            case 2:
                adminMenu(*(&customer), *(&order), *(&product), *(&material));
                break;
            case 3:
                importMenu(*(&customer), *(&order), *(&product), *(&material));
                break;
            case 4:
                exportMenu(*(&customer), *(&order), *(&product), *(&material));
                break;
        }
    } while (option != 0);
}
