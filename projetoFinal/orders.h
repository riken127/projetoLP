//created by r1ken
#ifndef PROJETO_ORDERS_H
#define PROJETO_ORDERS_H

#include "clients.h"
#include "products.h"

#define ASK_PRODUCT_ID "\nPlease type the desired id:"
#define ASK_ORDER_DATE "Please type the desired date:"
#define ASK_ORDER_QUANTITY "Please type the desired quantity:"

#define MIN_DAY 0
#define MAX_DAY 31

#define MIN_MONTH 0
#define MAX_MONTH 12

#define MIN_YEAR 2022

#define MIN_ORDER_QUANTITY 0
#define MAX_ORDER_QUANTITY 10000

#define NIF_MAX_SIZE 999999999
#define NIF_MIN_SIZE 000000000

#define ASK_FILE_NAME "\n\t\t\tPlease type the desired file name - "
#define MAX_FN_CHARS 100

#define ASK_CUSTOMER_NIF "Please type your nif"
#define NIF_ERROR_MSG "Typed nif does not exist!"

#define SUCCESS_IN_WRITING_ORDERS "\nOrders where written successfully!"
#define ERROR_IN_WRITING_ORDERS "\nAn error has occured while writing the orders! :/"

#define SUCCESS_IN_LOADING_ORDERS "\nOrders where loaded successfully!"
#define ERROR_IN_LOADING_ORDERS "\nAn error has occures while loading the orders! :/"

typedef struct {
    int day, month, year;
} Date;

typedef struct{
    int product_id, quantity;
}LinhaEncomenda;

typedef struct {
    int order_id, customer_id;
    Date order_date;
    LinhaEncomenda *linha_encomenda;
} Order;

typedef struct {
    Order *order;
    int counter;
} Orders;

void greetCustomer(Customers *customer, int nif);
void listAvaibleProducts(Products *product);
int newOrderId(Orders *order);
int newOrderCustomerId(Customers *customer, int nif);
int newOrderChoosenProduct(Products *product);
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