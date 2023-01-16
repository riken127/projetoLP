//
// Created by r1ken on 12-12-2022.
//
#include "production.h"
#include <stdio.h>
#include <time.h>
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
    } while (insertedDate.day < MIN_DAY || insertedDate.day > MAX_DAY ||
            insertedDate.month < MIN_MONTH || insertedDate.month > MAX_MONTH ||
            insertedDate.year < MIN_YEAR);
    return insertedDate;
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
    int i, j, k, d, f, nif;
    if (order->counter != 0) {
        date = askDate();
        nif = customerNif();
        struct tm t = { .tm_year = date.year, .tm_mon = date.month, .tm_mday = date.day};
        t.tm_mday += 5;
        mktime(&t);
        for (i = 0; i < order->counter; i++) {
            printf("%d %d",order->order[i].nif, nif);
            if ((order->order[i].order_date.day >= date.day && order->order[i].order_date.month >= date.month && order->order[i].order_date.year >= date.year ||
                order->order[i].order_date.day <= t.tm_mday && order->order[i].order_date.month <= t.tm_mon && order->order[i].order_date.year <= t.tm_year) &&
                order->order[i].nif == nif) {
                printf("\n\t\t\tOrder Number O%d", (i + 1));
                printf("\n\t\t\tList Of Materials for %d-%d-%d\n\t\t\t__________________________________", date.day, date.month, date.year);
                for (j = 0; j < order->order[i].line_order_size; j++) {
                    for(k = 0; k < product->counter; k++) {
                        if (strcmp(order->order[i].line_order[j].code, product->product[k].cod_Produto) == 0) {
                            for (f = 0; f < product->product[k].line_product_size; ++f) {
                                for (d = 0; d < material->counter; d++){
                                    if (strcmp(material->material[d].cod_Material, product->product[k].line_product[f].code) == 0){
                                        printf("\n\n\t\t\tMaterial Code   : %s", material->material[d].cod_Material);
                                        printf("\n\t\t\tDescription   : %s", material->material[d].description);
                                        printf("\n\t\t\tQuantity      : %d",  order->order[i].line_order[j].quantity*product->product[k].line_product[f].quantity);
                                        printf("\n\t\t\tUnit          : %d", material->material[k].unit);
                                        printf("\n\t\t\t__________________________________");
                                    }
                                }
                            }

                        }
                    }
                }
            }
            else {
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
