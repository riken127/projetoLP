/**
 * 
 * @file production.h
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Header production
 * 
 * Header file with all the functions about productions.
 */

#include "general.h"
#ifndef PROJECT_PRODUCTION_H
#define PROJECT_PRODUCTION_H
//macro  definition
#define MSG_MENU_PRODUCTION "\n\t\t\t========= Production Management Menu =========\n\n\t\t\t[1] - List materials.\n\t\t\t[0] - Quit.\n\t\t\t______________________________________________"

#define MSG_LIST_MENU "\n\n\t\t\t[1] - Rank Clients.\n\t\t\t[2] - Rank Products.\n\t\t\t[3] - Rank Materials.\n\t\t\t[4] - List 4.\n\t\t\t[5] - List 5.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________"

#define MSG_EXPORT_RANKED_DATA "\n\n\t\t\t[1] - Export to file.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________"

#define ASK_DESIRED_DATE "\n\t\t\tPlease type the desired date (xx-xx-xxxx) - "

#define NO_ORDERS_FOUND_MESSAGE "\n\t\t\tNo orders were found\n\t\t\t__________________________________"

#define NO_ORDERS_FOUND_TO_THAT_DATE_MESSAGE "\n\t\t\tNo orders were found for that date\n\t\t\t__________________________________"

#define MAX_MATERIALS 9999
//function definition
Date askDate();
void listRankClients();
void exportRankedProducts();
void listRankProducts(Materials *material,Orders *order, Products *product, Date date);
void exportRankedMaterials(char cod[MAX_MATERIALS][COD_MATERIAL_SIZE], char description[MAX_MATERIALS][MAX_DESCRIPTION_SIZE], int unit[MAX_MATERIALS], int quantity[MAX_MATERIALS], int count);
void listRankMaterials(Materials *material, Orders *order, Products *product, Date date);
int sortOrder(Order *a, Order *b);
void listRankOrders(Orders *order);
int listMenu(Materials *material, Orders *order, Products *product, Date date);
void listMaterials(Materials *material, Orders *order, Products *product);
void productionManagementMenu(Orders **order, Materials **material, Products **product);
#endif //PROJECT_PRODUCTION_H