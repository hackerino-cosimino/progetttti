
/**
 * @file proc_ricerca.c
 * @brief contiene i corpi  delle funzioni di ricerca dei film in base a dei criteri
 * contiene i corpi  delle funzioni di ricerca dei film in base a dei criteri quali il genere, l' anno, la nazione il regista o l attore
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */

#include "proc_ricerca.h"	//l'header file contiene tutti i prototipi delle procedure di ricerca
#include "struct_cost.h"	//l'header file  contiene un nuovo tipo di dato, delle strutture dati e delle definizioni di costanti
#include <string.h>

/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 *
 */
param_film film= {"","","","","","","",""};
char ricerca[20]="";
int lettura=0;
int presente=0;
int flag=0;
int lunghezza=0;

int ricerca_genere (FILE *p_film)
{
	printf("\n\nquale genere vuoi cercare? ");
	gets(ricerca);
	lunghezza=strlen(ricerca);	//ricavo il numero di caratteri del parametro da cercare

	do{
		lettura=fread(&film,sizeof(param_film),1,p_film);
		if(lettura)
		{
			if(lunghezza > 4)	//controlla se il genere che il genere da cercare sia almeno di 5 caratteri,la lunghezza minima di un genere
			{
				if(strstr(film.genere,ricerca) != NULL)	//confronta il genere imnserito con quello dei film
				{
					if(flag == 0)
					{
						printf("\nFilm %s\n",ricerca);	//stampa una volta
						flag=1;
					}
					presente=1;
					printf("\nTITOLO   : %s\nGENERE/I : %s\nNAZIONE  : %s\nREGIA    : %s\nATTORI   : %s\nDURATA   : %s\nANNO     : %s\nTRAMA    : %s\n\n",
							film.titolo,film.genere,film.nazione,film.regia,film.attori,film.durata,film.anno,film.trama);
					printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
			}
			else
			{
				printf("\nil nome inserito non e' valido\n");
				lettura=0;
			}
		}
	}while(lettura);

	if(presente == 1)
		return 1;
	else
		return 0;



}


/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 *
 */
int ricerca_anno (FILE *p_film)
{
	printf("\n\ninserisci l' anno di cui vuoi cercare i film: ");
	fgets(ricerca,6,stdin);
	do
	{
		lettura=fread(&film,sizeof(param_film),1,p_film);
		if(lettura)
		{
			if(strcmp(film.anno,ricerca) == 0)
			{
				if(flag == 0)
				{
					printf("\nfilm %s\n",ricerca);
					flag=1;
				}

				presente=1;
				printf("\nTITOLO   : %s\nGENERE/I : %s\nNAZIONE  : %s\nREGIA    : %s\nATTORI   : %s\nDURATA   : %s\nANNO     : %s\nTRAMA    : %s\n\n",
						film.titolo,film.genere,film.nazione,film.regia,film.attori,film.durata,film.anno,film.trama);
				printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}
		}
	}while(lettura);

	if(presente == 1)
		return 1;
	else
		return 0;

}

/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 *
 */
int ricerca_regista (FILE *p_film)
{
	//algoritmo uguale al case '1'
	printf("\n\ninserisci il nome del regista di cui vuoi cercare i film: ");
	gets(ricerca);
	lunghezza=strlen(ricerca);
	do
	{
		lettura=fread(&film,sizeof(param_film),1,p_film);
		if(lettura)
		{
			if(lunghezza > 2)	//lunghezza minima di un nome di persona
			{
				if(strstr(film.regia,ricerca) != NULL)
				{
					if(flag == 0){
						printf("\nFilm %s\n",ricerca);
						flag=1;
					}
					presente=1;
					printf("\nTITOLO   : %s\nGENERE/I : %s\nNAZIONE  : %s\nREGIA    : %s\nATTORI   : %s\nDURATA   : %s\nANNO     : %s\nTRAMA    : %s\n\n",
							film.titolo,film.genere,film.nazione,film.regia,film.attori,film.durata,film.anno,film.trama);
					printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
			}
			else
			{
				printf("\nil nome inserito non e' valido\n");
				lettura=0;

			}
		}
	}while(lettura);

	if(presente == 1)
		return 1;
	else
		return 0;

}

/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 *
 */
int ricerca_nazione (FILE *p_film){
	//algoritmo uguale al case '2'
	printf("\n\ninserisci la nazione della quale vuoi cercare i film: ");
	fgets(ricerca,20,stdin);
	do
	{
		lettura=fread(&film,sizeof(param_film),1,p_film);
		if(lettura)
		{
			if(strcasecmp(film.nazione,ricerca) == 0)
			{
				presente=1;
				if(flag == 0)
				{
					printf("\nFilm %s\n",ricerca);
					flag=1;
				}

				printf("\nTITOLO   : %s\nGENERE/I : %s\nNAZIONE  : %s\nREGIA    : %s\nATTORI   : %s\nDURATA   : %s\nANNO     : %s\nTRAMA    : %s\n\n",
						film.titolo,film.genere,film.nazione,film.regia,film.attori,film.durata,film.anno,film.trama);
				printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}
		}
	}while(lettura);

	if(presente == 1)
		return 1;
	else
		return 0;

}


/**
 * questa funzione prende in input il parametro da cercare e lo confronta con quello di ogni film. Ogni volta che combacia stampa a schermo quel film.
 *
 */
int ricerca_attore (FILE *p_film)
{	//algoritmo uguale al case '1'
	printf("\n\ni film di quale attore vuoi cercare? ");
	gets(ricerca);
	lunghezza=strlen(ricerca);
	do
	{
		lettura=fread(&film,sizeof(param_film),1,p_film);
		if(lettura)
		{
			if(lunghezza > 2)	//lunghezza minima di un nome
			{
				if(strstr(film.attori,ricerca) != NULL)
				{
					if(flag == 0)
					{
						printf("\nFilm %s\n",ricerca);
						flag=1;
					}
					lettura=0;
					presente=1;
					printf("\nTITOLO   : %s\nGENERE/I : %s\nNAZIONE  : %s\nREGIA    : %s\nATTORI   : %s\nDURATA   : %s\nANNO     : %s\nTRAMA    : %s\n\n",
							film.titolo,film.genere,film.nazione,film.regia,film.attori,film.durata,film.anno,film.trama);
					printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
			}
			else
			{
				printf("\nil nome inserito non e' valido\n");
				lettura=0;
			}
		}
	}while(lettura);

	if(presente == 1)
		return 1;
	else
		return 0;

}
