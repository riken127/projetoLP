//
// Created by r1ken on 12-12-2022.
//

#ifndef PROJECT_PRODUCTION_H
#define PROJECT_PRODUCTION_H

#include "production.h"
#include "orders.h"
#include "products.h"

#define MSG_MENU_PRODUCTION "\n[1] - List.\n[2] - Save.\n[3] - Load.\n"

#define ASK_DESIRED_DATE "\nPlease type the desired date: (xx-xx-xxxx)\n"

#define SUCCESS_IN_WRITING_PRODUCTION "\nProduction file was written successfully!\n"

Date askDate();
void dateMaterials(Products *product, Orders *order);
void saveDateMaterials(Products *product, Orders *order);
void loadDateMaterials();
void productionManagementMenu(Products **Product, Orders **order);

#endif //PROJECT_PRODUCTION_H