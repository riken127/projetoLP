//
// Created by r1ken on 12-12-2022.
//

#ifndef PROJETO_PRODUCTS_H
#define PROJETO_PRODUCTS_H
#include <stdbool.h>

#define MAX_MATERIALS 20
#define MAX_QUANTITY 20

#define MSG_PRODUCTS_MANAGEMENT_MENU "[1] - Create Material.\n[2] - Edit Materials.\n[3] - List Materials.\n" \
                                     "[4] - New Product.\n[5] - Edit Product.\n[6] - List Products.\n" \
                                     "[7] - Load Products & Materials.\n[8] - Save Products & Materials.\n[0] - Exit.\n"
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
    units unit;
} Material;
typedef struct {
    char code[COD_MATERIAL_SIZE];
    short int quantity;
} LineProduct;
typedef struct {
    char cod_Produto[COD_PRODUCT_SIZE];
    char name[MAX_PRODUCT_NAME_SIZE];
    double price;
    Dimensions dimension;
    LineProduct  *line_product;
    int line_product_size;
} Product;
typedef struct {
    Product *product;
    int counter;
}Products;
typedef struct{
    Material *material;
    int counter;
}Materials;
/*
 * Product functions definition
 */
void materialCode(char materialCode[COD_MATERIAL_SIZE]);//
void materialDescription(char materialDescription[MAX_DESCRIPTION_SIZE]);//
void materialUnit(units *materialUnit);//
void createMaterial(Materials *material);//
void productCode(char productCode[COD_PRODUCT_SIZE]);//
void productName(char productName[MAX_PRODUCT_NAME_SIZE]);//
void productDimension(Dimensions *productDimension);//
void productPrice(double *price);//
void listMaterial(Materials *material);
int verifyCode(char code[COD_MATERIAL_SIZE], Materials *material);
void newProduct(Products *product, Materials *material);//
void listProduct(Products *product);
void saveProductMaterials(Products *products, Materials *material);//
void loadProductMaterials(Products *product, Materials *material);
int findMaterialPosition(Materials *material, char code[COD_MATERIAL_SIZE]);//
void saveMaterialChanges(Materials *material, int position, Material current);//
void deleteMaterial(char code[COD_MATERIAL_SIZE], Materials *material, Products *product);//
void editMaterial(Materials *material, Products *product);
void saveProductChanges(Product product, Products *products, int pos);//
void deleteProduct(Products *product, char code[COD_PRODUCT_SIZE]);
void addMaterialLineProduct(Materials *material, Products *product, int position);
void changeProductData(Products *products, int pos, char code[COD_PRODUCT_SIZE], Materials *material);
void editProduct(Materials *material, Products *products);//
int menuRead(char message[], int min, int max);
void productsManagementMenu(Products *products, Materials *material);
#endif //PROJETO_PRODUCTS_H
