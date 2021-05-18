#include "analyseur_synt.h"
#include "analyseur_lex.h"

#include <stdio.h>
#include <stdlib.h>

void analyse_HEAD(FILE * source, char * c)
{
    if (token == MOTCLE_T)
    {
        scanner(source, c, tokenValue);
        analyse_TEXT(source, c);

        if(token == MOTCLE_A)
        {
            scanner(source, c, tokenValue);
            analyse_TEXT(source, c);
        }

        else
        {
            printf("Erreur dans l'analyse de HEAD\n");
            exit(-1);   
        }
    }
    else if (token == NOUV_PARA || token == SECTION || token == FIN)
    {
        // Rien à faire
    }
    else
    {
        printf("Erreur dans l'analyse de HEAD\n");
        exit(-1); 
    }
}

void analyse_TEXT(FILE * source, char * c)
{
    if (token == MOT)
    {
        scanner(source, c, tokenValue);
        analyse_TEXT(source, c);
    }
    else if (token == MOTCLE_A || token == MOTCLE_T || token == NOUV_PARA || token == SECTION || token == SSECTION || token == FIN)
    {
        // Rien à faire
    }
    else
    {
        printf("Erreur dans l'analyse de TEXT\n");
        exit(-1);
    }
}
