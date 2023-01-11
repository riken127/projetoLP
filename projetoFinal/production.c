//
// Created by r1ken on 12-12-2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "production.h"
#include "orders.h"
#include "products.h"
#include "clients.h"

Date askDate() {
    Date insertedDate;
    int i,j,max=31;
    do {
        printf(ASK_DESIRED_DATE);
        scanf("%d-%d-%d",
                &insertedDate.day,
                &insertedDate.month,
                &insertedDate.year);
    } while (insertedDate.day < MIN_DAY || insertedDate.day > MAX_DAY ||
            insertedDate.month < MIN_MONTH || insertedDate.month > MAX_MONTH ||
            insertedDate.year < MIN_YEAR);
    // 1-1-2023
    // 8-1-2023
    // 15-1-2023
    
    return insertedDate;
}

void listMenu() {
    int option;

    do {
        option = menuRead(MSG_LIST_MENU, 0, 3);

        switch (option) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
    } while (option != 0);
}

void listMaterials(Products *product, Orders *order) {
    Date date;
    int i, j, k;
    if (order->counter != 0) {
        date = askDate();
        for (i = 0; i < order->counter; i++) {
            if (order->order[i].order_date.day == date.day && order->order[i].order_date.month == date.month && order->order[i].order_date.year == date.year) {
                printf("\n\t\t\tList Of Materials for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
                for (j = 0; j < product->counter; j++) {
                    if (j + 1 == order->order[i].product_id) {
                        for (k = 0; k < product->product[j].material_count; k++) {
                            printf("\n\n\t\t\tMaterial Id   : %s", product->product[j].material[k].cod_Material);
                            printf("\n\t\t\tDescription   : %s", product->product[j].material[k].description);
                            printf("\n\t\t\tQuantity      : %d", product->product[j].material[k].quantity * order->order[i].quantity);
                            printf("\n\t\t\tUnit          : %d", product->product[j].material[k].unit);
                            printf("\n\t\t\t__________________________________");
                        }
                    }
                }
                listMenu();
            }
            else {
                errorMessage(NO_ORDERS_FOUND_TO_THAT_DATE_MESSAGE);
            }
        }
    } else {
        errorMessage(NO_ORDERS_FOUND_MESSAGE);
    }
}

void saveDateMaterials(Products *product, Orders *order) {
    FILE *fp;
    char fn[MAX_FN_CHARS];
    Date date;
    int i, j, k, z = 1;
    askFileName(fn);
    date = askDate();
    fp = fopen(fn, "w+");
    
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < order->counter; i++) {
        if (order->order[i].order_date.day == date.day &&
                order->order[i].order_date.month == date.month &&
                order->order[i].order_date.year == date.year) {
            for (j = 0; j < product->counter; j++) {
                if ((j + 1) == order->order[i].product_id) {
                    for (k = 0; k < product->product[j].material_count; k++) {
                        fprintf(fp, "%d,%s,%s,%d,%d,%d\n",
                                z,
                                product->product[j].material[k].cod_Material,
                                product->product[j].material[k].description,
                                product->product[j].material[k].quantity,
                                product->product[j].material[k].unit,
                                order->order[i].quantity);
                        z++;
                    }
                }
            }
        }
    }
    fclose(fp);
    printf(SUCCESS_IN_WRITING_PRODUCTION);
}

void productionManagementMenu(Products **product, Orders **order) {
    int option;

    do {
        option = menuRead(MSG_MENU_PRODUCTION, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:
                listMaterials(*product, *order);
                break;
            case 2:
                importOrders(*order);
                break;
        }
    } while (option != 0);
}