//
// Created by r1ken on 16-01-2023.
//

#include "menus.h"

//macro definition
#define MSG_MAIN_MENU "\n\t\t\t========= Main Menu =========\n\n\t\t\t[1] - User.\n\t\t\t[2] - Admin.\n\t\t\t[0] - Quit.\n\t\t\t_____________________________"
#define MSG_ADMIN_MENU                                                         \
  "\n\t\t\t=============== Admin Menu ===============\n\n\t\t\t[1] - Clients Management.\n\t\t\t[2] - Products & Materials Management.\n\t\t\t[3] - Production "   \
  "Management.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________________"
#define MSG_CLIENT_MENU                                                        \
  "\n\t\t\t========= Client Menu =========\n\n\t\t\t[1] - Do order.\n\t\t\t[2] - List orders.\n\t\t\t[3] - Export orders.\n\t\t\t[4] - Import orders.\n\t\t\t[0] - Quit.\n\t\t\t_______________________________"

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
                customerManagementMenu(customer);
                break;
            case 2:
                ProductsMaterialsManagementMenu(*product, *material);
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
            case 3:
                exportOrders(*order);
                break;
            case 4:
                importOrders(*order);
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
        option = menuRead(MSG_MAIN_MENU, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:
                clientMenu(*(&customer), *(&product), *(&order));
                break;
            case 2:
                adminMenu(*(&customer),*(&order), *(&product), *(&material));
                break;
        }
    } while (option != 0);
}
