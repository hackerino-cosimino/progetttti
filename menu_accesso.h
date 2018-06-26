/**
 * @file menu_accesso.h
 * @brief contiene prototipi delle procedure per accedere ai menu o registrarsi alla piattaforma
 * L'header file contiene i vari prototipi delle procedure  di login e di registrazione, i due menu (utente e amministratore) e la procedura per mascherare la password una volta digitata sullo schermo
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */


#include "struct_cost.h"

#ifndef MENU_ACCESSO_H_
#define MENU_ACCESSO_H_







/**
 * Questa procedura permette di accedere al menu amministratore o al menu utente a seconda delle credenziali inserite;se le credenziali non corrisponono stampa un messaggio di errore e torna al main
 *
 */
void login();




/**
 * Inserendo tutti i dati richiesti questa procedura permette di registrarsi sulla piattaforma e salvare i propri dati
 *
 */
void registra ();




/**
 * Questa procedura e' formata da varie chiamate di funzione che compongono il menu amministratore permettendogli di modificare sia il file utente che il file film e mostrarne il contenuto
 *
 */
void menu_amministratore();






/**
 * Questa procedura e' formata da varie chiamate di funzione che compongono il menu utente permettendogli di guardare la lista dei film,simularne la visione,ricercarli in base a dei criteri,modificare il proprio profilo e lasciare pareri sui film visti
 *@param ut_loggato  nome utente della persona che ha effettuato il login
 *@param  pos_utente variabile per salvare la posizione dell utente nel file
 *@param  dati struttura dati dell utente loggato
 */
void menu_utente(char const *ut_loggato,long int pos_utente,utente dati);







#endif /* MENU_ACCESSO_H_ */
