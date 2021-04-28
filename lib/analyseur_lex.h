#pragma once

char c;
enum TokenType {MOTCLE_T, MOTCLE_A, SECTION, SSECTION, NOUV_PARA, MOT, FIN} token;
char tokenValue[50];

int scanner(void);