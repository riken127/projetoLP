//created by r1ken
#include "orders.h"
#include "menus.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int verifyExistenceOfClientesAndProducts(Customers *customer, Products *product) {
    if (customer->counter != 0) {
        if (product->counter != 0) {
            return 1;
        } else {
            printf("\n\t\t\tNo products were found");
            pressAnyKeyToContinueFunction();
        }
    } else {
        printf("\n\t\t\tNo clients were found");
        pressAnyKeyToContinueFunction();
    }
    return 0;
}

/*
 * Bellow function greets a customer, it receives the customer struct as a parameter
 * and the nif written by the user, and then greets the user by his name.
 */
void greetCustomer(Customers *customer, int nif) {
    int i;
    for (i = 0; i < customer->counter; i++) {
        if (customer->customers[i].nif == nif) {
            printf("\n\t\t\tWelcome back, %s!\n\t\t\t__________________________________", customer->customers[i].name);
        }
    }
}

/*
 * Bellow function lists all the available products.
 */
void listAvailableProducts(Products * product) {
    int i;
    printf("\n\n\t\t\tList Of Products\n\t\t\t__________________________________");
    for (i = 0; i < product->counter; i++) {
        printf("\n\n\t\t\tProduct Id      : %s", product->product[i].cod_Produto);
        printf("\n\t\t\tName            : %s", product->product[i].name);
        printf("\n\t\t\tPrice           : %f", product->product[i].price);
        printf("\n\t\t\tDimensions      : %dx%dx%d", product->product[i].dimension.height, product->product[i].dimension.lenght, product->product[i].dimension.width);
        printf("\n\t\t\t__________________________________");
    }
}

/*
 * Bellow function returns a new order id.
 */
int newOrderId(Orders *order) {
    return (order->counter + 1);
}

/*
 * The bellow function verifies a product code, if the product code is found,
 * it returns 1, if not, it returns 0.
 */
int verifyChoosenProduct(char code[COD_PRODUCT_SIZE], Products * product) {
    int i;
    for (i = 0; i < product->counter; i++) {
        if (strcmp(product->product[i].cod_Produto, code) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * The bellow function returns a product code, it loops until the product code  is available
 */
void newOrderChoosenProductCode(Products *product, char code[]) {
    do {
        printf("\n"ASK_PRODUCT_CODE);
        scanf("%s", code);
    } while (!verifyChoosenProduct(code, product));
}

/*
 * The bellow function returns an order date, it loops tru the basic date requirements until the
 * requirements are met, then it returns the date struct.
 */
Date newOrderChoosenDate() {
    Date orderDate;
    do {
        printf(ASK_ORDER_DATE);
        scanf("%d-%d-%d", &orderDate.day, &orderDate.month, &orderDate.year);
    } while (orderDate.day < MIN_DAY || orderDate.day > MAX_DAY ||
            orderDate.month < MIN_MONTH || orderDate.month > MAX_MONTH ||
            orderDate.year < MIN_YEAR);
    system("cls || clear");
    return orderDate;
}

/*
 * The bellow function returns an order quantity, it asks the user for the desired quantity
 * until the value is between the quantity requirements (zero for minimum and ten thousand for maximum).
 */
int newOrderQuantity() {
    int quantity;
    do {
        printf(ASK_ORDER_QUANTITY);
        scanf(" %d", &quantity);
    } while (quantity < MIN_ORDER_QUANTITY || quantity > MAX_ORDER_QUANTITY);

    return quantity;
}

/*
 * The bellow function is responsible for the creation of a new order, it receives the customer struct,
 * the nif, the product struct and the order struct. This function reallocates memory everytime a new product
 * is added to the order, the line_product struct records the product code and the product quantity.
 */
int newOrder(Customers *customer, int nif, Products *product, Orders * order) {
    int option, j;
    order->order = realloc(order->order, sizeof (Order)*(customer->counter + 1));
    listAvailableProducts(*(&product));
    order->order[order->counter].order_id = newOrderId(order);
    order->order[order->counter].nif = nif;
    j = 0;
    order->order[order->counter].line_order_size = 0;
    order->order[order->counter].line_order = (OrderLine *)malloc(sizeof(OrderLine) * 1);
    do {
        order->order[order->counter].line_order = (OrderLine *) realloc(order->order[order->counter].line_order,
                sizeof(OrderLine) * (j + 1));
        order->order[order->counter].line_order_size += 1;
        newOrderChoosenProductCode(product, order->order[order->counter].line_order[j].code);
        order->order[order->counter].line_order[j].quantity = newOrderQuantity();
        printf("\t\t\t__________________________________");
        option = yesOrNoFunction(ASK_ANOTHER_PRODUCT);
        printf("\t\t\t__________________________________\n");
        j++;
    } while (option != 2);
    order->order[order->counter].order_date = newOrderChoosenDate();
    ++order->counter;
    return 1;
}

/*
 * The bellow function verifies a customer nif, the function loops tru the struct trying to find the nif,
 * if found it returns one, if not it returns zero.
 */
int verifyCustomerNif(Customers *customers, int customerNif) {
    int i;
    if (customerNif == 0) {
        return 1;
    } else {

        for (i = 0; i < customers->counter; i++) {
            if (customerNif == customers->customers[i].nif) {
                return 1;
            }
        }
        errorMessage(MSG_ERROR_MESSAGE);

    }
    return 0;
}

/*
 * The bellow function asks for the customer nif while the written nif doesn't exist, then, the customer
 * is greeted, and goes to the newOrder function where all the order information will be filled by the user.
 */
void doOrder(Customers *customer, Products *product, Orders *order) {
    int customerNif, verify;
    verify = verifyExistenceOfClientesAndProducts(*(&customer), *(&product));
    if (verify == 1) {
        do {
            customerNif = menuRead(ASK_CUSTOMER_NIF, NIF_MIN_SIZE, NIF_MAX_SIZE);
        } while (!verifyCustomerNif(*(&customer), customerNif));
        if (customerNif != 0) {
            greetCustomer(*(&customer), customerNif);
            newOrder(*(&customer), customerNif, product, order);
        }
    }
}

/*
 * The bellow function lists all the orders' information.
 */
void listOrders(Orders *order) {
    int i, j;
    if (order->counter != 0) {
        printf("\n\n\t\t\tList Of Orders\n\t\t\t__________________________________");
        for (i = 0; i < order->counter; i++) {
            printf("\n\n\t\t\tOrder Id             : %d", order->order[i].order_id);
            printf("\n\t\t\tClient Nif           : %d", order->order[i].nif);
            printf("\n\t\t\tDate                 : %d-%d-%d", order->order[i].order_date.day, order->order[i].order_date.month, order->order[i].order_date.year);
            printf("\n\t\t\t__________________________________\n");
            for (j = 0; j < order->order[i].line_order_size; j++) {
                printf("\n\t\t\tProduct Id - %s\n\t\t\tQuantity - %d\n", order->order[i].line_order[j].code, order->order[i].line_order[j].quantity);
            }
            printf("\t\t\t__________________________________");
        }
        pressAnyKeyToContinueFunctionListVersion();
    } else {
        printf("\n\t\t\tNo orders were found");
        pressAnyKeyToContinueFunctionListVersion();
    }
}

/*
 * Bellow function asks for a product's name.
 */
void askFileName(char fileName[MAX_FN_CHARS]) {
    printf(ASK_FILE_NAME);
    scanf("%s", fileName);
}

/*
 * The bellow function exports the orders' struct, it starts by asking for file name, and then the
 * process goes in the following way:
 *      ->writes order size.
 *          ->loops tru the order_size recording all the products' information.
 *              ->writes line_order_size
 *                      ->loop tru a certain product line_order recording all of its information.
 *      ->closes file pointer.
 *      ->success message.
 */
void exportOrders(Orders *order) {
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "wb+");
    if (fp == NULL) {
        printf(ERROR_IN_FILES);
        pressAnyKeyToContinueFunction();
    } else {
        fwrite(&order->counter, sizeof (int), 1, fp);
        for (i = 0; i < order->counter; i++) {
            fwrite(&order->order[i].nif, sizeof (int), 1, fp);
            fwrite(&order->order[i].order_date.day, sizeof (int), 1, fp);
            fwrite(&order->order[i].order_date.month, sizeof (int), 1, fp);
            fwrite(&order->order[i].order_date.year, sizeof (int), 1, fp);
            fwrite(&order->order[i].line_order_size, sizeof (int), 1, fp);
            for (j = 0; j < order->order[i].line_order_size; j++) {
                fwrite(&order->order[i].line_order[j].code, sizeof (char)*COD_PRODUCT_SIZE, 1, fp);
                fwrite(&order->order[i].line_order[j].quantity, sizeof (int), 1, fp);
            }
        }
        fclose(fp);
        printf(SUCCESS_IN_FILES);
        pressAnyKeyToContinueFunction();
    }
}

/*
 * The bellow function imports order data, the importing process goes in the following way:
 *      ->asks for the desired file name.
 *      ->reads the sizeof the orders.
 *          ->loops tru the size of the orders reading the orders.
 *              ->reads a certain order line_order_size
 *                  ->loop tru the size of the line_order_size reading the product codes and the quantity's.
 *      ->order counter + 1.
 *      closes file pointer.
 */
void importOrders(Orders *order) {
    FILE *fp;
    int i, c, j;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "rb+");
    if (fp == NULL) {
        printf(ERROR_IN_FILES);
        pressAnyKeyToContinueFunction();
    } else {
        fread(&c, sizeof (int), 1, fp);
        for (i = 0; i < c; i++) {
            order->order = realloc(order->order,
                                   sizeof (Order) * (order->counter + 1));
            order->order[i].order_id = (order->counter + 1);
            fread(&order->order[i].nif, sizeof (int), 1, fp);
            fread(&order->order[i].order_date.day, sizeof (int), 1, fp);
            fread(&order->order[i].order_date.month, sizeof (int), 1, fp);
            fread(&order->order[i].order_date.year, sizeof (int), 1, fp);
            fread(&order->order[i].line_order_size, sizeof (int), 1, fp);
            order->order[i].line_order = malloc(1 * sizeof (OrderLine));
            for (j = 0; j < order->order[i].line_order_size; j++) {
                order->order[i].line_order = realloc(order->order[i].line_order,
                        sizeof(OrderLine)*(j + 1));
                fread(&order->order[i].line_order[j].code, sizeof (char)*COD_PRODUCT_SIZE, 1, fp);
                fread(&order->order[i].line_order[j].quantity, sizeof (int), 1, fp);
            }
            order->counter++;
        }
        fclose(fp);
        printf(SUCCESS_IN_FILES);
        pressAnyKeyToContinueFunction();
    }
}
