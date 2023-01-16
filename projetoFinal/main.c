// Macro and Library definition
#include "menus.h"
#include <stdlib.h>
/*
 * This is the main function, this is all the structs are instantiated, here the
 * main menu is invoked.
 */
int main(int argc, char **argv) {
    Customers *customer;
    customer = (Customers *)malloc(sizeof(Customers) * INITIAL_CLIENT_SIZE);
    customer->customers = (Customer *)malloc(sizeof(Customer) * INITIAL_CLIENT_SIZE);
    customer->counter = 0;
    Products *product;
    product = (Products *)malloc(1 * sizeof(Products));
    product->product = (Product *)malloc(1 * sizeof(Product));
    product->counter = 0;
    Materials  *material;
    material = (Materials *)malloc(1 * sizeof(Materials));
    material->material = (Material *)malloc(1 * sizeof(Material));
    material->counter = 0;
    Orders *order;
    order = (Orders *)malloc(1 * sizeof(Orders));
    order->order = (Order *)malloc(1 * sizeof(Order));
    order->counter = 0;

    mainMenu(customer, &product, &order, &material);
    free(product->product);
    free(product);
    free(material->material);
    free (material);
    free(order->order);
    free(order);
    free(customer->customers);
    free(customer);
    return (EXIT_SUCCESS);
}
