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

    
}