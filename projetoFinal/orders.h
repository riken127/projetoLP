/**
 * 
 * @file orders.h
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Header orders
 * 
 * Header file with all the funcitons about orders.
 * Also has some macros that are used in those functions.
 */

#include "general.h"
//created by r1ken
#ifndef PROJETO_ORDERS_H
#define PROJETO_ORDERS_H


//macro definition
#define ASK_ORDER_DATE "\n\t\t\tPlease type the desired date - "

#define ASK_ORDER_QUANTITY "\n\t\t\tPlease type the desired quantity - "


#define MIN_ORDER_QUANTITY 0

#define MAX_ORDER_QUANTITY 10000

#define NIF_MAX_SIZE 999999999

#define NIF_MIN_SIZE 000000000

#define ASK_FILE_NAME "\n\t\t\tPlease type the desired file name - "

#define MAX_FN_CHARS 100

#define ASK_CUSTOMER_NIF "\n\t\t\tPlease type your nif"

#define NIF_ERROR_MSG "Typed nif does not exist!"

#define SUCCESS_IN_WRITING_ORDERS "\n\t\t\tOrders where written successfully!"

#define ERROR_IN_WRITING_ORDERS "\nAn error has occured while writing the orders! :/"

#define SUCCESS_IN_LOADING_ORDERS "\nOrders where loaded successfully!"

#define ERROR_IN_LOADING_ORDERS "\nAn error has occures while loading the orders! :/"

#define ASK_ANOTHER_PRODUCT "\n\t\t\tDo you want to add another product?[y/n] - "


//function definition
int verifyExistenceOfClientesAndProducts(Customers *customer, Products *product);
int verifyCustomerOrders(int nif, Orders *orders);
void greetCustomer(Customers *customer, int nif);
void listAvailableProducts(Products *product);
int newOrderId(Orders *order);
int newOrderCustomerId(Customers *customer, int nif);
void newOrderChoosenProductCode(Products *product, char code[COD_PRODUCT_SIZE]);
Date newOrderChoosenDate();
int newOrderQuantity();
int newOrder(Customers *customer, int nif, Products *product, Orders *order);
int getCustomerId(int nif, Customers *customer);
void doOrder(Customers *customer, Products *product, Orders *order);
void listOrders(Orders *order);
void askFileName(char fileName[MAX_FN_CHARS]);
void exportOrders(Orders *order);
void importOrders(Orders *order);
#endif