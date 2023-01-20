//
// Created by r1ken on 12-12-2022.
//
#include "production.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/*
 * Bellow function ask the user for a date and verifies if the date is valid, if so then the date
 * is returned.
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

void listRankClients() {

}

void listRankProducts() {

}

void exportRankedMaterials(char cod[MAX_MATERIALS][COD_MATERIAL_SIZE], char description[MAX_MATERIALS][MAX_DESCRIPTION_SIZE], int quantity[MAX_MATERIALS], int unit[MAX_MATERIALS], int count) {
    int option;

    option = menuRead(MSG_EXPORT_RANK_MATERIALS, 0, 1);

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
                printf(ERROR_IN_WRITING_MATERIALS);
                pressAnyKeyToContinueFunction();
            } else {
                fprintf(fp, "Material Code;Description;Quantity;Unit\n\n");
                for (i = 0; i < count; i++) {
                    fprintf(fp, "%s;%s;%d;%d\n",
                            cod[i],
                            description[i],
                            quantity[i],
                            unit[i]);
                }
                fclose(fp);
                printf(SUCCESS_IN_WRITING_MATERIALS);
                pressAnyKeyToContinueFunction();
            }
            break;
    }
}

void listRankMaterials(Materials *material, Orders *order, Products *product, Date date) {
    int i, j, k, d, f, count = 0, quantity[MAX_MATERIALS], unit[MAX_MATERIALS], tempQuantity, tempUnit;
    char description[MAX_MATERIALS][MAX_DESCRIPTION_SIZE], cod[MAX_MATERIALS][COD_MATERIAL_SIZE], tempCod[MAX_MATERIALS], tempDescription[MAX_MATERIALS];

    struct tm t = {.tm_year = date.year, .tm_mon = date.month, .tm_mday = date.day};
    t.tm_mday += 5;
    mktime(&t);
    for (d = 0; d < 20; d++) {
        quantity[d] = 0;
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

                                    if (quantity[d] == 0) {
                                        quantity[d] = order->order[i].line_order[j].quantity * product->product[k].line_product[f].quantity;
                                        strcpy(cod[d], material->material[d].cod_Material);
                                        strcpy(description[d], material->material[d].description);
                                        unit[d] = material->material[k].unit;
                                        count++;
                                    } else {
                                        quantity[d] = quantity[d] + order->order[i].line_order[j].quantity * product->product[k].line_product[f].quantity;
                                        strcpy(cod[d], material->material[d].cod_Material);
                                        strcpy(description[d], material->material[d].description);
                                        unit[d] = material->material[k].unit;
                                    }

                                }
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < count - 1; i++) {
                int Imin = i;
                for (int j = i + 1; j < count; j++) {
                    if (quantity[j] > quantity[Imin]) {
                        Imin = j;
                    }
                }
                tempQuantity = quantity[Imin];
                quantity[Imin] = quantity[i];
                quantity[i] = tempQuantity;

                tempUnit = unit[Imin];
                unit[Imin] = unit[i];
                unit[i] = tempUnit;

                strcpy(tempCod, cod[Imin]);
                strcpy(cod[Imin], cod[i]);
                strcpy(cod[i], tempCod);

                strcpy(tempDescription, description[Imin]);
                strcpy(description[Imin], description[i]);
                strcpy(description[i], tempDescription);
            }

            for (d = 0; d < count; d++) {
                printf("\n\n\t\t\tMaterial Code   : %s", cod[d]);
                printf("\n\t\t\tDescription     : %s", description[d]);
                printf("\n\t\t\tQuantity        : %d", quantity[d]);
                printf("\n\t\t\tUnit            : %d", unit[d]);
                printf("\n\t\t\t__________________________________");
            }
        }
    }
    exportRankedMaterials(cod, description, quantity, unit, count);
}

void avgMaterialPerProduct() {

}

void quantityPerOrder() {

}

int listMenu(Materials *material, Orders *order, Products *product, Date date) {
    int option;

        option = menuRead(MSG_LIST_MENU, 0, 5);

        switch (option) {
            case 0:
                break;
            case 1:
                listRankClients();
                break;
            case 2:
                listRankProducts();
                break;
            case 3:
                listRankMaterials(*(&material), *(&order), *(&product), date);
                break;
            case 4:
                avgMaterialPerProduct();
                break;
            case 5:
                quantityPerOrder();
                break;
        }
    return option;
}

/*
 * Bellow function lists all needed materials in a range of 5 days, firstly it verifies if
 * the order->counter is equal to zero, if so a message appear saying that no orders where
 * found, if not, it will ask the user for a date and for his nif, then it will pass the date
 * to a time.h data struct and add 5 days to the given date, it will then loop in the orders and verify
 * if the order is in the reach of both dates (initial date and the 5 days after date), then it will compare
 * the material codes present in the order to the material  codes present in the material struct, if the codes are equal
 * it will list all the material information + the quantity of the product in a certain order.
 */
void listMaterials(Materials *material, Orders *order, Products *product) {
    Date date;
    int i, j, k, d, f, option = 1;
    if (order->counter != 0) {
        date = askDate();
        struct tm t = {.tm_year = date.year, .tm_mon = date.month, .tm_mday = date.day};
        t.tm_mday += 5;
        mktime(&t);
        printf("\n\t\t\tList Of Materials for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
        for (i = 0; i < order->counter; i++) {
            if (order->order[i].order_date.day >= date.day && order->order[i].order_date.month >= date.month && order->order[i].order_date.year >= date.year ||
                    order->order[i].order_date.day <= t.tm_mday && order->order[i].order_date.month <= t.tm_mon && order->order[i].order_date.year <= t.tm_year) {
                do{
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
                option = listMenu(*(&material), *(&order), *(&product), date);
                system("cls || clear");
                printf("\n\t\t\tList Of Materials for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
                }while (option != 0);
            } else {
                errorMessage(NO_ORDERS_FOUND_TO_THAT_DATE_MESSAGE);
            }
        }
    } else {
        errorMessage(NO_ORDERS_FOUND_MESSAGE);
    }
}

/*
 * Bellow menu is where the listMaterials function can be found.
 */
void productionManagementMenu(Orders **order, Materials **material, Products **product) {
    int option;

    do {
        option = menuRead(MSG_MENU_PRODUCTION, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:
                listMaterials(*material, *order, *product);
                break;
        }
    } while (option != 0);
}
