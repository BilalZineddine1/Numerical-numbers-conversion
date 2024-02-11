#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
int* decimalToBinary(int decimalNumber) {
    int quotient = decimalNumber;
    int taille=nbr_digits_dec(decimalNumber);
    int* binaryArray=(int*)malloc(taille*sizeof(int));
    int index = 0;

    while (quotient != 0) {
        binaryArray[taille-index-1] = quotient % 2;
        quotient /= 2;
        index++;
    }
    return binaryArray;
}

int* fracEnBin(float x, int ver, int* taillefr, int p) {
    int i = 0;
    int *F = (int)malloc((p -ver) * sizeof(int));

      while (i < (p-ver)) {
        x = x * 2;
        if (x >= 1)
        { F[i]=1;
           x -= 1;
        }
        else{F[i]=0;}
        i++;
        }

    *taillefr =p-ver;

    return F;
}
void decimalEnVFixe() {
    float num, F;
    int E, p;
    int* E1;
    int* F1;
    int tailleF1;

    printf("Entrer votre nombre reel:\n");
    scanf("%f", &num);

    // Extraction de la partie entière avec floor()
    E = (int)floor(num);
    // Extraction de la partie fractionnaire
    F = num - E;

    int tailleE1 = nbr_digits_dec(E);
    E1 = (int*)malloc(tailleE1 * sizeof(int));

    printf("Entrer une precision pour la partie fractionnaire\n");
    scanf("%d", &p);

    // Conversion de la partie entière en binaire
    E1 = decimalToBinary(E);

    // Allocation de mémoire pour la partie fractionnaire en binaire
    F1 = (int*)malloc(p * sizeof(int));
    // Conversion de la partie fractionnaire en binaire
    F1 = fracEnBin(F, tailleF1, &tailleF1, p);

    printf("La representation en virgule fixe de votre nombre est : \n");
    affiche(E1, tailleE1);
    printf(".");
    affiche(F1, tailleF1);
    printf("\n");
}
void vFixeEnDecimal(){
    double E,F;
    printf("Entrer la partie entier de ton representation:\n");
    scanf("%lf",&E);
    int tailleE1=nbr_digits_bin(E);
    //on le convertit en un tableau
    int*E1=tbBin(E);
    E=binEnDec(E1,tailleE1);
    printf("Entrer la partie fractionaire de ton representation\n");
    scanf("%lf",&F);
    int tailleF1=nbr_digits_bin(F);
    int*F1=tbBin(F);
    float F2=0;
    float resultat;
    for(int i=0;i<tailleF1;i++){
            F2 += (F1[i] * pow(2, -(i+1)));
    }
    resultat=E+F2;
    printf("la conversion en decimale est : %f\n",resultat);
}
void decimalEnVFlot(int choix) {
    int i, tailleExp, taille, taillefr, signe = 0, E, p;
    int *Ex, *bin_fr;
    float num, fr;
    int *Xbin;

    printf("Entrez votre nombre reel: ");
    scanf("%f", &num);

    // Extraction de la partie entière avec floor()
    int x = (int)floor(num);
    taille = nbr_digits_dec(abs(x));
    if (x < 0)
        signe = 1;

    // Extraction de la partie fractionnaire
    fr = num - x;
    printf("donner la precision:\n");
    scanf("%d",&p);
    Xbin = decimalToBinary(abs(x));
    fr /= pow(10, nbr_digits_dec(fr));
    if(choix==1){
        bin_fr = fracEnBin(fr,taille-1, &taillefr, 23);
        E = (taille - 1) + 127;
        tailleExp=nbr_digits_dec(E);
        Ex = decimalToBinary(E);



        printf("%d ", signe);

        for (i = 0; i < 8; i++) {
            if (i < tailleExp)
                printf("%d", Ex[i]);
            else
                printf("%d", 0);
        }

        printf(" ");

        for (i = 1; i < taille; i++)
            printf("%d", Xbin[i]);

        for (int k = 0; k < taillefr; k++)
            printf("%d", bin_fr[k]);
        }
    if(choix==2){
        bin_fr = fracEnBin(fr,taille-1, &taillefr, 52);
        E = (taille - 1) + 1023;
        tailleExp=nbr_digits_dec(E);
        Ex = decimalToBinary(E);



        printf("%d ", signe);

        for (i = 0; i < 11; i++) {
            if (i < tailleExp)
                printf("%d", Ex[i]);
            else
                printf("%d", 0);
        }

        printf(" ");

        for (i = 1; i < taille; i++)
            printf("%d", Xbin[i]);

        for (int k = 0; k < taillefr; k++)
            printf("%d", bin_fr[k]);
    }
}
void menu() {
    // Affichage du menu
    int choix;
    printf("Veuiller entrer votre choix:\n");
    printf("1.Conversion du Decimal en Virgule Fixe\n");
    printf("2.Conversion du representation Virgule Fixe en Decimal\n");
    printf("3.conversion du Decimal en Virgule Flottante\n");

    // Lecture du choix de l'utilisateur
    scanf("%d", &choix);

    // Appel de la fonction appropriée en fonction du choix de l'utilisateur
    switch (choix) {
        case 1:
            decimalEnVFixe();
            break;
        case 2:
            vFixeEnDecimal();
            break;
        case 3:
            // Demander à l'utilisateur de choisir entre 32 et 64 bits
            printf("Choisissez la taille de virgule flottante (1 pour 32 bits, 2 pour 64 bits): ");
            int choixFlot;
            scanf("%d", &choixFlot);
            decimalEnVFlot(choixFlot);
            break;
        default:
            printf("Option invalide.\n");
    }
}

int main(){
    menu();
}
