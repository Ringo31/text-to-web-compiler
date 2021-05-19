#include "analyseur_synt.h"
#include "analyseur_lex.h"

#include <stdio.h>
#include <stdlib.h>

void analyse_HEAD(FILE * source, char * c)
{
    // Si token app aux possibles de la règle (head donne mot_cle_T text  mot_cle A text)
    if ()
    {
        if (token == MOTCLE_T) scanner(source, c, tokenValue);
        else exit(-1);
        analyse_TEXT(source, c);
        if (token == MOTCLE_A) scanner(source, c, tokenValue);
        else exit(-1);
        analyse_TEXT(source, c);
    }
    else exit(-1);

}


void analyse_TEXT(FILE * source, char * c)
{
    // Si token dans possibles de (text donne mot text)
    if(token == MOT)
    {
        if(token == MOT) scanner(source, c, tokenValue);
        else exit(-1);
        analyse_TEXT();
    }
    // Sinon si token dans possibles (text donne epsilon)
    else if (token == MOTCLE_T || token == MOTCLE_A || token == NOUV_PARA || token == SECTION || token == SSECTION || token == FIN)
    {
        // Rien à faire
    }
    else exit(-1);
}

