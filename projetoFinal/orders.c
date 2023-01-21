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
    order->order = realloc(order->order, sizeof (Order)*(order->counter + 1));
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
int verifyOrderId(Orders *order, int id){
    int i;
    for (i = 0; i < order->counter; i++){
        if (order->order[i].order_id == id){
            return 1;
        }
    }
    return 0;
}
int verifyProductOrderLine(LineProduct product, Order order){
    int i;
    for (i = 0; i < order.line_order_size; i++){
        if (strcmp(product.code, order.line_order[i].code) == 0){
            return i;
        }
    }
    return -1;
}
void changeOrderDate(Date *order_date){
    do{
        printf(ASK_ORDER_DATE);
        scanf("%d-%d-%d", &order_date->day, &order_date->month, &order_date->year);
    }while(order_date->day < MIN_DAY || order_date->day > MAX_DAY ||
            order_date->month < MIN_MONTH || order_date->month > MAX_MONTH ||
            order_date->year < MIN_YEAR);
    system("cls || clear");
}
void editLineProduct(Order *order){
    int i, position;
    LineProduct product;
    int option;
    do {
        for (i = 0; i < order->line_order_size; i++) {
            printf("\n\t\t\tProduct Code: %s\n\t\t\tProduct Quantity: %d\n", order->line_order[i].code,
                   order->line_order[i].quantity);
        }
        printf(ASK_PRODUCT_CODE);
        scanf("%s", product.code);
        position = verifyProductOrderLine(product, *order);
        if (position != -1){
            do {
                printf(ASK_ORDER_QUANTITY);
                scanf("%hd", &product.quantity);
            }while(product.quantity < MIN_ORDER_QUANTITY &&
                   product.quantity > MAX_ORDER_QUANTITY);
            order->line_order[position].quantity = product.quantity;
            option = yesOrNoFunction(ASK_EDIT_ORDER);
            if (option == 2){
                break;
            }
        }else{
            errorMessage(MSG_ERROR_MESSAGE);
        }
    }while (position != -1);

}
void removeLineProduct(Order *order){
    int i, position;
    LineProduct product;
    int option;
    do{
        for (i = 0; i < order->line_order_size; i++) {
            printf("\n\t\t\tProduct Code: %s\n\t\t\tProduct Quantity: %d\n", order->line_order[i].code,
                   order->line_order[i].quantity);
        }
        printf(ASK_PRODUCT_CODE);
        scanf("%s", product.code);
        position = verifyProductOrderLine(product, *order);
        if (position != -1){
            for (i = 0; i < order->line_order_size; i++){
                if (strcmp(order->line_order[i].code, product.code) == 0){
                    strcpy(order->line_order[i].code,order->line_order[i + 1].code);
                }
            }
            --order->line_order_size;
            option = yesOrNoFunction(ASK_DELETE_PRODUCT_LINE_PRODUCT);
            if (option == 2){
                break;
            }
        }else{
            errorMessage(MSG_ERROR_MESSAGE);
        }
    }while(position != -1);
}

void addLineProduct(Order *order, Products *products){
    int i, product_quantity;
    char product_code[COD_PRODUCT_SIZE];
    int option;
    do{
        for (i = 0; i < order->line_order_size; i++){
            printf("\n\t\t\tProduct Code: %s\n\t\t\tProduct Quantity: %d\n", order->line_order[i].code,
                   order->line_order[i].quantity);
        }
            do{
                newOrderChoosenProductCode(products, product_code);
                do{
                    printf(ASK_ORDER_QUANTITY);
                    scanf("%d", &product_quantity);
                }while(product_quantity < 0);
                order->line_order = (OrderLine *)realloc(order->line_order,
                                                         sizeof(OrderLine) * (order->line_order_size + 1));
                strcpy(order->line_order[order->line_order_size].code, product_code);
                order->line_order[order->line_order_size].quantity = product_quantity;
                order->line_order_size++;
                option = yesOrNoFunction(ASK_ADD_PRODUCT_LINE_PRODUCT);
            }while(option != 2);
    }while(option != 2);
}

void changeOrderLine(Order *order, Products *products){
    int option, i;
    do{
        option = menuRead(MSG_CHANGE_ORDER_LINE, 0, 3);
        switch (option) {
            case 0:
                break;
            case 1:
                editLineProduct(order);
                break;
            case 2:
                removeLineProduct(order);
                break;
            case 3:
                addLineProduct(order, products);
                break;
        }
    }while(option != 0);
}

void saveLineOrderChanges(Orders *order, int position, Order temp){
    int i;
    order->order[position].order_date = temp.order_date;
    order->order[position].line_order_size = temp.line_order_size;
    order->order[position].line_order = realloc(order->order[position].line_order,
                                                sizeof(Orders) * order->order[position].line_order_size);
    for (i = 0; i < order->order[position].line_order_size; i++){
        strcpy(order->order[position].line_order[i].code, temp.line_order[i].code);
        order->order[position].line_order[i].quantity = temp.line_order[i].quantity;
    }
}

void changeOrderData(Orders *order, int position, int id, Products *products){
    int option, i;
    Order temp;
    temp.order_date = order->order[position].order_date;
    temp.order_id = order->order[position].order_id;
    temp.nif = order->order[position].nif;
    temp.line_order_size = order->order[position].line_order_size;
    temp.line_order = (OrderLine *)malloc(sizeof(OrderLine) * temp.line_order_size);
    for (i = 0; i < temp.line_order_size; i++){
        strcpy(temp.line_order[i].code, order->order[position].line_order[i].code);
        temp.line_order[i].quantity =  order->order[position].line_order[i].quantity;
    }
    do{
        option = menuRead(MSG_CHANGE_ORDER_DATA, 0, 2);
        switch (option) {
            case 1:
                changeOrderDate(&temp.order_date);
                break;
            case 2:
                changeOrderLine(&temp, products);
                break;
        }
    }while(option != 0);
    saveLineOrderChanges(order, position, temp);
}

void editOrders(Orders *order, Products *products){
    int id, i, verify;
    system("cls || clear");
    listOrders(order);
    do{
        printf(ASK_ORDER_ID);
        scanf("%d", &id);
        system("cls || clear");
        if (id == 0)
            break;
        verify = verifyOrderId(order, id);
        if (verify == 1){
            for (i = 0; i < order->counter; i++) {
                if (order->order[i].order_id == id){
                    changeOrderData(order, i, id, products);
                }
            }
        } else
            errorMessage(MSG_ERROR_MESSAGE);
    }while(verify != 1);
}

void removeOrder(Orders *orders, int id){
    int i, j;
    for (i = 0; i < orders->counter; i++){
        if (orders->order[i].order_id == id){
            orders->order[i].order_id = orders->order[i + 1].order_id;
            orders->order[i].nif = orders->order[i + 1].nif;
            orders->order[i].order_date.day = orders->order[i + 1].order_date.day;
            orders->order[i].order_date.month = orders->order[i + 1].order_date.month;
            orders->order[i].order_date.year = orders->order[i + 1].order_date.year;
            orders->order[i].line_order_size = orders->order[i + 1].line_order_size;
            orders->order[i].line_order = (OrderLine *) realloc(orders->order[i].line_order,
                                                                sizeof(OrderLine)*orders->order[i + 1].line_order_size);
            for (j = 0; j < orders->order[i + 1].line_order_size; j++){
                strcpy(orders->order[i].line_order[j].code,
                       orders->order[i + 1].line_order[j].code);
                orders->order[i].line_order[j].quantity =
                        orders->order[i + 1].line_order[j].quantity;
            }
        }
    }
    --orders->counter;
}

void removeOrders(Orders *order){
    int id, verify;
    system("cls || clear");
    listOrders(order);
    do{
        printf(ASK_ORDER_ID);
        scanf(" %d", &id);
        system("cls || clear");
        if (id == 0)
            break;
        verify = verifyOrderId(order, id);
        if (verify == 1){
            removeOrder(order, id);
        } else
            errorMessage(MSG_ERROR_MESSAGE);
    } while (verify != 1);
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
