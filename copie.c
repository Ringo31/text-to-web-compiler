#include "lib/analyseur_lex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// int scanner();

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

    char c = fgetc(source); // lecture du caractere suivant du fichier source.
    while (c!=EOF) // tant que la fin du fichier n'est pas atteinte
    {
        fputc(c,target); // ecrire c dans le fichier target
        c = fgetc(source); // lecture du caractere suivant
    }
    if (source != NULL) fclose(source); // fermeture du fichier source
    if (target!=NULL) fclose(target); //fermeture du fichier target
    
    return 0;
}

