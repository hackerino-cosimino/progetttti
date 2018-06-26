#include "struct_cost.h"
#include <stdio.h>
#ifndef PROC_MODIFICA_H_
#define PROC_MODIFICA_H_

/**
 * @file proc_modifica_utente.h
 * @brief contiene i prototipi delle procedure per modificare l' utente
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */


/**
 * questa procedura serve a modificare l' utente
 * @param p_utenti puntatore al file utenti
 * @param dati puntatore alla struttura dati dell'utente loggato
 */
void modifica_nome_utente (FILE *p_utenti,utente dati);



/**
 * questa procedura serve a modificare l' utente
 * @param p_utenti puntatore al file utenti
 * @param dati puntatore alla struttura dati dell'utente loggato
 *
 */
void modifica_nome (FILE *p_utenti,utente dati);




/**
 * questa procedura serve a modificare l' utente
 * @param p_utenti puntatore al file utenti
 * @param dati puntatore alla struttura dati dell'utente loggato
 *
 */
void modifica_cognome (FILE *p_utenti,utente dati);




/**
 * questa procedura serve a modificare l' utente
 * @param p_utenti puntatore al file utenti
 * @param dati puntatore alla struttura dati dell'utente loggato
 *
 */
void modifica_data_nascita (FILE *p_utenti,utente dati);




/**
 * questa procedura serve a modificare l' utente
 * @param p_utenti puntatore al file utenti
 * @param dati puntatore alla struttura dati dell'utente loggato
 *
 */
void modifica_password (FILE *p_utenti,utente dati);





/**
 * questa procedura serve a modificare l' utente
 * @param p_utenti puntatore al file utenti
 * @param dati puntatore alla struttura dati dell'utente loggato
 *
 */
void modifica_intero_utente (FILE *p_utenti,utente dati);


#endif /* PROC_MODIFICA_H_ */
