/**
 * @file proc_amministratore.h
 * @brief contiene prototipi delle procedure accessibili solo dal menu amministatore
 * L'header file contiene i vari prototipi delle procedure usate  esclusivamente dall' amministratore per manipolare e visualizzare i dati sul disco, quali film e utenti
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */


#ifndef MODIFICA_FILE_FILM_H_
#define MODIFICA_FILE_FILM_H_


/**
 * Questa procedura chiamata esclusivamente dal menu amministratore permette di salvare salvare nel file i film
 *
 */
void inserisci_film();



/**
 * Questa procedura elimina il film digitato creando un nuovo file e spostando tutti i film che si vogliono mantenere in esso.Infine rinomina il nuovo file con il nome del vecchio cancellando quest'ultimo.
 * Accessibile solo dal menu amministratore
 */
void elimina_film();



/**
 * Questa procedura permette di modificare qualsiasi campo della struttura del film o di modificarlo tutto sovrascrivendo i dati precedenti ma non eniminandoli del tutto.
 *
 */
void modifica_film();


/**
 * Questa procedura elimina l'utente digitato creando un nuovo file e spostando tutti gli utenti che si vogliono mantenere in esso.Infine rinomina il nuovo file con il nome del vecchio cancellando quest'ultimo.
 * Accessibile solo dal menu amministratore
 *
 *
 */
void elimina_utente();


/**
 * Questa funzione apre il file degli utenti in lettura mostrando a schermo il contenuto restituendo 1 in caso di presenza di almeno un utente,0 in caso contrario
 * @return 1 se e presente almeno un utente
 * @return 0 se il catalogo e' vuoto
 */
int visualizza_utenti();


/**
 * Questa procedura permette di aprire il file,se esiste, con le preferenze degli utenti e film visti e mostrare a schermo quelle dell'utente
 *Accessibile solo dal menu amministratore
 *@warning confronto nome utente case sensitive
 */
void visualizza_pref_utente();




#endif /* MODIFICA_FILE_FILM_H_ */
