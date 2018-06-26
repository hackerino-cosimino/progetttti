/**
 * @file proc_controllo.c
 * @brief funzioni di controllo nei file
 *
 * Contiene i corpi delle funzioni che servono per controllare l esistenza di un nome utente o un film uguale a quello che si vuole inserire o eliminare.
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */

#include "struct_cost.h"	//l'header file  contiene un nuovo tipo di dato, delle strutture dati e delle definizioni di costanti
#include "proc_controllo.h"	//l'header file  contiene tutti i prototipi di procedure e funzioni di controllo
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

/**
 *
 * Apre il file film in lettura e confronta il titolo passatole come parametro con tutti titoli dei film salvati nel file.
 * @pre il parametro passatole deve essere l'indirizzo del film da controllare
 * @post trovato il nome utente esce tornando 1
 * @post se non trova un film che corrisponde a quello passatole come parametro chiude il file restituendo 0
 * @warning il controllo viene eseguito attraverso case insensitive
 */
int contr_eliminazione_film(char const *titolo_contr)
{
	int lettura=0;
	FILE *p_film;
	p_film=fopen("file_film.dat","rb");
	param_film film={"","","","","","","",""};

	if(p_film != NULL)
	{
		do
		{
			lettura=fread(&film,sizeof(param_film),1,p_film);
			if(lettura)
			{
				if(strcasecmp(film.titolo,titolo_contr) == 0)	//se il film salvato nel file corrisponde con il film da cercare
				{
					fclose(p_film);
					return 1;
				}
			}
		}while(lettura);
		fclose(p_film);
		printf("\nIl film digitato non esiste\n");
	}
	return 0;
}


/**
 *
 * Apre il file utenti in lettura e confronta il nome utente passatole come parametro con tutti i nomi utente salvati nel file.
 * @pre il parametro passatole deve essere l'indirizzo dell'utente da controllare
 * @post trovato il nome utente esce dalla funzione ritornando 1
 * @post se non trova un nome utente che corrisponde a quello passatole come parametro chiude il file restituendo 0
 * @warning il controllo viene eseguito attraverso case insensitive
 *
 */
int contr_eliminazione_utente(char const *nome_ut)
{
	int lettura;
	FILE *p_utenti;
	p_utenti=fopen("file_utenti.dat","rb");
	utente dati={"","","",{0,0,0},""};

	if(p_utenti != NULL)
	{
		do
		{
			lettura=fread(&dati,sizeof(utente),1,p_utenti);
			if(lettura)
			{
				if(strcmp(dati.nomeutente, nome_ut) == 0)	  //se il nome utente salvato nel file corrisponde con il nome utente da cercare
				{
					fclose(p_utenti);
					return 1;
				}
			}
		}while(lettura);
		fclose(p_utenti);
		printf("\nL'utente digitato non esiste\n");
	}
	return 0;
}


/**
 * Apre il file utenti in lettura e confronta il nome utente passatole come parametro con tutti i nomi utenti salvati nel file.
 * @pre il parametro passatogli deve essere l'indirizzo del nome utente da controllare
 * @post trovato il nome utente stampa messaggio di errore
 * @post se non trova un nome utente che corrisponde a quello passatole come parametro chiude il file restituendo 0
 * @warning il controllo viene fatto attraverso case sensitive
 */
int contr_nomeut(char const *nome_ut)
{
	int lettura;
	FILE *p_utenti;
	p_utenti=fopen("file_utenti.dat","rb");
	utente dati={"","","",{0,0,0},""};

	if(p_utenti != NULL)
	{
		do
		{
			lettura=fread(&dati,sizeof(utente),1,p_utenti);
			if(lettura)
			{
				if(strcmp(dati.nomeutente, nome_ut) == 0)	  //se il nome utente esiste gia nel catalogo
				{
					printf("il nome utente e' gia usato,riprova\n\ninserisci un nome utente: ");
					fclose(p_utenti);
					return 1;
				}
			}
		}while(lettura);
		fclose(p_utenti);
	}
	return 0;
}




/**
 * Apre il file film in lettura e confronta il titolo passatole come parametro con tutti i titoli dei film salvati nel file.
 * @pre il parametro passatogli deve essere l'indirizzo del titolo da controllare
 * @post trovato il titolo stampa messaggio di errore
 * @post se non trova un titolo che corrisponde a quello passatole come parametro chiude il file restituendo 0
 * @warning il controllo viene fatto attraverso case insensitive
 */
int contr_ins_film(char const *titolo_contr)
{
	int lettura;
	FILE *p_film;
	p_film=fopen("file_film.dat","rb");
	param_film film={"","","","","","","",""};

	if(p_film != NULL)
	{
		do
		{
			lettura=fread(&film,sizeof(param_film),1,p_film);
			if(lettura)
			{
				if(strcasecmp(film.titolo,titolo_contr) == 0){	//se il titolo del film esiste
					printf("\nil film inserito e' gia' presente nel catalogo,riprova\n\ninserisci un titolo: ");
					fclose(p_film);
					return 1;
				}
			}
		}while(lettura);
		fclose(p_film);
	}
return 0;
}


/**
 *Ogni carattere che prende in input genera un * mascherando la password e contemporaneamente controlla se il carattere inserito e' un segno di punteggiatura o un numero.
 *Una volta premuto invio o inserito venti caratteri se la password contiene almeno un segno di punteggiatura e un numero inserisce '\0' al posto di INVIO per i confronti da effettuare successivamente,
 *Una altrimenti reitera l'inserimento della password non restituendo il controllo alla funzione chiamante
 */
void genera_password(char *password)
{
	int i=0;
	unsigned int num=0;
	unsigned int punt=0;

	do
	{
		punt=0;
		num=0;
		for(i=0;(password[i] = getch())!=INVIO && i < MAX_PASSWORD;i++)	//finchè non premi invio o non inserisci 20 caratteri
		{
			if(password[i]==BACKSLASH && i>0)	//se digiti backslash;  il controllo i>0 evita di cancellare altro oltre la password inserita
			{
				if(isdigit(password[i-1]))	//se il carattere che si vuole cancellare è un numero
					num--;	//sottrai 1 alla variabile segni di punteggiatura;

				if(ispunct(password[i-1]))	//se il carattere che si vuole cancellare è un segno di punteggiatura
					punt--;	 //sottrai 1 alla variabile numeri;

				i=i-2;	//sottai due all'indice per sovrascrivere a partire dal carattere cancellato
				printf("\b \b");	//cancella l'ultima lettera inserita a schermo
			}
			else if(password[i] != BACKSLASH)	//se il carattere non é backslash
			{
				printf("*");

				if(isdigit(password[i]))	//se il carattere è un numero
					num++;
				if(ispunct(password[i]))	//se il carattere è un segno di punteggiatura
					punt++;
			}
			else	//impedisce di cancellare altro oltre le * riferite alla password
			i--;
		}
		if(num == 0)
			printf("\n\nla password deve contenere almeno un numero: ");
		if(punt == 0)
			printf("\nla password deve contenere almeno un segno di punteggiatura: ");

	}while(punt == 0 || num == 0);

	password[i]='\0';	//inserisci un carattere di terminazione stringa alla fine della password

}




/**
 *Ogni carattere che prende in input genera un * mascherando la password senza effettuare controlli sui caratteri inseriti
 *Una volta premuto invio o inserito venti caratteri inserisce '\0' al posto di INVIO per i confronti da effettuare successivamente
 */
void digita_password(char *password)
{
	int i=0;
	for(i=0;(password[i]=getch()) != INVIO && i < MAX_PASSWORD;i++)
	{
		if(password[i]==BACKSLASH&&i>0)
		{
			i=i-2;
			printf("\b \b");
		}
		else if(password[i]!=BACKSLASH)
			printf("*");

		else	//impedisce di cancellare altro oltre le * riferite alla password
					i--;
	}
	password[i]='\0';
}

