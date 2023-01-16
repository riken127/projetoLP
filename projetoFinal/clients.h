//
// Created by r1ken on 11-12-2022.
//

#ifndef PROJETOLP_CLIENTS_H
#define PROJETOLP_CLIENTS_H

//macro definition
#define INITIAL_CLIENT_SIZE 1

#define MAX_NAME_CHARS 50

#define MAX_ADDRESS_CHARS 50

#define MAX_COUNTRY_CHARS 50

#define MAX_VERIFY_CHARS 50

#define MSG_CUSTOMER_MANAGEMENT_MENU                                           \
  "\n\t\t\t========= Customer Management Menu =========\n\n\t\t\t[1] - Record.\n\t\t\t[2] - Edit.\n\t\t\t[3] - Delete.\n\t\t\t[4] - List.\n\t\t\t[5] - Export file.\n\t\t\t[6] - Import file.\n\t\t\t[0] - Quit.\n\t\t\t____________________________________________"

#define MSG_CHANGE_CUSTOMER_DATA "\n\t\t\t========= Edit =========\n\n\t\t\t[1] - Name\n\t\t\t[2] - Adress\n\t\t\t[3] - Nif\n\t\t\t[4] - Country.\n\t\t\t[0] - Quit.\n\t\t\t________________________"
#define MSG_CUSTOMER_NAME "\t\t\tName - "

#define MSG_CUSTOMER_ADDRESS "\t\t\tAddress - "

#define MSG_CUSTOMER_NIF "\t\t\tNif - "

#define MSG_CUSTOMER_COUNTRY "\t\t\tCountry - "

#define CLIENT_ID_MSG "\n\t\t\tType the desired client id - "

#define MSG_ERROR_MESSAGE "\n\t\t\t========== ERROR MESSAGE ==========\n\n\t\t\tThe given value is out of reach\n\t\t\t___________________________________"

#define YES_OR_NO_MESSAGE_RECORD "\t\t\tDo you want to add another record?[y/n] - "

#define SUCCESS_IN_WRITING_CUSTOMERS "\n\t\t\tCustomer were written successfully"

#define SUCCESS_IN_IMPORTING_CUSTOMERS "\n\t\t\tCustomer were imported successfully"

#define ERROR_IN_WRITING_CUSTOMERS "\nt\t\t\tAn error has occurred"
//struct definition
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
//function definition
void errorMessage(char message[]);
int yesOrNoFunction(char message[]);
int menuRead(char message[], int min, int max);
int verifyCustomersId(Customers *customer, int requestedId);
void customerName(char name[]);
void customerAddress(char address[]);
int customerNif();
int nifVerify();
void customerCountry(char country[]);
int customerId(int curentID);
void saveCustomer(char name[], char address[], int nif, char country[], int id,
        Customers *customer, int pos);
void recordCustomers(Customers *customer);
void changeCustomerData(Customers *customer, int pos, int id);
void editCustomers(Customers *customer);
int deleteCustomers(Customers *customer);
void listCustomers(Customers *customer);
void exportCustomers(Customers *customer);
void importCustomers(Customers *customer);
void customerManagementMenu(Customers *customer);
#endif // PROJETOLP_CLIENTS_H