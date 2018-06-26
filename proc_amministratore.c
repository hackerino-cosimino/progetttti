/**
 * @file proc_amministratore.c
 * @brief contiene i corpi delle procedure accessibili solo dal menu amministatore
 * Il source file contiene i vari corpi delle procedure usate  esclusivamente dall' amministratore per manipolare e visualizzare i dati sul disco, quali film e utenti
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */

#include "proc_amministratore.h"	//l'header file  contiene tutti i prototipi di procedure usate dell'amministratore
#include "proc_controllo.h"	//l'header file  contiene tutti i prototipi di procedure e funzioni di controllo
#include "visualizza_ricerca_film.h"	//l'header file contiene tutti i prototipi delle procedure di ricerca
#include "struct_cost.h"	//l'header file  contiene un nuovo tipo di dato, delle strutture dati e delle definizioni di costanti
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

/**
 *
 *Apre il file film o lo crea se non esiste e, inseriti tutti i campi della struttura film  la salva nel file in modalita accodamento
 *@warning i film si salvano solo dopo aver inserito tutti i film specificati all'inizio
 */
void inserisci_film()
{
	FILE *p_film;
	param_film film={"","","","","","","",""};
	int i;
	printf("\nquanti film vuoi inserire: ");
	int film_ins=0;		//variabile usata per specificare quanti film si vogliono inserire

	while (scanf("%d",&film_ins) != 1)
	{
		printf("Inserisci un'intero non una stringa: ");
		fflush(stdin);
	}
	p_film=fopen("file_film.dat","ab+");	//apri file_film in modalita accodamento
	if(p_film != NULL)
	{
		for( i=0; i<film_ins; i++)	//finche non si inseriscono tutti i film specificati precedentemente
		{
			printf("\ninserisci il titolo   (max 50 car)   : ");

			//prendi in input il titolo finchè esiste almeno un titolo uguale nel file_film o non è stato inserito nemmeno un carattere
			do{
				fgets(film.titolo,52,stdin);
			}while(strlen(film.titolo) == 1||contr_ins_film(film.titolo) == 1);

			printf("inserisci il genere   (max 50 car)   : ");
			fgets(film.genere,52,stdin);

			printf("inserisci la nazione  (max 30 car)   : ");
			fgets(film.nazione,32,stdin);

			printf("inserisci la regia    (max 80 car)   : ");
			fgets(film.regia,82,stdin);

			printf("inserisci gli attori  (max 100 car)  : ");
			fgets(film.attori,102,stdin);

			printf("inserisci la durata   (max 20 car)   : ");
			fgets(film.durata,22,stdin);

			printf("inserisci l'anno di uscita al cinema : ");
			fgets(film.anno,6,stdin);

			printf("inserisci la trama    (max 500 car)  : ");
			fgets(film.trama,502,stdin);

			if(fwrite(&film,sizeof(param_film),1,p_film) == 1)	//accoda su file la struttura del film presa in input
				printf("\nfilm salvato correttamente\n\n");

			else
				printf("errore di scrittura sul file\n");

		}
		fclose(p_film);

	}else
		printf("\nsi e' verificato un errore nell'apertura del file film\n ");

}




/**
 *Una volta preso in input il titolo del film che si vuole eliminare chiama la funzione contr_eliminazione_film per controllare se il film inserito esiste.
 *
 *Una volta accertatosi che esiste si prosegue con la creazione di un nuovo file e la copia di tutti i film che non corrispondono al film da eliminare nel nuovo file.
 *
 *Terminata la copia rinomina il nuovo file con il nome del vecchio ed elimina il vecchio file.
 */
void elimina_film()
{
	int lettura= 0;
	char scegli= ' ';	//variabile usata per scegliere se si vuole eliminare un altro film o si vuole tornare alla schermata precedente
	char elimina_film[52]= "";
	param_film film= {"","","","","","","",""};
	FILE *p_film;
	FILE *p_film_appoggio;

	if(visualizza_titoli())	//se esiste almeno un film nel catalogo stampa il/i titolo/i
	{
		do
		{
			printf("digita il titolo del film che vuoi eliminare\n");
			do{
				fgets(elimina_film,52,stdin);
			}while(strlen(elimina_film) == 1);

			if( contr_eliminazione_film(elimina_film) == 1)	//controlla se il film inserito esiste nell ' archivio chiamando la procedura contr_eliminazione
			{
				p_film=fopen("file_film.dat","rb");	//apri il file film in lettura
				p_film_appoggio=fopen("file_film_appoggio.dat","wb");	//crea un file per l'aggiornamento.Se il file esiste cancella il contenuto

				if(p_film != NULL && p_film_appoggio != NULL)	//se l'apertura dei due file è avvenuta in maniera corretta
				{
					do
					{
						lettura=fread(&film,sizeof(param_film),1,p_film);
						if( lettura)
						{
							if(strcasecmp(elimina_film,film.titolo) != 0)	/*esegui un confronto tra il film che vuoi eliminare ed il titolo del film presente nel file non distinguendo maiuscole e minuscole*/
								fwrite(&film,sizeof(param_film),1,p_film_appoggio);	//copia nel nuovo file tutti i film tranne quello che si vuole eliminare
							else
								printf("\nil film %se'stato eliminato\n\n",film.titolo);
						}
					}while(lettura);

					fclose(p_film_appoggio);
					fclose(p_film);
					remove("file_film.dat");
					rename("file_film_appoggio.dat","file_film.dat");
				}
				else
				{
					printf("\nerrore dell'apertura dei file\n");
					break;
				}
			}
			printf("vuoi eliminare un altro film?(s o n)\n\n");
			scegli=getch();

		}while(scegli=='s');//reitera finchè non si inserisce un carattere diverso da 's'
	}
}



/**
 * Apre il file film in aggiornamento e confronta il titolo dei film con il titolo inserito dall'amministratore poco prima.Una volta trovato stampa a schermo la struttura dell'utente nascondendo la password con delle '*'.
 *
 * A questo punto l'amministratore decide quale descrizione modificare e prosegue con la digitazione del nuovo testo da sovrascrivere. A questo viene spostato il puntatore a file indietro di una struttura utente per modificare l'utente giusto e viene sovrascritta l'intera struttura letta con pero' le eventuali modifiche apportate.
 * @pre non deve essere gia' stato modificato una volta il nome utente senza uscire dal menu
 * @pre accessibile solo dal menu amministratore
 * @post il file viene modificato correttamente e appare un messaggio di successo restituendo il controllo al menu amministratore.
 */
void modifica_film()
{
	int trovato=0;
	char scelta_modifica=' ';
	int lettura;
	char modifica_film[52]= "";
	param_film film= {"","","","","","","",""};
	FILE *p_film;

	if(visualizza_titoli())	//se esiste almeno un film nel catalogo stampa il/i titolo/i
	{
		p_film=fopen("file_film.dat","rb+");
		printf ("\n\ninserisci il nome del film che vuoi modificare :");

		do{
			fgets(modifica_film,52,stdin);
		}while(strlen(modifica_film) == 1);

		do
		{
			lettura=fread(&film,sizeof(param_film),1,p_film);
			if(lettura)
			{

				if(strcasecmp(modifica_film,film.titolo) == 0)	//confronta il titolo inserito con il titolo del film salvato senza tenere conto di maiuscole o minuscole
				{
					trovato=1;
					printf("cosa vuoi modificare?\n\n1) titolo\n2) genere\n3) nazione\n4) regia\n5) attori\n6) durata\n7) anno\n8) trama\n9) tutti i campi\n\nESC) esci\n");
					scelta_modifica=getch();

					switch(scelta_modifica)
					{
					case '1':

						printf("digita il titolo con il quale vuoi sostituire il vecchio: ");

						do{
							fgets(film.titolo,52,stdin);
						}while(strlen(film.titolo) == 1||contr_ins_film(film.titolo) == 1);

						fseek(p_film,-sizeof(param_film),SEEK_CUR);	//sposta il puntatore al file di una struttura catalogo indietro cosi da modificare il film giusto

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\ntitolo modificato correttamente\n\n");

						lettura=0;
						break;

					case '2':

						printf("digita il genere con il quale vuoi sostituire il vecchio: ");

						do{
							fgets(film.genere,52,stdin);
						}while(strlen(film.genere) == 1);

						fseek(p_film, -sizeof(param_film),SEEK_CUR);

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\ngenere modificato correttamente\n\n");

						lettura=0;
						break;


					case '3':

						printf("digita la nazione con la quale vuoi sostituire la vecchia: ");
						do{
							fgets(film.nazione,32,stdin);
						}while(strlen(film.nazione) == 1);

						fseek(p_film, -sizeof(param_film),SEEK_CUR);

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\nnazione modificata correttamente\n\n");

						lettura=0;
						break;


					case '4':

						printf("digita la regia con la quale  vuoi sostituire la regia precedente salvata: ");
						do{
							fgets(film.regia,82,stdin);
						}while(strlen(film.regia) == 1);

						fseek(p_film, -sizeof(param_film),SEEK_CUR);

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\nregia modificata correttamente\n\n");

						lettura=0;
						break;


					case '5':

						printf("digita gli attori con i quali vuoi sostituire gli attori precedenti salvati: ");
						do{
							fgets(film.attori,102,stdin);
						}while(strlen(film.attori) == 1);

						fseek(p_film, -sizeof(param_film),SEEK_CUR);

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\nattori modificati correttamente\n\n");

						lettura=0;
						break;


					case '6':

						printf("digita la durata con la quale vuoi sostituire la durata precedente salvata:");
						do{
							fgets(film.durata,22,stdin);
						}while(strlen(film.durata) == 1);

						fseek(p_film, -sizeof(param_film),SEEK_CUR);

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\ndurata modificata correttamente\n\n");

						lettura=0;
						break;


					case '7':

						printf("digita l'anno di uscita con il quale  vuoi sostituire l'anno precedente salvato: ");
						do{
							fgets(film.anno,22,stdin);
						}while(strlen(film.anno) == 1);

						fseek(p_film, -sizeof(param_film),SEEK_CUR);

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\nanno modificato correttamente\n\n");

						lettura=0;
						break;



					case '8':

						printf("digita la trama con la quale trama vuoi sostituire la precedente salvata: ");
						do{
							fgets(film.trama,502,stdin);
						}while(strlen(film.trama) == 1);

						fseek(p_film, -sizeof(param_film),SEEK_CUR);

						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\nfilm modificato correttamente\n\n");

						lettura=0;

						break;


					case '9':

						printf("\ninserisci di seguito \ntitolo:  ");
						do{
							fgets(film.titolo,52,stdin);
						}while(strlen(film.titolo) == 1 || contr_ins_film(film.titolo) == 1);

						printf("genere: ");
						do{
							fgets(film.genere,42,stdin);
						}while(strlen(film.genere) == 1);

						printf("nazione: ");
						do{
							fgets(film.nazione,32,stdin);
						}while(strlen(film.nazione) == 1);

						printf("regia: ");
						do{
							fgets(film.regia,82,stdin);
						}while(strlen(film.regia) == 1);

						printf("attori: ");
						do{
							fgets(film.attori,102,stdin);
						}while(strlen(film.attori) == 1);

						printf("durata:");
						do{
							fgets(film.durata,22,stdin);
						}while(strlen(film.durata) == 1);
						printf("anno: ");
						do{
							fgets(film.anno,6,stdin);
						}while(strlen(film.anno) == 1);

						printf("trama: ");
						do{
							fgets(film.trama,502,stdin);
						}while(strlen(film.trama) ==1 );

						fseek(p_film, -sizeof(param_film),SEEK_CUR);
						if(fwrite(&film,sizeof(param_film),1,p_film))
							printf("\nfilm modificato correttamente\n\n");

						lettura=0;
						break;

					case ESC:
						lettura=0;
						break;


					case ' ':
					case '\n':
					case '\t':
						printf("non hai inserito nessun carattere,riprova");
						break;

					default:
						printf("\nil carattere inserito non e' corretto, riprova\n");
						rewind(p_film);

					}
				}
			}
		}while(lettura);
		fclose(p_film);

		if(trovato == 0)
			printf("\nil film non e' presente nel catalogo\n\n");

	}
}



/**
 *Una volta preso in input il nome utente di chi si vuole eliminare chiama la funzione contr_eliminazione_utente per controllare se l'utente inerito esiste.
 *
 *Una volta accertatosi che esiste si prosegue con la creazione di un nuovo file e la copia di tutti gli utenti che non corrispondono all'utente che si vuole eliminare nel nuovo file.
 *
 *Terminata la copia rinomina il nuovo file con il nome del vecchio ed elimina il vecchio file.
 *In questo modo non si lascia alcun dato vecchio nel file.
 *@post creazione di un nuovo file identico al primo senza pero' l'utente eliminato.
 *@post se l' utente inserito non esiste ti chiede se vuoi eliminare un altro utente
 */
void elimina_utente()
{
	char scegli=' ';
	char elimina_utente[22]="";
	int lettura=0;

	utente dati= {"","","",{0,0,0},""};
	FILE *p_utenti;
	FILE *p_ut_appoggio;
	if(visualizza_utenti())	 //se nel file esiste almeno un utente registrato stampali a schermo
	{
		do
		{
			printf("\ndigita il nome utente della persona che vuoi eliminare\n");
			do{
				fgets(elimina_utente,22,stdin);
			}while(strlen(elimina_utente) == 1);

			if(contr_eliminazione_utente(elimina_utente) == 1)	//se l'utente inserito esiste
			{
				p_utenti=fopen("file_utenti.dat","rb");	 //apri file
				p_ut_appoggio=fopen("file_ut_appoggio.dat","wb+");	//crea un file per l'aggiornamento.Se il file esiste cancella il contenuto

				if(p_utenti!=NULL&&p_ut_appoggio != NULL)	//se l'apertura dei due file è avvenuta in maniera corretta
				{
					do
					{
						lettura=fread(&dati,sizeof(utente),1,p_utenti);
						if( lettura)
						{
							if(strcmp(elimina_utente,dati.nomeutente) != 0 )
							{
								fwrite(&dati,sizeof(utente),1,p_ut_appoggio);	/*scrivi sul nuovo file gli utenti che si vogliono tenere,ovvero
						        quelli che non corrispondono al nome utente della persona che si vuole eliminare*/
							}
						}
					}while(lettura);
					fclose(p_ut_appoggio);
					fclose(p_utenti);
					remove("file_utenti.dat");	 //rimuovi il vecchio file con l'utente da eliminare
					rename("file_ut_appoggio.dat","file_utenti.dat");	//rinomina il nuovo file con il nome del vecchio
					printf("\nl'utente %s e'stato eliminato\n\n",elimina_utente);

				}
				else
				{
					printf("\nerrore dell'apertura dei file\n");
					break;
				}
			}
			printf("vuoi eliminare un' altro utente?(s o n)\n\n");
			scegli=getch();
		}while(scegli == 's');	//reitera finchè non si inserisce un carattere diverso da 's'
	}
}






/**
 *Se esiste apre il file_utenti in lettura e mostra gli utenti registrati.Se è presente almeno un utente ritorna 1 altrimenti ritorna 0
 */
int visualizza_utenti()
{
	int pieno=0;
	int lettura;
	utente dati={"","","",{0,0,0},""};
	FILE *p_utenti;
	p_utenti=fopen("file_utenti.dat","rb");	 //apri file_utenti in lettura
	if(p_utenti!=NULL)
	{
		do
		{
			lettura=fread(&dati,sizeof(utente),1,p_utenti);
			if(lettura)
			{
				printf("\n\nNOMEUTENTE   : %sNOME         : %sCOGNOME      : %sDATA NASCITA : %d/%d/%d\nPASSWORD     : %s\n\n",
						dati.nomeutente,dati.nome,dati.cognome,dati.nascita.giorno,dati.nascita.mese,dati.nascita.anno,dati.password);
				pieno=1;
			}
		}
		while(lettura);

		if(pieno == 1)	//se esiste almeno un utente registrato nel file_utenti chiudi il file e restituisci 1
		{
			fclose(p_utenti);
			return 1;
		}
		else
			printf("il catalogo e' vuoto\n");
	}
	else
		printf("\nSi e' verificato un errore nell'apertura del file utenti\n");

	return 0;
}




/**
 * Questa procedura permette di mostrare a schermo i film visti di uno specifico utente con eventuali recensioni
 *@warning confronto nome utente case sensitive
 */
void  visualizza_pref_utente()
{
	FILE*p_preferenze;
	int flag=0;
	int trovato=0;
	char nome_appoggio[22];
	int lettura=0;
	pref_utente preferenze={"","",""};
	p_preferenze=fopen("file_preferenze.dat","rb");	  //apro file preferenze in lettura

	if(p_preferenze != NULL){
		printf("inserisci il nome utente del quale vuoi visualizzare le preferenze: ");

		do{
			fgets(nome_appoggio,22,stdin);
		}while(strlen(nome_appoggio) == 1);

		do
		{
			lettura=fread(&preferenze,sizeof(pref_utente),1,p_preferenze);
			if(lettura)
			{
				if(strcmp(nome_appoggio,preferenze.nome_utente) == 0)	//se il nome utente inserito combacia con quello salvato nel file mostra a mostra a schermo il contenuto
				{
					trovato=1;
					if(flag == 0)
					{
						printf("\n\nFilm visti da %s\n",nome_appoggio);	  //stampa una volta
						flag=1;
					}
					printf("\n-%s %s\n",preferenze.film,preferenze.valutazione);
				}
			}
		}while(lettura);

		if(trovato == 0)	//se il nome utente inserito non combacia con nessuno nel file preferenze
			printf ("l'utente non esiste o non ha ancora visto nessun film");

		fclose(p_preferenze);
	}
	else
		printf("\nsi e' verificato un errore nell'apertura del file\n");

}


