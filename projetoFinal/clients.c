/**
 * 
 * @file clients.c
 * @author João Pereira, Henrique Noronha, Ângelo Lopes
 * @date 16 Janeiro 2023
 * @brief Source file clients
 * 
 * Source file containing all the functions about clients.
 */
#include "menus.h"
#include "clients.h"
#include "orders.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function below appears when an error appears, it receives the error message
 * as a parameter, and then waits for the user to press a key, if so, the screen
 * is cleaned and the function ends.
 *
 * @param message[] Vector which the error message is going to be stored.
 */
void errorMessage(char message[]) {
    system("cls || clear");
    puts(message);
    pressAnyKeyToContinueFunction();
}

/**
 * Function below checks if the given value
 * is between two values, if not, the cycle continues.
 *
 * @param min Minimum value of the menu option.
 * @param max Maximum value of the menu option.
 * @param message[] Vector that hold the Menu message.
 * @return option Returns the option that the user has chosen.
 */


/**
 * Function below receives a message and depending on what the character that was
 * written the value that is returned is different.
 *
 * @param message[] Confirmation message.
 * @return 1 if the letter Y is pressed.
 * @return 2 if the letter N is pressed.
 */
int yesOrNoFunction(char message[]) {
    char option;
    do {
        printf(message);
        scanf(" %c", &option);
    } while (option != 'y' && option != 'n' && option != 'Y' && option != 'N');
    switch (option) {
        case 'y':
        case 'Y':
            return 1;
            break;
        case 'n':
        case 'N':
            return 2;
            break;
    }
}

/**
 * Function below checks for an id in the struct array,
 * if found, returns the value 1, if not, returns the value 0.
 *
 * @param *customer Brings the customers stored in the struct Customers into the
 * function.
 * @param requestedId Stores the Id that the customer has requested.
 * @return count Receives the number that decides if the Id has been successfully
 * checked, 1 if the Id exits, 0 if not.
 */
int verifyCustomersId(Customers *customer, int requestedId) {
    int i = 0, count = 0;
    for (i = 0; i < customer->counter; i++) {
        if (*(&customer->customers[i].id) == requestedId) {
            ++count;
            break;
        }
    }
    return count;
}

/**
 * Function below takes a given name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 *
 * @param name[] Stores the customers name its given position.
 */
void customerName(char name[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_NAME);
    scanf("%c", &temp);
    scanf("%[^\n]", name);
}

/**
 * Function below takes a given address and stores it in the struct array
 * In the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 *
 * @param adress[] Stores the customers address its given position.
 */
void customerAddress(char address[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_ADDRESS);
    scanf("%c", &temp);
    scanf("%[^\n]", address);
}

/**
 * Function below verifies if the nif is a number and if the number is greater
 * than zero, if not, the loop continues. If so, the value is returned
 * as an integer.
 *
 * @return nif Returns the nif as an integer.
 */
int nifVerify() {
    int nif;
    char verify[MAX_VERIFY_CHARS];
    do {
        do {
            printf("\n"MSG_CUSTOMER_NIF);
            scanf("%s", verify);
            if (!(nif = atoi(verify))) {
                puts(MSG_ERROR_MESSAGE);
            }
        } while (!(nif = atoi(verify)));
        if (nif <= 0) {
            puts(MSG_ERROR_MESSAGE);
        }
    } while (nif <= 0);
    return nif;
}

/**
 * Function below takes a given integer and passes the value as an
 * argument to a function that verifies the data (nifVerify function), if the
 * written field is an integer greater than zero, the value is returned, if not,
 * the loop continues.
 *
 * @return nif Returns the nif.
 */
int customerNif() {
    int nif;

    nif = nifVerify();

    return nif;
}

/**
 * Function below takes a given country name and stores it in the struct array
 * in the given position. The first scanf makes sure the buffer is clean,
 * the second scanf gets the value given by the user.
 *
 * @param country[] Receives the empty country vector, to be eventually filled
 * information.
 */
void customerCountry(char country[]) {
    char temp;
    printf("\n"MSG_CUSTOMER_COUNTRY);
    scanf("%c", &temp);
    scanf("%[^\n]", country);
}

/**
 * Function below creates an id for the user who is being created,
 * the given id is equal to the last given id (from the last created user)
 * incremented by one.
 * 
 * @param currentID Has the last user's ID stored. If last ID is 45, 46 will be
 * the next one.
 */
int customerId(int curentID) {
    return (curentID + 1);
}

/**
 * Function below saves a specific customer data, it receives the position and
 * the input data, and then saves the data of the customer in the given position.
 * 
 * @param name Brings the current name vector into the funtion.
 * @param address Brings the current address vector into the funtion.
 * @param nif Brings the current nif into the funtion.
 * @param country Brings the current country vector into the funtion.
 * @param id Brings the current id value into the funtion.
 * @param customer Brings the customer struct into the funtion.
 * @param pos Brings the position value into the funtion.
 */

void saveCustomer(char name[], char address[], int nif, char country[], int id,
        Customers *customer, int pos) {
    *(&customer->customers[pos].id) = id;
    strcpy(*(&customer->customers[pos].name), name);
    strcpy(*(&customer->customers[pos].address), address);
    *(&customer->customers[pos].nif) = nif;
    strcpy(*(&customer->customers[pos].country), country);
    *(&customer->customers[pos].state) = 1;
}

//ESTE COMENTARIO N ENTENDI TA BUGADO CONFIA VVVVVVVV

/**
 * The function above calls other 5 functions that help create the customer,
 * each function fills a field in the new user's position in the struct array.
 */

/**
 * 
 * @param customer
 */
void editCustomers(Customers *customer) {
    int id, i, verify;
    do {
        printf(CLIENT_ID_MSG);
        scanf("%d", &id);
        system("cls || clear");
        if (id == 0)
            break;
        verify = verifyCustomersId(*(&customer), id);
        if (verify == 1) {
            for (i = 0; i < customer->counter; i++) {
                if (*(&customer->customers[i].id) == id) {
                    changeCustomerData(*(&customer), i, id);
                }
            }
        } else
            errorMessage(MSG_ERROR_MESSAGE);
    } while (verify != 1);
}

/*
 * Bellow function records a customer, it gets the customer struct as an argument and
 * then goes tru every field function so that the data is passed to the variables, at the end,
 * all the data that was written goes on the saveCustomer function where the user is created and
 * then the program asks the user tru the yesOrNoFunction if the user wants to add another user,
 * if so the loop continues.
 */


void recordCustomers(Customers *customer) {
    char name[MAX_NAME_CHARS], address[MAX_ADDRESS_CHARS],
            country[MAX_COUNTRY_CHARS];
    int nif, option = 1;
    do {
        printf("\t\t\t__________________________________\n");
        customerName(name);
        customerAddress(address);
        customerCountry(country);
        nif = customerNif();

        printf("\t\t\t__________________________________\n");
        customer->customers = (Customer *) realloc(customer->customers, sizeof (Customer)* (customer->counter + 1));

        saveCustomer(name, address, nif, country, customerId(customer->counter),
                *(&customer), customer->counter);
        customer->counter++;
        option = yesOrNoFunction(YES_OR_NO_MESSAGE_RECORD);
        system("cls || clear");
    } while (option != 2);
}

/*
 * The Bellow function edit's a line in the struct array. It receives the struct array,
 * the current id of the customer, and the position in the struct array, it then passes all the
 * user information to some local variables and asks the user what field does he want to change,
 * when the user exits all the changes made are saved.
 */
void changeCustomerData(Customers *customer, int pos, int id) {
    int option, nif;
    char name[MAX_NAME_CHARS], address[MAX_ADDRESS_CHARS],
            country[MAX_COUNTRY_CHARS];
    strcpy(name, *(&customer->customers[pos].name));
    strcpy(address, *(&customer->customers[pos].address));
    nif = *(&customer->customers[pos].nif);
    strcpy(country, *(&customer->customers[pos].country));
    do {
        option = menuRead(MSG_CHANGE_CUSTOMER_DATA, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                printf("\n\t\t\tPrevious - %s", name);
                customerName(name);
                system("cls || clear");
                break;
            case 2:
                printf("\n\t\t\tPrevious - %s", address);
                customerAddress(address);
                system("cls || clear");
                break;
            case 3:
                printf("\n\t\t\tPrevious - %d", nif);
                nif = customerNif();
                system("cls || clear");
                break;
            case 4:
                printf("\n\t\t\tPrevious - %s", country);
                customerCountry(country);
                system("cls || clear");
                break;
        }
    } while (option != 0);

    saveCustomer(name, address, nif, country, id, *(&customer), pos);
}

int verifyCustomerOrders(int nif, Orders *orders) {
    int i, j;
    for (i = 0; i < orders->counter; i++) {
        if (orders->order[i].nif == nif) {
            return 1;
        }
    }

    return 0;
}

/*
 * The bellow function deletes a user in the struct array. It receives the struct and
 * the amount of users by parameter then asks the user for an integer and loops
 * tru the struct trying to find the given id, if found, the user is deleted, if
 * not an error message is displayed.
 */

int deleteCustomers(Customers *customer, Orders *orders) {
    int id, i, verify, verifyOrders;
    do {
        printf(CLIENT_ID_MSG);
        scanf("%d", &id);
        if (id == 0) {
            break;
        } else {
            verify = verifyCustomersId(*(&customer), id);
            if (verify == 0) {
                errorMessage(MSG_ERROR_MESSAGE);
            } else {
                for (i = 0; i < *(&customer->counter); i++) {
                    if (*(&customer->customers[i].id) == id) {
                        verifyOrders = verifyCustomerOrders(customer->customers[i].nif, orders);
                        if (verifyOrders == 0) {
                            *(&customer->customers[i].id) = *(&customer->customers[i + 1].id);
                            strcpy(*(&customer->customers[i].name),
                                    *(&customer->customers[i + 1].name));
                            strcpy(*(&customer->customers[i].address),
                                    *(&customer->customers[i + 1].address));
                            *(&customer->customers[i].nif) = *(&customer->customers[i + 1].nif);
                            strcpy(*(&customer->customers[i].country),
                                    *(&customer->customers[i + 1].country));
                            *(&customer->customers[i].state) = *(&customer->customers[i + 1].state);
                        } else {
                            *(&customer->customers[i].state) = 0;

                        }
                    }
                }
            }

        }

    } while (verify != 1);
    system("cls || clear");
    if (id == 0 || verifyOrders == 1)
        return customer->counter;

    else
        return customer->counter--;
}

/*
 * The bellow function displays all available customers if possible, if not a message appears saying
 * that no customers where found, the list will appear until the user presses any keu, then the list will
 * be closed.
 */
void listCustomers(Customers *customer) {
    int i;
    if (customer->counter == 0) {
        printf("\n\t\t\tNo customers were found\n\t\t\t__________________________________");
    } else {
        printf("\n\t\t\tList Of Clients\n\t\t\t__________________________________");
        for (i = 0; i < customer->counter; i++) {

            printf("\n\n\t\t\tClient Id : %d", customer->customers[i].id);
            printf("\n\t\t\tName      : %s", customer->customers[i].name);
            printf("\n\t\t\tAddress   : %s", customer->customers[i].address);
            printf("\n\t\t\tNif       : %d", customer->customers[i].nif);
            printf("\n\t\t\tCountry   : %s", customer->customers[i].country);
            printf("\n\t\t\tState     : %s", customer->customers[i].state == 1 ? "Active" : "Inactive");
            printf("\n\t\t\t__________________________________");
        }
    }
    pressAnyKeyToContinueFunctionListVersion();
}

/*
 * The bellow function exports all the customer data, it does so by looping tru the struct array
 * and saving all the customer fields separated by a comma.
 */
void exportCustomers(Customers *customer) {
    FILE *fp;
    int i;
    char fn[100];
    askFileName(fn);
    fp = fopen(fn, "w");
    if (fp == NULL) {
        printf(ERROR_IN_WRITING_CUSTOMERS);
        pressAnyKeyToContinueFunction();
    } else {
        for (i = 0; i < customer->counter; i++) {

            fprintf(fp, "%s,%s,%d,%s,%d\n",
                    customer->customers[i].name,
                    customer->customers[i].address,
                    customer->customers[i].nif,
                    customer->customers[i].country,
                    customer->customers[i].state);
        }
        fclose(fp);
        printf(SUCCESS_IN_WRITING_CUSTOMERS);
        pressAnyKeyToContinueFunction();
    }
}

/*
 * The bellow function imports customers to the program, it does so by asking the user for the file name,
 * then it passes all the data in the file to a string, and reallocates one more position (until the end of the file),
 * then it parses the string tru the commas, after every user is written to the struct a success message appears and file
 * pointer closes.
 */
void importCustomers(Customers *customer) {
    FILE *fp;
    char fn[MAX_FN_CHARS], buff[1024], *sp;
    askFileName(fn);
    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf(ERROR_IN_WRITING_CUSTOMERS);
        pressAnyKeyToContinueFunction();
    } else {
        while (fgets(buff, 1024, fp) != NULL) {
            customer->customers = (Customer*) realloc(customer->customers, sizeof (Customer) * (customer->counter + 1));

            customer->customers[customer->counter].id = (customer->counter + 1);
            sp = strtok(buff, ",");
            strcpy(customer->customers[customer->counter].name, sp);
            sp = strtok(NULL, ",");
            strcpy(customer->customers[customer->counter].address, sp);
            sp = strtok(NULL, ",");
            customer->customers[customer->counter].nif = atoi(sp);
            sp = strtok(NULL, ",");
            strcpy(customer->customers[customer->counter].country, sp);
            sp = strtok(NULL, ",");
            customer->customers[customer->counter].state = atoi(sp);
            ++customer->counter;
        }
        fclose(fp);
        printf(SUCCESS_IN_IMPORTING_CUSTOMERS);
        pressAnyKeyToContinueFunction();
    }
}

/*
 * The bellow menu manages the customers, it loops until the integer [option] given by
 * the user is equal to zero.
 */
void customerManagementMenu(Customers *customer, Orders *orders) {
    int option;
    do {
        option = menuRead(MSG_CUSTOMER_MANAGEMENT_MENU, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:
                recordCustomers(*(&customer));
                break;
            case 2:
                editCustomers(customer);
                break;
            case 3:
                deleteCustomers(customer, orders);
                break;
            case 4:
                listCustomers(customer);
                break;
        }
    } while (option != 0);
}
