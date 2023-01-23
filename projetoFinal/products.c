//
// Created by gui on 12-12-2022.
//
#include "products.h"
#include "clients.h"
#include "orders.h"
#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * The bellow function gets the material's code as a parameter
 * and asks the user to type a material code, the first scan makes
 * sure that nothing will interfere with the buffer, so that
 * no camps are skipped or something of the sort.
 * @param materialCode material code
 */
void materialCode(char materialCode[COD_MATERIAL_SIZE]) {
    char temp;
    printf("\n"ASK_MATERIAL_CODE);
    scanf("%c", &temp);
    scanf("%[^\n]", materialCode);
}

/**
 * The bellow function gets the material's description as a parameter
 * and asks the user to type a material description, the first scan makes
 * sure that nothing will interfere with the buffer, so that
 * no camps are skipped or something of the sort, the second scan makes
 * sure that spaces in a description won't make so that the program skips future
 * camps.
 * @param materialDescription material description
 */
void materialDescription(char materialDescription[MAX_DESCRIPTION_SIZE]) {
    char temp;
    printf("\n"ASK_MATERIAL_DESCRIPTION);
    scanf("%c", &temp);
    scanf("%[^\n]", materialDescription);
}

/**
 * The bellow function gets the material's unit, which is an enum
 * that can store two values (either UN or PAR), it receives the enum as pointer.
 * @param materialUnit material's unit
 */
void materialUnit(units *materialUnit) {
    printf("\n"ASK_MATERIAL_UNIT);
    do {
        scanf("%u", materialUnit);
    } while (*materialUnit < 0 || *materialUnit > 1);
}

/**
 * The bellow function creates a new material, it receives the material struct as a parameter
 * then reallocates the struct with one more position, and asks the user to fill the material data
 * tru other functions (materialCOde, materialDescription, materialUnit). Then starts a loop
 * so that the user can type the materials, while the option the user chooses is different from false
 * the loop continues and the space for the materials is reallocated..
 * @param material Pointer o the material struct
 */
void createMaterial(Materials *material) {
    int option = 1;
    do {
        material->material = (Material *) realloc(material->material, sizeof (Material)*(material->counter + 1));
        printf("\t\t\t__________________________________\n");
        materialCode(material->material[material->counter].cod_Material);
        materialDescription(material->material[material->counter].description);
        materialUnit(&material->material[material->counter].unit);
        printf("\t\t\t__________________________________\n");
        material->counter++;

        option = yesOrNoFunction(YES_OR_NO_MESSAGE_RECORD);
        system("cls || clear");
    } while (option != 2);
}

/**
 * The bellow function gets the product code as a parameter
 * and asks the user to type a product id, the first scan makes
 * sure that nothing will interfere with the buffer, so that no camps
 * are skipped or something of the sort.
 * @param productCode product's code
 */
void productCode(char productCode[COD_PRODUCT_SIZE]) {
    char temp;
    printf("\n"ASK_PRODUCT_CODE);
    scanf("%c", &temp);
    scanf("%[^\n]", productCode);
}
/**
 * The bellow function gets the product name as a parameter
 * and asks the user to type a product name, the first scan makes
 * sure that nothing will interfere with the buffer, so that no camps
 * are skipped or something of the sort. The second scan retrieves data
 * until an enter is found, so that no camps are skipped because of an enter.
 * @param productName product's name
 */
void productName(char productName[MAX_PRODUCT_NAME_SIZE]) {
    char temp;
    printf("\n"ASK_PRODUCT_NAME);
    scanf("%c", &temp);
    scanf("%[^\n]", productName);
}

/**
 * The bellow function gets the product's dimension as a pointer,
 * the product's dimension is a struct, which in composed by three integer
 * values, the height, the width, and the length. The values are scanned between
 * x's, this makes so that the user can type all the dimensions at once, and
 * makes sure that the program ignores them.
 * @param productDimension product's dimension
 */
void productDimension(Dimensions *productDimension) {
    printf(ASK_PRODUCT_DIMENSION);
    scanf("%dx%dx%d", &productDimension->lenght,
            &productDimension->height,
            &productDimension->width);
}

/**
 * The bellow function gets the product's price as a pointer.
 * @param price product's price
 */
void productPrice(double *price) {
    printf("\n"ASK_PRODUCT_PRICE);
    scanf("%lf", price);
}

/**
 * The bellow function lists all the materials information
 * @param material pointer to the material struct
 */
void listMaterial(Materials *material) {
    int i;
    if (material->counter == 0) {
        printf("\n\t\t\tNo materials were found\n\t\t\t__________________________________");
    } else {
        printf("\n\t\t\tList Of Materials\n\t\t\t__________________________________");
        for (i = 0; i < material->counter; i++) {
            printf("\n\n\t\t\tMaterial Id      : %s", material->material[i].cod_Material);
            printf("\n\t\t\tDescription      : %s", material->material[i].description);
            printf("\n\t\t\tUnit             : %d", material->material[i].unit);
            printf("\n\t\t\t__________________________________");
        }
    }
    pressAnyKeyToContinueFunctionListVersion();
}

/**
 * The bellow function verifies is the given code is already present in the material struct,
 * if so, it returns 1, if not, it returns 0.
 * @param code material's code
 * @param material pointer to the material's struct
 * @return return 1 if the material code exists and 0 if it does not.
 */
int verifyCode(char code[COD_MATERIAL_SIZE], Materials *material) {
    int i;
    for (i = 0; i < material->counter; i++) {
        if (strcmp(code, material->material[i].cod_Material) == 0) {
            return 1;
        }
    }

    return 0;
}

/**
 * The bellow function creates a new product, it receives the product struct as a parameter and the material struct
 * then reallocates the struct with one more position, and asks the user to fill the product data
 * tru other functions (productCode, productName, productDimension and productPrices). Then starts a loop
 * so that the user can type the materials, while the option the user chooses is different from false
 * the loop continues and the space for the materials is reallocated, at the end the
 * line_product value is given, which is equal to the loop variable.
 * @param product pointer to the product struct
 * @param material pointer to the material struct
 */
void newProduct(Products *product, Materials *material) {
    int i, opProduct, opMaterial, quantity;
    char code[COD_PRODUCT_SIZE];

    if (material->counter != 0) {
        do {
            product->product = (Product *) realloc(product->product, sizeof (Product)*(product->counter + 1));
            printf("\t\t\t__________________________________\n");
            productCode(product->product[product->counter].cod_Produto);
            productName(product->product[product->counter].name);
            productPrice(&product->product[product->counter].price);
            productDimension(&product->product[product->counter].dimension);
            product->product[product->counter].state = 1;
            printf("\t\t\t__________________________________\n");
            i = 0;
            product->product[product->counter].line_product = (LineProduct *) malloc(sizeof (LineProduct) * 1);
            do {
                product->product[product->counter].line_product = (LineProduct *) realloc(product->product[product->counter].line_product,
                        sizeof (LineProduct) * (i + 1));
                do {
                    printf("\n"ASK_MATERIAL_CODE);
                    scanf("%s", code);
                    if (verifyCode(code, material)) {
                        strcpy(product->product[product->counter].line_product[i].code, code);
                        printf("\n"ASK_MATERIAL_QUANTITY);
                        scanf("%d", &quantity);
                        if (quantity > 0) {
                            product->product[product->counter].line_product[i].quantity = quantity;
                            printf("\t\t\t__________________________________\n");
                        }
                        ++i;
                    } else {
                        printf("\t\t\tWritten material code does not exist.\n");
                    }
                } while (verifyCode(code, material) == 0);
                product->product[product->counter].line_product_size = i;
                opMaterial = yesOrNoFunction(YES_OR_NO_MESSAGE_RECORD_MATERIAL);
                printf("\t\t\t__________________________________\n");
            } while (opMaterial != 2);
            product->counter++;
            opProduct = yesOrNoFunction(YES_OR_NO_MESSAGE_RECORD_PRODUCT);
            system("cls || clear");
        } while (opProduct != 2);
    } else {
        errorMessage(NO_MATERIAL_FOUND_MESSAGE);
    }
}

/**
 * The bellow function lists all of a products information and all of its material's information.
 * @param product Pointer to the product struct.
 */
void listProduct(Products *product) {
    int i, j;
    if (product->counter == 0) {
        printf("\n\t\t\tNo products were found\n\t\t\t__________________________________");
    } else {
        printf("\n\t\t\tList Of Products\n\t\t\t__________________________________");
        for (i = 0; i < product->counter; i++) {
            printf("\n\n\t\t\tProduct Id      : %s", product->product[i].cod_Produto);
            printf("\n\t\t\tName            : %s", product->product[i].name);
            printf("\n\t\t\tPrice           : %f", product->product[i].price);
            printf("\n\t\t\tDimensions      : %dx%dx%d", product->product[i].dimension.height, product->product[i].dimension.lenght, product->product[i].dimension.width);
            printf("\n\t\t\tState     : %s", product->product[i].state == 1 ? "Active" : "Inactive");
            printf("\n\t\t\t__________________________________\n");
            for (j = 0; j < product->product[i].line_product_size; j++) {
                printf("\n\t\t\tMaterial Id - %s\n\t\t\tQuantity - %d\n", product->product[i].line_product[j].code,
                        product->product[i].line_product[j].quantity);
            }
            printf("\t\t\t__________________________________");
        }
    }
    pressAnyKeyToContinueFunctionListVersion();
}

/**
 * The bellow function saves all the product and material struct data. The saving process is made
 * in the following way:
 *      ->asks for the file name.
 *          ->writes the number of products in the struct.
 *                 ->loops tru the struct and writes all the struct data.
 *                 ->loops tru all the line_product positions writing all the line_product data
 *          ->writes the number of materials.
 *                  ->loops tru the material struct and writes all the material data.
 * @param product pointer to the product struct.
 * @param material pointer to the material struct.
 */
void saveProductMaterials(Products *product, Materials *material) {
    FILE *fp;
    int i, j;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "w+");
    if (fp == NULL) {
        printf(ERROR_IN_FILES);
        pressAnyKeyToContinueFunction();
    } else {
        fwrite(&product->counter, sizeof (int), 1, fp);
        i = 0;
        do {
            fwrite(&product->product[i].cod_Produto, sizeof (char)*COD_PRODUCT_SIZE, 1, fp);
            fwrite(&product->product[i].name, sizeof (char)*MAX_PRODUCT_NAME_SIZE, 1, fp);
            fwrite(&product->product[i].price, sizeof (double), 1, fp);
            fwrite(&product->product[i].dimension.height, sizeof (int), 1, fp);
            fwrite(&product->product[i].dimension.lenght, sizeof (int), 1, fp);
            fwrite(&product->product[i].dimension.width, sizeof (int), 1, fp);
            fwrite(&product->product[i].state, sizeof (int), 1, fp);
            i++;
        } while (i < product->counter);

        for (i = 0; i < product->counter; i++) {
            j = 0;
            fwrite(&product->product[i].line_product_size, sizeof (int), 1, fp);
            do {
                fwrite(&product->product[i].line_product[j].code, sizeof (char)*COD_MATERIAL_SIZE, 1, fp);
                fwrite(&product->product[i].line_product[j].quantity, sizeof (int), 1, fp);
                j++;
            } while (j < product->product[i].line_product_size);
        }
        fwrite(&material->counter, sizeof (int), 1, fp);
        for (i = 0; i < material->counter; i++) {
            fwrite(&material->material[i].cod_Material, sizeof (char)*COD_MATERIAL_SIZE, 1, fp);
            fwrite(&material->material[i].description, sizeof (char)*MAX_DESCRIPTION_SIZE, 1, fp);
            fwrite(&material->material[i].unit, sizeof (units), 1, fp);
        }
        fclose(fp);
        printf(SUCCESS_IN_FILES);
        pressAnyKeyToContinueFunction();
    }
}

/**
 * The bellow function saves all the product and material struct data. The saving process is made
 * in the following way:
 *      ->asks for the file name.
 *          ->reads the number of products in the struct.
 *                 ->loops tru the struct and reads all the struct data.
 *                 ->loops tru all the line_product positions reading all the line_product data
 *          ->reads the number of materials.
 *                  ->loops tru the material struct and reads all the material data.
 * @param product pointer to the product struct.
 * @param material pointer to the material struct.
 */
void loadProductMaterials(Products *product, Materials *material) {
    FILE *fp;
    int i, j, c, k;
    char fn[MAX_FN_CHARS];
    askFileName(fn);
    fp = fopen(fn, "rb+");
    if (fp == NULL) {
        printf(ERROR_IN_FILES);
        pressAnyKeyToContinueFunction();
    } else {
        fread(&c, sizeof (int), 1, fp);
        k = product->counter;
        for (i = 0; i < c; i++) {
            product->product = (Product *) realloc(product->product,
                    (product->counter + 1) * sizeof (Product));
            fread(&product->product[product->counter].cod_Produto, sizeof (char)*COD_PRODUCT_SIZE, 1, fp);
            fread(&product->product[product->counter].name, sizeof (char)*MAX_PRODUCT_NAME_SIZE, 1, fp);
            fread(&product->product[product->counter].price, sizeof (double), 1, fp);
            fread(&product->product[product->counter].dimension.height, sizeof (int), 1, fp);
            fread(&product->product[product->counter].dimension.lenght, sizeof (int), 1, fp);
            fread(&product->product[product->counter].dimension.width, sizeof (int), 1, fp);
            fread(&product->product[product->counter].state, sizeof (int), 1, fp);
            product->counter++;
        }
        for (i = 0; i < c; i++) {
            fread(&product->product[k + i].line_product_size, sizeof (int), 1, fp);
            product->product[k + i].line_product = (LineProduct *) malloc(
                    sizeof (LineProduct) * product->product[k + i].line_product_size);
            for (j = 0; j < product->product[k + i].line_product_size; j++) {
                fread(&product->product[k + i].line_product[j].code, sizeof (char)*COD_MATERIAL_SIZE, 1, fp);
                fread(&product->product[k + i].line_product[j].quantity, sizeof (int), 1, fp);
            }
        }

        fread(&c, sizeof (int), 1, fp);
        k = material->counter;
        for (i = 0; i < c; i++) {
            material->material = (Material *) realloc(material->material,
                    (material->counter + 1) * sizeof (Material));
            fread(&material->material[k + i].cod_Material, sizeof (char)*COD_MATERIAL_SIZE, 1, fp);
            fread(&material->material[k + i].description, sizeof (char)*MAX_DESCRIPTION_SIZE, 1, fp);
            fread(&material->material[k + i].unit, sizeof (int), 1, fp);
            material->counter++;
        }
        fclose(fp);
        printf(SUCCESS_IN_FILES);
        pressAnyKeyToContinueFunction();
    }
}

/**
 * The bellow function returns a material position, it loops tru the material struct
 * trying to find a material which has a code equal to the code given in the parameters, if found,
 * it returns the position, if not, it returns -1.
 * @param material
 * @param code
 * @return returns the material position if not return -1
 */
int findMaterialPosition(Materials *material, char code[COD_MATERIAL_SIZE]) {
    int i, count = 0;
    for (i = 0; i < material->counter; i++) {
        if (strcmp(code, material->material[i].cod_Material) == 0) {
            return i;
        } else {
            count++;
        }
    }
    if (count == material->counter) {
        return -1;
    }
}

/**
 * The bellow function returns a product position, it loops tru the product struct
 * trying to find a product which has a code equal to the code given in the parameters, if found,
 * it returns the position, if not, it returns -1.
 * @param product pointer to the product struct
 * @param code product code
 * @return return the position if found, if not returns -1.
 */
int findProductPosition(Products *product, char code[COD_MATERIAL_SIZE]) {
    int i, count = 0;
    for (i = 0; i < product->counter; i++) {
        if (strcmp(code, product->product[i].cod_Produto) == 0) {
            return i;
        } else {
            count++;
        }
    }
    if (count == product->counter) {
        return -1;
    }
}


/**
 * The bellow function saves all of a material information, it does so by passing all the
 * data passed by in the current material struct to the Materials material struct in the given position.
 * @param material pointer to the material struct
 * @param position position of the material
 * @param current temporary material struct where changes are made.
 */
void saveMaterialChanges(Materials *material, int position, Material current) {
    strcpy(material->material[position].cod_Material, current.cod_Material);
    strcpy(material->material[position].description, current.description);
    material->material[position].unit = current.unit;
}

/**
 * Bellow function deletes a material, it receives the material struct and the code of the material
 * that is being edited. The deleting process is made in the following way:
 *          ->copies the next position to the current position of materials.
 *          ->loops tru the material size
 *          ->changes the values
 *               counter --
 * @param code material's code
 * @param material pointer to the material struct
 * @param product pointer to the product struct
 */
void deleteMaterial(char code[COD_MATERIAL_SIZE], Materials *material, Products *product) {
    int i, j;
    for (i = 0; i < material->counter; i++) {
        if (strcmp(material->material[i].cod_Material, code) == 0) {
            strcpy(material->material[i].cod_Material,
                    material->material[i + 1].cod_Material);
            strcpy(material->material[i].description,
                    material->material[i + 1].description);
            material->material[i].unit = material->material[i + 1].unit;
        }
    }
    material->counter--;
    for (i = 0; i < product->counter; i++) {
        for (j = 0; j < product->product[i].line_product_size; j++) {
            if (strcmp(product->product[i].line_product[j].code,
                    code) == 0) {
                strcpy(product->product[i].line_product[j].code,
                        product->product[i].line_product[j + 1].code);
                product->product[i].line_product[j].quantity = product->product[i].line_product[j + 1].quantity;
                product->product[i].line_product_size--;
            }
        }
    }
}

/**
 * Bellow function is the menu responsible for all the changes who are made to a certain material,
 * first it asks the user for a material code, then it verifies if the material exists, if not
 * the user comes across an error message, if not, the user gets to see a menu where the following functions are listed:
 *      ->change unit (materialUnit),
 *      ->change description (materialDescription),
 *      ->delete Material (deleteMaterial).
 * @param material pointer to the material struct
 * @param product pointer to the product struct
 */
void editMaterial(Materials *material, Products *product) {
    char editedMaterial[COD_MATERIAL_SIZE];
    int position, option, i;
    Material current;
    if (material->counter != 0) {
        printf("\n\t\t\tList Of Materials\n\t\t\t_______________________________________");
        for (i = 0; i < material->counter; i++) {
            printf("\n\n\t\t\tMaterial Id      : %s", material->material[i].cod_Material);
            printf("\n\t\t\tDescription      : %s", material->material[i].description);
            printf("\n\t\t\tUnit             : %d", material->material[i].unit);
            printf("\n\t\t\t_______________________________________");
        }
        printf("\n\t\t\tSelect the material you want to edit - ");
        scanf("%s", editedMaterial);
        system("cls || clear");
        position = findMaterialPosition(material, editedMaterial);
        if (position == -1) {
            printf("\n\t\t\tERROR!\n");
        } else {
            strcpy(current.cod_Material, material->material[position].cod_Material);
            strcpy(current.description, material->material[position].description);
            current.unit = material->material[position].unit;
            do {
                printf("\n\t\t\tChanging %s...", current.description);
                printf("\n\t\t\t__________________________________\n");
                option = menuRead(MSG_CHANGE_PRODUCT_MATERIAL_DATA, 0, 3);
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
                        deleteMaterial(editedMaterial, material, product);
                        option = 0;
                        break;
                }
            } while (option != 0);
            saveMaterialChanges(material, position, current);
        }
    } else {
        errorMessage(NO_MATERIAL_FOUND_MESSAGE);
    }
}

/**
 * Bellow function saves all the changes made to the product.
 * @param product product temporary struct
 * @param products pointer to the product struct
 * @param pos position of the product that is being edited.
 */
void saveProductChanges(Product product, Products *products, int pos) {
    strcpy(products->product[pos].name, product.name);
    products->product[pos].price = product.price;
    products->product[pos].dimension = product.dimension;
}
/**
 * Bellow function verifies if a product is added to any orders.
 * @param code product's code
 * @param orders pointer to the order's struct
 * @return returns 1 if found, 0 if not found.
 */
int verifyProductOrders(char code[COD_PRODUCT_SIZE], Orders *orders) {
    int i, j;
    for (i = 0; i < orders->counter; i++) {
        for (j = 0; j < orders->order[i].line_order_size; j++) {
            if (strcmp(orders->order[i].line_order[j].code, code) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * The bellow function deletes a product, it does this by firstly getting the product's struct,
 * then the product code, which indicates what product the user wishes to delete,
 * if found the deleting process is made in the following way:
 *      ->strcmp compares both codes and is equal to zero:
 *          ->copies the next position to the current position of products.
 *          ->reallocates the line_product_size of the current position to the next line_product_size.
 *          ->loops tru the new line_product_size
 *          ->changes the values
 *              ->verifies if the counter is != from 0
 *                  if true?
 *                      counter --
 * @param product pointer to the product struct
 * @param code product struct code
 * @param orders pointer to the order struct
 */
void deleteProduct(Products *product, char code[COD_PRODUCT_SIZE], Orders *orders) {
    int i, j;

    for (i = 0; i < product->counter; i++) {
        if (strcmp(product->product[i].cod_Produto, code) == 0) {
            if (!verifyProductOrders(code, orders)) {
                strcpy(product->product[i].cod_Produto,
                        product->product[i + 1].cod_Produto);
                strcpy(product->product[i].name,
                        product->product[i + 1].name);
                product->product[i].price = product->product[i + 1].price;
                product->product[i].dimension = product->product[i + 1].dimension;
                product->product[i].line_product_size = product->product[i + 1].line_product_size;
                if (product->product[i + 1].line_product_size < 200) {
                    product->product[i].line_product = (LineProduct *) realloc(product->product[i].line_product,
                                                                               sizeof(LineProduct) *
                                                                               product->product[i +
                                                                                                1].line_product_size);
                    for (j = 0; j < product->product[i + 1].line_product_size; j++) {
                        strcpy(product->product[i].line_product[j].code, product->product[i + 1].line_product[j].code);
                        product->product[i].line_product[j].quantity = product->product[i + 1].line_product[j].quantity;
                    }
                }
                product->counter--;
            } else {
                product->product[i].state = 0;
            }
        }
    }

    printf(SUCCESS_IN_DELETING);
}

/**
 * The bellow function gets the product_position and adds data to the line_product struct until
 * the option is equal to zero.
 * @param material pointer to the material struct
 * @param product pointer to the product struct
 * @param position product's position
 */
void addMaterialLineProduct(Materials *material, Products *product, int position) {
    LineProduct line;
    int i, op;
    i = product->product[position].line_product_size;
    do {
        product->product[position].line_product = (LineProduct *) realloc(product->product[position].line_product,
                sizeof (LineProduct) * (i + 1));
        listMaterial(material);
        do {
            printf(ASK_MATERIAL_CODE);
            scanf("%s", line.code);
        }while(!verifyCode(line.code, material));
        do {
            printf(ASK_MATERIAL_QUANTITY);
            scanf("%hu", &line.quantity);
        }while(line.quantity < 0);

        strcpy(product->product[position].line_product[i].code, line.code);
        product->product[position].line_product[i].quantity = line.quantity;
        ++i;
        op = yesOrNoFunction("Do you wish to add another material?");
    } while (op != 2);
    product->product[position].line_product_size = (i);
}
/**
 * Bellow function verifies if a material's code is already in the same product line.
 * @param code material's code
 * @param line_product a product's LineProduct struct
 * @param line_product_size the size of the LineProduct struct
 * @return returns 1 if found, 0 if not.
 */
int verifyCodeInLine(char code[COD_MATERIAL_SIZE],
                     LineProduct *line_product,
                     int line_product_size){
    int i;
    for (i = 0; i < line_product_size; i++){
        if (strcmp(line_product[i].code, code) == 0){
            return 1;
        }
    }
    return 0;
}
/**
 * Bellow function saves all of the changes made to the line product.
 * @param temp temporary LineProduct variable
 * @param products pointer to the product struct
 * @param position position of the product that is being edited
 */
void saveLineProductChanges(const LineProduct temp,
                            Products *products,
                            int position){
    int i;
    for (i = 0; i < products->product[position].line_product_size; i++){
        if (strcmp(products->product[position].line_product[i].code, temp.code) == 0){
            products->product[position].line_product[i].quantity = temp.quantity;
        }
    }
}
/**
 * Bellow function edit's a line product information, it start's by asking for a material code,
 * if the code is valid it asks for a quantity, if the quantity is valid then the program asks the
 * user if he want's to edit another user, if so, the loop continue and the changes are saved, if not,
 * the changes are saved and the user exit's the loop.
 * @param materials pointer to the material's struct
 * @param products pointer to the product's struct
 * @param position position of the product
 */
void editMaterialLineProduct(Materials *materials, Products *products, int position){
    LineProduct line;
    int op;
    do{
        do {
            printf(ASK_MATERIAL_CODE);
            scanf("%s", line.code);
        }while(!verifyCodeInLine(line.code,
                                 products->product[position].line_product,
                                 products->product[position].line_product_size));
        do {
            printf(ASK_MATERIAL_QUANTITY);
            scanf("%hd", &line.quantity);
        }while(line.quantity < 0);

        op = yesOrNoFunction("Do you wish to edit another product?");
        saveLineProductChanges(line, products, position);
    }while(op != 2);
}
/**
 * Below function removes a material from the line product, it starts by asking the
 * user for a material code, if the code is valid, the program asks the user want's to delete
 * more materials, if not the material is removed and the user exit's the loop, if not, the material is removed
 * and the loop continues.
 * @param materials pointer to the material struct
 * @param products pointer to the product struct
 * @param position position of the selected product
 */
void removeMaterialLineProduct(Materials *materials, Products *products, int position){
    LineProduct line;
    char code[COD_MATERIAL_SIZE];
    int op, i, pos;
    do{
        do{
            printf(ASK_MATERIAL_CODE);
            scanf("%s", code);
        }while(!verifyCodeInLine(code,
                                 products->product[position].line_product,
                                 products->product[position].line_product_size));
        op = yesOrNoFunction("Do you wish to delete another product?");
        for (i = 0; i < products->product[position].line_product_size; i++){
            if (strcmp(products->product[position].line_product[i].code, code) == 0){
                pos = i;
                break;
            }
        }
        for (i = 0; i < products->product[position].line_product_size; i++){
            strcpy(products->product[position].line_product[pos + i].code,
                   products->product[position].line_product[pos + i + 1].code);
            products->product[position].line_product[pos + i].quantity =
                    products->product[position].line_product[pos + i + 1].quantity;
        }
        products->product[position].line_product_size--;
    }while(op != 2);
}
/**
 * Bellow function is responsible for changing all the product data this function
 * receives the product struct the product position and code written by the user.
 * This menu is composed by the following options:
 *      ->change name (productName),
 *      ->change price (productPrice),
 *      ->change Dimension (productDimension),
 *      ->change Materials (addMaterialLineProduct) <- another menu;
 * @param products pointer to the product's struct
 * @param pos product position
 * @param code product's code
 * @param material pointer to the material's struct
 * @param orders pointer to the order's struct
 */
void changeProductData(Products *products, int pos, char code[COD_PRODUCT_SIZE], Materials *material, Orders *orders) {
    int option;
    Product product;
    strcpy(product.name, products->product[pos].name);
    product.price = products->product[pos].price;
    product.dimension.height = products->product[pos].dimension.height;
    product.dimension.width = products->product[pos].dimension.width;
    product.dimension.lenght = products->product[pos].dimension.lenght;
    do {
        printf("\n\t\t\tChanging %s...", product.name);
        printf("\n\t\t\t__________________________________\n");

        option = menuRead(MSG_CHANGE_PRODUCT_DATA, 0, 7);

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
                deleteProduct(products, code, orders);
                option = 0;
                break;
            case 5:
                addMaterialLineProduct(material, products, pos);
                break;
            case 6:
                editMaterialLineProduct(material, products, pos);
                break;
            case 7:
                removeMaterialLineProduct(material, products, pos);
                break;
        }
    } while (option != 0);

    saveProductChanges(product, products, pos);
}

/**
 * The following function loops tru the product struct until it finds
 * the code written by the user, if not found, an error message appears,
 * if found, the user is redirected to the menu (changeProductData).
 * @param material pointer to the material's struct
 * @param product pointer to the product's struct
 * @param orders pointer to the order's struct
 */
void editProduct(Materials *material, Products *product, Orders *orders) {
    int i, count = 0, position;
    char code[COD_PRODUCT_SIZE];
    if (product->counter != 0) {
        printf("\n\t\t\tList Of Products\n\t\t\t_______________________________________");
        for (i = 0; i < product->counter; i++) {
            printf("\n\n\t\t\tProduct Id      : %s", product->product[i].cod_Produto);
            printf("\n\t\t\tName            : %s", product->product[i].name);
            printf("\n\t\t\tPrice           : %f", product->product[i].price);
            printf("\n\t\t\tDimensions      : %dx%dx%d", product->product[i].dimension.height, product->product[i].dimension.lenght, product->product[i].dimension.width);
            printf("\n\t\t\t_______________________________________");
        }
        printf("\n\t\t\tSelect the product you want to edit - ");
        scanf("%s", code);
        system("cls || clear");
        position = findProductPosition(product, code);
        if (position == -1) {
            printf("\nERROR\n");
        } else {
            for (i = 0; i < product->counter; i++) {
                if (strcmp(code, product->product[i].cod_Produto) == 0) {
                    changeProductData(product, i, code, material, orders);
                } else {
                    count++;
                    continue;
                }
            }
        }
    } else {
        errorMessage(NO_PRODUCTS_FOUND_MESSAGE);
    }
}

/**
 * The bellow menu is responsible to any data manipulation related to products.
 * @param products pointer to the product's struct
 * @param material pointer to the material's struct
 * @param orders pointer to the order's struct
 */
void productsManagementMenu(Products *products, Materials *material, Orders *orders) {
    int option;

    do {
        option = menuRead(MSG_PRODUCTS_MANAGEMENT_MENU, 0, 3);

        switch (option) {
            case 1:
                newProduct(products, material);
                break;
            case 2:
                editProduct(material, products, orders);
                break;
            case 3:
                listProduct(products);
                break;
            case 0:
                break;
        }
    } while (option != 0);
}

/**
 * The bellow menu is responsible to any data manipulation related to materials.
 * @param products pointer to the product's struct
 * @param material pointer to the material's struct
 */
void materialManagementMenu(Products *products, Materials *material) {
    int option;

    do {
        option = menuRead(MSG_MATERIALS_MANAGEMENT_MENU, 0, 3);

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
            case 0:
                break;
        }
    } while (option != 0);
}

/**
 * The bellow menu is the primary product/material menu, this menu is divided into other
 * @param products pointer to the product's struct
 * @param material pointer to the material's struct
 * @param orders pointer to the order's struct
 */
void productsMaterialsManagementMenu(Products *products, Materials *material, Orders *orders) {
    int option;

    do {
        option = menuRead(MSG_PRODUCTS_MATERIALS_MANAGEMENT_MENU, 0, 4);

        switch (option) {
            default:
                break;
            case 1:
                productsManagementMenu(products, material, orders);
                break;
            case 2:
                materialManagementMenu(products, material);
                break;
            case 0:
                break;
        }
    } while (option != 0);
}