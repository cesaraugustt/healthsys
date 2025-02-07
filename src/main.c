#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main() {
    Lista* pacientes = carregar_bd();
    menu(pacientes);
    return 0;
}