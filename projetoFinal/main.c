// Macro and Library definition
#include "clients.h"
#include "orders.h"
#include "production.h"
#include "products.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_MAIN_MENU "\n\t\t\t========= Main Menu =========\n\n\t\t\t[1] - User.\n\t\t\t[2] - Admin.\n\t\t\t[0] - Quit.\n\t\t\t_____________________________"
#define MSG_ADMIN_MENU                                                         \
  "\n\t\t\t========= Admin Menu =========\n\n\t\t\t[1] - Clients Management.\n\t\t\t[2] - Products Management.\n\t\t\t[3] - Production "   \
  "Management.\n\t\t\t[0] - Quit.\n\t\t\t______________________________"
#define MSG_CLIENT_MENU                                                        \
  "\n\t\t\t========= Client Menu =========\n\n\t\t\t[1] - Do order.\n\t\t\t[2] - Save orders.\n\t\t\t[3] - List orders.\n\t\t\t[4] - Load orders.\n\t\t\t[0] - Quit.\n\t\t\t_______________________________"


void adminMenu(Customers *customer, Orders **order, Products **product) {
    int option;

    do {
        option = menuRead(MSG_ADMIN_MENU, 0, 3);

        switch (option) {
            case 0:
                break;
            case 1:
                customerManagementMenu(*(&customer)) /*curentID*/;
                break;
            case 2:
                productsManagementMenu(*product);
                break;
            case 3:
                productionManagementMenu(product, order);
                break;
        }
    } while (option != 0);
}
/*
 * This menu is divided into three sub-menus, it loops until the integer
 * [option] given by the user is equal to zero.
 */
void clientMenu(Customers *customer, Products **product, Orders **order) {
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
                saveOrders(*order);
                break;
            case 3:
                listOrders(*order);
                break;
            case 4:
                loadOrders(*order);
                break;
        }
    } while (option != 0);
}
void mainMenu(Customers *customer, Products **product,
              Orders **order) {
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
                adminMenu(*(&customer),*(&order), *(&product));
                break;
        }
    } while (option != 0);
}
/*
 * This is the main menu, it's divided in two sides, the customer side, and the
 * admin side, it loops until the integer [option] given by the user is equal to
 * zero.
 */
int main(int argc, char **argv) {
    int curentID = 0;
    Customers customer[MAX_CLIENTS];
    customer->counter = 0;
    Products *product;
    product = (Products *)malloc(1 * sizeof(Products));
    product->product = (Product *)malloc(3 * sizeof(Product));
    Orders *order;
    order = (Orders *)malloc(1 * sizeof(Orders));
    order->order = (Order *)malloc(2 * sizeof(Order));
    order->counter = 0;
    mainMenu(customer, &product, &order);

    return (EXIT_SUCCESS);
}

/*
 * This is the main function, this is all the structs are instantiated, here the
 * main menu is invoked.
 */