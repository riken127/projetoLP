/**
 * 
 * @file clients.h
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Biblioteca clients
 * 
 *  Biblioteca com todas as funções sobre os clientes.
 */

#ifndef PROJETOLP_CLIENTS_H
#define PROJETOLP_CLIENTS_H
#include "orders.h"
#include "general.h"
//macro definition
#define MSG_CUSTOMER_MANAGEMENT_MENU                                           \
  "\n\t\t\t========= Customer Management Menu =========\n\n\t\t\t[1] - Record.\n\t\t\t[2] - Edit.\n\t\t\t[3] - Delete.\n\t\t\t[4] - List.\n\t\t\t[0] - Quit.\n\t\t\t____________________________________________"

#define MSG_CHANGE_CUSTOMER_DATA "\n\t\t\t========= Edit =========\n\n\t\t\t[1] - Name\n\t\t\t[2] - Adress\n\t\t\t[3] - Nif\n\t\t\t[4] - Country.\n\t\t\t[0] - Quit.\n\t\t\t________________________"
#define MSG_CUSTOMER_NAME "\t\t\tName - "

#define MSG_CUSTOMER_ADDRESS "\t\t\tAddress - "

#define MSG_CUSTOMER_NIF "\t\t\tNif - "

#define MSG_CUSTOMER_COUNTRY "\t\t\tCountry - "

#define CLIENT_ID_MSG "\n\t\t\tType the desired client id - "


#define YES_OR_NO_MESSAGE_RECORD "\t\t\tDo you want to add another record?[y/n] - "

#define SUCCESS_IN_WRITING_CUSTOMERS "\n\t\t\tCustomer were written successfully"

#define SUCCESS_IN_IMPORTING_CUSTOMERS "\n\t\t\tCustomer were imported successfully"

#define ERROR_IN_WRITING_CUSTOMERS "\nt\t\t\tAn error has occurred"

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
void listCustomers(Customers *customer);
void customerManagementMenu(Customers *customer, Orders *order);
void exportCustomers(Customers *customer);
void importCustomers(Customers *customer);
#endif // PROJETOLP_CLIENTS_H