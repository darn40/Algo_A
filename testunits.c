#include <algobrutF.h>

/*tests unitaires*/
void printBinary(uint8_t num) {
    int i;
    for (i = sizeof(num) * 5 - 1; i >= 0; i--) {
        if (num & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

void affiche_carre(struct carre *le_carre){
    printf("top : ");
    printBinary(le_carre->line_tp);
    printf("right : ");
    printBinary(le_carre->line_rt);
    printf("bottom : ");
    printBinary(le_carre->line_bo);
    printf("left : ");
    printBinary(le_carre->line_lf);
}

void test_renverse(struct carre *le_carre){
    printf("\n***********test renverse bord****************\n");

    printf("le bord right : " );
    printBinary(le_carre->line_rt);
    printf("sa forme renverser: "); 
    printBinary(reverse_bord(le_carre->line_rt)); 

    
    printf("\n****************tests renverse face****************\n");
    printf("\nles bords normaux: \n" );
    affiche_carre(le_carre);


    printf("\nles bords nouveaux top, right, bottom, left : \n" );
    reverse_face(&le_carre);
    affiche_carre(le_carre);
    
    printf("\nretour au bords de base top, right, bottom, left : \n" );
    reverse_face(&le_carre);
    affiche_carre(le_carre);
}

void test_tourne_carre(struct carre *le_carre){
    printf("\n****************tests tourne carre****************\n");
    printf("\nCarre de base : \n" );
    affiche_carre(le_carre);

    printf("\nCarre ne tourne pas: \n" );
    tourne_carre(&le_carre, left);
    affiche_carre(le_carre);
    

    printf("\nCarre bord top passe à gauche: \n" );
    tourne_carre(&le_carre, top);
    affiche_carre(le_carre);
    printf("retour à la normal ou new bottom à gauche:\n");
    tourne_carre(&le_carre, bottom);
    affiche_carre(le_carre);

    printf("\nCarre bord right: \n" );
    tourne_carre(&le_carre, right);
    affiche_carre(le_carre);
    printf("retour à la normal, ou new right à gauche:\n");
    tourne_carre(&le_carre,right);
    affiche_carre(le_carre);
}

void test_compatible_bo_bo(){
    printf("\n****************tests compatible bord à bord****************\n");
    uint8_t val1 = 0b0;
    uint8_t val2 = 0B0;

    printf("\n Cas 1 :\n");
    val1 = 0B01000;
    printBinary(val1);
    val2 = 0B00110;
    printBinary(val2);

    printf("resultat compatiblite :  %u",compatible_bo_bo(val1, val2));

    printf("\n Cas 2 :\n");
    val1 = 0B11010;
    printBinary(val1);
    val2 = 0B10101;
    printBinary(val2);

    printf("resultat compatiblite :  %u",compatible_bo_bo(val1, val2));
    
    printf("\n Cas 3 :\n");
    val1 = 0B01010;
    printBinary(val1);
    val2 = 0B00100;
    printBinary(val2);

    printf("resultat compatiblite :  %u",compatible_bo_bo(val1, val2));
    
    printf("\n Cas 4 :\n");
    val1 = 0B11010;
    printBinary(val1);
    val2 = 0B00101;
    printBinary(val2);

    printf("resultat compatiblite :  %u",compatible_bo_bo(val1, val2));
    
    printf("\n Cas 5 :\n");
    val1 = 0B01011;
    printBinary(val1);
    val2 = 0B00101;
    printBinary(val2);

    printf("resultat compatiblite :  %u\n",compatible_bo_bo(val1, val2));
    
}

void test_compatible_bo_fa(){
    printf("\n****************tests compatible bord à face****************\n");
    uint8_t val1 = 0b00010;
    struct carre *carre1 = malloc(sizeof(struct carre));
    
    carre1->line_tp = 0B11101;
    carre1->line_rt = 0B11101;
    carre1->line_bo = 0B01100;
    carre1->line_lf = 0B11100;
    carre1->nom = 1;
    
    printf("resultat compatiblite cas 1:  \n");
    printBinary(compatible_bo_fa(val1, carre1));

    carre1->line_tp = 0B10111;
    carre1->line_rt = 0B11101;
    carre1->line_bo = 0B01100;
    carre1->line_lf = 0B10110;
    carre1->nom = 1;
    
    printf("resultat compatiblite cas 1:  \n");
    printBinary(compatible_bo_fa(val1, carre1));
}


int main(){

    printf("Tests unitaires\n");
    struct carre *carre1 = malloc(sizeof(struct carre));
    
    carre1->line_tp = 0B11001;
    carre1->line_rt = 0B10100;
    carre1->line_bo = 0B00110;
    carre1->line_lf = 0B11100;
    carre1->nom = 1;

    printf("le nom du carré est : %u\n", carre1->nom);

    test_renverse(carre1);

    test_tourne_carre(carre1);

    test_compatible_bo_bo();

    test_compatible_bo_fa();
}