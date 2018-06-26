#include "proc_modifica_utente.h"
#include <stdio.h>
#include "struct_cost.h"
#include <string.h>
#include "proc_controllo.h"

/**
 * @file proc_modifica_utente.c
 * @brief contiene i corpi  delle procedure per modificare l' utente
 * contiene i corpi  delle procedure per modifica sia il singolo parametro sia l' intero utente sul file utente
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */


/**
 * questa procedura prende in input il nuovo nomeutente con il quale si vuole rimpiazzare  e controlla se gia esiste
 *
 * se il nuovo nome utente non esiste gia nel file lo rimpiazza con il vecchio e torna al menu utente
 *
 */
void modifica_nome_utente (FILE *p_utenti,utente dati)
{
	printf("digita il nuovo nome utente: ");
	do{
		fgets(dati.nomeutente,22,stdin);
	}while(strlen(dati.nomeutente) == 1 || contr_nomeut(dati.nomeutente) == 1);	//finche non e stato inserito niente o il nuono nomeutente esiste

	fseek(p_utenti,-sizeof(utente),SEEK_CUR);	//sposta l'indicatore interno al file di una struct utente indietro per poter modificare l'utente giusto

	if(fwrite(&dati,sizeof(utente),1,p_utenti))	//sovrascrivi nome utente
		printf("\nnome utente modificato correttamente\n\n");

	else
		printf("\nsi  presentato un errore nella modifica del profilo utente\n\n");


}



/**
questa procedura prende in input il nuovo nome con il quale si vuole rimpiazzare  e lo modifica restituendo il controllo al menu_utente
 *
 */
void modifica_nome (FILE *p_utenti,utente dati)
{
	printf("digita il nuovo nome: ");

	do{
		fgets(dati.nome,22,stdin);
	}while(strlen (dati.nome) ==  1);
	fseek(p_utenti,-sizeof(utente),SEEK_CUR);	//sposta l'indicatore interno al file di una struct utente indietro per poter modificare l'utente giusto

	if(fwrite(&dati,sizeof(utente),1,p_utenti))	//sovrascrivi nome
		printf("\nnome modificato correttamente\n\n");
	else
		printf("\nsi è presentato un errore nella modifica del profilo utente\n\n");

}



/**
 * questa procedura prende in input il nuovo cognome che con il quale si vuole rimpiazzare  e lo modifica restituendo il controllo al menu_utente
e
 */
void modifica_cognome (FILE *p_utenti,utente dati)
{
	printf("digita il nuovo cognome: ");

	do{
		fgets(dati.cognome,22,stdin);
	}while(strlen(dati.cognome) == 1);
	fseek(p_utenti, -sizeof(utente),SEEK_CUR);	//sposta l'indicatore interno al file di una struct utente indietro per poter modificare l'utente giusto

	if(fwrite(&dati,sizeof(utente),1,p_utenti))	//sovrascrivi utente
		printf("\ncognome modificato correttamente\n\n");
	else
		printf("\nsi è presentato un errore nella modifica del profilo utente\n\n");

}



/**
 * questa procedura prende in input la nuova data di nascita con il quale si vuole rimpiazzare  e lo modifica restituendo il controllo al menu_utente

 *
 */
void modifica_data_nascita (FILE *p_utenti,utente dati)
{
	printf("digita la nuova data di nascita: ");

	while (scanf("%2d",&dati.nascita.giorno) != 1 || scanf("%2d",&dati.nascita.mese) != 1 || scanf("%4d",&dati.nascita.anno) != 1)
	{
		printf("non puoi inserire lettere,riprova(es 31 10 1993)\n");
		fflush(stdin);
	}

	fseek(p_utenti, -sizeof(utente),SEEK_CUR);	//sposta l'indicatore interno al file di una struct utente indietro per poter modificare l'utente giusto

	if(fwrite(&dati,sizeof(utente),1,p_utenti))	//sovrascrivi utente
		printf("\ndata di nascita modificata correttamente\n\n");
	else
		printf("\nsi è presentato un errore nella modifica del profilo utente\n\n");

}



/**
 * questa procedura prende in input la nuova password e la confronta con la vecchia, de combacia la modifica restituendo il controllo al menu_utente

 *
 */
void modifica_password (FILE *p_utenti,utente dati)
{
	char pass_appoggio[22]="";

	printf("digita la vecchia password: ");

	digita_password(pass_appoggio);
	if(strcmp(pass_appoggio,dati.password) == 0){	//se la password combacia con quella salvata nel file
		printf("\ndigita la nuova password: ");
		genera_password(dati.password);
		fseek(p_utenti, -sizeof(utente),SEEK_CUR);	//sposta l'indicatore interno al file di una struct utente indietro per poter modificare l'utente giusto

		if(fwrite(&dati,sizeof(utente),1,p_utenti))	//sovrascrivi utente
			printf("\n\npassword modificata correttamente\n\n");

		else
			printf("\nsi è presentato un errore nella modifica del profilo utente\n\n");

	}
	else
		printf("\n\nla password non corrisponde\n");

}



/**
 * questa procedura prende in input tutti i campi dell 'utente e modifica l intero utente nel file
 *
 */
void modifica_intero_utente (FILE *p_utenti,utente dati)
{
	char pass_appoggio[22]="";
	printf("digita il nuovo nome utente:  ");

	do{
		fgets(dati.nomeutente,22,stdin);
	}while(strlen(dati.nomeutente) == 1||contr_nomeut(dati.nomeutente) == 1);

	printf("digita il nuovo nome: ");
	do{
		fgets(dati.nome,22,stdin);
	}while(strlen(dati.nome) == 1);

	printf("digita il nuovo cognome: ");

	do{
		fgets(dati.cognome,32,stdin);
	}while(strlen(dati.cognome) == 1);

	printf("digita la nuova data di nascita(es 31 10 1993): ");

	while (scanf("%2d",&dati.nascita.giorno) != 1||scanf("%2d",&dati.nascita.mese) != 1||scanf("%4d",&dati.nascita.anno) != 1)
	{
		printf("non puoi inserire lettere,riprova(es 31 10 1993)\n");
		fflush(stdin);
	}

	printf("digita la vecchia password: ");
	digita_password(pass_appoggio);

	if(strcmp(pass_appoggio,dati.password) == 0)	//se la password combacia con quella salvata nel file
	{
		printf("\ndigita la nuova password : ");
		genera_password(dati.password);
		fseek(p_utenti, -sizeof(dati),SEEK_CUR);	//sposta l'indicatore interno al file di una struct utente indietro per poter modificare l'utente giusto

		if(fwrite(&dati,sizeof(utente),1,p_utenti))	//sovrascrivi utente
			printf("\nutente modificato correttamente\n\n");
		else
			printf("\nsi e' presentato un errore nella modifica del profilo utente\n\n");

	}
	else
		printf("\n\nla password non corrisponde,non e' possibile modificare l'utente\n");

}

