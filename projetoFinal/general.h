/**
 * 
 * @file general.h
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Header general
 * 
 * Header file containing all the general functions/structs/macros that are used
 * all around the program.
 */

#ifndef PROJECT_GENERAL_H
#define PROJECT_GENERAL_H
//struct definition
#define MAX_NAME_CHARS 50

#define MAX_ADDRESS_CHARS 50

#define MAX_COUNTRY_CHARS 50

#define COD_MATERIAL_SIZE 6

#define COD_PRODUCT_SIZE 7

#define MAX_DESCRIPTION_SIZE 100

#define MAX_PRODUCT_NAME_SIZE 100

#define INITIAL_CLIENT_SIZE 1

#define MIN_DAY 0

#define MAX_DAY 31

#define MIN_MONTH 0

#define MAX_MONTH 12

#define MIN_YEAR 2022

#define MSG_ERROR_MESSAGE "\n\t\t\t========== ERROR MESSAGE ==========\n\n\t\t\tThe given value is out of reach"


#define ASK_PRODUCT_CODE "\t\t\tProduct code - "

#define ASK_PRODUCT_NAME "\t\t\tProduct name - "

#define ASK_PRODUCT_DIMENSION "\n\t\t\tProduct dimension (#x#x#) - "

#define ASK_PRODUCT_PRICE "\t\t\tProduct price - "

#define ASK_MATERIAL_CODE "\t\t\tMaterial code - "

#define ASK_MATERIAL_DESCRIPTION "\t\t\tMaterial description - "

#define ASK_MATERIAL_QUANTITY "\t\t\tMaterial quantity - "

#define ASK_MATERIAL_UNIT "\t\t\tMaterial unit [1|0] - "

#define MAX_VERIFY_CHARS 50

#define ERROR_IN_FILES "\n\t\t\tAn error has occurred"

#define SUCCESS_IN_FILES "\n\t\t\tOperation success"

typedef struct {
    int id;
    char name[MAX_NAME_CHARS];
    char address[MAX_ADDRESS_CHARS];
    int nif;
    char country[MAX_COUNTRY_CHARS];
    int state;
} Customer;

typedef struct {
    int counter;
    Customer *customers;
} Customers;

//struct definition
typedef struct {
    int day, month, year;
} Date;

typedef struct{
    char code[COD_PRODUCT_SIZE];
    int quantity;
}OrderLine;

typedef struct {
    int order_id, nif;
    Date order_date;
    OrderLine *line_order;
    int line_order_size;
} Order;

typedef struct {
    Order *order;
    int counter;
} Orders;

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
    int state;
} Product;

typedef struct {
    Product *product;
    int counter;
}Products;

typedef struct{
    Material *material;
    int counter;
}Materials;

int menuRead(char message[], int min, int max);
void errorMessage(const char message[]);
int yesOrNoFunction(const char message[]);
void pressAnyKeyToContinueFunction();
void pressAnyKeyToContinueFunctionListVersion();
#endif //PROJECT_GENERAL_H
