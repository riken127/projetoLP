//
// Created by r1ken on 12-12-2022.
//

#ifndef PROJETO_PRODUCTS_H
#define PROJETO_PRODUCTS_H
#define MAX_MATERIALS 20
#define MAX_QUANTITY 20

typedef struct {
    int cod_Produto;
    char designition[20];
    int price;
    int cod_Material[MAX_MATERIALS];
    int quantity[MAX_QUANTITY];
} Products;

typedef struct {
    int cod_Material;
    char description[20];
} Materials;

int menuRead(char message[], int min, int max);
void productsManagementMenu();
#endif //PROJETO_PRODUCTS_H
