/**
 * 
 * @file production.c
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Productions file
 * 
 * File containing all the funtions about the productions.
 */
#include "production.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/**
 * This function asks the user for a date and verifies if the date is valid, if so,
 * then the date is returned.
 */

Date askDate() {
    Date insertedDate;
    do {
        printf(ASK_DESIRED_DATE);
        scanf("%d-%d-%d",
                &insertedDate.day,
                &insertedDate.month,
                &insertedDate.year);
        system("cls || clear");
    } while (insertedDate.day < MIN_DAY || insertedDate.day > MAX_DAY ||
            insertedDate.month < MIN_MONTH || insertedDate.month > MAX_MONTH ||
            insertedDate.year < MIN_YEAR);

    return insertedDate;
}

/**
 * This function exports the customers by the amount of orders they have requested.
 * 
 * @param customer Pointer to the customers struct
 * @param counter Local variable for counting.
 * @param nif Nif of the customers
 * @param count Number of customers
 */


void exportRankedCustomers(Customers *customer, int counter, int nif[MAX_CLIENTS], int count[MAX_CLIENTS]) {
    int option;

    option = menuRead(MSG_EXPORT_RANKED_DATA, 0, 1);

    switch (option) {
        case 0:
            break;
        case 1:
            FILE *fp;
            int i;
            char fn[100];
            askFileName(fn);
            fp = fopen(fn, "w");
            if (fp == NULL) {
                printf(ERROR_IN_FILES);
                pressAnyKeyToContinueFunction();
            } else {
                fprintf(fp, "Client Id;Name;Address;Nif;Country;Orders;State\n\n");
                for (i = 0; i < counter; i++) {
                    if (nif[i] == customer->customers[i].nif) {
                        fprintf(fp, "%d;%s;%s;%d;%s;%d;%s\n",
                                customer->customers[i].id,
                                customer->customers[i].name,
                                customer->customers[i].address,
                                nif[i],
                                customer->customers[i].country,
                                count[i],
                                customer->customers[i].state == 1 ? "Active" : "Inactive");
                    }
                }
                fclose(fp);
                printf(SUCCESS_IN_FILES);
                pressAnyKeyToContinueFunction();
            }
    }
}

/**
 * This function lists the customers by the amount of orders they have requested.
 * It then asks the user if he wants to export the data, if so, the exportRankCustomers
 * function is called.
 * 
 * @param order Pointer to the orders struct.
 * @param date Date value.
 * @param customer Pointer to the customers struct.
 */

void listRankCustomers(Orders *order, Date date, Customers *customer) {
    int i, j, counter = 0, tempNif = 0, tempCount = 0;
    int *nif, *count;
    nif = (int *)calloc(customer->counter, sizeof(int));
    count = (int *)calloc(customer->counter, sizeof(int));
    nif[0] = 0;
    struct tm t = {.tm_year = date.year, .tm_mon = date.month, .tm_mday = date.day};
    t.tm_mday += 5;
    mktime(&t);
    printf("\n\t\t\tRanked Customers for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
    for (i = 0; i < order->counter; i++) {
        if (order->order[i].order_date.day >= date.day && order->order[i].order_date.month >= date.month && order->order[i].order_date.year >= date.year ||
                order->order[i].order_date.day <= t.tm_mday && order->order[i].order_date.month <= t.tm_mon && order->order[i].order_date.year <= t.tm_year) {
            for (j = 0; j < customer->counter; j++) {
                if (order->order[i].nif == customer->customers[j].nif) {
                    if (nif[j] == 0) {
                        nif[j] = customer->customers[j].nif;
                        count[j] = 1;
                        counter++;
                    } else {
                        count[j] = count[j] + 1;
                    }
                }
            }
        }
    }
    for (i = 0; i < counter - 1; i++) {
        int Imin = i;
        for (j = i + 1; j < counter; j++) {
            if (count[j] > count[Imin]) {
                Imin = j;
            }
        }
        tempCount = count[Imin];
        count[Imin] = count[i];
        count[i] = tempCount;

        tempNif = nif[Imin];
        nif[Imin] = nif[i];
        nif[i] = tempNif;
    }
    for (i = 0; i < customer->counter; i++) {
        if (nif[i] == customer->customers[i].nif) {
            printf("\n\n\t\t\tClient Id : %d", nif[i]);
            printf("\n\t\t\tName      : %s", customer->customers[i].name);
            printf("\n\t\t\tAddress   : %s", customer->customers[i].address);
            printf("\n\t\t\tNif       : %d", customer->customers[i].nif);
            printf("\n\t\t\tCountry   : %s", customer->customers[i].country);
            printf("\n\t\t\tOrders    : %d", count[i]);
            printf("\n\t\t\tState     : %s", customer->customers[i].state == 1 ? "Active" : "Inactive");
            printf("\n\t\t\t__________________________________");
        }
    }
    exportRankedCustomers(*(&customer), counter, nif, count);
    free(nif);
    free(count);
}

/**
 * This function exports the Products by the amount of that product that were requested.
 * 
 * @param cod Vector that stores the Quantity and Size of the product
 * @param name Name of the product
 * @param price Price of the product
 * @param height Height of the product
 * @param lenght Lenght of the product
 * @param width Width of the product
 * @param quantity Quantity of the product
 * @param count Local variable for counting
 */


void exportRankedProducts(ProductionProducts *pp, int count) {
    int option;

    option = menuRead(MSG_EXPORT_RANKED_DATA, 0, 1);

    switch (option) {
        case 0:
            break;
        case 1:
            FILE *fp;
            int i;
            char fn[100];
            askFileName(fn);
            fp = fopen(fn, "w");
            if (fp == NULL) {
                printf(ERROR_IN_FILES);
                pressAnyKeyToContinueFunction();
            } else {
                fprintf(fp, "Product Code;Name;Price;Dimensions;Quantity\n\n");
                for (i = 0; i < count; i++) {
                    fprintf(fp, "%s;%s;%f;%dx%dx%d;%d\n",
                            pp[i].cod,
                            pp[i].name,
                            pp[i].price,
                            pp[i].dimension.height,
                            pp[i].dimension.width,
                            pp[i].dimension.width,
                            pp[i].quantity);
                }
                fclose(fp);
                printf(SUCCESS_IN_FILES);
                pressAnyKeyToContinueFunction();
            }
            break;
    }
}

/**
 * This function lists the products by the amount of products that were requested.
 * It then asks the user if he wants to export the data, if so, the exportRankProducts
 * function is called.
 * 
 * @param order Pointer to the orders struct
 * @param product Pointer to the products struct
 * @param date Date value
 */

void listRankProducts(Orders *order, Products *product, Date date) {
    int i, j, k, f, count = 0, tempQuantity;
    char *tempCod;
    ProductionProducts *pp;
    pp = (ProductionProducts *)malloc(sizeof(ProductionProducts)*product->counter);
    tempCod = (char *)malloc(sizeof(char)*product->counter);
    struct tm t = {.tm_year = date.year, .tm_mon = date.month, .tm_mday = date.day};
    t.tm_mday += 5;
    mktime(&t);
    for (i = 0; i < product->counter; i++) {
        pp[i].quantity = 0;
    }
    printf("\n\t\t\tRanked Products for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
    for (i = 0; i < order->counter; i++) {
        if (order->order[i].order_date.day >= date.day && order->order[i].order_date.month >= date.month && order->order[i].order_date.year >= date.year ||
                order->order[i].order_date.day <= t.tm_mday && order->order[i].order_date.month <= t.tm_mon && order->order[i].order_date.year <= t.tm_year) {
            for (j = 0; j < order->order[i].line_order_size; j++) {
                for (k = 0; k < product->counter; k++) {
                    if (strcmp(order->order[i].line_order[j].code, product->product[k].cod_Produto) == 0) {

                        if (pp[k].quantity == 0) {
                            pp[k].quantity = order->order[i].line_order[j].quantity;
                            count++;
                        } else {
                            pp[k].quantity = pp[k].quantity + order->order[i].line_order[j].quantity;
                        }
                        strcpy(pp[k].cod, order->order[i].line_order[j].code);
                    }
                }
            }
        }
    }
    for (i = 0; i < count - 1; i++) {
        int Imin = i;
        for (j = i + 1; j < count; j++) {
            if (pp[j].quantity > pp[Imin].quantity) {
                Imin = j;
            }
        }
        tempQuantity = pp[Imin].quantity;
        pp[Imin].quantity = pp[i].quantity;
        pp[i].quantity = tempQuantity;

        strcpy(tempCod, pp[Imin].cod);
        strcpy(pp[Imin].cod, pp[i].cod);
        strcpy(pp[i].cod, tempCod);
    }

    for (i = 0; i < order->counter; i++) {
        if (order->order[i].order_date.day >= date.day && order->order[i].order_date.month >= date.month && order->order[i].order_date.year >= date.year ||
                order->order[i].order_date.day <= t.tm_mday && order->order[i].order_date.month <= t.tm_mon && order->order[i].order_date.year <= t.tm_year) {
            for (j = 0; j < order->order[i].line_order_size; j++) {
                for (k = 0; k < product->counter; k++) {
                    if (strcmp(order->order[i].line_order[j].code, product->product[k].cod_Produto) == 0) {
                        for (f = 0; f < count; f++) {
                            if (strcmp(pp[f].cod, order->order[i].line_order[j].code) == 0) {
                                strcpy(pp[f].name, product->product[k].name);
                                pp[f].price = product->product[k].price;
                                pp[f].dimension.height = product->product[k].dimension.height;
                                pp[f].dimension.lenght = product->product[k].dimension.lenght;
                                pp[f].dimension.width = product->product[k].dimension.width;
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < count; i++) {
        printf("\n\n\t\t\tProduct Code       : %s", pp[i].cod);
        printf("\n\t\t\tName               : %s", pp[i].name);
        printf("\n\t\t\tPrice              : %f", pp[i].price);
        printf("\n\t\t\tDimensions         : %dx%dx%d", pp[i].dimension.height,
                                                        pp[i].dimension.lenght,
                                                        pp[i].dimension.width);
        printf("\n\t\t\tQuantity           : %d", pp[i].quantity);
        printf("\n\t\t\t__________________________________");
    }

    exportRankedProducts(pp, count);
    free(pp);
    free(tempCod);
}

/**
 * This function exports the Materials by the amount of that Material that was requested.
 * 
 * @param cod Vector that stores the Quantity and Size of the Material
 * @param description Vector that stores the MAximum number and Maximum Description
 * Size of the Material
 * @param quantity Quantity of the Material
 * @param unit Units of that Material
 * @param count Local variable for counting
 */

void exportRankedMaterials(ProductionMaterials  *rm, int count) {
    int option;

    option = menuRead(MSG_EXPORT_RANKED_DATA, 0, 1);

    switch (option) {
        case 0:
            break;
        case 1:
            FILE *fp;
            int i;
            char fn[100];
            askFileName(fn);
            fp = fopen(fn, "w+");
            if (fp == NULL) {
                printf(ERROR_IN_FILES);
                pressAnyKeyToContinueFunction();
            } else {
                fprintf(fp, "Material Code;Description;Quantity;Unit\n\n");
                for (i = 0; i < count; i++) {
                    fprintf(fp, "%s;%s;%d;%d\n",
                            rm[i].cod,
                            rm[i].description,
                            rm[i].quantity,
                            rm[i].unit);
                }
                fclose(fp);
                printf(SUCCESS_IN_FILES);
                pressAnyKeyToContinueFunction();
            }
            break;
    }
}

/**
 * This function lists the products by the amount of Materials that were requested.
 * It then asks the user if he wants to export the data, if so, the exportRankMaterials
 * function is called.
 * 
 * @param material Pointer to the materials struct
 * @param order Pointer to the orders struct
 * @param product Pointer to the products struct
 * @param date Date value
 */


void listRankMaterials(Materials *material, Orders *order, Products *product, Date date) {
    int i, j, k, d, f, count = 0, tempQuantity, tempUnit;
    char *tempCod, *tempDescription;
    ProductionMaterials *rm;
    rm = (ProductionMaterials *)malloc(sizeof(ProductionMaterials) * material->counter);
    tempCod = (char *)malloc(sizeof(char) * material->counter);
    tempDescription = (char *)malloc(sizeof(char) * material->counter);
    struct tm t = {.tm_year = date.year, .tm_mon = date.month, .tm_mday = date.day};
    t.tm_mday += 5;
    mktime(&t);
    for (d = 0; d < material->counter; d++) {
        rm[d].quantity = 0;
    }
    printf("\n\t\t\tRanked Materials for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
    for (i = 0; i < order->counter; i++) {
        if (order->order[i].order_date.day >= date.day && order->order[i].order_date.month >= date.month && order->order[i].order_date.year >= date.year ||
                order->order[i].order_date.day <= t.tm_mday && order->order[i].order_date.month <= t.tm_mon && order->order[i].order_date.year <= t.tm_year) {
            for (j = 0; j < order->order[i].line_order_size; j++) {
                for (k = 0; k < product->counter; k++) {
                    if (strcmp(order->order[i].line_order[j].code, product->product[k].cod_Produto) == 0) {
                        for (f = 0; f < product->product[k].line_product_size; ++f) {
                            for (d = 0; d < material->counter; d++) {
                                if (strcmp(material->material[d].cod_Material, product->product[k].line_product[f].code) == 0) {
                                    if (rm[d].quantity == 0) {
                                        rm[d].quantity = order->order[i].line_order[j].quantity * product->product[k].line_product[f].quantity;
                                        count++;
                                    } else {
                                        rm[d].quantity = rm[d].quantity + order->order[i].line_order[j].quantity * product->product[k].line_product[f].quantity;
                                    }
                                    strcpy(rm[d].cod, material->material[d].cod_Material);
                                    strcpy(rm[d].description, material->material[d].description);
                                    rm[d].unit = material->material[k].unit;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < count; i++) {
        int Imin = i;
        for (j = i + 1; j < count; j++) {
            if (rm[j].quantity > rm[Imin].quantity) {
                Imin = j;
            }
        }
        tempQuantity = rm[Imin].quantity;
        rm[Imin].quantity = rm[i].quantity;
        rm[i].quantity = tempQuantity;

        tempUnit = rm[Imin].unit;
        rm[Imin].unit = rm[i].unit;
        rm[i].unit = tempUnit;

        strcpy(tempCod, rm[Imin].cod);
        strcpy(rm[Imin].cod, rm[i].cod);
        strcpy(rm[i].cod, tempCod);

        strcpy(tempDescription, rm[Imin].description);
        strcpy(rm[Imin].description, rm[i].description);
        strcpy(rm[i].description, tempDescription);
    }

    for (d = 0; d < count; d++) {
        printf("\n\n\t\t\tMaterial Code   : %s", rm[d].cod);
        printf("\n\t\t\tDescription     : %s", rm[d].description);
        printf("\n\t\t\tQuantity        : %d", rm[d].quantity);
        printf("\n\t\t\tUnit            : %d", rm[d].unit);
        printf("\n\t\t\t__________________________________");
    }

    exportRankedMaterials(rm, count);
    free(rm);
    free(tempCod);
    free(tempDescription);
}

/**
 * Function that quickly sorts the struct Orders by Date.
 * 
 * @param aa Value 1
 * @param bb Value 2
 * @return The sort value.
 */

int sortOrder(const void *aa, const void *bb) {
    const Order *a = aa, *b = bb;
    if (a->order_date.day == b->order_date.day &&
            a->order_date.month == b->order_date.month &&
            a->order_date.year == b->order_date.year) {
        return 0;
    } else if (a->order_date.day <= b->order_date.day &&
            a->order_date.month <= b->order_date.month &&
            a->order_date.year <= b->order_date.year) {
        return -1;
    } else {
        return +1;
    }
}

/**
 * Exports the list of Orders.
 * 
 * @param temp
 */

void exportRankOrders(Orders *temp) {
    int option;

    option = menuRead(MSG_EXPORT_RANKED_DATA, 0, 1);

    switch (option) {
        case 0:
            break;
        case 1:
            FILE *fp;
            int i,j;
            char fn[100];
            askFileName(fn);
            fp = fopen(fn, "w");
            if (fp == NULL) {
                printf(ERROR_IN_FILES);
                pressAnyKeyToContinueFunction();
            } else {
                fprintf(fp, "Order Id;NIF;Order Date\n");
                for (i = 0; i < temp->counter; i++) {
                    fprintf(fp, "%d;%d;%d/%d/%d\n",
                            temp->order[i].order_id,
                            temp->order[i].nif,
                            temp->order[i].order_date.day,
                            temp->order[i].order_date.month,
                            temp->order[i].order_date.year);
                    fprintf(fp, "Product Id;Quantity\n");
                    for (j = 0; j < temp->order[i].line_order_size; j++) {
                        fprintf(fp, "%s;%d", temp->order[i].line_order[j].code, temp->order[i].line_order[j].quantity);
                    }
                    fprintf(fp,"\n\n");
                }
                fclose(fp);
                printf(SUCCESS_IN_FILES);
                pressAnyKeyToContinueFunction();
            }
    }
}

/**
 * This funciton lists the orders by date, from the newest to the oldest. 
 * It then asks the user if he wants to export the data, if so, the exportRankOrders
 * function is called.
 * 
 * @param order Pointer to the orders struct
 */

void listRankOrders(Orders *order) {
    Orders *temp;
    int i, j;
    temp = (Orders *) malloc(sizeof (Orders));
    temp->counter = order->counter;
    temp->order = (Order *) malloc(sizeof (Order)*(temp->counter + 1));
    for (i = 0; i < temp->counter; i++) {
        temp->order[i].order_date.month = order->order[i].order_date.month;
        temp->order[i].order_date.year = order->order[i].order_date.year;
        temp->order[i].order_date.day = order->order[i].order_date.day;
        temp->order[i].line_order_size = order->order[i].line_order_size;
        temp->order[i].order_id = order->order[i].order_id;
        temp->order[i].nif = order->order[i].nif;
        temp->order[i].line_order = (OrderLine *) malloc(sizeof (OrderLine) *
                temp->order[i].line_order_size);
        for (j = 0; j < temp->order[i].line_order_size; j++) {
            strcpy(temp->order[i].line_order[j].code, order->order[i].line_order[j].code);
            temp->order[i].line_order[j].quantity = order->order[i].line_order[j].quantity;
        }
    }
    qsort(temp->order, temp->counter, sizeof (Order), sortOrder);
    printf("\n\n\t\t\tList Of Orders (By date)\n\t\t\t________________________");
    for (i = 0; i < temp->counter; i++) {
        printf("\n\n\t\t\tOrder Id             : %d", temp->order[i].order_id);
        printf("\n\t\t\tClient Nif           : %d", temp->order[i].nif);
        printf("\n\t\t\tDate                 : %d-%d-%d", temp->order[i].order_date.day, temp->order[i].order_date.month, temp->order[i].order_date.year);
        printf("\n\t\t\t__________________________________\n");
        for (j = 0; j < temp->order[i].line_order_size; j++) {
            printf("\n\t\t\tProduct Id - %s\n\t\t\tQuantity - %d\n", temp->order[i].line_order[j].code, temp->order[i].line_order[j].quantity);
        }
        printf("\t\t\t__________________________________");
    }
    exportRankOrders(temp);
    free(temp->order);
    free(temp);
}

/**
 * This function sorts the customer per Address.
 * 
 * @param aa Value 1
 * @param bb Value 2
 * @return The sort value.
 */

int sortCustomerPerAddress(const void *aa, const void *bb) {
    const Customer *a = aa, *b = bb;
    return strcmp(a->address, b->address);
}

/**
 * Exports the listed customers.
 * 
 * @param temp Temporary value.
 */

void exportRankedCustomersPerAddress(Customers *temp) {
    int option;

    option = menuRead(MSG_EXPORT_RANKED_DATA, 0, 1);

    switch (option) {
        case 0:
            break;
        case 1:
            FILE *fp;
            int i;
            char fn[100];
            askFileName(fn);
            fp = fopen(fn, "w");
            if (fp == NULL) {
                printf(ERROR_IN_FILES);
                pressAnyKeyToContinueFunction();
            } else {
                fprintf(fp, "Client Id;Name;Address;Nif;Country;State\n\n");
                for (i = 0; i < temp->counter; i++) {
                    fprintf(fp, "%d;%s;%s;%d;%s;%s\n",
                            temp->customers[i].id,
                            temp->customers[i].name,
                            temp->customers[i].address,
                            temp->customers[i].nif,
                            temp->customers[i].country,
                            temp->customers[i].state == 1 ? "Active" : "Inactive");
                }
                fclose(fp);
                printf(SUCCESS_IN_FILES);
                pressAnyKeyToContinueFunction();
            }
    }
}

/**
 * This function list the customers by the address that they have.
 * It then asks the user if he wants to export the data, if so, the exportRankCustomersPerAddress
 * function is called.
 * 
 * @param customers
 */

void listRankCustomersPerAddress(Customers *customers) {
    Customers *temp;
    int i;
    temp = (Customers *) malloc(sizeof (Customers));
    temp->counter = customers->counter;
    temp->customers = (Customer *) malloc(sizeof (Customer)*(temp->counter + 1));
    for (i = 0; i < temp->counter; i++) {
        temp->customers[i].id = customers->customers[i].id;
        temp->customers[i].nif = customers->customers[i].nif;
        strcpy(temp->customers[i].country, customers->customers[i].country);
        strcpy(temp->customers[i].address, customers->customers[i].address);
        strcpy(temp->customers[i].name, customers->customers[i].name);
        temp->customers[i].state = customers->customers[i].state;
    }
    qsort(temp->customers, temp->counter, sizeof (Customer), sortCustomerPerAddress);
    printf("\n\n\t\t\tCustomers by Address\n\t\t\t________________________");
    for (i = 0; i < temp->counter; i++) {

        printf("\n\n\t\t\tClient Id : %d", temp->customers[i].id);
        printf("\n\t\t\tName      : %s", temp->customers[i].name);
        printf("\n\t\t\tAddress   : %s", temp->customers[i].address);
        printf("\n\t\t\tNif       : %d", temp->customers[i].nif);
        printf("\n\t\t\tCountry   : %s", temp->customers[i].country);
        printf("\n\t\t\tState     : %s", temp->customers[i].state == 1 ? "Active" : "Inactive");
        printf("\n\t\t\t__________________________________");
    }
    exportRankedCustomersPerAddress(temp);
    free(temp->customers);
    free(temp);
}

/**
 * Menu that has all the listings possible.
 * 
 * @param material Pointer to the materials struct
 * @param order Pointer to the orders struct
 * @param product Pointer to the products struct
 * @param date Date value
 * @param customers Pointer to the customers struct
 * @return 
 */


int listMenu(Materials *material, Orders *order, Products *product, Date date, Customers *customers) {
    int option;

    option = menuRead(MSG_LIST_MENU, 0, 6);
    switch (option) {
        case 0:
            break;
        case 1:
            listRankCustomers(*(&order), date, *(&customers));
            break;
        case 2:
            listRankProducts(*(&order), *(&product), date);
            break;
        case 3:
            listRankMaterials(*(&material), *(&order), *(&product), date);
            break;
        case 4:
            listRankOrders(order);
            break;
        case 5:
            listRankCustomersPerAddress(customers);
            break;
        default:
            break;
    }
    return option;
}

/**
 * This function lists all needed materials in a range of 5 days, firstly it verifies if
 * the order->counter is equal to zero, if so a message appears saying that no orders where
 * found, if not, it will ask the user for a date and for his nif, then it will pass the date
 * to a time.h data struct and add 5 days to the given date, it will then loop in the orders and verify
 * if the order is in the reach of both dates (initial date and the 5 days after date), then it will compare
 * the material codes present in the order to the material  codes present in the material struct, if the codes are equal
 * it will list all the material information + the quantity of the product in a certain order.
 * 
 * @param material Pointer to the materials struct.
 * @param order Pointer to the orders struct.
 * @param product Pointer to the products struct.
 * @param customer Pointer to the customers struct.
 */

void listMaterials(Materials *material, Orders *order, Products *product, Customers *customer) {
    Date date;
    int i, j, k, d, f, option = 1, count = 0;

    if (order->counter != 0) {
        date = askDate();
        struct tm t = {.tm_year = date.year, .tm_mon = date.month, .tm_mday = date.day};
        t.tm_mday += 5;
        mktime(&t);
        do {
            printf("\n\t\t\tList Of Materials for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
            for (i = 0; i < order->counter; i++) {
                if (order->order[i].order_date.day >= date.day && order->order[i].order_date.month >= date.month && order->order[i].order_date.year >= date.year &&
                        order->order[i].order_date.day <= t.tm_mday && order->order[i].order_date.month <= t.tm_mon && order->order[i].order_date.year <= t.tm_year) {
                    for (j = 0; j < order->order[i].line_order_size; j++) {
                        for (k = 0; k < product->counter; k++) {
                            if (strcmp(order->order[i].line_order[j].code, product->product[k].cod_Produto) == 0) {
                                for (f = 0; f < product->product[k].line_product_size; ++f) {
                                    for (d = 0; d < material->counter; d++) {
                                        if (strcmp(material->material[d].cod_Material, product->product[k].line_product[f].code) == 0) {
                                            printf("\n\n\t\t\tMaterial Code   : %s", material->material[d].cod_Material);
                                            printf("\n\t\t\tDescription     : %s", material->material[d].description);
                                            printf("\n\t\t\tQuantity        : %d", order->order[i].line_order[j].quantity * product->product[k].line_product[f].quantity);
                                            printf("\n\t\t\tUnit            : %d", material->material[k].unit);
                                            printf("\n\t\t\t__________________________________");
                                        }
                                    }
                                }
                            }
                        }
                    }
                    ++count;
                }
            }
            if (count == 0) {
                errorMessage(NO_ORDERS_FOUND_TO_THAT_DATE_MESSAGE);
            } else {
                option = listMenu(*(&material), *(&order), *(&product), date, *(&customer));
            }
        } while (option != 0);
    } else {
        errorMessage(NO_ORDERS_FOUND_MESSAGE);
    }

}

/**
 * This menu is where the listMaterials function can be found.
 * 
 * @param order
 * @param material
 * @param product
 * @param customers
 */

void productionManagementMenu(Orders **order, Materials **material, Products **product, Customers *customers) {
    int option;

    do {
        option = menuRead(MSG_MENU_PRODUCTION, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:
                listMaterials(*material, *order, *product, customers);
                break;
        }
    } while (option != 0);
}
