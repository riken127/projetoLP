//
// Created by r1ken on 12-12-2022.
//

#ifndef PROJETO_PRODUCTS_H
#define PROJETO_PRODUCTS_H
#include <stdbool.h>

#define MAX_MATERIALS 20
#define MAX_QUANTITY 20

#define MSG_PRODUCTS_MANAGEMENT_MENU "[1] - Save.\n[2] - Load.\n[3] - Create.\n[4] - Edit.\n[5] - Delete.\n[6] - List.\n"

#define COD_MATERIAL_SIZE 6
#define COD_PRODUCT_SIZE 7

#define MAX_DESCRIPTION_SIZE 100
#define MAX_PRODUCT_NAME_SIZE 100

#define ASK_PRODUCT_CODE "Product's code - "

#define ASK_PRODUCT_NAME "Product's name - "

#define ASK_PRODUCT_DIMENSION "Product's dimension (#x#x#) - "

#define ASK_PRODUCT_PRICE "Product's price - "

#define ASK_MATERIAL_CODE "Material's code - "

#define ASK_MATERIAL_DESCRIPTION "Material's description - "

#define ASK_MATERIAL_QUANTITY "Material's quantity - "

#define ASK_MATERIAL_UNIT "Material's unit - "

#define ASK_ANOTHER_MATERIAL "Would you like to type another material?[1/0]\n"

#define MSG_CHANGE_PRODUCT_DATA "[1] - Name.\n[2] - Price.\n[3] - Dimension.\n[4] - Materials.\n"
#define MSG_CHANGE_PRODUCT_MATERIAL_DATA "[1] - Unit.\n[2] - Description.\n[3] - Quantity.\n[4] - Delete.\n[0] - Exit.\n"

#define MSG_DELETE_PRODUCT "Are you sure?[Y/n]"

#define INITIAL_PRODUCT_SIZE 1
#define INITIAL_MATERIAL_SIZE 1

#define ERROR_READING "ERROR READING FROM FILE\n"
#define SUCCESS_READING "DATA READ OK.\n"

#define ERROR_WRITING "ERROR WRITING IN FILE\n"
#define SUCCESS_WRITING "WRITE DATA OK.\n"
/*
 * Product struct definition
 */
typedef enum {UN, PAR} units;

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
/*
 * Product functions definition
 */
void productCode(char productCode[COD_PRODUCT_SIZE]);
void productName(char productName[MAX_PRODUCT_NAME_SIZE]);
void productDimension(Dimensions *productDimension);
void productPrice(double *price);
void materialCode(char materialCode[COD_MATERIAL_SIZE]);
void materialDescription(char materialDescription[MAX_DESCRIPTION_SIZE]);
void materialQuantity(short int *materialQuantity);
void materialUnit(units *materialUnit);
bool newMaterial();
void newProduct(Products *product);
void saveProducts(Products *products);
void deleteProducts(Products *products);
void listProductMaterials(Products *products, int pos);
int findMaterialPosition(Products *products, char code[COD_MATERIAL_SIZE], int productPosition);
void saveMaterialChanges(Products *products, int productPosition, int materialPos,
                         Materials editedMaterial);
void deleteMaterial(Products *products, int productPosition, int materialPosition, Materials material);

void materialEditMenu(Products *products, int pos);
void saveProductChanges(char name[MAX_PRODUCT_NAME_SIZE], double price,
                        Dimensions dimensions, Products *products, int pos);
void changeProductData(Products *products, int pos, char code[COD_PRODUCT_SIZE]);
void editProducts(Products *products);
void loadProducts(Products *products);
void listProducts(Products *product);
int menuRead(char message[], int min, int max);
void productsManagementMenu(Products *products);
#endif //PROJETO_PRODUCTS_H
