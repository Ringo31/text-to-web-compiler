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

void analyse_BODY(FILE * source, char * c)
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

void analyse_P(FILE * source, char * c)
{
    // Si token dans possibles(P -> NOUV_PARA Text P)
    if(token == NOUV_PARA)
    {
        if(token == NOUV_PARA) scanner(source, c, tokenValue);
        else
        {
            printf("Erreur analyse P.\n");
            exit(-1);
        }
        analyse_TEXT(source, c);
        analyse_P(source, c);
    }
    // Sinon si token dans possibles(P -> epsilon)
    else if(token == SECTION || token == SSECTION || token == FIN)
    {
        // Rien à faire
    }
    else
    {
        printf("Erreur analyse P.\n");
        exit(-1);
    }
}

void analyse_S1(FILE * source, char * c)
{
    // Si token dans possibles(S1 -> H1 P S2 S1)
    if(token == SECTION)
    {
        analyse_H1(source, c);
        analyse_P(source, c);
        analyse_S2(source, c);
        analyse_S1(source, c);
    }
    // Sinon si token dans possibles(S1 -> epsilon)
    else if(token == FIN)
    {
        // Rien à faire
    }
    else
    {
        printf("Erreur analyse S1.\n");
        exit(-1);
    }
}

void analyse_H1(FILE * source, char * c)
{
    // Si token dans possibles(H1 -> SECTION Text)
    if(token == SECTION)
    {
        if(token == SECTION) scanner(source, c, tokenValue);
        else
        {
            printf("Erreur analyse H1.\n");
            exit(-1);
        }
        analyse_TEXT(source, c);
    }
    else
    {
        printf("Erreur analyse H1\n");
        exit(-1);
    }
}

void analyse_S2(FILE * source, char * c)
{
    // Si token dans possibles(S2 -> H2 P S2)
    if(token == SSECTION)
    {
        analyse_H2(source, c);
        analyse_P(source, c);
        analyse_S2(source, c);
    }
    // Sinon si token dans possibles(S2 -> epsilon)
    else if(token == SECTION || token == FIN)
    {
        // Rien à faire
    }
    else
    {
        printf("Erreur analyse S2");
        exit(-1);
    }
}

void analyse_H2(FILE * source, char * c)
{
    // Si token dans possibles(H2 -> SSECTION Text)
    if(token == SSECTION)
    {
        if(token == SSECTION) scanner(source, c, tokenValue);
        else
        {
            printf("Erreur analyse H2.\n");
            exit(-1);
        }
        analyse_TEXT(source, c);
    }
    else
    {
        printf("Erreur analyse H2.\n");
    }
}

