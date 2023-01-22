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

#define MSG_LIST_MENU "\n\n\t\t\t[1] - Rank Clients.\n\t\t\t[2] - Rank Products.\n\t\t\t[3] - Rank Materials.\n\t\t\t[4] - Rank by Date.\n\t\t\t[5] - Rank by Address.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________"

#define MSG_EXPORT_RANKED_DATA "\n\n\t\t\t[1] - Export to file.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________"

#define ASK_DESIRED_DATE "\n\t\t\tPlease type the desired date (xx-xx-xxxx) - "

#define NO_ORDERS_FOUND_MESSAGE "\n\t\t\tNo orders were found\n\t\t\t__________________________________"

#define NO_ORDERS_FOUND_TO_THAT_DATE_MESSAGE "\n\t\t\tNo orders were found for that date\n\t\t\t__________________________________"

#define MAX_MATERIALS 9999
#define MAX_PRODUCTS 9999
#define MAX_CLIENTS 9999
//function definition
Date askDate();
void exportRankedCustomers(Customers *customer, int counter, int nif[MAX_CLIENTS], int count[MAX_CLIENTS]);
void listRankCustomers(Orders *order,Date date, Customers *customer);
void exportRankedProducts(char cod[MAX_PRODUCTS][COD_PRODUCT_SIZE], char name[MAX_PRODUCTS][MAX_NAME_CHARS], double price[MAX_PRODUCTS], int height[MAX_PRODUCTS], int lenght[MAX_PRODUCTS], int width[MAX_PRODUCTS], int quantity[MAX_PRODUCTS], int count);
void listRankProducts(Orders *order, Products *product, Date date);
void exportRankedMaterials(char cod[MAX_MATERIALS][COD_MATERIAL_SIZE], char description[MAX_MATERIALS][MAX_DESCRIPTION_SIZE], int unit[MAX_MATERIALS], int quantity[MAX_MATERIALS], int count);
void listRankMaterials(Materials *material, Orders *order, Products *product, Date date);
int sortOrder(const void *aa, const void *bb);
void exportRankOrders();
void listRankOrders(Orders *order);
int sortCustomerPerAddress(const void *aa, const void *bb);
void exportRankedCustomersPerAddress(Customers *temp);
void listRankCustomersPerAddress(Customers *customers);
int listMenu(Materials *material, Orders *order, Products *product, Date date, Customers *customers);
void listMaterials(Materials *material, Orders *order, Products *product, Customers *customers);
void productionManagementMenu(Orders **order, Materials **material, Products **product, Customers *customers);
#endif //PROJECT_PRODUCTION_H