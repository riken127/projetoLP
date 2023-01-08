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
    product->product[product->counter - 1].material = (Materials *) malloc(sizeof(Materials) * 1);
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

        product->product[product->counter - 1].material = (Materials *) realloc(
                product->product[product->counter - 1].material, sizeof(Materials) * (i + 1));
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

void deleteProducts(Products *products) {
    int i, j, count = 0;
    char code[COD_PRODUCT_SIZE];
    //do {
    printf(ASK_PRODUCT_CODE);
    scanf("%s", code);
    for (i = 0; i < products->counter; i++) {
        printf("%s, %s", code, products->product[i].cod_Produto);
        if (strcmp(code, products->product[i].cod_Produto) == 0) {
            strcpy(products->product[i].cod_Produto, products->product[i + 1].cod_Produto);
            strcpy(products->product[i].name, products->product[i + 1].name);
            products->product[i].material_count = products->product[i + 1].material_count;
            products->product[i].price = products->product[i + 1].price;
            products->product[i].dimension.lenght = products->product[i + 1].dimension.lenght;
            products->product[i].dimension.width = products->product[i + 1].dimension.width;
            products->product[i].dimension.height = products->product[i + 1].dimension.height;
            products->product[i].material = (Materials *) realloc(products->product[i].material, sizeof(Materials) *
                                                                                                 products->product[i].material_count);
            for (j = 0; j < products->product[i].material_count; j++) {
                strcpy(products->product[i].material[j].cod_Material,
                       products->product[i + 1].material[j].cod_Material);
                strcpy(products->product[i].material[j].description,
                       products->product[i + 1].material[j].description);
                products->product[i].material[j].unit = products->product[i + 1].material[j].unit;
                products->product[i].material[j].unit = products->product[i + 1].material[j].quantity;
            }
            if(products->counter != 0) {
                products->counter--;
            }
        } else {
            count++;
            continue;
        }
    }
    if (count == products->counter && products->counter != 0) {
        printf(MSG_ERROR_MESSAGE);
    }
    printf("%d", products->counter);
}

void listProductMaterials(Products *products, int pos) {
    int i;
    for (i = 0; i < products->product[pos].material_count; i++) {
        printf("%d - %s, %s, %hu, %d\n", (i + 1), products->product[pos].material[i].cod_Material,
               products->product[pos].material[i].description,
               products->product[pos].material[i].quantity,
               products->product[pos].material[i].unit);
    }
}

int findMaterialPosition(Products *products, char code[COD_MATERIAL_SIZE], int productPosition) {
    int i,  count = 0;
    for (i = 0;i<products->product[productPosition].material_count; i++){
        printf("\n%s\n%s\n",products->product[productPosition].material[i].cod_Material,
               code);
        if (strcmp(code, products->product[productPosition].material[i].cod_Material) == 0){
            return i;
        }else{
            count++;
            continue;
        }
    }
    if (count == products->product[productPosition].material_count)
        return -1;
}
void saveMaterialChanges(Products *products, int productPosition, int materialPos, Materials editedMaterial){
    strcpy(products->product[productPosition].material[materialPos].description, editedMaterial.description);
    products->product[productPosition].material[materialPos].unit = editedMaterial.unit;
    products->product[productPosition].material[materialPos].quantity = editedMaterial.quantity;
}
void deleteMaterial(Products *products, int productPosition, int materialPosition, Materials material){
    int i;
    for(i = 0; i < products->product[productPosition].material_count; i++) {
        if (strcmp(products->product[productPosition].material[i].cod_Material, material.cod_Material) == 0) {
            strcpy(products->product[productPosition].material[i].cod_Material,
                   products->product[productPosition].material[i + 1].cod_Material);
            strcpy(products->product[productPosition].material[i].description,
                   products->product[productPosition].material[i + 1].description);
            products->product[productPosition].material[i].unit = products->product[productPosition].material[i + 1].unit;
            products->product[productPosition].material[i].quantity = products->product[productPosition].material[i + 1].quantity;
        }
    }
    products->product[productPosition].material_count--;
    printf("%d", products->product[productPosition].material_count);
}
void materialEditMenu(Products *products, int pos) {
    int materialPosition, option;
    Materials material;
    listProductMaterials(products, pos);
    printf(ASK_MATERIAL_CODE);
    scanf("%s", material.cod_Material);
    materialPosition = findMaterialPosition(products, material.cod_Material, pos);
    if (materialPosition == -1){
        printf(MSG_ERROR_MESSAGE);
    }else {
        material.unit = products->product[pos].material[materialPosition].unit;
        strcpy(material.description, products->product[pos].material[materialPosition].description);
        material.quantity = products->product[pos].material[materialPosition].quantity;
        strcpy(material.cod_Material, products->product[pos].material[materialPosition].cod_Material);

        do {
            printf("Changing %s...\n", material.description);
            option = menuRead(MSG_CHANGE_PRODUCT_MATERIAL_DATA, 0, 4);
            switch (option) {
                case 0:
                    break;
                case 1:
                    printf("\n\t\t\tPrevious - %hu", material.unit);
                    materialUnit(&material.unit);
                    system("cls || clear");
                    break;
                case 2:
                    printf("\n\t\t\tPrevious - %s", material.description);
                    materialDescription(material.description);
                    system("cls || clear");
                    break;
                case 3:
                    printf("\n\t\t\tPrevious - %d", material.quantity);
                    materialQuantity(&material.quantity);
                    system("cls || clear");
                    break;
                case 4:
                    deleteMaterial(products, pos, materialPosition, material);
                    system("cls || clear");
                    option = 0;
                    break;
            }
        }while(option != 0);
        saveMaterialChanges(products, pos, materialPosition, material);
    }
}

void saveProductChanges(char name[MAX_PRODUCT_NAME_SIZE], double price,
                        Dimensions dimensions, Products *products,
                        int pos) {
    strcpy(products->product[pos].name, name);
    products->product[pos].dimension = dimensions;
    products->product[pos].price = price;

}

void changeProductData(Products *products, int pos, char code[COD_PRODUCT_SIZE]) {
    int option, nif;
    char name[MAX_PRODUCT_NAME_SIZE];
    double price;
    Dimensions dimension;
    strcpy(name, products->product[pos].name);
    price = products->product[pos].price;
    dimension.height = products->product[pos].dimension.height;
    dimension.width = products->product[pos].dimension.width;
    dimension.lenght = products->product[pos].dimension.lenght;
    do {
        option = menuRead(MSG_CHANGE_PRODUCT_DATA, 0, 4);
        switch (option) {
            case 0:
                break;
            case 1:
                //change product name
                printf("\n\t\t\tPrevious - %s", name);
                productName(name);
                system("cls || clear");
                break;
            case 2:
                //change product price
                printf("\n\t\t\tPrevious - %.2lf", price);
                productPrice(&price);
                system("cls || clear");
                break;
            case 3:
                //change product dimension
                printf("\n\t\t\tPrevious - %dx%dx%d", dimension.lenght,
                       dimension.width,
                       dimension.height);
                productDimension(&dimension);
                system("cls || clear");
                break;
            case 4:
                materialEditMenu(products, pos);
                break;
        }
    } while (option != 0);

    saveProductChanges(name, price, dimension, products, pos);
}

void editProducts(Products *products) {
    int i, count = 0;
    char code[COD_PRODUCT_SIZE];

    printf(ASK_PRODUCT_CODE);
    scanf(" %s", code);
    for (i = 0; i < products->counter; i++) {
        if (strcmp(code, products->product[i].cod_Produto) == 0) {
            changeProductData(*(&products), i, code);
        } else {
            count++;
            continue;
        }
    }
    if (count == products->counter) {
        printf(MSG_ERROR_MESSAGE);
    }
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
        products->product[k + i].material = (Materials *) malloc(
                sizeof(Materials) * products->product[k + i].material_count);
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
void listProducts(Products *product) {
    int i, j;
    printf("Product list.\n");
    for (i = 0; i < product->counter; i++) {
        printf("%s, %s, %.2lf, %dx%dx%d\n",
               product->product[i].cod_Produto,
               product->product[i].name,
               product->product[i].price,
               product->product[i].dimension.height,
               product->product[i].dimension.width,
               product->product[i].dimension.lenght);
        for (j = 0; j < product->product[i].material_count; j++) {
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
                editProducts(products);
                break;
            case 5:
                deleteProducts(products);
                break;
            case 6:
                listProducts(products);
                break;
        }
    } while (option != 0);
}