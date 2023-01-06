//
// Created by gui on 12-12-2022.
//

#include "products.h"
#include "orders.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_PRODUCTS_MANAGEMENT_MENU "[1] - Save.\n[2] - Load.\n[3] - Delete.\n"

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

void saveProducts(Products *products){
    FILE *fp;
    int i, j, c;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "w+");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    printf("counter:\t%d\n", products->counter);
    fwrite(&products->counter, sizeof(int), 1, fp);
    i = 0;
    do{
        fwrite(&products->product[i].cod_Produto, sizeof(char) * COD_PRODUCT_SIZE, 1, fp);
        fwrite(&products->product[i].name, sizeof(char) * MAX_PRODUCT_NAME_SIZE, 1, fp);
        fwrite(&products->product[i].price, sizeof(double), 1, fp);
        fwrite(&products->product[i].dimension.height, sizeof(int), 1, fp);
        fwrite(&products->product[i].dimension.lenght, sizeof(int), 1, fp);
        fwrite(&products->product[i].dimension.width, sizeof(int), 1, fp);
        i++;
    }while(i < products->counter);

    for (i = 0; i < products->counter; i++){
        j = 0;
        fwrite(&products->product[i].material_count, sizeof(int), 1, fp);
        printf("material:\t%d\n", products->product[i].material_count);
        do{
            fwrite(&products->product[i].material[j].cod_Material, sizeof(char)*COD_MATERIAL_SIZE, 1, fp);
            fwrite(&products->product[i].material[j].description, sizeof(char)*MAX_DESCRIPTION_SIZE, 1, fp);
            fwrite(&products->product[i].material[j].quantity, sizeof(short int), 1, fp);
            fwrite(&products->product[i].material[j].unit, sizeof(units), 1, fp);
            j++;
        }while(j < products->product[i].material_count);
    }
    printf("%d", c);
    fclose(fp);
    printf(SUCCESS_IN_WRITING_ORDERS);
}
void loadProducts(Products *products){
    FILE *fp;
    int i, j, c;
    char fn[MAX_FN_CHARS], buff[1024], *sp, *d;
    askFileName(fn);
    fp = fopen(fn, "rb+");
    fread(&c, sizeof(int), 1, fp);
    printf("%d\n", c);
    products = (Products *)malloc(1 * sizeof(Products));
    products->product = (Product *)malloc(c * sizeof(Product));
    for (i = 0; i < c; i++){
        //fread(&products->product[i], sizeof(Products), 1, fp);
        fread(&products->product[i].cod_Produto, sizeof(char) * COD_PRODUCT_SIZE,1,fp);
        fread(&products->product[i].name, sizeof(char)*MAX_PRODUCT_NAME_SIZE, 1, fp);
        fread(&products->product[i].price, sizeof(double), 1, fp);
        fread(&products->product[i].dimension.height, sizeof(int), 1, fp);
        fread(&products->product[i].dimension.lenght, sizeof(int), 1, fp);
        fread(&products->product[i].dimension.width, sizeof(int), 1, fp);
    }
    for(i = 0; i < c;i++){
        fread(&products->product[i].material_count, sizeof(int), 1, fp);
        products->product[i].material = (Materials *)malloc(sizeof(Materials)*products->product[i].material_count);
        printf("material_count: %d\n", products->product[i].material_count);
        for (j = 0; j < products->product[i].material_count; j++){
            fread(&products->product[i].material[j].cod_Material, sizeof(char) * COD_MATERIAL_SIZE, 1, fp);
            fread(&products->product[i].material[j].description, sizeof(char)*MAX_DESCRIPTION_SIZE, 1, fp);
            fread(&products->product[i].material[j].quantity, sizeof(short int), 1, fp);
            fread(&products->product[i].material[j].unit, sizeof(int), 1, fp);
        }
    }
    printf("%s",products->product[1].material[0].cod_Material);
    fclose(fp);
}

void loadProductsBin(Products *product){
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS], buff[1024], *sp;
    askFileName(fn);
    fp = fopen(fn, "wb+");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    i = 0;
    j = 0;
    /*do{
        fwrite(&product->counter, sizeof(int), 1, fp);
        fwrite(&product->product[i], sizeof(Products), 1, fp);
        i++;
    }while(i <= product->counter);
    fwrite(product, )
    */
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

    //fillStruct(products);
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