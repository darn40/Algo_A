#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*On part du prrinicipe qu'on a pas de pièce 0000 ou 1111*/

/**
 * @struct carre
 * @brief structure d'une pièce du puzzle,
 * les bords sont des binaires
 */
struct carre
{
    uint8_t line_tp; /* bord du haut */
    uint8_t line_rt; /* bord de droite */
    uint8_t line_bo; /* bord du bas */
    uint8_t line_lf; /* bord de gauche */
    char nom;
    carre *suivant;
    carre *precedent; // ne pas oublier d'inialiser à null
    bool reverse; // initialiser à false //pas encore traité
}typedef carre;



enum bord{top, right, bottom, left}typedef bord;

/**
 * @fn tourne carre
 * @brief tourne un carre du puzzle, redefinissant ainsi les bord,
 * le sens dans lequel on tourne n'a pas d'importance
 * 
 * @param face le carré considéré
 * @param new_left  le bord qui sera placé à gauche 
 */
void tourne_carre(carre** face, bord new_left){
    uint8_t tab[] = {(*face)->line_tp, (*face)->line_rt, (*face)->line_bo, (*face)->line_lf};
    
    uint8_t val;
    switch (new_left)
    {
        case top:
            val = -1;
            break;
        case right:
            val = 0;
        case bottom:
            val = 1;
        case left:
            val = 2;        
        default:
            exit(-1);
    }

    (*face)->line_tp = tab[(val + 2)%4]; 
    (*face)->line_rt = tab[(val + 3)%4];
    (*face)->line_bo =  tab[(val + 4)%4];
    (*face)->line_lf =  tab [(val + 5)%4];
}

/**
 * @brief 
 * 
 * @param bord1 
 * @param bord2 
 * @return uint8_t 
 */
uint8_t compatible_bo_bo(uint8_t bord1, uint8_t bord2){
    if (bord1 + bord2 == 0b01110 
        | bord1 + bord2 == 0b11110 
        | bord1 + bord2 == 0b01111 
        | bord1 + bord2 == 0b11111) return 1; 

    else return 0;
}

/**
 * @brief vérifie si un a des compatibilité à un carré sous forme de bit  de 4 bit
 * 
 * @param bord 
 * @param face 
 * @return uint8_t 
 */
uint8_t compatible_bo_fa(uint8_t bord, carre* face){
    uint8_t tab[4] = {face->line_tp, face->line_rt, face->line_bo, face->line_lf};
    uint8_t res; 
    for (uint8_t i=0; i< 4; i++){
        /*if (bord + tab[i] == 0b01110 
        | bord + tab[i] == 0b11110 
        | bord + tab[i] == 0b01111 
        | bord + tab[i] == 0b11111){
        res += 1;
        }*/
        res+=compatible_bo_bo(bord, tab[i]);
    
        res = res << 1;
    }
}

/**
 * @brief 
 * 
 * @param a_list 
 * @return uint8_t 
 */
uint8_t compatible_fa_fa(uint8_t a_list[], carre* face){
    for (uint8_t i = 0; i < 4; i++){
        if (compatible_bo_bo(face->line_tp, a_list[i%4]) ==1 
            && compatible_bo_bo(face->line_rt, a_list[(i+1)%4]) ==1){
            // le xor entre 3 bord 
            if ((face->line_tp & 1) ^ (a_list[i%4] & 1) ^ ((a_list[(i+1)%4])>>3)){
                if (compatible_bo_bo(face->line_bo, a_list[(i+2)%4]) == 1 
                    && compatible_bo_bo(face->line_lf, a_list[(i+3)%4]) == 1){
                    // le xor entre 3 bord 
                    if ((face->line_lf & 1) ^ (a_list[(i+3)%4] & 1) ^ ((a_list[(i+2)%4])>>3)){
                        return a_list[(i+3)%4];
                    }
                }
            }
        }
    }
    return 0; //  si on part du principe q'on a pas de piece 0000
}

void verif_two_last_piece(carre* face, carre *list_two_faces[], uint8_t nbelem_list){
    if (nbelem_list != 2){print(nbelem_list + "verif two last piece"); exit(-1);}

    uint8_t list_tp_borders[4];
    uint8_t list_bo_borders[4];

    uint8_t compt = 0;
    while (face->precedent != NULL){
        list_tp_borders[compt] = face->line_tp;
        list_bo_borders[compt] = face->line_bo;
    }

    // reste à comparer les deux dernière face restantes

    for(uint8_t i = 0; i < 2; i++){
        uint8_t val1 = compatible_fa_fa(list_tp_borders, list_two_faces[i]); 
        if(val1 != 0){
            /*tourne_carre(&list_two_faces[i],val1);
            face->suivant = list_two_faces[i];
            list_two_faces[i]->precedent = face;*/
            uint8_t val2 = compatible_fa_fa(list_bo_borders, list_two_faces[(i+1)%2]);
            if(val2 !=0){
                tourne_carre(&list_two_faces[i],val1);
                face->suivant = list_two_faces[i];
                list_two_faces[i]->precedent = face;

                tourne_carre(&list_two_faces[(i+1)%2],val1);
                face->suivant = list_two_faces[i];
                list_two_faces[i]->precedent = face;
            } 

        }
    }
}


//les carrés ont un nom faire un recursif qi print les noms à la fin 
/**
 * @brief 
 * 
 * @param face la pièce considérée du puzzle
 * @param list_face liste des faces pas encore placées
 * @param nbelem_list la taille de list_face
 * @return carre* 
 */
void recherche_intermediaire(carre *face, carre *list_face[], uint8_t nbelem_list){
    if (nbelem_list >=3){
        for (uint8_t i=0; i<nbelem_list; i++){
            uint8_t res = compatible_bo_fa(list_face[0]->line_rt, list_face[i]);
            
            if (res != 0){
                face->suivant = list_face[i];
                list_face[i]->precedent = face;

                carre *new_list[nbelem_list-1];
                uint8_t compt = 0;
                for (uint8_t z = 0; z < nbelem_list; z++)
                    if(list_face[z]->nom != list_face[i]->nom){new_list[compt] = list_face[z]; compt++;}
                
                for (int8_t k = 3; k > -1; k--){
                    if (res & 0b0001 == 1){ /*postion des bitsdans res, respectivement, top right bottom left*/

                        /* tourner le carré si nécessaire*/
                        tourne_carre(&list_face[i], k);
                        recherche_intermediaire(list_face[i], new_list, nbelem_list-1);
                    }
                    if(k>0)res >> 1;
                }
                
            }
        }
    }

    else{
        
    }
}


carre* recherche_solution(carre liste_face[6]){
    return 0;
}