#include <algobrutF.h>

int main(){

    printf("hello\n");
    struct carre *carre1 = malloc(sizeof(struct carre));
    struct carre *carre2 = malloc(sizeof(struct carre));
    struct carre *carre3 = malloc(sizeof(struct carre));
    struct carre *carre4 = malloc(sizeof(struct carre));
    struct carre *carre5 = malloc(sizeof(struct carre));
    struct carre *carre6 = malloc(sizeof(struct carre));

    carre1->line_tp = 0B11011;
    carre1->line_rt = 0B10100;
    carre1->line_bo = 0B01010;
    carre1->line_lf = 0B10100;
    carre1->nom = 1;

    carre2->line_tp = 0B00101;
    carre2->line_rt = 0B11011;
    carre2->line_bo = 0B01011;
    carre2->line_lf = 0B00100;
    carre2->nom = 2;

    carre3->line_tp = 0B11010;
    carre3->line_rt = 0B01010;
    carre3->line_bo = 0B01010;
    carre3->line_lf = 0B10100;
    carre3->nom = 3;
    
    carre4->line_tp = 0B10100;
    carre4->line_rt = 0B01011;
    carre4->line_bo = 0B00101;
    carre4->line_lf = 0B11010;
    carre4->nom = 4;

    carre5->line_tp = 0B11010;
    carre5->line_rt = 0B00100;
    carre5->line_bo = 0B00100;
    carre5->line_lf = 0B10100;
    carre5->nom = 5;
    
    carre6->line_tp = 0B01010;
    carre6->line_rt = 0B00100;
    carre6->line_bo = 0B01010;
    carre6->line_lf = 0B00100;
    carre6->nom = 6;


    // carre1->line_tp = 0B01100;
    // carre1->line_rt = 0B01110;
    // carre1->line_bo = 0B01010;
    // carre1->line_lf = 0B00100;
    // carre1->nom = 1;
    // carre1->precedent =NULL;

    // carre2->line_tp = 0B00100;
    // carre2->line_rt = 0B00101;
    // carre2->line_bo = 0B11011;
    // carre2->line_lf = 0B00001;
    // carre2->nom = 2;

    // carre3->line_tp = 0B00011;
    // carre3->line_rt = 0B11011;
    // carre3->line_bo = 0B00011;
    // carre3->line_lf = 0B00100;
    // carre3->nom = 3;
    
    // carre4->line_tp = 0B11011;
    // carre4->line_rt = 0B11011;
    // carre4->line_bo = 0B00011;
    // carre4->line_lf = 0B11100;
    // carre4->nom = 4;

    // carre5->line_tp = 0B00100;
    // carre5->line_rt = 0B00100;
    // carre5->line_bo = 0B11000;
    // carre5->line_lf = 0B00111;
    // carre5->nom = 5;
    
    // carre6->line_tp = 0B00100;
    // carre6->line_rt = 0B01010;
    // carre6->line_bo = 0B01100;
    // carre6->line_lf = 0B01010;
    // carre6->nom = 6;


    struct carre *tab[] = {carre1, carre2, carre3, carre4, carre5, carre6};
    
    recherche_solution(tab, 6);
    printf("hello\n");
    return 0;
}