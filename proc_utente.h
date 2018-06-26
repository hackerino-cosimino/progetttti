/**
 * @file proc_utente.h
 * @brief contiene i prototipi delle procedure accessibili esclusivamente dal menu utente
 * L'header file contiene i prototipi delle procedure usate esclusivamente dall ' utente per simulare la visione di un film e dire se è stato di suo gradimento e modificare il suo profilo
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */

#include "struct_cost.h"

#ifndef PROC_UTENTE_H_
#define PROC_UTENTE_H_


/**
 * Questa procedura crea un nuovo file per le preferenze se non esiste e ,dopo aver chiesto l'opinione dell'utente riguardo il film salva nel file il nome dell'utente,il film visto ed eventuale preferenza nel file
 * @param ut_loggato nome utente della persona che ha effettuato il login per salvare le preferenze
 */
void guarda_film(char const *ut_loggato);


/**
* prototipo della procedura per scrivere la recensione del film su di un file
* @param ut_loggato puntatore al nome utente di chi ha effettuato il login
* @param film_guardato puntatore  al film di cui si è simulata la visione
*/
void recensiona_film(char const*ut_loggato,char const *film_guardato);


/**
 * Questa procedura apre il file_utenti in aggiornamento e permette di sovrascrivere sui dati gia presenti,sia se si vuole modificare un solo campo sia se si vuole modificarli tutti,nascondendo i vecchi dati ma non eliminandoli del tutto.
 * @param  pos_utente variabile per salvare la posizione dell utente nel file
 * @param  dati struttura dati dell utente loggato
 */
void modifica_utente (long int pos_utente,utente dati);


#endif /* PROC_UTENTE_H_ */
