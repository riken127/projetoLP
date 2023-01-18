/**
 * 
 * @file production.h
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Biblioteca production
 * 
 *  Biblioteca com todas as funções sobre as produções.
 */

#include "orders.h"
#ifndef PROJECT_PRODUCTION_H
#define PROJECT_PRODUCTION_H
//macro  definition
#define MSG_MENU_PRODUCTION "\n\t\t\t========= Production Management Menu =========\n\n\t\t\t[1] - List materials.\n\t\t\t[0] - Quit.\n\t\t\t______________________________________________"

#define MSG_LIST_MENU "\n\n\t\t\t[1] - Rank Clients.\n\t\t\t[2] - Rank Products.\n\t\t\t[3] - Rank Materials.\n\t\t\t[4] - List 4.\n\t\t\t[5] - List 5.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________"

#define ASK_DESIRED_DATE "\n\t\t\tPlease type the desired date (xx-xx-xxxx) - "

#define NO_ORDERS_FOUND_MESSAGE "\n\t\t\tNo orders were found\n\t\t\t__________________________________"

#define NO_ORDERS_FOUND_TO_THAT_DATE_MESSAGE "\n\t\t\tNo orders were found for that date\n\t\t\t__________________________________"
//function definition
Date askDate();
void listRankClients();
void listRankProducts();
void listRankMaterials();
void list4();
void list5();
void listMenu(Materials *material, Orders *order, Products *product, Date *date);
void listMaterials(Materials *material, Orders *order, Products *product);
void productionManagementMenu(Orders **order, Materials **material, Products **product);
void errorMessage(char message[]);
#endif //PROJECT_PRODUCTION_H