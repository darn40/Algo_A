#ifndef __ALGOBRUTF_H__
#define __ALGOBRUTF_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
    uint8_t nom;
    bool reverse; // initialiser à false //pas encore traité
    struct carre *suivant;
    struct carre *precedent; // ne pas oublier d'initialiser à null
};

/**
 * @brief 
 * 
 */
typedef enum {top, right, bottom, left} bord;

/**
 * @fn reverse face
 * @brief 
 * 
 * @param face 
 */
void reverse_face(struct carre** face);

/**
 * @fn tourne carre
 * @brief tourne un carre du puzzle, redefinissant ainsi les bord,
 * le sens dans lequel on tourne n'a pas d'importance
 * 
 * @param face le carré considéré
 * @param new_left  le bord qui sera placé à gauche 
 */
void tourne_carre(struct carre** face, bord new_left);

/**
 * @brief 
 * 
 * @param bord 
 * @return uint8_t 
 */
uint8_t reverse_bord(uint8_t bord);

/**
 * @brief 
 * 
 * @param bord1 
 * @param bord2 
 * @return uint8_t 
 */
uint8_t compatible_bo_bo(uint8_t bord1, uint8_t bord2);

/**
 * @brief vérifie si un bord a des compatibilité avec un carré sous forme de 4 bord de 5 bit  
 * 
 * @param bord 
 * @param face 
 * @return uint8_t 
 */
uint8_t compatible_bo_fa(uint8_t bord, struct carre* face);

/**
 * @brief 
 * 
 * @param a_list 
 * @return uint8_t 
 */
uint8_t compatible_fa_fa(uint8_t a_list[], struct carre** face, bool reversed);

/**
 * @brief 
 * 
 * @param face 
 * @param list_two_faces 
 * @param nbelem_list 
 */
void verif_two_last_piece(struct carre* face, struct carre *list_two_faces[], uint8_t nbelem_list);


//les carrés ont un nom faire un recursif qi print les noms à la fin 
/**
 * @brief fonction secondaire recursive de recherche d'une solution
 * 
 * @param face la pièce considérée du puzzle
 * @param list_face liste des faces pas encore placées
 * @param nbelem_list la taille de list_face
 * @return carre* 
 */
void recherche_intermediaire(struct carre *face, struct carre *list_face[], uint8_t nbelem_list);

/**
 * @brief fonction principale de recherche d'une solution
 * 
 * @param list_face liste des faces pas encore placées
 * @param nbelem_list la taille de list_face
 * @return carre* 
 */
struct carre* recherche_solution(struct carre* liste_face[], uint8_t nbelem_list);

#endif