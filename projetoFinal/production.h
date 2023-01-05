//
// Created by r1ken on 12-12-2022.
//

#ifndef PROJECT_PRODUCTION_H
#define PROJECT_PRODUCTION_H

#include "production.h"
#include "orders.h"
#include "products.h"
#include "clients.h"

#define MSG_MENU_PRODUCTION "\n\t\t\t========= Production Management Menu =========\n\n\t\t\t[1] - List materials.\n\t\t\t______________________________________________"

#define ASK_DESIRED_DATE "\nPlease type the desired date: (xx-xx-xxxx)\n"

#define SUCCESS_IN_WRITING_PRODUCTION "\nProduction file was written successfully!\n"

#define NO_ORDERS_FOUND_MESSAGE "\n\t\t\tNo orders were found\n\t\t\t__________________________________"


#define NO_ORDERS_FOUND_TO_THAT_DATE_MESSAGE "\n\t\t\tNo orders were found for that date\n\t\t\t__________________________________"

Date askDate();
void listMaterials(Products *product, Orders *order);
void saveDateMaterials(Products *product, Orders *order);
void productionManagementMenu(Products **Product, Orders **order);
void errorMessage(char message[]);
#endif //PROJECT_PRODUCTION_H