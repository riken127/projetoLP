//
// Created by gui on 12-12-2022.
//

#include "products.h"
#include "orders.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void productCode(char productCode[COD_PRODUCT_SIZE]) {
    char temp;
    printf(ASK_PRODUCT_CODE);
    scanf("%c", &temp);
    scanf("%[^\n]", productCode);
}

void productName(char productName[MAX_PRODUCT_NAME_SIZE]) {
    char temp;
    printf(ASK_PRODUCT_NAME);
    scanf("%c", &temp);
    scanf("%[^\n]", productName);
}

void productDimension(Dimensions *productDimension) {
    printf(ASK_PRODUCT_DIMENSION);
    scanf("%dx%dx%d", &productDimension->lenght,
          &productDimension->height,
          &productDimension->width);
}

void productPrice(double *price) {
    printf(ASK_PRODUCT_PRICE);
    scanf("%lf", price);
}

void materialCode(char materialCode[COD_MATERIAL_SIZE]) {
    char temp;
    printf(ASK_MATERIAL_CODE);
    scanf("%c", &temp);
    scanf("%[^\n]", materialCode);
}

void materialDescription(char materialDescription[MAX_DESCRIPTION_SIZE]) {
    char temp;
    printf(ASK_MATERIAL_DESCRIPTION);
    scanf("%c", &temp);
    scanf("%[^\n]", materialDescription);
}

void materialQuantity(short int *materialQuantity) {
    printf(ASK_MATERIAL_QUANTITY);
    scanf("%hu", *(&materialQuantity));
}

void materialUnit(units *materialUnit) {
    printf(ASK_MATERIAL_UNIT);
    scanf("%u", *(&materialUnit));
}


void newProduct(Products *product) {
    int i;
    bool op;
    product->product = (Product *) realloc(product->product, sizeof(Product) * (++product->counter));
    product->product[product->counter - 1].material_count = 1;
    product->product[product->counter - 1].material = (Materials *)malloc(sizeof(Materials) * 1);
    productCode(product->product[product->counter - 1].cod_Produto);
    productName(product->product[product->counter - 1].name);
    productDimension(&(product->product[product->counter - 1].dimension));
    productPrice(&product->product[product->counter - 1].price);
    i = 0;
    do {
        materialCode(product->product[product->counter - 1].material[i].cod_Material);
        materialDescription(product->product[product->counter - 1].material[i].description);
        materialQuantity(&product->product[product->counter - 1].material[i].quantity);
        materialUnit(&product->product[product->counter - 1].material[i].unit);
        op = menuRead(ASK_ANOTHER_MATERIAL, 0, 1);
        i++;

        product->product[product->counter - 1].material = (Materials *)realloc(product->product[product->counter - 1].material, sizeof(Materials) * (i + 1));
    } while (op != false);
    product->product[product->counter - 1].material_count = (i);
}

void saveProducts(Products *products) {
    FILE *fp;
    int i, j, c;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "w+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&products->counter, sizeof(int), 1, fp);
    i = 0;
    do {
        fwrite(&products->product[i].cod_Produto, sizeof(char) * COD_PRODUCT_SIZE, 1, fp);
        fwrite(&products->product[i].name, sizeof(char) * MAX_PRODUCT_NAME_SIZE, 1, fp);
        fwrite(&products->product[i].price, sizeof(double), 1, fp);
        fwrite(&products->product[i].dimension.height, sizeof(int), 1, fp);
        fwrite(&products->product[i].dimension.lenght, sizeof(int), 1, fp);
        fwrite(&products->product[i].dimension.width, sizeof(int), 1, fp);
        i++;
    } while (i < products->counter);

    for (i = 0; i < products->counter; i++) {
        j = 0;
        fwrite(&products->product[i].material_count, sizeof(int), 1, fp);
        printf("material:\t%d\n", products->product[i].material_count);
        do {
            fwrite(&products->product[i].material[j].cod_Material, sizeof(char) * COD_MATERIAL_SIZE, 1, fp);
            fwrite(&products->product[i].material[j].description, sizeof(char) * MAX_DESCRIPTION_SIZE, 1, fp);
            fwrite(&products->product[i].material[j].quantity, sizeof(short int), 1, fp);
            fwrite(&products->product[i].material[j].unit, sizeof(units), 1, fp);
            j++;
        } while (j < products->product[i].material_count);
    }
    printf("%d", c);
    fclose(fp);
    printf(SUCCESS_IN_WRITING_ORDERS);
}

void loadProducts(Products *products) {
    FILE *fp;
    int i, j, c, k;
    char fn[MAX_FN_CHARS], buff[1024], *sp, *d;
    askFileName(fn);
    fp = fopen(fn, "rb+");
    fread(&c, sizeof(int), 1, fp);
    k = products->counter;
    for (i = 0; i < c; i++) {
        products->product = (Product *) realloc(products->product, (products->counter + 1) * sizeof(Product));
        fread(&products->product[products->counter].cod_Produto, sizeof(char) * COD_PRODUCT_SIZE, 1, fp);
        fread(&products->product[products->counter].name, sizeof(char) * MAX_PRODUCT_NAME_SIZE, 1, fp);
        fread(&products->product[products->counter].price, sizeof(double), 1, fp);
        fread(&products->product[products->counter].dimension.height, sizeof(int), 1, fp);
        fread(&products->product[products->counter].dimension.lenght, sizeof(int), 1, fp);
        fread(&products->product[products->counter].dimension.width, sizeof(int), 1, fp);
        products->counter++;
    }
    printf("%d", products->counter);
    for (i = 0; i < c; i++) {
        fread(&products->product[k + i].material_count, sizeof(int), 1, fp);
        printf("%d", products->product[k + i].material_count);
        products->product[k + i].material = (Materials *) malloc(sizeof(Materials) * products->product[k + i].material_count);
        printf("material_count: %d\n", products->product[k + i].material_count);
        for (j = 0; j < products->product[k + i].material_count; j++) {
            fread(&products->product[k + i].material[j].cod_Material, sizeof(char) * COD_MATERIAL_SIZE, 1, fp);
            fread(&products->product[k + i].material[j].description, sizeof(char) * MAX_DESCRIPTION_SIZE, 1, fp);
            fread(&products->product[k + i].material[j].quantity, sizeof(short int), 1, fp);
            fread(&products->product[k + i].material[j].unit, sizeof(int), 1, fp);
        }
        products->product[k + i].material_count = (j);
    }

    fclose(fp);
}

/*
 * carregar por memória já que ainda n sabemos como fazer por ficheiro
 */
void listProducts(Products *product){
    int i, j;
    printf("Product list.\n");
    for (i = 0; i < product->counter; i++){
        printf("%s, %s, %.2lf, %dx%dx%d\n",
               product->product[i].cod_Produto,
               product->product[i].name,
               product->product[i].price,
               product->product[i].dimension.height,
               product->product[i].dimension.width,
               product->product[i].dimension.lenght);
        for (j = 0; j < product->product[i].material_count; j++){
            printf("\t%s, %s, %hu, %d\n",
                   product->product[i].material[j].cod_Material,
                   product->product[i].material[j].description,
                   product->product[i].material[j].quantity,
                   product->product[i].material[j].unit);
        }
    }
}

void productsManagementMenu(Products *products) {
    int option;

    products->product->material = malloc(11 * sizeof(Materials));
    for (int i = 0; i < 2; i++) {
        products->product[i].material = malloc(2 * sizeof(Materials));
    }


    do {
        option = menuRead(MSG_PRODUCTS_MANAGEMENT_MENU, 0, 6);

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
                newProduct(products);
                break;
            case 4:
                //edit.
                break;
            case 5:
                //delete.
                break;
            case 6:
                listProducts(products);
                break;
        }
    } while (option != 0);
}