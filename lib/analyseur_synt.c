#include "analyseur_synt.h"
#include "analyseur_lex.h"

#include <stdio.h>
#include <stdlib.h>

void analyse_HEAD(FILE * source, char * c)
{
    // Si token app aux possibles de la règle (head donne mot_cle_T text  mot_cle A text)
    if (token == MOTCLE_T)
    {
        if (token == MOTCLE_T) scanner(source, c, tokenValue);
        else 
        {
            printf("Erreur analyse HEAD.\n");
            exit(-1);
        }
        analyse_TEXT(source, c);
        if (token == MOTCLE_A) scanner(source, c, tokenValue);
        else
        {
            printf("Erreur analyse HEAD.\n");
            exit(-1);
        }
        analyse_TEXT(source, c);
    }
    else
    {
            printf("Erreur analyse HEAD.\n");
            exit(-1);
    }

}


void analyse_TEXT(FILE * source, char * c)
{
    // Si token dans possibles de (text donne mot text)
    if(token == MOT)
    {
        if(token == MOT) scanner(source, c, tokenValue);
        else
        {
            printf("Erreur analyse TEXT.\n");
            exit(-1);
        }
        analyse_TEXT(source, c);
    }
    // Sinon si token dans possibles (text donne epsilon)
    else if (token == MOTCLE_T || token == MOTCLE_A || token == NOUV_PARA || token == SECTION || token == SSECTION || token == FIN)
    {
        // Rien à faire
        return;
    }
    else
    {
        printf("Erreur analyse TEXT.\n");
        exit(-1);
    }
}

void analyse_BODY(FILE * soucre, char * c)
{
    // Si token dans possibles(BODY -> P S1)
    if(token == NOUV_PARA || token == SECTION || token == FIN)
    {
        analyse_P(source, c);
        ananlyse_S1(source, c);
    }
    else
    {
        printf("Erreur analyse BODY.\n");
        exit(-1);
    }
}



