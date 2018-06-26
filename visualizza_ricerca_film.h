/**
 * @file visualizza_ricerca_film.h
 * @brief contiene i prototipi delle procedure di ricerca e visualizzazione del file_film accessibili sia dall' amministratore che dall' utente
 * contiene i corpi delle procedure che ricercano e visualizzano i film nel file_film
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */



#ifndef VISUALIZZA_RICERCA_FILM_H_
#define VISUALIZZA_RICERCA_FILM_H_


/**
 * Questa procedura permette di aprire il file,se esiste, con gli utenti registrati e mostrarne a schermo il contenuto
 */
void visualizza_cat();



/**
 * Questa procedura permette di cercare i film presenti nel catalogo attraverso dei criteri specifici quali genere,regista,anno,nazione o attore
 */
void ricerca_criterio();


/**
 * Questa procedura permette di mostrare a schermo gli ultimi 10 film inseriti.
 */
void ultimi_10film();


/**
 * Questa funzione apre apre il file_film in lettura e mostra i titoli dei film in output restituendo 0 in caso di presenza di almeno un film nel catalogo,1 in caso contrario
 * @return 1 se e presente almeno un film
 * @return 0 se il catalogo e' vuoto
 */
int visualizza_titoli();




#endif /* VISUALIZZA_RICERCA_FILM_H_ */
