#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <algobrutF.h>

/*On part du prrinicipe qu'on a pas de pièce 00000 ou 11111*/
/* Un peu trop de 4 un peu partout, rendre portable pour un carré à n face*/

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


uint8_t reverse_bord(uint8_t bord){
    uint8_t res = 0;
    for (uint8_t k = 0; k < 5; k++){
        res += ((bord>>k) & 0B1);
        if(k!=4){
            res = res << 1;
        }
    }
    return res;
}

void reverse_face(struct carre** face){
    uint8_t tab[] = {(*face)->line_tp, 
                    reverse_bord((*face)->line_rt), 
                    (*face)->line_bo, 
                    reverse_bord((*face)->line_lf)};
    
    (*face)->line_tp = tab[2]; 
    (*face)->line_rt = tab[1];
    (*face)->line_bo = tab[0];
    (*face)->line_lf = tab[3];
}

void tourne_carre(struct carre** face, bord new_left){
    uint8_t tab[] = {(*face)->line_tp, (*face)->line_rt, (*face)->line_bo, (*face)->line_lf};
    
    uint8_t val;
    switch (new_left)
    {
        case top:
            tab[0] = reverse_bord(tab[0]);
            tab[2] = reverse_bord(tab[2]);
            val = -1;
            break;
        case right:
            tab[0] = reverse_bord(tab[0]);
            tab[2] = reverse_bord(tab[2]);
            tab[3] = reverse_bord(tab[3]);
            tab[1] = reverse_bord(tab[1]);
            val = 0;
            break;
        case bottom:
            tab[3] = reverse_bord(tab[3]);
            tab[1] = reverse_bord(tab[1]);
            val = 1;
            break;
        case left:
            val = 2;
            break;        
        default:
            exit(-1);
    }

    (*face)->line_tp = tab[(val + 2)%4]; 
    (*face)->line_rt = tab[(val + 3)%4];
    (*face)->line_bo =  tab[(val + 4)%4];
    (*face)->line_lf =  tab [(val + 5)%4];
}


uint8_t compatible_bo_bo(uint8_t bord1, uint8_t bord2){ 
    if ((((bord1 & 0B01110) ^ (bord2 & 0B01110)) == 0b01110) 
        && (((bord1>>4) + (bord2>>4)) <= 1)
        && (((bord1 & 0B1) + (bord2 & 0B1)) <= 1) ) return 1; 

    else return 0;
}

uint8_t compatible_bo_fa(uint8_t bord, struct carre* face){
    uint8_t tab[4] = {reverse_bord(face->line_tp), reverse_bord(face->line_rt), face->line_bo, face->line_lf};
    
    uint8_t res = 0; 
    for (uint8_t i=0; i< 4; i++){
        res+=compatible_bo_bo(bord, tab[i]);
    
        if(i!=3){
            res = res << 1;
        }
    }
    return res;
}

uint8_t compatible_fa_fa(uint8_t a_list[], struct carre** face, bool reversed){ 
    
    for (uint8_t i = 0; i < 4; i++){
        uint8_t value_bord = (i+3)%4;
        tourne_carre(face,value_bord);
        if (compatible_bo_bo((*face)->line_lf, a_list[0]) ==1 
            && compatible_bo_bo((*face)->line_bo, a_list[1]) ==1){
            
            if (((*face)->line_lf & 1) ^ (a_list[0] & 1) ^ ((a_list[1])>>4)){
                
                if (compatible_bo_bo((*face)->line_rt, a_list[2]) == 1 
                    && compatible_bo_bo((*face)->line_tp, a_list[3]) == 1){
                    
                    if (((*face)->line_tp & 1) ^ (a_list[3] & 1) ^ ((a_list[2])>>4)){

                        if((((*face)->line_tp >> 4) ^ (a_list[3] >> 4) ^ ((a_list[0])>>4))
                            && (((*face)->line_rt & 1) ^ (a_list[1] & 1) ^ ((a_list[2]) & 1))
                        )
                        return a_list[3]; 
                    }
                }
            }
        }
 
        if (value_bord == 0) tourne_carre(face, bottom);
        else if (value_bord == 1) tourne_carre(face, right);
        else if (value_bord == 2) tourne_carre(face, top);

    }
    if(reversed == true){
        return 0;
    }
    reverse_face(face);
    return compatible_fa_fa(a_list, face, true);
}

void verif_two_last_piece(struct carre* face, struct carre *list_two_faces[], uint8_t nbelem_list){  
    if(nbelem_list != 2){printf("%i verif two last piece", nbelem_list); exit(-1);} 
    

    uint8_t list_tp_borders[4];
    uint8_t list_bo_borders[4];

    uint8_t compt = 0;
    struct carre *face_copy = face;
    while (face_copy->precedent != NULL){
        if (compt>=2){
            list_tp_borders[compt] = face_copy->line_tp;
            list_bo_borders[compt] = face_copy->line_bo;
        }
        else{
            list_tp_borders[compt] = reverse_bord(face_copy->line_tp);
            list_bo_borders[compt] = reverse_bord(face_copy->line_bo);
        }
        face_copy = face_copy->precedent;
        compt++;
    }
    list_tp_borders[compt] = face_copy->line_tp;
    list_bo_borders[compt] = face_copy->line_bo;
            

    for(uint8_t i = 0; i < 2; i++){
        uint8_t val1 = compatible_fa_fa(list_tp_borders, &(list_two_faces[i]), false); 
        if(val1 != 0){
            uint8_t val2 = compatible_fa_fa(list_bo_borders, &(list_two_faces[(i+1)%2]), false);
            if(val2 !=0){
                face->suivant = list_two_faces[i];
                list_two_faces[i]->precedent = face;

                list_two_faces[i]->suivant = list_two_faces[(i+1)%2];
                list_two_faces[(i+1)%2]->precedent = list_two_faces[i];

                face = list_two_faces[(i+1)%2];
                
                printf("\n********************il y a une solution ****************************\n");
                
                face_copy = face;
                while (face_copy->precedent != NULL){
                    printf("%u ; bord de gauche : ",face_copy->nom); 
                    printBinary(face_copy->line_lf);
                    printf(" ----> ");
                    face_copy = face_copy->precedent;
                }
                printf("%u ; %u ; ",face_copy->nom, face_copy->reverse);
                printBinary(face_copy->line_lf);
                printf("\n");   
                exit(0);    
            } 

        }
    }
}


void recherche_intermediaire(struct carre *face, struct carre *list_face[], uint8_t nbelem_list){
    struct carre *face_copy = face;
    face_copy = face;

    if (nbelem_list >=3){
        for (uint8_t i=0; i<nbelem_list; i++){
            uint8_t res = compatible_bo_fa(face->line_rt, list_face[i]);
            if (res != 0){
                face->suivant = list_face[i];
                list_face[i]->precedent = face;

                struct carre *new_list[nbelem_list-1];
                uint8_t compt = 0;
                for (uint8_t z = 0; z < nbelem_list; z++)
                    if(list_face[z]->nom != list_face[i]->nom){new_list[compt] = list_face[z]; compt++;}
                
                for (int8_t k = 3; k > -1; k--){
                    if ((res & 0b0001) == 1){ 

                        tourne_carre(&list_face[i], k);

                        if ((nbelem_list-1) == 2){
                            if (compatible_bo_bo(list_face[i]->line_rt, face_copy->line_lf) != 0){
                                recherche_intermediaire(list_face[i], new_list, nbelem_list-1);
                            }
                        }else{
                            recherche_intermediaire(list_face[i], new_list, nbelem_list-1);
                            
                            printf("\nREVERSE les carrés : \n");
                            for(uint8_t w =0; w < nbelem_list-1; w++){
                                printf("%u   ", new_list[w]->nom);
                                reverse_face(&new_list[w]);
                            }
                            printf("\n");
                            
                            recherche_intermediaire(list_face[i], new_list, nbelem_list-1); 
                        }
                        
                         
                        if (k == 0) tourne_carre(&list_face[i], bottom);
                        else if (k == 1) tourne_carre(&list_face[i], right);
                        else if (k == 2) tourne_carre(&list_face[i], top);
                    }
                    if(k>0)res = res >> 1;
                }
                
            }
        }
    }
    else{
        verif_two_last_piece(face, list_face, nbelem_list);
    }
}


struct carre* recherche_solution(struct carre* liste_face[], uint8_t nbelem_list){
    

    struct carre *new_list[nbelem_list-1];
    uint8_t compt = 0;
    for (uint8_t z = 0; z < nbelem_list; z++)
        if(liste_face[z]->nom != liste_face[0]->nom){new_list[compt] = liste_face[z]; compt++;}
    
    recherche_intermediaire(liste_face[0], new_list, nbelem_list-1);
    
    printf("\n********************il n'y a pas de solution ****************************\n");
    return 0;
}
