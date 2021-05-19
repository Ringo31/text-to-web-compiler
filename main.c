#include "lib/analyseur_lex.h"
#include "lib/analyseur_synt.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *source, *target = NULL;
char c;

int main()
{
    // Ouvre le fichier test.txt en lecture seulement
    // (le fichier doit exister) :
    source = fopen("tests/source.md", "r");
    
    if (source == NULL)
    {
        printf("Impossible d'ouvrir le fichier source\n");
        return -1;
    }


    char c = fgetc(source); // lecture du caractere suivant du fichier source.
    while (token != FIN) // tant que la fin du fichier n'est pas atteinte
    {
        analyse_AXIOME(source, &c);
        // scanner(source, &c, tokenValue);
        // if (token == MOTCLE_T) printf("Titre\n");
        // if (token == MOTCLE_A) printf("Auteur\n");
        // if (token == SECTION) printf("Section\n");
        // if (token == SSECTION) printf("Sous-section\n");
        // if (token == NOUV_PARA) printf("Nouveau paragraphe\n");
        // if (token == MOT)
        // {
        //     printf("Mot : ");
        //     printf("%s\n", tokenValue);
        // }
    }
    if (source != NULL) fclose(source); // fermeture du fichier source
    
    return 0;
}

