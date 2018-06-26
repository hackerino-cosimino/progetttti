/**
 * @file proc_controllo.h
 * @brief prototipi di funzioni di controllo nei file.
 *
 * Contiene i prototipi delle funzioni che servono per controllare l esistenza di un nome utente o un film uguale a quello che si vuole inserire o eliminare.
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */



#ifndef PROC_CONTROLLO_H_
#define PROC_CONTROLLO_H_

/**
 *  Questa funzione  controlla se il film che si vuole inserire, passatole come parametro ,esiste gia nel catologo.Cosi facendo si evita di salvare due film con lo stesso titolo
 *
 * @param titolo_contr puntatore all'indirizzo del titolo del film che si vuole controllare
 * @return 1 appena trova un film che combacia
 * @return 0 se non trova nessun film che combacia
 */
int contr_ins_film(char const *titolo_contr);



/**
 * Questa funzione controlla se il nome che si vuole inserire, passatole come parametro, esiste gia nel catologo.Cosi facendo si evita di salvare piu' utenti con lo stesso nome utente
 *
 * @param nome_ut puntatore all'indirizzo del nome nome utente da controllare
 * @return 1 appena trova un nome utente che combacia
 * @return 0 se non trova nessun nome utente che combacia
 */
int contr_nomeut(char const *nome_ut);



/**
 *  Questa funzione controlla se il film che si vuole eliminare, passatole come parametro, esiste nel catologo.
 * @param titolo_contr titolo del film da controllare
 * @return 1 appena trova un film che combacia
 * @return 0 se non trova nessun film che combacia
 */
int contr_eliminazione_film(char const *titolo_contr);




/**
 * Questa funzione controlla se il nome utente della persona che si vuole eliminare dal file, passatole come parametro, esiste nel catologo.
 * @param nome_ut puntatore all' indirizzo del nome utente da controllare l'esistenza nel file utenti
 * @return 1 appena trova un nome utente che combacia
 * @return 0 se non trova nessun nome utente che combacia
 */
int contr_eliminazione_utente(char const *nome_ut);


/**
 * Questa procedura fa inserire all'utente una password finche' non contiene almeno un numero e un segno di punteggiatura e contemporaneamente ne maschera l'output con degli asterisci
 * @param password puntatore all'array password della struttura utente dove si salverà la password una volta inserita correttamente
 */
void genera_password(char *password);







/**
 * Questa procedura fa inserire  una password mascherando l'output sullo schermo con degli asterischi.Inoltre premendo backslash cancella l'ultima *.
 * @param password puntatore all'array pass_appoggio,array usato per fare il confronto con le varie password
 */
void digita_password(char *password);



#endif /* PROC_CONTROLLO_H_ */
