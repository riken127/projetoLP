//
// Created by r1ken on 12-12-2022.
//

#include "products.h"
#include <stdio.h>
#include <string.h>
#define MSG_PRODUCTS_MANAGEMENT_MENU "[1] - Edit.\n[2] - Delete."

void productsManagementMenu(){
    int option;
    Materials material[11];

    material[0].cod_Material = 1;
    material[1].cod_Material = 2;
    material[2].cod_Material = 3;
    material[3].cod_Material = 4;
    material[4].cod_Material = 5;
    material[5].cod_Material = 6;
    material[6].cod_Material = 7;
    material[7].cod_Material = 8;
    material[8].cod_Material = 9;
    material[9].cod_Material = 10;
    material[10].cod_Material = 11;
    
    strcpy(material[0].description, "Tubo de Cola");
    strcpy(material[1].description, "Base");
    strcpy(material[2].description, "Parafuso");
    strcpy(material[3].description, "Bucha");
    strcpy(material[4].description, "Pés");
    strcpy(material[5].description, "Porta");
    strcpy(material[6].description, "Laterais");
    strcpy(material[7].description, "Cavilhas");
    strcpy(material[8].description, "Prateleiras");
    strcpy(material[9].description, "Ferragem");
    strcpy(material[10].description, "Frente");
    
    do {
        option = menuRead(MSG_PRODUCTS_MANAGEMENT_MENU, 0, 2);

        switch (option) {
            case 0:
                break;
            case 1:

                break;
            case 2:
                
                break;
        }
    } while (option != 0);
}