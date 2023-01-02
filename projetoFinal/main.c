// Macro and Library definition
#include "clients.h"
#include "orders.h"
#include "production.h"
#include "products.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_MAIN_MENU "[1] - User.\n[2] - Admin."
#define MSG_ADMIN_MENU                                                         \
  "[1] - Clients Management.\n[2] - Products Management.\n[3] - Production "   \
  "Management."
#define MSG_CLIENT_MENU                                                        \
  "\n[1] - Do order.\n[2] - Save orders.\n[3] - List orders.\n[4] - Load orders.\n[0] - Quit.\n"

// teste

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
        printf("%d", option);
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
void mainMenu(Customers *customer, /*int curentID*/ Products **product,
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
                adminMenu(*(&customer), /*curentID*/*(&order), *(&product));
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
    mainMenu(customer, /*curentID*/ &product, &order);

    return (EXIT_SUCCESS);
}

/*
 * This is the main function, this is all the structs are instantiated, here the
 * main menu is invoked.
 */