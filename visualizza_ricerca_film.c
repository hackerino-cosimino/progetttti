/**
 * @file visualizza_ricerca_film.c
 * @brief contiene i corpi delle procedure di ricerca e visualizzazione del file_film accessibili sia dall' amministratore che dall' utente
 * contiene i corpi delle procedure che ricercano e visualizzano i film nel file_film
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */
#include "proc_ricerca.h"	//l'header file contiene tutti i prototipi delle procedure di ricerca
#include "visualizza_ricerca_film.h"	//l'header file contiene tutti i prototipi delle procedure di ricerca e visualizzazion
#include "proc_utente.h"	//l'header file  contiene tutti i prototipi di procedure usate esclusivamenete dll'utente
#include "struct_cost.h"	//l'header file  contiene un nuovo tipo di dato, delle strutture dati e delle definizioni di costanti
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

/**
 *Apre il file_film se esiste e stampa a schermo il contenuto.
 *@param ut_loggato se la procedura e' chiamata da un utente riceve l indirizzo del nome utente di chi ha effettuato il login
 *@pre il file_film deve esistere
 *@post visualizzazione a schermo dei film presenti nel file
 *@post se non ci sono film stampa messaggio
 */
void visualizza_cat(char const *ut_loggato)
{
	char scelta;
	int trovato=0;
	FILE *p_film;
	param_film film={"","","","","","","",""};
	int lettura=1;
	p_film=fopen("file_film.dat","rb");	//apri file_film in lettura
	if(p_film!=NULL)
	{
		//stampa tutti i film presenti finchè non si incontra il caratterere di fine file
		do
		{
			lettura=fread(&film,sizeof(param_film),1,p_film);
			if(lettura)
			{
				printf("\nTITOLO   : %s\nGENERE/I : %s\nNAZIONE  : %s\nREGIA    : %s\nATTORI   : %s\nDURATA   : %s\nANNO     : %s\nTRAMA    : %s\n\n",
						film.titolo,film.genere,film.nazione,film.regia,film.attori,film.durata,film.anno,film.trama);
				printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				trovato=1;
			}
			else if(lettura == 0 && trovato != 1)	//altrimenti se non è stato letto nessun film e non si sta ancora leggendo il file
				printf("il catalogo e'vuoto");
		}
		while(lettura);
		fclose(p_film);

		if(modalita == utenti && trovato == 1)	//se è presente almeno un film e la funzione è stata chiamata da un utente
		{
			printf("\nvuoi guardare un  film?(premi s per guardare)");
			scelta=getch();

			if(scelta == 's')
				guarda_film(ut_loggato);
		}
	}
	else
		printf("\nsi e' verificato un'errore nell'apertura del file film\n");

}




/**
 *Una volta scelta la modalita di ricerca (genere,anno,regista,nazione,attori)chiama la relativa funzione
 * @warning il confronto viene effettuato usando case sensitive
 * @post visualizzazione a schermo dei film richiesti
 * @post se non ci sono film che corrispondono alla richiesta stampa messaggio
 */
void ricerca_criterio(char const *ut_loggato)
{
	char guarda=0;
	FILE *p_film;
	int presente=0;
	char scelta;

	p_film=fopen("file_film.dat","rb");	//apri file film in lettura
	rewind(p_film);
	if(p_film != NULL)
	{
		printf("\n1) ricerca per genere\n2) ricerca per anno\n3) ricerca per regista\n4) ricerca per nazione del film\n5) ricerca per attore\n");
		scelta=getch();

		switch(scelta)
		{
		case '1':


			if(ricerca_genere(p_film) == 1)	//se sono stati trovati film del genere richiesto
				presente=1;
			else
				printf("\nnon ci sono film che corrispondono al genere inserito\n");


			break;



		case '2':

			if(ricerca_anno(p_film) == 1)	//se sono stati trovati film dell' anno richiesto
				presente=1;
			else
				printf("\nnon ci sono film che corrispondono all'anno richiesto\n");


			break;




		case '3':

			if(ricerca_regista(p_film) == 1)	//se sono stati trovati film del regista richiesto
				presente=1;
			else
				printf("\nnon ci sono film che corrispondono al regista inserito\n");


			break;



		case '4':


			if(ricerca_nazione(p_film) == 1)
				presente=1;
			else
				printf("\nnon ci sono film che corrispondono alla nazione richiesta\n");


			break;




		case '5':


			if(ricerca_attore(p_film) == 1)
				presente=1;
			else
				printf("\nnon ci sono film che corrispondono all'attore inserito\n");


			break;




		default:

			printf("\nscelta non valida\n\n");
			break;
		}

		fclose(p_film);

		if(modalita == utenti && presente == 1)	//se è stato trovato almeni un film ed è un utente che hachiesto di cercare un film
		{
			printf("\nvuoi guardare un  film?(premi s per guardare)");
			guarda=getch();

			if(guarda == 's')
				guarda_film(ut_loggato);
		}
	}
	else
		printf("\nsi e' verificato un errore nell' apertura del file\n");


}




/**
 * Apre il file_film in lettura e sposta il puntatore del file indietro di dieci strutture film a partire dalla fine del file e stampa i film presenti a partire da quella posizione fino alla fine del file
 *@post visualizzazione a schermo degli ultimi 10 film inseriti
 */

void ultimi_10film(char const *ut_loggato)
{
	char guarda;
	FILE *p_film;
	param_film film={"","","","","","","",""};
	int pieno=0;
	int lettura;

	p_film=fopen("file_film.dat","rb");	//apri file film in lettura
	if(p_film != NULL)
	{
		fseek(p_film,-10*sizeof(param_film),SEEK_END);	//sposta l'indicatore interno al file di 10 posizioni indietro a partire dalla fine
		do
		{
			lettura=fread(&film,sizeof(param_film),1,p_film);
			if(lettura)
			{
				printf("\nTITOLO   : %s\nGENERE/I : %s\nNAZIONE  : %s\nREGIA    : %s\nATTORI   : %s\nDURATA   : %s\nANNO     : %s\nTRAMA    : %s\n\n",
						film.titolo,film.genere,film.nazione,film.regia,film.attori,film.durata,film.anno,film.trama);
				printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				pieno=1;
			}
			else if(!lettura && pieno != 1)
				printf("il catalogo e'vuoto");


		}while(lettura);
		fclose(p_film);

		if(modalita == utenti && pieno == 1)
		{
			printf("\nvuoi guardare un  film?(premi s per guardare)");
			guarda=getch();

			if(guarda == 's')
				guarda_film(ut_loggato);


		}
	}
	else
		printf("\nsi e' verificato un errore nell'apertura del file\n");

}



/**
 * Apre il file film in lettura e stampa a schermo tutti i titoli dei film presenti.Se il catalogo e' vuoto ritona 0 atrimenti ritorna 1.
 */

int visualizza_titoli()
{
	int lettura=0;
	param_film film={"","","","","","","",""};
	FILE *p_film;
	p_film=fopen("file_film.dat","rb");
	if(p_film != NULL){
		printf("\n\n%s\n\n","FILM");
		do
		{
			lettura=fread(&film,sizeof(param_film),1,p_film);
			if(lettura)
			{
				printf("%-40s\n",film.titolo);
			}
		}while(lettura);
		fclose(p_film);
		return 1;

	}else
		printf("\nSi e' verificato un errore nell'apertura del catalogo dei film\n");

	return 0;

}




