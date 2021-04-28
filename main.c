#include "lib/analyseur_lex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *source, *target = NULL;
char c;

int scanner();

int main(int argc, char const *argv[])
{
    // Ouvre le fichier test.txt en lecture seulement
    // (le fichier doit exister) :
    source = fopen("tests/source.md", "r");
    // Cree et ouvre un fichier tmp.html en lecture/ecriture,
    // avec suppression du contenu au prealable :
    target = fopen("tests/target.html", "w+");

    if (source == NULL)
    {
        printf("Impossible d'ouvrir le fichier source\n");
        return -1;
    }

    if (target == NULL)
    {
        printf("Impossible d'ouvrir le fichier target\n");
        return -1;
    }

    c = fgetc(source); // lecture du caractere suivant du fichier source.
    printf("%s\n", &c);
    while(scanner())
    {
        printf("%s\n", &c);
    }
    // while (c!=EOF) // tant que la fin du fichier n'est pas atteinte
    // {
    //     fputc(c,target); // ecrire c dans le fichier target
    //     c = fgetc(source); // lecture du caractere suivant
    // }
    if (source != NULL) fclose(source); // fermeture du fichier source
    if (target!=NULL) fclose(target); //fermeture du fichier target
    
    return 0;
}


int est_caractere(char lettre)
{
    if (
        (lettre >= 97 && lettre <= 122) // [a-z]
    || (lettre >= 65 && lettre <= 90) // [A-Z]
    || (lettre >= 48 && lettre <= 57) // [0-9]
    || (lettre == 44 ||lettre == 45 || lettre == 46 || lettre == 33 || lettre == 63 || lettre == 58 || lettre == 59) // ',' + '-' + '.' + '!' + '?' + ':' + ';'
    )
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int scanner()
{
    goto initial;

    initial:
        if (c == EOF) goto fin; // Etat final
        if (c == '\n') 
        {
            c = fgetc(source);
            goto i_np1;
        }
        if (c == '>')
        {
            c = fgetc(source);
            goto mc1_mc2;
        }
        if (c == '=')
        {
            c = fgetc(source);
            goto s1_ss1;
        }
        if (est_caractere(c))
        {
            c = fgetc(source);
            goto m1;
        }
        if (c == '\t' || c == ' ')
        {
            c = fgetc(source);
            goto initial;
        }
        else goto erreur;


    i_np1: 
        if (c == EOF) goto fin; // Etat final
        if (c == '\n') 
        {
            c = fgetc(source);
            goto i_np1_np2;
        }
        if (c == '>')
        {
            c = fgetc(source);
            goto mc1_mc2;
        }
        if (c == '=')
        {
            c = fgetc(source);
            goto s1_ss1;
        }
        if (est_caractere(c))
        {
            c = fgetc(source);
            goto m1;
        }
        else goto erreur;


    mc1_mc2:
        if(c == 'T')
        {
            c = fgetc(source); // i
            c = fgetc(source); // t
            c = fgetc(source); // r
            c = fgetc(source); // e

            c = fgetc(source);
            goto mc1b;
        }
        if(c == 'A')
        {
            c = fgetc(source); // u
            c = fgetc(source); // t
            c = fgetc(source); // e
            c = fgetc(source); // u
            c = fgetc(source); // r

            c = fgetc(source);
            goto mc2b;
        }
        else goto erreur;

    s1_ss1:
        if(c == EOF || c == '\n' || c == '\t' || c == ' ')
        {
            goto section;
        }
        if(c == '=')
        {
            c = fgetc(source);
            goto ss2;
        }
        else goto erreur;

    m1:
        if (c == EOF || c == '\n' || c == '\t' || c == ' ')
        {
            goto mot;
        }
        if (est_caractere(c))
        {
            c = fgetc(source);
            goto m1;
        }
        else goto erreur;

    i_np1_np2:
        if (c == EOF) goto fin;
        if (c == '\n' || c == ' ' || c == '\t')
        {
            c = fgetc(source);
            goto i_np1_np2;
        }
        if (c == '>')
        {
            c = fgetc(source);
            goto mc1_mc2;
        }
        if (c == '=')
        {
            c = fgetc(source);
            goto s1_ss1;
        }
        if (est_caractere(c))
        {
            goto nouv_para;
        }
        else goto erreur;

    mc1b:
        if (c == EOF || c == '\n' || c == ' ' || c == '\t')
        {
            goto titre;
        }
        else goto erreur;

    mc2b:
        if (c == EOF || c == '\n' || c == ' ' || c == '\t')
        {
            goto auteur;
        }
        else goto erreur;

    ss2:
        if (c == EOF || c == '\n' || c == ' ' || c == '\t')
        {
            goto ssection;
        }
        else goto erreur;

    section:
        token = SECTION;
        return 1;

    mot: 
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
