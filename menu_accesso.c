
/**
 * @file menu_accesso.c
 * @brief contiene i corpi  delle procedure per accedere ai menu o registrarsi alla piattaforma
 * Il source file contiene i vari corpi delle procedure  di login e di registrazione e i due menu (utente e amministratore)
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */

#include "proc_controllo.h"	//l'header file  contiene tutti i prototipi di procedure e funzioni di controllo
#include "visualizza_ricerca_film.h"	//l'header file contiene tutti i prototipi delle procedure di ricerca
#include "proc_utente.h"	//l'header file  contiene tutti i prototipi di procedure usate esclusivamenete dll'utente
#include "struct_cost.h"	//l'header file  contiene un nuovo tipo di dato, delle strutture dati e delle definizioni di costanti
#include "menu_accesso.h"	//l'header file  contiene tutti i prototipi di procedure per effettuare l'accesso e i 2 menu
#include "proc_amministratore.h"	//l'header file  contiene tutti i prototipi di procedure usate dell'amministratore
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>


/**
 *Apre o crea file_utenti se non esiste.
 *
 *Prende in input le credenziali dell'utente inserendole nella struttura utente e salvandola nel file in modalita accodamento.
 */
void registra ()
{
	FILE *p_utenti;
	utente dati= {"","","",{0,0,0},""};

	p_utenti=fopen("file_utenti.dat","ab+");	//apri il file_utenti.dat in accodamento in modalità binaria oppure se non esiste crealo e assegnalo al puntatore p_utenti
	if(p_utenti != NULL)
	{
		printf("\ninserisci un nome utente: ");

		do{	//prendi in input il nome utente finchè esiste almeno un nome utente uguale nel file o non è stato inserito nessun carattere
			fgets(dati.nomeutente,21,stdin);
		}while(strlen(dati.nomeutente) == 1 || contr_nomeut(dati.nomeutente) == 1);

		printf("Inserisci il tuo nome: ");

		do{
			fgets(dati.nome,22,stdin);
		}while(strlen(dati.nome) == 1);

		printf("Inserisci il tuo cognome: ");

		do{
			fgets(dati.cognome,22,stdin);
		}while(strlen(dati.cognome) == 1);

		printf("inserisci il tuo giorno, mese e anno di nascita separati da uno spazio (es.31 10 1993)\n");

		//prendi in input la data di nascita finchè non sono stati inseriti solo numeri
		while(scanf("%2d",&dati.nascita.giorno) != 1||scanf("%2d",&dati.nascita.mese) != 1||scanf("%4d",&dati.nascita.anno) != 1)
		{
			printf("puoi inserire soltanto numeri,riprova(es 31 10 1993)\n");
			fflush(stdin);
		}

		printf("Inserisci una password sicura (max 20 caratteri): ");
		genera_password(dati.password);

		if(fwrite(&dati,sizeof(utente),1,p_utenti) == 1) //se la scrittura riesce correttamente mostra messaggio di successo
			printf("\n\noperazione riuscita\naccedi con le tue credenziali dal menu login\n\n");

		else
			printf("errore di scrittura sul file");

		fclose(p_utenti);
	}
	else
		printf("\nsi e' presentato un'errore nell'apertura del file utenti\n");

}


/**
 *Prende in input nome utente e password e le confronta con le credenziali dell'amministatore create al momento dell'apertura della procedura.
 *
 * Se non combaciano apre il file_utenti e controlla se le credenziali corrisponodo con quelle degli utenti.
 *
 * Se le credenziali combaciano con quelle dell' amministratore o con quelle di un utente apre il corrispondente menu altrimenti torna al main.
 * @warning  confronto nome utente con case sensitive
 */
void login()
{
	int lettura=0;
	char pass_amm[21]="123";	//password amministratore
	char nome_amm[22]="cosimo\n";	//nome utente amministratore.\n serve per fare il confronto con strcmp nel modo giusto
	char pass_appoggio[21]="";
	char nomeut_appoggio[22]="";
	unsigned int login=0;	//variabile usata per capire se si è riusciti a fare il login
	utente dati= {"","","",{0,0,0},""};
	FILE *p_utenti;
	long int pos_utente;	//variabile usata per salvare la posizione dell utente nel file

	printf("\nnome utente : ");
	do{
		fgets(nomeut_appoggio,22,stdin);
	}while(strlen(nomeut_appoggio) == 1);

	printf("\npassword    : ");
	digita_password(pass_appoggio);

	//se il nome e la password inserita combaciano con quelle salvate dell'amministatore chiama il menu amministratore
	if(strcmp(nomeut_appoggio,nome_amm) == 0 && strcmp(pass_appoggio,pass_amm) == 0)
	{
		modalita=amministratore;
		printf("\n\n\nBENVENUTO NEL MENU AMMINISTRATORE\n");
		menu_amministratore();
	}
	else
	{
		p_utenti=fopen("file_utenti.dat","rb");
		if(p_utenti!=NULL)
		{
			//leggi tutto il file e confronta la password e il nome utente degli utenti registrati
			do
			{
				lettura=fread(&dati,sizeof(utente),1,p_utenti);
				if(lettura)//se non è stato letto EOF
				{
					//se la password e il nome utente combaciano con uno dei profili salvati nel file chiudi quest'ultimo e vai al menu utente
					if(strcmp(nomeut_appoggio,dati.nomeutente)==0 && strcmp(pass_appoggio,dati.password)==0)
					{
						pos_utente=ftell(p_utenti);
						fclose(p_utenti);
						modalita=utenti;
						printf("\n\n\nBenvenuto %s",dati.nomeutente);
						menu_utente(dati.nomeutente,pos_utente,dati);
						login=1;
						lettura=0;
					}
				}
			}
			while(lettura);

			if(login != 1)
			{
				printf("\nil nome utente e la password non corrispondono\n\n");
				fclose(p_utenti);
			}
		}
		else
			printf("\nsi e' verificato un errore nell'apertura del file utenti\n");

	}
}




/**
 *Il menu amministratore e' formata da uno switch con le varie chiamate a procedure per permettere la manipolazione dei film e degli utenti nei corrispondenti file
 *
 */
void menu_amministratore()
{
	char continua=1;
	char menu;

	do
	{
		printf("\n\nMenu amministratore\n\n");
		printf("1) inserisci film\n2) elimina film\n3) elimina utenti\n4) ricerca film in base a dei criteri\n"
				"5) visualizza il catalogo dei film\n6) visualizza preferenze utenti\n7) visualizza i 10 film piu recenti\n8) modifica film \n9) visualizza utenti registrati\n\nESC) esci\n\n");

		menu=getch();

		switch(menu)
		{
		case '1':
			inserisci_film();
			break;

		case '2':
			elimina_film();
			break;

		case '3':
			elimina_utente();
			break;

		case '4':
			ricerca_criterio();
			break;

		case '5':
			visualizza_cat();
			break;

		case '6':
			visualizza_pref_utente();
			break;

		case '7':
			ultimi_10film();
			break;

		case '8':
			modifica_film();
			break;

		case '9':
			visualizza_utenti();
			break;

		case ESC:
			continua=0;
			break;

		case ' ':
		case '\n':
		case '\t':
			printf("non hai inserito nessun carattere,riprova\n\n");
			break;


		default:
			printf("\nil carattere inserito non e' corretto.Riprova\n\n ");
		}
	}
	while(continua);

}



/**
 * Il menu utente e' formato da uno switch con le chiamate a procedure per cercare film,simularne la visione, aggiungere le proprie preferenze e modificare il proprio profilo manipolando il file_utenti
 * @param ut_loggato  nome utente della persona che ha effettuato il login
 * @param pos_utente variabile per salvare la posizione dell utente nel file
 * @param dati struttura dati dell utente loggato
 */
void menu_utente (char const *ut_loggato,long int pos_utente,utente dati)
{
	char continua=1;
	char menu;

	while(continua)
	{
		printf("\n\nMenu\n\n");
		printf("1) visualizza catalogo film\n2) ricerca film in base a dei criteri\n"
				"3) visualizza i 10 film piu recenti\n4) modifica profilo\n\nESC) esci\n");

		menu = getch();

		switch(menu)
		{
		case '1':
			visualizza_cat(ut_loggato);
			break;

		case '2':
			ricerca_criterio(ut_loggato);
			break;

		case '3':
			ultimi_10film(ut_loggato);
			break;

		case '4':
			modifica_utente(pos_utente,dati);
			break;

		case ESC:
			continua=0;
			break;

		case ' ':
		case '\n':
		case '\t':
			printf("non hai inserito nessun carattere,riprova\n\n");
			break;

		default:
			printf("\nil carattere inserito non e' corretto.Riprova\n\n ");

		}
	}
}






