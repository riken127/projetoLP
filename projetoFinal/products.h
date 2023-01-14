//
// Created by r1ken on 12-12-2022.
//

#ifndef PROJETO_PRODUCTS_H
#define PROJETO_PRODUCTS_H
#include <stdbool.h>

#define MAX_MATERIALS 20
#define MAX_QUANTITY 20
//macro definition
#define MSG_PRODUCTS_MATERIALS_MANAGEMENT_MENU "\n\t\t\t========= Products & Materials Management Menu =========\n\n\t\t\t[1] - Products.\n\t\t\t[2] - Materials.\n\t\t\t" \
                                     "[3] - Import Products & Materials.\n\t\t\t[4] - Export Products & Materials.\n\t\t\t[0] - Quit.\n\t\t\t________________________________________________________"

#define MSG_PRODUCTS_MANAGEMENT_MENU "\n\t\t\t========= Products Management Menu =========\n\n\t\t\t[1] - Create.\n\t\t\t[2] - Edit.\n\t\t\t" \
                                     "[3] - List.\n\t\t\t[0] - Quit.\n\t\t\t____________________________________________"


#define MSG_MATERIALS_MANAGEMENT_MENU "\n\t\t\t========= Materials Management Menu =========\n\n\t\t\t[1] - Create.\n\t\t\t[2] - Edit.\n\t\t\t" \
                                     "[3] - List.\n\t\t\t[0] - Quit.\n\t\t\t_____________________________________________"

#define NO_MATERIAL_FOUND_MESSAGE "\n\t\t\t========== ERROR MESSAGE ==========\n\n\t\t\tNo materials were found\n\t\t\t___________________________________"


#define NO_PRODUCTS_FOUND_MESSAGE "\n\t\t\t========== ERROR MESSAGE ==========\n\n\t\t\tNo products were found\n\t\t\t___________________________________"

#define YES_OR_NO_MESSAGE_RECORD_MATERIAL "\t\t\tDo you want to add another material?[y/n] - "

#define YES_OR_NO_MESSAGE_RECORD_PRODUCT "\t\t\tDo you want to add another product?[y/n] - "

#define COD_MATERIAL_SIZE 6
#define COD_PRODUCT_SIZE 7

#define MAX_DESCRIPTION_SIZE 100
#define MAX_PRODUCT_NAME_SIZE 100

#define ASK_PRODUCT_CODE "\t\t\tProduct code - "

#define ASK_PRODUCT_NAME "\t\t\tProduct name - "

#define ASK_PRODUCT_DIMENSION "\n\t\t\tProduct dimension (#x#x#) - "

#define ASK_PRODUCT_PRICE "\t\t\tProduct price - "

#define ASK_MATERIAL_CODE "\t\t\tMaterial code - "

#define ASK_MATERIAL_DESCRIPTION "\t\t\tMaterial description - "

#define ASK_MATERIAL_QUANTITY "\t\t\tMaterial quantity - "

#define ASK_MATERIAL_UNIT "\t\t\tMaterial unit [1|0] - "

#define ASK_ANOTHER_MATERIAL "Would you like to type another material?[y/n]\n"

#define MSG_CHANGE_PRODUCT_DATA "\n\t\t\t[1] - Name.\n\t\t\t[2] - Price.\n\t\t\t[3] - Dimension.\n\t\t\t[4] - Delete\n\t\t\t[5] - Materials.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________"
#define MSG_CHANGE_PRODUCT_MATERIAL_DATA "\n\t\t\t[1] - Unit.\n\t\t\t[2] - Description.\n\t\t\t[3] - Delete.\n\t\t\t[0] - Quit.\n\t\t\t__________________________________"

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
void materialManagementMenu(Products *products, Materials *material);
void ProductsMaterialsManagementMenu(Products *products, Materials *material);
#endif //PROJETO_PRODUCTS_H
