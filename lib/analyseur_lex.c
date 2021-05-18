#include "analyseur_lex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int est_caractere(char lettre)
{
    if (
        (lettre >= 'a' && lettre <= 'z')
    || (lettre >= 'A' && lettre <= 'Z')
    || (lettre >= '0' && lettre <= '9')
    || (lettre == ',' ||lettre == '-' || lettre == '.' || lettre == '!' || lettre == '?' || lettre == ':' || lettre == ';' || lettre == '\'' || lettre == '#')
    )
    {
        return 1;
    }

    else
    {
        return 0;
    }
}


int scanner(FILE* source, char* c, char* mot)
{
    int i_mot = 0;
    goto initial;

    initial:
        if (*c == EOF) goto fin; // Etat final
        if (*c == '\n') 
        {
            *c = fgetc(source);
            goto i_np1;
        }
        if (*c == '>')
        {
            *c = fgetc(source);
            goto mc1_mc2;
        }
        if (*c == '=')
        {
            *c = fgetc(source);
            goto s1_ss1;
        }
        if (est_caractere(*c))
        {
            mot[i_mot] = *c;
            i_mot++;
            *c = fgetc(source);
            goto m1;
        }
        if (*c == '\t' || *c == ' ')
        {
            *c = fgetc(source);
            goto initial;
        }
        else goto erreur;


    i_np1: 
        if (*c == EOF) goto fin; // Etat final
        if (*c == '\n') 
        {
            *c = fgetc(source);
            goto i_np1_np2;
        }
        if (*c == '>')
        {
            *c = fgetc(source);
            goto mc1_mc2;
        }
        if (*c == '=')
        {
            *c = fgetc(source);
            goto s1_ss1;
        }
        if (est_caractere(*c))
        {
            mot[i_mot] = *c;
            i_mot++;
            *c = fgetc(source);
            goto m1;
        }
        else goto erreur;


    mc1_mc2:
        if(*c == 'T')
        {
            *c = fgetc(source); // i
            *c = fgetc(source); // t
            *c = fgetc(source); // r
            *c = fgetc(source); // e

            *c = fgetc(source);
            goto mc1b;
        }
        if(*c == 'A')
        {
            *c = fgetc(source); // u
            *c = fgetc(source); // t
            *c = fgetc(source); // e
            *c = fgetc(source); // u
            *c = fgetc(source); // r

            *c = fgetc(source);
            goto mc2b;
        }
        else goto erreur;

    s1_ss1:
        if (*c == EOF || *c == '\n' || *c == '\t' || *c == ' ')
        {
            goto section;
        }
        if(*c == '=')
        {
            *c = fgetc(source);
            goto ss2;
        }
        else goto erreur;

    m1:
        if (*c == EOF || *c == '\n' || *c == '\t' || *c == ' ')
        {
            goto mot;
        }
        if (est_caractere(*c))
        {
            mot[i_mot] = *c;
            i_mot++;
            *c = fgetc(source);
            goto m1;
        }
        else goto erreur;

    i_np1_np2:
        if (*c == EOF) goto fin;
        if (*c == '\n' || *c == ' ' || *c == '\t')
        {
            *c = fgetc(source);
            goto i_np1_np2;
        }
        if (*c == '>')
        {
            *c = fgetc(source);
            goto mc1_mc2;
        }
        if (*c == '=')
        {
            *c = fgetc(source);
            goto s1_ss1;
        }
        if (est_caractere(*c))
        {
            goto nouv_para;
        }
        else goto erreur;

    mc1b:
        if (*c == EOF || *c == '\n' || *c == '\t' || *c == ' ')
        {
            goto titre;
        }
        else goto erreur;

    mc2b:
        if (*c == EOF || *c == '\n' || *c == '\t' || *c == ' ')
        {
            goto auteur;
        }
        else goto erreur;

    ss2:
        if (*c == EOF || *c == '\n' || *c == '\t' || *c == ' ')
        {
            goto ssection;
        }
        else goto erreur;

    section:
        token = SECTION;
        return 1;

    mot: 
        tokenValue[i_mot] = '\0';
        token = MOT;
        return 1;
    
    nouv_para:
        token = NOUV_PARA;
        return 1;

    titre:
        token = MOTCLE_T;
        return 1;

    auteur:
        token = MOTCLE_A;
        return 1;

    ssection:
        token = SSECTION;
        return 1;

    fin:
        token = FIN;
        return 1;

    erreur:
        printf("Aucun token trouvé.\n");
        exit(-1);
}
