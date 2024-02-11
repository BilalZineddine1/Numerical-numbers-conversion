#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool testDebordementVS(int n, int nbBits) {
    int intervalle_min = -pow(2, nbBits);
    int intervalle_max = pow(2, nbBits);

    if (n >= intervalle_min && n <= intervalle_max) {
        return true;
    } else {
        return false;
    }
}

bool testDebordementC1(int n, int nbBits) {
    int intervalle_min = 1 - pow(2, nbBits) / 2;
    int intervalle_max = -1 + pow(2, nbBits) / 2;

    if (n >= intervalle_min && n <= intervalle_max) {
        return true;
    } else {
        return false;
    }
}

bool testDebordementC2(int n, int nbBits) {
    int intervalle_min = -pow(2, nbBits) / 2;
    int intervalle_max = -1 + pow(2, nbBits) / 2;

    if (n >= intervalle_min && n <= intervalle_max) {
        return true;
    } else {
        return false;
    }
}

void affiche(int* tab, int taille){
    for(int i=0; i<taille; i++)
        printf("%d", tab[i]);
}
int nbr_digits_dec(int x){
    int digit=0;
    int A=x;
    while(A!=0){
        A/=2;
        digit++;
    }
    return digit;
}

int nbr_digits_bin(double y) {
    int digit = 0;
    double A = y;
    while(A >= 1) {
        A /= 10;
        digit++;
    }
    return digit;
}

int* tbBin(double bin) {
    int taille = nbr_digits_bin(bin);
    int* binaryArray = (int*)malloc(taille * sizeof(int));
    int B = (int)bin;
    int index = 0;
    while(B != 0) {
        binaryArray[taille - index - 1] = B % 10;
        B /= 10;
        index++;
    }
    return binaryArray;
}

int binEnDec(int* presBin,int taille) {

    int resultat = 0;
    for (int i = 0; i < taille; i++) {
        resultat += presBin[i] * (int)pow(2, taille - 1 - i);
    }
    return resultat;
}
int* decEnBin(int decimalNumber, int nbrBits) {
    int quotient = decimalNumber;
    int* binaryArray = (int*)malloc(nbrBits * sizeof(int));

    // Initialisation du tableau avec des zéros
    for (int i = 0; i < nbrBits; i++) {
        binaryArray[i] = 0;
    }

    int index = 0;

    // Convertir en binaire et stocker dans le tableau
    while (quotient != 0 && index < nbrBits) {
        binaryArray[nbrBits - index - 1] = quotient % 2;
        quotient /= 2;
        index++;
    }

    return binaryArray;
}


// Fonction pour convertir un nombre en nombre signee (VS)
int* decEnVs(int n, int nbBits) {

    int* resultat;
    if (n >= 0) {
    resultat = decEnBin(n, nbBits);
    } else {
    resultat = decEnBin(-n, nbBits);
    resultat[0] = 1;
    }
    return resultat;
    }

// Fonction pour convertir une nombre signee (VS) en representation binaire pure
int* vsEnDec(int* presBin, int nbrBits) {
    if (presBin[0] == 1) {
        // Si le bit de signe est 1, c'est un nombre negatif.
        // Pour le convertir en binaire pur, changez le bit de signe en 0.
        presBin[0] = 0;
        return -binEnDec(presBin, nbrBits);
    }
    return binEnDec(presBin,nbrBits);
}


// Fonction pour convertir un nombre en complement a un (Ca1)
int* decEnC1(int n, int nbBits) {
    if(n >=0){
        return decEnBin(n,nbBits);
    }else{
    int* presBinVS = decEnVs(n, nbBits);

    // Ignorer le bit de signe, qui est le premier bit (index 0)
    for (int i = 1; i < nbBits; i++) {
        if (presBinVS[i] == 0) {
            presBinVS[i] = 1;
        } else {
            presBinVS[i] = 0;
        }
    }

    return presBinVS;
    }
}

// Fonction pour convertir une representation en complement a un (Ca1) en binaire pur
int c1EnDec(int* presBin, int nbrBits) {
    if (presBin[0] == 1){
        int* resultat = presBin;// Allouer de la memoire pour le resultat
        // Inversion des bits sauf le bit de signe
        for (int i = 1; i<nbrBits; i++) {
            if (presBin[i] == 0) {
                resultat[i] = 1;
            } else {
                resultat[i] = 0;
            }
        }
        return vsEnDec(resultat, nbrBits);
    }else{
        // Sinon, c'est un nombre positif en Ca1
        return binEnDec(presBin,nbrBits);
    }
}

// Fonction pour convertir une representation binaire pure en complement a deux (Ca2)
int* decEnC2(int n, int nbBits) {
    int* c1 = decEnC1(n, nbBits); // Convertir en Ca1
    int* resultat = (int*)malloc(strlen(c1) + 1); // Allouer de la memoire pour le resultat
    resultat = c1;
    int retenue  = 1;
    for (int i = strlen(c1) - 1; i >= 0; i--) {
        if (retenue  == 0) {
            resultat[i] = c1[i];
        } else {
            if (c1[i] == 0) {
                resultat[i] = 1;
                retenue  = 0;
            } else {
                resultat[i] = 0;
            }
        }
    }
    return resultat;
}

// Fonction pour convertir une representation en complement a deux (Ca2) en nombre entier
int c2EnDec(int* presBin,int nbBits) {
    // Si le bit de signe est 1, c'est un nombre negatif
    if (presBin[0] == 1) {
        int* valC1 = presBin; // Allouer de la memoire pour le resultat
    // Inversion des bits sauf le bit de signe
    for (int i = 1; i<nbBits; i++) {
        if (presBin[i] == 0) {
            valC1[i] = 1;
        } else {
            valC1[i] = 0;
        }
    }
        // Ajouter 1 en ignorant le bit de signe (index 0)
        int* resultat = valC1; // Allouer de la memoire pour le resultat
        int retenue  = 1;
        for (int i = nbBits - 1; i >= 0; i--) {
            if (retenue  == 0) {
                resultat[i] = valC1[i];
            } else {
                if (valC1[i] == 0) {
                resultat[i] = 1;
                retenue  = 0;
                } else {
                resultat[i] = 0;
                }
            }
        }
        return vsEnDec(resultat,nbBits);
        } else {
        // Sinon, c'est un nombre positif en Ca2
        return binEnDec(presBin,nbBits);
    }
}

// Fonction menu de la conversion de nombre signe en representation volue
void convertirSigneMenu(int nbBits) {
    int choix ;
    printf("Choisissez l'operation :\n");
    printf("1. Conversion de nombre signe en representaion VS (Valeur signee)\n");
    printf("2. Conversion de representaion VS (Valeur signee) en nombre signe\n");
    printf("3. Conversion de de nombre signe en Ca1 (Complement a un)\n");
    printf("4. Conversion de Ca1 (Complement a un) en nombre signe\n");
    printf("5. Conversion de de nombre signe en Ca2 (Complement a deux)\n");
    printf("6. Conversion de Ca2 (Complement a deux) en nombre signe\n");
    printf("7. Quitter\n");
    scanf("%d", &choix );

    if (choix  == 1) {
        int n;
        printf("Entrez un nombre entier : ");
        scanf("%d", &n);
        if (testDebordementVS(n, nbBits)) {
            affiche(decEnVs(n,nbBits),nbBits);
        } else {
            printf("Il y a un problème de debordement!\n");
        }
    } else if (choix  == 2) {
        double nbr;
        printf("Entrez la representation binaire : ");
        scanf("%lf", &nbr);
        int *presBin=(int*)malloc(nbBits*sizeof(int));
        presBin= tbBin(nbr);
        printf("Votre nombre signe est : %d\n",vsEnDec(presBin,nbBits));
    } else if (choix  == 3) {
        int n;
        printf("Entrez un nombre entier : ");
        scanf("%d", &n);
        if (testDebordementC1(n, nbBits)) {
            printf("la representaion en Ca1 de %d est :\n", n);
            affiche(decEnC1(n,nbBits),nbBits);
        } else {
            printf("Il y a un problème de debordement!\n");
        }
    } else if (choix  == 4) {
        double nbr;
        printf("Entrez la representation Ca1 : ");
        scanf("%lf", &nbr);
        int *presBin=(int*)malloc(nbBits*sizeof(int));
        presBin= tbBin(nbr);
        printf("votre nombre signe est : %d\n", c1EnDec(presBin,nbBits));
    } else if (choix  == 5) {
        int n;
        printf("Entrez un nombre entier : ");
        scanf("%d", &n);
        if (testDebordementC2(n, nbBits)) {
            printf("la representaion en Ca2 de %d est : \n", n);
            affiche(decEnC2(n, nbBits),nbBits);
        } else {
            printf("Il y a un problème de debordement!\n");
        }
    } else if (choix  == 6) {
        double nbr;
        printf("Entrez la representation Ca2 : ");
        scanf("%lf", &nbr);
        int *presBin=(int*)malloc(nbBits*sizeof(int));
        presBin= tbBin(nbr);
        printf("Votre nombre signe est : %d\n", c2EnDec(presBin,nbBits));
    } else {
        return;
    }
}

int main() {
    int nbBits;
    printf("Donner le nombre de bits : ");
    scanf("%d", &nbBits);
    convertirSigneMenu(nbBits);
    return 0;
}
