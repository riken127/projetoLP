/**
 * 
 * @file menus.h
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Biblioteca menus
 * 
 *  Biblioteca com todas as funções sobre os Menus.
 */

#ifndef PROJECT_MENUS_H
#define PROJECT_MENUS_H

#include "general.h"


void adminMenu(Customers *customer, Orders **order, Products **product, Materials **material);
void clientMenu(Customers *customer, Products **product, Orders **order);
void importMenu(Customers *customer, Orders **order,
        Products **product, Materials **material);
void exportMenu(Customers *customer, Orders **order,
        Products **product, Materials **material);
void mainMenu(Customers *customer, Products **product, Orders **order, Materials **material);

#endif //PROJECT_MENUS_H
