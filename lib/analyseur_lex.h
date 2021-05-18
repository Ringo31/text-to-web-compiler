#pragma once

#include <stdio.h>
#include <stdlib.h>


enum TokenType {MOTCLE_T, MOTCLE_A, SECTION, SSECTION, NOUV_PARA, MOT, FIN} token;
char tokenValue[50];

int est_caractere(char lettre);
int scanner(FILE* source, char* c, char* mot);

