//created by r1ken
#include "orders.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void greetCustomer(Customers *customer, int nif) {
    printf("%p", customer);
    int i;
    for (i = 0; i < customer->counter; i++) {
        if (customer->customers[i].nif == nif) {
            printf("\nWelcome back,\n\t\t%s!", customer->customers[i].name);
        }
    }
}

void listAvaibleProducts(Products *product) {
    int i;
    for (i = 0; i < product->counter; i++) {
        printf("\n[%d] - | %s | %s | %.2lf | %dx%dx%d |\n", (i + 1),
               product->product[i].cod_Produto, product->product[i].name,
               product->product[i].price, product->product[i].dimension.lenght,
               product->product[i].dimension.width,
               product->product[i].dimension.height);
    }
}
int newOrderId(Orders *order) {
    return (order->counter + 1);
}
int newOrderCustomerId(Customers *customer, int nif) {
    int i;
    for (i = 0; i < customer->counter; i++) {
        if (customer->customers[i].nif == nif) {
            return customer->customers[i].id;
        }
    }
}
int verifyChoosenProduct(char code[COD_PRODUCT_SIZE], Products *product){
    int i;
    for (i = 0; i < product->counter; i++){
        if(strcmp(product->product[i].cod_Produto, code) == 0){
            return 1;
        }
    }
    return 0;
}
void newOrderChoosenProductCode(Products *product, char code[]) {
    do {
        printf(ASK_PRODUCT_CODE);
        scanf("%s", code);
    } while (!verifyChoosenProduct(code, product));
}
Date newOrderChoosenDate() {
    Date orderDate;
    do {
        printf(ASK_ORDER_DATE);
        scanf("%d-%d-%d", &orderDate.day, &orderDate.month, &orderDate.year);
    } while (orderDate.day < MIN_DAY || orderDate.day > MAX_DAY ||
             orderDate.month < MIN_MONTH || orderDate.month > MAX_MONTH ||
             orderDate.year < MIN_YEAR);
    return orderDate;
}
int newOrderQuantity() {
    int quantity;
    do {
        printf(ASK_ORDER_QUANTITY);
        scanf(" %d", &quantity);
    } while (quantity < MIN_ORDER_QUANTITY || quantity > MAX_ORDER_QUANTITY);

    return quantity;
}

int newOrder(Customers *customer, int nif, Products *product, Orders *order) {
    int option, j;
    order->order = realloc(order->order, sizeof(Order)*(customer->counter + 1));
    listAvaibleProducts(*(&product));
    order->order[order->counter].order_id = newOrderId(order);
    order->order[order->counter].nif = newOrderCustomerId(customer, nif);
    order->order[order->counter].order_date = newOrderChoosenDate();
    j = 0;
    do{
        order->order[order->counter].line_order = (OrderLine *)realloc(order->order[order->counter].line_order,
                                                                       sizeof(OrderLine) * (j + 1));
        order->order[order->counter].line_order_size += 1;
        newOrderChoosenProductCode(product, order->order[order->counter].line_order[j].code);
        order->order[order->counter].line_order[j].quantity = newOrderQuantity();
        printf(ASK_ANOTHER_PRODUCT);
        scanf(" %d", &option);
        j++;
    }while(option != 0);
    ++order->counter;
    return 1;
}
int verifyCustomerNif(Customers *customers, int customerNif){
    int i;
    for (i = 0; i < customers->counter; i++){
        if (customerNif == customers->customers[i].nif){
            return 1;
        }
    }
    return 0;
}
void doOrder(Customers *customer, Products *product, Orders *order) {
    int customerNif;
    do {
        customerNif = menuRead(ASK_CUSTOMER_NIF, NIF_MIN_SIZE, NIF_MAX_SIZE);
    } while (!verifyCustomerNif(*(&customer), customerNif));
    greetCustomer(*(&customer), customerNif);
    newOrder(*(&customer), customerNif, product, order);
}

void listOrders(Orders *order) {
    int i, j;
    for (i = 0; i < order->counter; i++) {
        printf("\n%dº - | %d | %d-%d-%d |\n",
               order->order[i].order_id, order->order[i].nif,
               order->order[i].order_date.day,
               order->order[i].order_date.month, order->order[i].order_date.year);
            for (j = 0; j < order->order[i].line_order_size; j++){
                printf("\t%s - %d\n",
                                   order->order[i].line_order[j].code,
                                   order->order[i].line_order[j].quantity);
            }
    }
}

void askFileName(char fileName[MAX_FN_CHARS]){
    printf(ASK_FILE_NAME);
    scanf("%s", fileName);
}

void exportOrders(Orders *order) {
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "wb+");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    fwrite(&order->counter, sizeof(int), 1, fp);
    for (i = 0; i < order->counter; i++){
        fwrite(&order->order[i].nif, sizeof(int), 1, fp);
        fwrite(&order->order[i].order_date.day, sizeof(int), 1, fp);
        fwrite(&order->order[i].order_date.month, sizeof(int), 1, fp);
        fwrite(&order->order[i].order_date.year, sizeof(int), 1, fp);
        fwrite(&order->order[i].line_order_size, sizeof(int), 1, fp);
        for (j = 0; j < order->order[i].line_order_size; j++){
            fwrite(&order->order[i].line_order[j].code, sizeof(char)*COD_MATERIAL_SIZE, 1, fp);
            fwrite(&order->order[i].line_order[j].quantity, sizeof(int), 1, fp);
        }
    }
    fclose(fp);
    printf(SUCCESS_IN_WRITING_ORDERS);
}

void importOrders(Orders *order) {
    FILE *fp;
    int i, c, j;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "rb+");
    fread(&c, sizeof(int), 1, fp);
    for (i = 0; i < c; i++){
        order->order = realloc(order->order, sizeof(Order)*(order->counter + 1));
        order->order[i].order_id = (order->counter + 1);
        fread(&order->order[i].nif, sizeof(int), 1, fp);
        fread(&order->order[i].order_date.day, sizeof(int), 1, fp);
        fread(&order->order[i].order_date.month, sizeof(int), 1, fp);
        fread(&order->order[i].order_date.year, sizeof(int), 1, fp);
        fread(&order->order[i].line_order_size, sizeof(int), 1, fp);
        order->order[i].line_order = malloc(1 * sizeof(OrderLine));
        for (j = 0; j < order->order[i].line_order_size; j++){
            order->order[i].line_order = realloc(order->order[i].line_order,
                                                 sizeof(OrderLine)*(j + 1));
            fread(&order->order[i].line_order[j].code, sizeof(char)*COD_MATERIAL_SIZE, 1, fp);
            fread(&order->order[i].line_order[j].quantity, sizeof(int), 1, fp);
        }
        order->counter++;
    }
    fclose(fp);
}
*/