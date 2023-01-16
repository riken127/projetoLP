//
// Created by r1ken on 16-01-2023.
//

#ifndef PROJECT_MENUS_H
#define PROJECT_MENUS_H

#include "clients.h"
#include "orders.h"
#include "products.h"
#include "production.h"

void adminMenu(Customers *customer, Orders **order, Products **product, Materials **material);
void clientMenu(Customers *customer, Products **product, Orders **order);
void mainMenu(Customers *customer, Products **product, Orders **order, Materials **material);

#endif //PROJECT_MENUS_H
