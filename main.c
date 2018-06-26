
/**
 * @file main.c
 * Il main e' costituito da un menu principale uguale per utenti ed amministratore da cui ci si puo' registrare o si puo' fare il login
 *
 * @version 1.0
 * @date 13/07/2017
 * @authors Cosimo Polito mat.669984
 * @copyright GNU Public License
 */
#include "menu_accesso.h"
#include "proc_controllo.h" //includo la libreria statica "funzioni.h"
#include "struct_cost.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


/**
 * Menu principale da cui e' possibile registrarsi o effettuare il login
 *
 */
int main()
{
	char menu;
	int continua=1;

	printf("BENVENUTO SU NETFLIX\n");
	do
	{
		printf("\n1) registrati\n2) effettua login\n\nESC) esci\n");
		fflush(stdin);
		menu=getch();

		switch(menu)
		{
		case '1':
			registra();
			break;

		case '2':
			login();
			break;

		case ESC:
			continua=0;
			break;

		case ' ':
		case '\n':
		case '\t':
		printf("\nnon hai inserito nessun carattere,riprova\n");
		break;

		default:
			printf("scelta non valida,riprova\n\n");
		}

	}while(continua);
	system ("pause");
	return 0;
}




