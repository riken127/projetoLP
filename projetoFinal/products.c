//
// Created by r1ken on 12-12-2022.
//

#include "products.h"
#include <stdio.h>
#include <string.h>
#define MSG_PRODUCTS_MANAGEMENT_MENU "[1] - Edit.\n[2] - Delete.\n[3] - meter produto (temporario).\n[4] - meter material (temporario)."

void productsManagementMenu(){
    int option;

    do {
        option = menuRead(MSG_PRODUCTS_MANAGEMENT_MENU, 0, 4);

        switch (option) {
            case 0:
                break;
            case 1:

                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
        }
    } while (option != 0);
}