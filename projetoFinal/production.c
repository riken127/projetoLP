//
// Created by r1ken on 12-12-2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "production.h"
#include "orders.h"
#include "products.h"


Date askDate(){
    Date insertedDate;
    do{
        printf(ASK_DESIRED_DATE);
        scanf("%d-%d-%d",
              &insertedDate.day,
              &insertedDate.month,
              &insertedDate.year);
        //printf("%d-%d-%d", insertedDate.day, insertedDate.month, insertedDate.year);
    }while(insertedDate.day < MIN_DAY || insertedDate.day > MAX_DAY ||
           insertedDate.month < MIN_MONTH || insertedDate.month > MAX_MONTH ||
           insertedDate.year < MIN_YEAR);

    return insertedDate;
}

void dateMaterials(Products *product, Orders *order){
    Date date;
    int i, j, k, z = 1;
    date = askDate();
    //printf("%d-%d-%d", date.day, date.month, date.year);
    for (i = 0; i < order->counter; i++){
        //printf("%d", order->counter);
        if (order->order[i].order_date.day == date.day &&
            order->order[i].order_date.month == date.month &&
            order->order[i].order_date.year == date.year){
            for (j=0;j<product->counter;j++){
                if (j + 1  == order->order[i].product_id){
                    for (k = 0; k < product->product[j].material_count; k++){
                        printf("%d - | %s | %s | %d | %d | * %d\n", z,
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
}

void saveDateMaterials(Products *product, Orders *order){
    FILE *fp;
    char fn[MAX_FN_CHARS];
    Date date;
    int i, j, k, z = 1;
    askFileName(fn);
    date = askDate();
    fp = fopen(fn, "w+");
    if(fp == NULL){
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < order->counter; i++){
        if (order->order[i].order_date.day == date.day &&
            order->order[i].order_date.month == date.month &&
            order->order[i].order_date.year == date.year){
            for (j = 0; j < product->counter; j++){
                if ((j + 1) == order->order[i].product_id){
                    for (k = 0; k < product->product[j].material_count; k++){
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
        fclose(fp);
        printf(SUCCESS_IN_WRITING_PRODUCTION);
    }
}
void productionManagementMenu(Products **product, Orders **order){
    int option;

    do{
        option = menuRead(MSG_MENU_PRODUCTION, 0, 3);

        switch (option){
            case 0:
                break;
            case 1:
                dateMaterials(*product, *order);
                break;
            case 2:
                saveDateMaterials(*product, *order);
                break;
            case 3:
                break;
        }
    }while(option != 0);
}