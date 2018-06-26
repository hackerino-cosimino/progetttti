/**
 * @file proc_utente.c
  * @brief contiene i corpi delle procedure accessibili esclusivamente dal menu utente
 * Il source file contiene i corpi delle procedure usate esclusivamente dall ' utente per simulare la visione di un film e dire se è stato di suo gradimento e modificare il suo profilo
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */

#include "proc_modifica_utente.h"	//l'header file  contiene le procedure per modificare il profilo utente
#include "visualizza_ricerca_film.h"//l'header file  contiene tutti i prototipi di procedure
#include "proc_controllo.h"	//l'header file  contiene tutti i prototipi di procedure e funzioni di controllo
#include "proc_utente.h"	//l'header file  contiene tutti i prototipi di procedure usate esclusivamenete dll'utente
#include "struct_cost.h"	//l'header file  contiene un nuovo tipo di dato, delle strutture dati e delle definizioni di costanti
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>



/**
 * Apre il file_film e, ricevuto in input dall'utente il film che si vuole guardare lo cerca nel catalogo.
 *
 se trova il film chiama la procedura recensiona_film altrimenti stampa messaggio di errore
 *
 * @param ut_loggato puntatore al nome utente di chi ha effettuato il login
 * @warning il confronto tra il titolo del film che si vuole guardare e i film presenti nel catalogo viene effettuato utilizzando il case insensitive
 */
void guarda_film(char const *ut_loggato)
{
	param_film film= {"","","","","","","",""};
	char film_scelto[52];
	int presente=0;
	int lettura=0;
	FILE *p_film;

	if(visualizza_titoli())
	{
		printf("\n\ninserisci il titolo del film che vuoi guardare: ");
		do{
			fgets(film_scelto,52,stdin);
		}while(strlen(film_scelto) == 1);

		p_film=fopen("file_film.dat","rb");
		if(p_film!=NULL)
		{
			do
			{
				lettura=fread(&film,sizeof(param_film),1,p_film);
				if(lettura)
				{
					if(strcasecmp(film_scelto,film.titolo) == 0)	//il confronto viene fatto non distinguendo maiuscole e minuscole
					{
						presente=1;
						fclose(p_film);
						recensiona_film(ut_loggato,film_scelto);
					}
				}
			}while(lettura);

			if (presente == 0)
				printf("il fim non esiste nel catalogo");

		}
		else
			printf("errore nell'apertura del file utenti\n");
	}

}

/**
* la procedura chiede la recensione del film che si e' simulato di vedere digitanto 'y' se e' stato di suo gradimento o 'n' se non ,o e' stato.
* preso in input il carattere salva nel file_preferenze il nome dell'utente,il film visto e l'eventuale recensione
*/
void recensiona_film(char const *ut_loggato,char const *film_guardato)
{
		pref_utente preferenze={"","",""};
		char piaciuto;
		FILE *p_preferenze;

		printf("\nil film e' stato di tuo gradimento?(s o n)");

					piaciuto=getch();
					if((p_preferenze=fopen("file_preferenze.dat","ab+")) != NULL)	//crea o apri in accodamento un nuovo file per scriverci le preferenze dell'utente loggato
					{
						if(piaciuto == 's')
							strcpy(preferenze.valutazione,"piaciuto");
						else
							if(piaciuto == 'n')

								strcpy(preferenze.valutazione,"non piaciuto");

							else	//se si inserisce un carattere diverso da 's' o 'n'
								{
								printf("\ncarattere inserito non valido, nessuna recensione inserita\n");
								strcpy(preferenze.valutazione,"nessuna recensione");
								}

						strcpy(preferenze.film,film_guardato);	//copia il film che si è scelto di guardare nella varibile di tipo preferenze
						strcpy(preferenze.nome_utente,ut_loggato);	//copia il nome utente della persona loggata nella varibile di tipo preferenze
						fwrite(&preferenze,sizeof(pref_utente),1,p_preferenze);	//accoda su file la struct preferenze
						fclose(p_preferenze);
					}
					else
						printf("\nsi e' presentato un errore nell'aperture del file preferenze\n");

}




/**
 * Apre il file utenti in aggiornamento e cerca il nome utente della persona loggata.Una volta trovato stampa a schermo la struttura dell'utente nascondendo la password con delle '*'.
 *
 * A questo punto l'utente decide quale parametro modificare e prosegue con la digitazione del nuovo parametro da sovrascrivere. A questo viene spostato il puntatore a file indietro di una struttura utente per modificare l'utente giusto e viene sovrascritta l'intera struttura letta con pero' le eventuali modifiche apportate.
 * @pre non deve essere gia' stato modificato una volta il nome utente senza uscire dal menu
 * @post Se il nome utente  non viene trovato significa che si e' cercato di modificare il nome utente per ben due volte di seguito.Questo non e' possibile quindi esce direttamente dalla procedura restituendo il controllo al menu utente.
 * @post il file viene modificato correttamente e appare un messaggio di successo restituendo il controllo al menu utente.
  *@param  pos_utente variabile per salvare la posizione dell utente nel file
  *@param  dati  sa
 */
void modifica_utente (long int pos_utente,utente dati)
{
	char scelta=0;
	int i=0;
	int pass_dim=0;
	int continua=1;
	FILE *p_utenti;

	p_utenti=fopen("file_utenti.dat","rb+");	//apro il file utenti in aggiornamento
	if(p_utenti != NULL)
	{
		fseek(p_utenti,pos_utente,SEEK_CUR);	//sposta il puntatore al file della posizione salvata nella nella procedura di login cosi da modificare l' utente giusto

		printf("\n\nPROFILO ATTUALE\n\n");
		printf("NOMEUTENTE   : %sNOME         : %sCOGNOME      : %sDATA NASCITA : %d/%d/%d\n",
				dati.nomeutente,dati.nome,dati.cognome,dati.nascita.giorno,dati.nascita.mese,dati.nascita.anno);

		pass_dim=strlen(dati.password);
		printf("PASSWORD     : ");

		for(i=0;i < pass_dim;i++)	//stampa * tanti quanti sono i caratteri della password
			printf("*");

		printf("\n");

		do
		{
			printf("\ncosa vuoi modificare?\n\n1) nome utente\n2) nome\n3) cognome\n4) data di nascita\n5) password\n6) tutti i campi\n\nESC) esci\n\n");
			scelta=getch();

			switch(scelta)
			{

			case '1':

				modifica_nome_utente (p_utenti,dati);
				continua=0;	//esci dal ciclo do while
				break;


			case '2':

				modifica_nome (p_utenti,dati);
				continua=0;	//esci dal ciclo do while
				break;


			case '3':
				modifica_cognome (p_utenti,dati);
				continua=0;	//esci dal ciclo do while
				break;


			case '4':
				modifica_data_nascita (p_utenti,dati);
				continua=0;	//esci dal ciclo do while
				break;


			case '5':

				modifica_password (p_utenti,dati);
				continua=0;	//esci dal ciclo do while
				break;



			case '6':
				modifica_intero_utente (p_utenti,dati);
				continua=0;	//esci dal ciclo do while

				break;



			case ESC:
				continua=0;	//esci dal ciclo do while
				break;


			default:
				printf("\nil carattere inserito non e' corretto, riprova\n");
				break;
			}

		}while(continua);	//finchè no si ha modificato qualcosa o si ha premuto il tasto ESC

		fclose(p_utenti);
	}
}


