
/**
 * @file struct_cost.h
 * L'header file contiene  un nuovo tipo di dato, delle strutture dati e delle definizioni di costanti
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */


#ifndef STRUCT_H_
#define STRUCT_H_
/**
 * DEFINE ESC 27 : Codice ASCII corrispettivo al tasto ESC su tastiera
 */
#define ESC 27






/**
 * DEFINE INVIO 13 : Codice ASCII corrispettivo al tasto INVIO su tastiera; utilizzato per uscire dalla modalita di inserimento della password
 */
#define  INVIO 13






/**
 * DEFINE  BACKSLASH 8 : Codice ASCII corrispettivo al tasto BACKSLASH su tastiera; utilizzato per cancellare le * corrispondenti ai caratteri della password mascherata
 */
#define  BACKSLASH 8






/**
 * DEFINE MAX_PASSWORD 20 : Valore massimo per l’inserimento della stringa della password
 */
#define MAX_PASSWORD 20


/**
 * @brief serve a salvare sul file l'opinione dei film visti dai vari utenti
 * Questa struttura,composta da tre campi, e' utilizzata per salvare e leggere le preferenze dei vari utenti su file
 */
typedef struct
{
	char nome_utente[22];/**<  (vettore di caratteri), serve ad inserire il nome utente di chi ha visto un film */
	char film[52];/**<  (vettore di caratteri), serve ad inserire il titolo del film visto */
	char valutazione[19];/**<  (vettore di caratteri), serve ad inserire "piaciuto" o "non piaciuto" o "nessuna recensione" */
}pref_utente;







/**
 * @brief serve ad inserire la daa di nascita dell' utente ed a salvarla nel file
 * Questa sottostruttura ,composta da tre campi ,e' utilizzata per salvare la data di nascita degli utenti
 */
typedef struct
{
	int giorno;/**<  (intero), serve ad inserire il giorno di nascita */
	int mese;/**<  (intero), serve ad inserire il mese di nascita */
	int anno;/**<  (intero), serve ad inserire l'anno di nascita*/
}data;







/**
 * @brief serve ad inserire i dati dell'utente e a salvarli sul file
 * Questa struttura,composta da 4 campi piu' un sottocampo formato a sua volta da 3 campi e' utilizzata per salvare,caricare,modificare,eliminare gli utenti su file
 */
typedef struct
{
    char nomeutente[22];/**<  (vettore di caratteri), serve ad inserire il nome utente */
	char nome[22];/**<  (vettore di caratteri), serve ad inserire il nome */
	char cognome[22];/**<  (vettore di caratteri), serve ad inserire il cognome */
	data nascita;/**<  (sottostruttura di interi), serve ad inserire la data di nascita */
	char password[21];/**<  (vettore di caratteri), serve ad inserire la password */
} utente;







/**
 * @brief serve ad inserire tutti i dati riguardanti un film e di salvarlo sul file
 * Questa struttura, composta da otto campi, e' utilizzata per salvare, caricare, modificare,eliminare, ricercare i file su file
 */
typedef struct
{
	char titolo[52]; /**<  (vettore di caratteri), serve ad inserire il titolo */
	char genere[52]; /**<  (vettore di caratteri), serve ad inserire il genere*/
	char nazione[32];/**<  (vettore di caratteri), serve ad inserire la nazione del film*/
	char regia[82];  /**<  (vettore di caratteri), serve ad inserire il nome del regista*/
	char attori[102];/**<  (vettore di caratteri), serve ad inserire nome e cognome degli attori */
	char durata[22]; /**<  (vettore di caratteri), serve ad inserire la durata complessiva del film*/
    char anno[6];    /**<  (vettore di caratteri), serve ad inserire l'anno di distribuzione */
	char trama[502]; /**<  (vettore di caratteri), serve ad inserire la trama*/
} param_film;



/**
 * @enum stato
 * @brief I valori rappresentano la modalita di accesso nel programma
*/

typedef enum
{
	utenti,  /**<modalita' utente */
	amministratore  /**<modalita' amministratore */

}stato;

/**
 * Variabile di tipo stato. Accetta solo i nomi specificati nella dichiarazione e serve per riconoscere se ad entrare nel programma e' un amministratore o un utente
 */
stato modalita;




#endif /* STRUCT_H_ */
