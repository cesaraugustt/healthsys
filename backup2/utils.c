#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}