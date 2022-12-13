//
// Created by r1ken on 12-12-2022.
//

#include "products.h"
#include <stdio.h>
#include <string.h>
#define MSG_PRODUCTS_MANAGEMENT_MENU "[1] - Edit.\n[2] - Delete.\n[3] - meter produto (temporario).\n[4] - meter material (temporario)."

void productsManagementMenu(){
    int option;
    Materials material[10];

    material[0] = {1, "Tubo de Cola"};
    material[1] = {2, "Base"};
    material[2] = {3, "Parafuso"};
    material[3] = {4, "Bucha"};
    material[4] = {5, "Pés"};
    meterial[5] = {6, "Porta"};
    material[6] = {7, "Laterais"};
    material[7] = {8, "Cavilhas"};
    material[8] = {9, "Prateleiras"};
    material[9] = {10, "Ferragem"};
    material[10] = {11, "Frente"};
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