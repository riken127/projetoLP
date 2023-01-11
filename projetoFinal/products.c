//
// Created by gui on 12-12-2022.
//

#include "products.h"
#include "orders.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void materialUnit(units *materialUnit) {
    printf(ASK_MATERIAL_UNIT);
    do{
        scanf("%u", materialUnit);
    }while(*materialUnit < 0 || *materialUnit > 1);
}

void createMaterial(Materials *material){
    int c;
    do{
        material->material = (Material *)realloc(material->material, sizeof(Material)*(material->counter + 1));

        materialCode(material->material[material->counter].cod_Material);
        materialDescription(material->material[material->counter].description);
        materialUnit(&material->material[material->counter].unit);

        material->counter++;

        printf(ASK_ANOTHER_MATERIAL);
        scanf("%d", &c);
    }while(c != 0);
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

void listMaterial(Materials *material){
    int i;
    for (i = 0; i < material->counter; i++){
        printf("%s, %s, %d\n", material->material[i].cod_Material,
               material->material[i].description,
               material->material[i].unit);
    }
}
int verifyCode(char code[COD_MATERIAL_SIZE], Materials *material){
    int i;
    for (i = 0; i < material->counter; i++){
        if (strcmp(code, material->material[i].cod_Material) == 0){
            return 1;
        }
    }

    return 0;
}

void newProduct(Products *product, Materials *material){
    int i, op, quantity;
    char code[COD_PRODUCT_SIZE];
    printf("%d", (product->counter + 1));
    product->product = (Product *)realloc(product->product, sizeof(Product)*(product->counter + 1));

    productCode(product->product[product->counter].cod_Produto);
    productName(product->product[product->counter].name);
    productPrice(&product->product[product->counter].price);
    productDimension(&product->product[product->counter].dimension);
    i = 0;
    product->product[product->counter].line_product = (LineProduct *)malloc(sizeof(LineProduct) * 1);
    do{
        product->product[product->counter].line_product = (LineProduct *)realloc(product->product[product->counter].line_product,
                                                                                 sizeof(LineProduct) * (i + 1));
        listMaterial(material);
        printf(ASK_MATERIAL_CODE);
        scanf("%s", code);
        if (verifyCode(code, material)){
            strcpy(product->product[product->counter].line_product[i].code, code);
            printf(ASK_MATERIAL_QUANTITY);
            scanf("%d", &quantity);
            if (quantity > 0){
                product->product[product->counter].line_product[i].quantity = quantity;
            }
            ++i;
        }else{
            printf("Written material code does not exist.\n");
        }

        product->product[product->counter].line_product_size = i;
        printf("Do you wish to add another material?");
        scanf("%d", &op);
    }while(op != 0);
    product->counter++;
}
void listProduct(Products *product){
    int i, j;
    for (i = 0; i < product->counter; i++){
        printf("::\t%s, %s, %.2lf, %dx%dx%d\n", product->product[i].cod_Produto,
               product->product[i].name,
               product->product[i].price,
               product->product[i].dimension.height,
               product->product[i].dimension.lenght,
               product->product[i].dimension.width);
        for (j = 0; j < product->product[i].line_product_size; j++){
            printf("\t%s, %d\n", product->product[i].line_product[j].code,
                   product->product[i].line_product[j].quantity);
        }

    }
}
void saveProductMaterials(Products *product, Materials *material){
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "w+");
    if (fp == NULL){
        printf("An erro has occured!");
        exit(EXIT_FAILURE);
    }
    fwrite(&product->counter, sizeof(int), 1, fp);
    i = 0;
    do{
        fwrite(&product->product[i].cod_Produto, sizeof(char)*COD_PRODUCT_SIZE, 1, fp);
        fwrite(&product->product[i].name, sizeof(char)*MAX_PRODUCT_NAME_SIZE, 1, fp);
        fwrite(&product->product[i].price, sizeof(double), 1, fp);
        fwrite(&product->product[i].dimension.height, sizeof(int), 1, fp);
        fwrite(&product->product[i].dimension.lenght, sizeof(int), 1, fp);
        fwrite(&product->product[i].dimension.width, sizeof(int), 1, fp);
        i++;
    }while(i < product->counter);

    for (i = 0; i < product->counter; i++){
        j = 0;
        fwrite(&product->product[i].line_product_size, sizeof(int), 1, fp);
        do{
            fwrite(&product->product[i].line_product[j].code, sizeof(char)*COD_MATERIAL_SIZE, 1, fp);
            fwrite(&product->product[i].line_product[j].quantity, sizeof(int), 1, fp);
            j++;
        }while(j < product->product[i].line_product_size);
    }
    fwrite(&material->counter, sizeof(int), 1, fp);
    for (i = 0; i < material->counter; i++){
        fwrite(&material->material[i].cod_Material, sizeof(char)*COD_MATERIAL_SIZE, 1, fp);
        fwrite(&material->material[i].description, sizeof(char)*MAX_DESCRIPTION_SIZE, 1, fp);
        fwrite(&material->material[i].unit, sizeof(units), 1, fp);
    }
    fclose(fp);
    printf("\nSUCCESS!");
}
void loadProductMaterials(Products *product, Materials *material){
    FILE *fp;
    int i, j, c, k;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "rb+");
    if (fp == NULL){
        printf("An erro has occured!");
        exit(EXIT_FAILURE);
    }
    fread(&c, sizeof(int), 1, fp);
    k = product->counter;
    for (i = 0; i < c; i++){
        product->product = (Product *)realloc(product->product,
                                              (product->counter + 1)*sizeof(Product));
        fread(&product->product[product->counter].cod_Produto, sizeof(char)*COD_PRODUCT_SIZE, 1, fp);
        fread(&product->product[product->counter].name, sizeof(char)*MAX_PRODUCT_NAME_SIZE, 1, fp);
        fread(&product->product[product->counter].price, sizeof(double), 1, fp);
        fread(&product->product[product->counter].dimension.height, sizeof(int), 1, fp);
        fread(&product->product[product->counter].dimension.lenght, sizeof(int), 1, fp);
        fread(&product->product[product->counter].dimension.width, sizeof(int), 1, fp);
        product->counter++;
    }
    printf("%d", product->counter);
    for (i = 0; i < c; i++){
        fread(&product->product[k + i].line_product_size, sizeof(int), 1, fp);
        printf("%d", product->product[k + i].line_product_size);
        product->product[k + i].line_product = (LineProduct *) malloc(
                sizeof(LineProduct) * product->product[k + i].line_product_size);
        for (j = 0; j < product->product[k + i].line_product_size; j++){
            fread(&product->product[k + i].line_product[j].code, sizeof(char)*COD_MATERIAL_SIZE, 1, fp);
            fread(&product->product[k + i].line_product[j].quantity, sizeof(int), 1, fp);
        }
    }

    fread(&c, sizeof(int), 1, fp);
    k = material->counter;
    for (i = 0; i < c; i++){
        material->material = (Material *)realloc(material->material,
                                                 (material->counter + 1)*sizeof(Material));
        fread(&material->material[k + i].cod_Material, sizeof(char)*COD_MATERIAL_SIZE, 1, fp);
        fread(&material->material[k + i].description, sizeof(char)*MAX_DESCRIPTION_SIZE, 1, fp);
        fread(&material->material[k + i].unit, sizeof(int), 1, fp);
        material->counter++;
    }
    fclose(fp);
}
int findMaterialPosition(Materials *material, char code[COD_MATERIAL_SIZE]) {
    int i,  count = 0;
    for (i = 0;i<material->counter; i++){
        if (strcmp(code, material->material[i].cod_Material) == 0){
            return i;
        }else{
            count++;
        }
    }
    if (count == material->counter) {
        return -1;
    }
}
void saveMaterialChanges(Materials *material, int  position, Material current){
    strcpy(material->material[position].cod_Material, current.cod_Material);
    strcpy(material->material[position].description, current.description);
    material->material[position].unit =  current.unit;
}
void deleteMaterial(char code[COD_MATERIAL_SIZE], Materials *material, Products *product){
    int i, j;
    for (i = 0; i < material->counter; i++){
        //printf("%s", material->material[i].cod_Material);
        if(strcmp(material->material[i].cod_Material, code) == 0){
            strcpy(material->material[i].cod_Material,
                   material->material[i + 1].cod_Material);
            strcpy(material->material[i].description,
                   material->material[i + 1].description);
            material->material[i].unit = material->material[i + 1].unit;
        }
    }
    material->counter--;
    for (i = 0; i < product->counter; i++){
        for (j = 0; j < product->product[i].line_product_size; j++){
            printf("\n%s, %s", product->product[i].line_product[j].code,
                   code);
            if (strcmp(product->product[i].line_product[j].code,
                       code) == 0){
                strcpy(product->product[i].line_product[j].code,
                       product->product[i].line_product[j + 1].code);
                product->product[i].line_product[j].quantity = product->product[i].line_product[j + 1].quantity;
                product->product[i].line_product_size--;
            }
        }
    }
}
void editMaterial(Materials *material, Products *product){
    char editedMaterial[COD_MATERIAL_SIZE];
    int position, option, i;
    Material current;
    printf("Select the material you want to edit\n");
    for (i = 0; i < material->counter; i++){
        printf("%s, %s, %d\n",
               material->material[i].cod_Material,
               material->material[i].description,
               material->material[i].unit);
    }

    scanf("%s", editedMaterial);
    position = findMaterialPosition(material, editedMaterial);
    printf("%d", position);
    if (position == -1){
        printf("\nERROR\n");
    }else{
        strcpy(current.cod_Material ,material->material[position].cod_Material);
        strcpy(current.description ,material->material[position].description);
        current.unit = material->material[position].unit;
        do{
            printf("Changing %s...\n", current.description);
            option = menuRead(MSG_CHANGE_PRODUCT_MATERIAL_DATA, 0, 4);
            switch (option) {
                case 0:
                    break;
                case 1:
                    printf("\n\t\t\tPrevious - %hu", current.unit);
                    materialUnit(&current.unit);
                    system("cls || clear");
                    break;
                case 2:
                    printf("\n\t\t\tPrevious - %s", current.description);
                    materialDescription(current.description);
                    system("cls || clear");
                    break;
                case 3:
                    printf("\n\t\t\tPrevious - %s", current.cod_Material);
                    materialCode(current.cod_Material);
                    system("cls || clear");
                    break;
                case 4:
                    deleteMaterial(editedMaterial, material, product);
                    option = 0;
                    break;
            }
        } while(option != 0);
        saveMaterialChanges(material, position, current);
    }
}
void saveProductChanges(Product product, Products *products, int pos){
    strcpy(products->product[pos].name , product.name);
    products->product[pos].price = product.price;
    products->product[pos].dimension = product.dimension;
}
void deleteProduct(Products *product, char code[COD_PRODUCT_SIZE]){
    int i, j;

    for (i = 0; i < product->counter; i++){
        if (strcmp(product->product[i].cod_Produto, code) == 0){
            strcpy(product->product[i].cod_Produto,
                   product->product[i + 1].cod_Produto);
            strcpy(product->product[i].name,
                   product->product[i + 1].name);
            product->product[i].price = product->product[i + 1].price;
            product->product[i].dimension = product->product[i + 1].dimension;
            product->product[i].line_product_size = product->product[i + 1].line_product_size;
            product->product[i].line_product = (LineProduct *)realloc(product->product[i].line_product, sizeof(LineProduct) * product->product[i + 1].line_product_size);
            for (j = 0; j < product->product[i + 1].line_product_size; j++){
                strcpy(product->product[i].line_product[j].code, product->product[i + 1].line_product[j].code);
                product->product[i].line_product[j].quantity = product->product[i + 1].line_product[j].quantity;
            }
        }
    }
    product->counter--;
    printf("PRODUCT DELETED SUCCESSFULLY");
}
void addMaterialLineProduct(Materials *material, Products *product, int position){
    LineProduct line;
    int i, op;
    i = product->product[position].line_product_size;
    do{
        product->product[position].line_product = (LineProduct *)realloc(product->product[position].line_product,
                                                                         sizeof(LineProduct) * (i + 1));
        listMaterial(material);
        printf(ASK_MATERIAL_CODE);
        scanf("%s", line.code);
        if (verifyCode(line.code, material)){
            strcpy(product->product[position].line_product[i].code, line.code);
            printf(ASK_MATERIAL_QUANTITY);
            scanf("%hu", &line.quantity);
            if (line.quantity > 0){
                product->product[position].line_product[i].quantity = line.quantity;
            }
            ++i;
        }else{
            printf("Written material code does not exist.\n");
        }

        product->product[product->counter].line_product_size = i;
        printf("Do you wish to add another material?");
        scanf("%d", &op);
    }while(op != 0);
    product->product[position].line_product_size = i;
    printf("%d", product->product[position].line_product_size);
}
void changeProductData(Products *products, int pos, char code[COD_PRODUCT_SIZE], Materials *material) {
    int option;
    Product product;
    strcpy(product.name, products->product[pos].name);
    product.price = products->product[pos].price;
    product.dimension.height = products->product[pos].dimension.height;
    product.dimension.width = products->product[pos].dimension.width;
    product.dimension.lenght = products->product[pos].dimension.lenght;
    do {
        option = menuRead(MSG_CHANGE_PRODUCT_DATA, 0, 5);
        switch (option) {
            case 0:
                break;
            case 1:
                //change product name
                printf("\n\t\t\tPrevious - %s", product.name);
                productName(product.name);
                system("cls || clear");
                break;
            case 2:
                //change product price
                printf("\n\t\t\tPrevious - %.2lf", product.price);
                productPrice(&product.price);
                system("cls || clear");
                break;
            case 3:
                //change product dimension
                printf("\n\t\t\tPrevious - %dx%dx%d", product.dimension.lenght,
                       product.dimension.width,
                       product.dimension.height);
                productDimension(&product.dimension);
                system("cls || clear");
                break;
            case 4:
                deleteProduct(products, code);
                option = 0;
                break;
            case 5:
                addMaterialLineProduct(material, products, pos);
                break;
        }
    } while (option != 0);

    saveProductChanges(product, products, pos);
}
void editProduct(Materials *material, Products *product){
    int i, count = 0;
    char code[COD_PRODUCT_SIZE];
    for (i = 0; i < product->counter; i++){
        printf("%s, %s, %.2lf, %dx%dx%d\n",
               product->product[i].cod_Produto,
               product->product[i].name,
               product->product[i].price,
               product->product[i].dimension.height,
               product->product[i].dimension.lenght,
               product->product[i].dimension.width);
    }
    productCode(code);
    for (i = 0; i < product->counter; i++){
        if (strcmp(code, product->product[i].cod_Produto) == 0){
            changeProductData(product, i, code, material);
        }else {
            count++;
            continue;
        }
    }
    if (count == product->counter) {
        printf("ERROR");
    }
}
void productsManagementMenu(Products *products, Materials *material) {
    int option;
/*
    products->product->material = malloc(11 * sizeof(Materials));
    for (int i = 0; i < 2; i++) {
        products->product[i].material = malloc(2 * sizeof(Materials));
    }*/


    do {
        option = menuRead(MSG_PRODUCTS_MANAGEMENT_MENU, 0, 8);

        switch (option) {
            default:
                break;
            case 1:
                createMaterial(material);
                break;
            case 2:
                editMaterial(material, products);
                break;
            case 3:
                listMaterial(material);
                break;
            case 4:
                newProduct(products, material);
                break;
            case 5:
                editProduct(material, products);
                break;
            case 6:
                listProduct(products);
                break;
            case 7:
                loadProductMaterials(products, material);
                break;
            case 8:
                saveProductMaterials(products, material);
                break;
            case 0:
                break;
        }
    } while (option != 0);
}