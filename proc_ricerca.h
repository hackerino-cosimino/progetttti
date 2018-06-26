
/**
 * @file proc_ricerca.h
 * @brief contiene i prototipi delle funzioni di ricerca dei film in base a dei criteri
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */

#include "struct_cost.h"
#include <stdio.h>
#ifndef PROC_RICERCA_H_
#define PROC_RICERCA_H_



/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 * @param p_film puntatore al file dei film
 * @return 0 se non trova nessun film che combacia con il parametro richiesto
 * @return 1 se trova film che corrispondono
 */
int ricerca_genere (FILE *p_film);




/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 * @param p_film puntatore al file dei film
 * @return 0 se non trova nessun film che combacia con il parametro richiesto
 * @return 1 se trova film che corrispondono
 */
int ricerca_anno (FILE *p_film);




/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 * @param p_film puntatore al file dei film
 * @return 0 se non trova nessun film che combacia con il parametro richiesto
 * @return 1 se trova film che corrispondono
 */
int ricerca_regista (FILE *p_film);




/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 * @param p_film puntatore al file dei film
 * @return 0 se non trova nessun film che combacia con il parametro richiesto
 * @return 1 se trova film che corrispondono
 */
int ricerca_nazione (FILE *p_film);




/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 * @param p_film puntatore al file dei film
 * @return 0 se non trova nessun film che combacia con il parametro richiesto
 * @return 1 se trova film che corrispondono
 */
int ricerca_attore (FILE *p_film);



#endif /* PROC_RICERCA_H_ */
