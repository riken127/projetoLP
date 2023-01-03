//
// Created by gui on 12-12-2022.
//

#include "products.h"
#include "orders.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_PRODUCTS_MANAGEMENT_MENU "[1] - View.\n[2] - Edit.\n[3] - Delete.\n"

void fillStruct(Products *product) {
    strcpy((product->product[0].cod_Produto), "P00001");
    strcpy((product->product[0].name), "Movel WC");
    product->product[0].price = 99;
    product->product[0].dimension.lenght = 80;
    product->product[0].dimension.height = 120;
    product->product[0].dimension.width = 60;

    strcpy(product->product[0].material[0].cod_Material, "M0001");
    strcpy(product->product[0].material[0].description, "Tubo Cola 10GR");
    product->product[0].material[0].quantity = 1;
    product->product[0].material[0].unit = 0;

    strcpy(product->product[0].material[1].cod_Material, "M0002");
    strcpy(product->product[0].material[1].description, "Parafuso 30MM");
    product->product[0].material[1].quantity = 4;
    product->product[0].material[1].unit = 0;
    product->product[0].material_count = 2;

    strcpy((product->product[1].cod_Produto), "P00002");
    strcpy((product->product[1].name), "Comoda");
    product->product[1].price = 299;
    product->product[1].dimension.lenght = 160;
    product->product[1].dimension.height = 120;
    product->product[1].dimension.width = 60;

    strcpy(product->product[1].material[0].cod_Material, "M0001");
    strcpy(product->product[1].material[0].description, "Tubo Cola 10GR");
    product->product[1].material[0].quantity = 1;
    product->product[1].material[0].unit = 0;

    strcpy(product->product[1].material[1].cod_Material, "M0002");
    strcpy(product->product[1].material[1].description, "Parafuso 30MM");
    product->product[1].material[1].quantity = 4;
    product->product[1].material[1].unit = 0;
    product->product[1].material_count = 2;

    product->counter = 2;
}

void saveProducts(Products *product){
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "w+");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < product->counter; i++){
        for (j = 0; j < product->product[i].material_count; j++) {
            fprintf(fp, "%s,%s,%.2lf,%dx%dx%d,%s,%s,%hu,%u\n",
                    product->product[i].cod_Produto,
                    product->product[i].name,
                    product->product[i].price,
                    product->product[i].dimension.height,
                    product->product[i].dimension.lenght,
                    product->product[i].dimension.width,
                    product->product[i].material[j].cod_Material,
                    product->product[i].material[j].description,
                    product->product[i].material[j].quantity,
                    product->product[i].material[j].unit);
        }
    }
    fclose(fp);
    printf(SUCCESS_IN_WRITING_ORDERS);
}
void loadProducts(Products *product){
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS], buff[1024], *sp, *d;
    askFileName(fn);
    fp = fopen(fn, "r");
    while (fgets(buff, 1024, fp) != NULL){
        sp = strtok(buff, ",");
        strcpy(product->product[product->counter - 1].cod_Produto, sp);
        sp = strtok(NULL, ",");
        strcpy(product->product[product->counter - 1].name, sp);
        sp = strtok(NULL, ",");
        product->product[product->counter - 1].price = atof(sp);
        sp = strtok(NULL, "x");
        product->product[product->counter - 1].dimension.lenght = atoi(sp);
        sp = strtok(NULL, "x");
        product->product[product->counter - 1].dimension.width = atoi(sp);
        sp = strtok(NULL, ",");
        product->product[product->counter - 1].dimension.height = atoi(sp);


        //printf("\n%s", buff);
    }

}
/*
bool writeData(char *filename, Products *data, int total)
{
    FILE *file;

    file = fopen(filename, "wb+");
    void *tmp = data->material;
    data->material = NULL;
    if (file == NULL)
        return NULL;
    if (fwrite(&total, sizeof(int), 1, file) != 1)
        return NULL;
    for (int j = 0; j < total; j++) {
        for (int i = 0; i < data->material_count; i++) {
            if (fwrite((data + j)->material[i], sizeof(Materials), 1, file) ==
1) continue; printf("ERROR"); return false;
        }
    }

    if (fwrite(data, sizeof(Products), total, file) != total)
        return NULL;
    if (fclose(file) == EOF)
        return false;

    data->material = tmp;

    return true;
}*/
/*
 * carregar por memória já que ainda n sabemos como fazer por ficheiro
 */

void productsManagementMenu(Products *products) {
    int option;

    products->product->material = malloc(11 * sizeof(Materials));
    for (int i = 0; i < 2; i++) {
        products->product[i].material = malloc(2 * sizeof(Materials));
    }

    fillStruct(products);
    do {
        option = menuRead(MSG_PRODUCTS_MANAGEMENT_MENU, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:
                saveProducts(products);
                break;
            case 2:
                loadProducts(products);
                break;
            case 3:
                break;
        }
    } while (option != 0);
}