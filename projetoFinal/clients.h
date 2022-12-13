//
// Created by r1ken on 11-12-2022.
//

#ifndef PROJETOLP_CLIENTS_H
#define PROJETOLP_CLIENTS_H
#define NAME_LENGHT 50
#define ADDRESS_LENGHT 50
#define COUNTRY_LENGHT 50
typedef struct {
    int id;
    char name[NAME_LENGHT];
    char address[ADDRESS_LENGHT];
    int nif;
    char country[COUNTRY_LENGHT];
} Customer;
int menuRead(char message[], int min, int max);
int verifyCustomersId(Customer customer[], int contCustomers, int requestedId);
void customerName(Customer customer[], int contCustomers);
void customerAddress(Customer customer[], int contCustomers);
void customerNif(Customer customer[], int contCustomers);
void customerCountry(Customer customer[], int contCustomers);
void customerId(Customer customer[], int contCustomers, int curentID);
int recordCustomers(Customer customer[], int contCustomers, int curentID);
void editCustomers(Customer customer[], int contCustomers);
int deleteCustomers(Customer customer[], int contCustomers);
void listCustomers(Customer customer[], int contCustomers);
void customerManagementMenu(Customer customer[], int *contCustomers, int curentID);
#endif //PROJETOLP_CLIENTS_H
