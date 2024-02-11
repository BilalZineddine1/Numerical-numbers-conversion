#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour convertir un caractère hexadécimal en décimal

int hexaCaractereEnDecimal(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': case 'a': return 10;
        case 'B': case 'b': return 11;
        case 'C': case 'c': return 12;
        case 'D': case 'd': return 13;
        case 'E': case 'e': return 14;
        case 'F': case 'f': return 15;
        default:
            printf("Caractère invalide : %c\n", c);
            exit(1);
    }
}

// Fonction pour convertir un caractère décimal en hexadécimal

char decimalEnHexaCaractere(int n) {
    switch (n) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default:
            return '\0';
    }
}

// Fonction pour convertir un nombre d'une base A vers la base 10
int convertirEnDecimal(const char* nombre, int baseA) {
    int longueur = strlen(nombre);
    int i;
    int resultat = 0;
    int multiplicateur = 1;

    for ( i = longueur - 1; i >= 0; i--) {
        int chiffre = hexaCaractereEnDecimal(nombre[i]);
        if (chiffre < 0 || chiffre >= baseA) {
            printf("Caractere invalide dans le nombre %s pour la base %d.\n", nombre, baseA);
            exit(1);
        }
        resultat += chiffre * multiplicateur;
        multiplicateur *= baseA;
    }

    return resultat;
}

// Fonction pour convertir un nombre de la base 10 vers la base B
void convertirDeDecimal(int nombreDecimal, int baseB) {
    char resultat[60];
    int k = 0;

    while (nombreDecimal > 0) {
        int reste = nombreDecimal % baseB;
        resultat[k] = decimalEnHexaCaractere(reste);
        k++;
        nombreDecimal /= baseB;
    }

    if (k == 0) {
        printf("0"); // Cas spécial pour le nombre 0
    } else {
        for (int i = k - 1; i >= 0; i--) {
            printf("%c", resultat[i]);
        }
    }

    printf("\n");
}

// Fonction principale pour convertir de la base A à la base B

void convertirBase(char* nombre, int baseA, int baseB) {
    int nombreDecimal = convertirEnDecimal(nombre, baseA);

    printf("Le nombre %s en base %d est equivalent a ", nombre, baseA);
    convertirDeDecimal(nombreDecimal, baseB);
}

int main() {
    char nombre[65];
    int baseA, baseB;

    printf("Entrez le nombre : ");
    scanf("%s", nombre);

    printf("Entrez la base de depart (entre 2 et 16) : ");
    scanf("%d", &baseA);

    printf("Entrez la base de destination (entre 2 et 16) : ");
    scanf("%d", &baseB);

    if (baseA < 2 || baseA > 16 || baseB < 2 || baseB > 16) {
        printf("Les bases doivent etre comprises entre 2 et 16.\n");
        return 1;
    }

    convertirBase(nombre, baseA, baseB);

    return 0;
}
