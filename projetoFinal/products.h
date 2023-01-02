//
// Created by r1ken on 12-12-2022.
//

#ifndef PROJETO_PRODUCTS_H
#define PROJETO_PRODUCTS_H

#define MAX_MATERIALS 20
#define MAX_QUANTITY 20

#define COD_MATERIAL_SIZE 6
#define COD_PRODUCT_SIZE 7

#define MAX_DESCRIPTION_SIZE 100
#define MAX_PRODUCT_NAME_SIZE 100
typedef enum {UN, PAR}units;

typedef struct {
    int lenght, height, width;
} Dimensions;
typedef struct {
    char cod_Material[COD_MATERIAL_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    short int quantity;
    units unit;
} Materials;
typedef struct {
    char cod_Produto[COD_PRODUCT_SIZE];
    char name[MAX_PRODUCT_NAME_SIZE];
    double price;
    Dimensions dimension;
    Materials* material;
    int material_count;
} Product;
typedef struct {
    Product *product;
    int counter;
}Products;
int menuRead(char message[], int min, int max);
void productsManagementMenu(Products *products);
#endif //PROJETO_PRODUCTS_H
