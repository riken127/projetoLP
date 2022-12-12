//
// Created by r1ken on 11-12-2022.
//

#ifndef PROJETOLP_CLIENTS_H
#define PROJETOLP_CLIENTS_H
#define MAX_CLIENTS 20
#define MAX_NAME_CHARS 50
#define MAX_ADDRESS_CHARS 50
#define MAX_COUNTRY_CHARS 50
typedef struct {
    int id;
    char name[50];
    char address[50];
    int nif;
    char country[50];
} Customer;

typedef struct {
    int counter;
    Customer customers[MAX_CLIENTS];
} Customers;

int menuRead(char message[], int min, int max);
int verifyCustomersId(Customers *customer, int requestedId);
void customerName(char name[]);
void customerAddress(char address[]);
int customerNif();
void customerCountry(char country[]);
int customerId(int curentID);
void saveCustomer(char name[], char address[], int nif, char country[], int id, Customers *customer, int pos);
void recordCustomers(Customers *customer, int curentID);
void changeCustomerData(Customers *customer, int pos, int id);
void editCustomers(Customers *customer);
int deleteCustomers(Customers *customer);
void listCustomers(Customers *customer);
void customerManagementMenu(Customers *customer, int curentID);
#endif //PROJETOLP_CLIENTS_H
