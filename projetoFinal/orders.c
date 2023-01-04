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
        printf("\n[%d] - | %s | %s | %.2lf | %dx%dx%d |", (i + 1),
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
    return -1;
}
int newOrderChoosenProduct(Products *product) {
    int i, newId;
    do {
        printf(ASK_PRODUCT_ID);
        scanf(" %d", &newId);
    } while (newId < 0 || newId > (product->counter));
    return newId;
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
    int i, choosenProduct;
    order->order = realloc(order->order, sizeof(Order)*(customer->counter + 1));
    listAvaibleProducts(*(&product));
    order->order[order->counter].order_id = newOrderId(order);
    order->order[order->counter].customer_id = newOrderCustomerId(customer, nif);
    order->order[order->counter].product_id = newOrderChoosenProduct(product);
    order->order[order->counter].order_date = newOrderChoosenDate();
    order->order[order->counter].quantity = newOrderQuantity();
    ++order->counter;
    return 1;
}
int getCustomerId(int nif, Customers *customer) {
    int i;
    for (i = 0; i < customer->counter; i++) {
        if (customer->customers[i].nif == nif){
            return customer->customers[i].id;
        }
    }
    printf("\nTyped NIF was not found, please try again.\n");
    return 0;
}
void doOrder(Customers *customer, Products *product, Orders *order) {
    int customerNif, customerId;
    customerNif = menuRead(ASK_CUSTOMER_NIF, NIF_MIN_SIZE, NIF_MAX_SIZE);
    do {
        customerId = getCustomerId(customerNif, *(&customer));
    } while (!verifyCustomersId(*(&customer), customerId));
    greetCustomer(*(&customer), customerNif);
    newOrder(*(&customer), customerNif, product, order);
}

void listOrders(Orders *order) {
    int i;
    for (i = 0; i < order->counter; i++) {
        printf("\n%dº - | %d | %d | %d-%d-%d | %d |",
               order->order[i].order_id, order->order[i].customer_id,
               order->order[i].product_id, order->order[i].order_date.day,
               order->order[i].order_date.month, order->order[i].order_date.year,
               order->order[i].quantity);
    }
}

void askFileName(char fileName[MAX_FN_CHARS]){
    printf(ASK_FILE_NAME);
    scanf("%s", fileName);
}

void saveOrders(Orders *order) {
    FILE *fp;
    int i;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "w+");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < order->counter; i++){
        fprintf(fp,"%d,%d,%d-%d-%d,%d\n",
                order->order[i].customer_id,
                order->order[i].product_id, order->order[i].order_date.day,
                order->order[i].order_date.month, order->order[i].order_date.year,
                order->order[i].quantity);
    }
    fclose(fp);
    printf(SUCCESS_IN_WRITING_ORDERS);

}

void loadOrders(Orders *order) {
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS], buff[1024], *sp;
    askFileName(fn);
    fp = fopen(fn, "r");
    while(fgets(buff, 1024, fp) != NULL) {
        order->order = (Order *) realloc(order->order, sizeof(Order) * (order->counter +  1));

        order->order[order->counter].order_id = (order->counter + 1);
        sp = strtok(buff, ",");
        order->order[order->counter].customer_id = atoi(sp);
        sp = strtok(NULL, ",");
        order->order[order->counter].product_id = atoi(sp);
        sp = strtok(NULL, "-");
        order->order[order->counter].order_date.day = atoi(sp);
        sp = strtok(NULL, "-");
        order->order[order->counter].order_date.month = atoi(sp);
        sp = strtok(NULL, ",");
        order->order[order->counter].order_date.year = atoi(sp);
        sp = strtok(NULL, ",");
        order->order[order->counter].quantity = atoi(sp);
        ++order->counter;
    }
    fclose(fp);
}
