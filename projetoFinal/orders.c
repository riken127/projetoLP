//created by r1ken
#include "orders.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void greetCustomer(Customers *customer, int nif) {
    int i;
    for (i = 0; i < customer->counter; i++) {
        if (customer[i].customers->nif == nif) {
            printf("\nWelcome back,\n\t\t%s!", customer[i].customers->name);
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
    //printf("%d", order->order[order->counter].order_id);
    order->order[order->counter].customer_id = newOrderCustomerId(customer, nif);
    //printf("%d", order->order[order->counter].customer_id);
    order->order[order->counter].product_id = newOrderChoosenProduct(product);
    //printf("%d", order->order[order->counter].product_id);
    order->order[order->counter].order_date = newOrderChoosenDate();

    order->order[order->counter].quantity = newOrderQuantity();
    ++order->counter;
    // printf("%d", order->counter);
    return 1;
}
int getCustomerId(int nif, Customers *customer) {
    int i;
    for (i = 0; i < customer->counter; i++) {
        if (customer->customers[i].nif == nif)
            return customer->customers[i].id;
    }
    printf("\nTyped NIF was not found, please try again.\n");
    return 0;
}
void doOrder(Customers *customer, Products *product, Orders *order) {
    int customerNif, customerId;
    do {
        customerNif = menuRead(ASK_CUSTOMER_NIF, NIF_MIN_SIZE, NIF_MAX_SIZE);
        customerId = getCustomerId(customerNif, *(&customer));
    } while (verifyCustomersId(*(&customer), customerId) != 1);
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
        fprintf(fp,"%d,%d,%d,%d-%d-%d,%d\n",
                order->order[i].order_id, order->order[i].customer_id,
                order->order[i].product_id, order->order[i].order_date.day,
                order->order[i].order_date.month, order->order[i].order_date.year,
                order->order[i].quantity);
    }
    fclose(fp);
    printf(SUCCESS_IN_WRITING_ORDERS);

}

void loadOrders(Orders *order){
/*  FILE *fp;
  int i;
  char fn[MAX_FN_CHARS];
  askFileName(fn);
  fp = fopen(fn, "r");
  if (!fp){
    printf(ERROR_IN_LOADING_ORDERS);
    exit(EXIT_FAILURE);
  }
  char buff[1024];
  int row_count = 0;
  int field_count = 0;

  i = 0;
  while(fgets(buff, 1024, fp)){
    //printf("%s\n", buff);
    field_count = 0;
    row_count++;
    if (row_count == 1){
      continue;
    }
    char *field = strtok(buff, ",");
    while(field){
      if (field_count == 0)
        strcpy(order->order[i].customer_id, field);
      if (field_count == 1)
        strcpy(order->order[i].order_date.day, field);
        strcpy(order->order[i].order_date.month, field);
        strcpy(order->order[i].order_date.year, field);
      if (field_count == 2)
        strcpy(order->order[i].product_id, field);
      if (field_count == 3)
        strcpy(order->order[i].quantity, field);

      field = strtok(NULL, ",");
      field_count++;
    }
    i++;
  }
  fclose(fp);

  */
}