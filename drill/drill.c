/*Načte subor a ukáze znak, int 32-bit nebo double 64-bit. Například po zadání c 0 -> #, c 0 5 -> #incl.
Když zadám i 0 -> 1668180259 (Jsou to první 4 znaky souboru #inc, zakádovné do 32-bitového čísla)
Bacha, pokud bude potom z čísla do řetězce, tak číst po zpátku.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define D_PROMPT ">"
#define D_ADDRC  ':'
#define D_ADDRF "%08d"
#define D_DETCH 6
#define D_COMMAND_LEN 1024
#define D_BUFFER_LEN 10
#define D_LINE_LEN 12

#define D_ISIZE 4
#define D_DSIZE 8
#define D_CSIZE 1

/*

  	Globální proměnné
 
*/

char *filename;				/* jméno souboru */
char *file;					/* buffer souboru */
int fverbose = 0;			/* příznak detailního vypisování */
int fsize = 0;				/* velikost souboru */

/**
	- testuje platnost offsetu, tj. zda je offset větší nebo roven 0 a menší než
	velikost souboru
*/ 
int inbound(int offs) {
	return (offs >= 0 && offs < fsize) ? 1 : 0;
}

/**
	- nahrává celý soubor z disku do paměti; alokuje buffer, na který ukazuje globální
	proměnná *file a následně jej naplní obsahem souboru
*/ 
int load(char *filename) {
	FILE *fin;

	fin = fopen(filename, "rb+");
	if (fin == NULL) return 0;

    fseek(fin, 0L, SEEK_END);			/* přesun aktuální pozice na konec souboru */
    fsize = ftell(fin);					/* zjištění aktuální pozice od začátku souboru */

	file = malloc(fsize);				/* alokace bufferu */
	if (file != NULL) {
		fseek(fin, 0L, SEEK_SET);
		fread(file, 1, fsize, fin);		/* načtení obsahu souboru */
	}

	fclose(fin);

	return file != NULL ? 1 : 0;		/* vrátit 1, podařilo-li se soubor načíst */
}

/**
	- inicializuje aplikaci; analyzuje přepínače na příkazovém řádku, zajišťuje načtení
	souboru, atd.
*/
void init(int argc, char *argv[]) {
	int i;

	/* kontrola počtu argumentů na příkazovém řádku */
	if (argc < 2) {
		printf("Usage: drill <filename> [<options>]\n");
		exit(EXIT_FAILURE);
	}

	/* výpis úvodní hlášky */
	printf("Drill 0.99 Alpha Rel. 20-Oct-2015\n");
	printf("Hardcore file viewer/editor/analyzer\n\n");

	/* načtení jména souboru, který se bude zpracovávat ... */
	filename = malloc(strlen(argv[1]) + 1);
	strcpy(filename, argv[1]);
	
	/* ... a jeho nahrání do připraveného bufferu */
	printf("Drilling \'%s\'\n",filename);
	if (!load(filename)) {
		printf("! Unable to load the file \'%s\'\n", filename);
	}

	/* zpracování přepínačů na příkazovém řádku */
	for (i = 2; i < argc; i++) {
		if (argv[i][0] == '-' || argv[i][0] == '/') {
			switch (argv[i][1]) {
				case 'v':
				case 'V': printf("  + verbose mode on");
						  fverbose = 1;
						  break;
				default : printf("  - ignoring unknown option \"%s\"...", argv[i]);
			}
		}
		else {
			printf("  - ignoring illegal command-line switch \"%s\"...", argv[i]);
		}
	}
}

/**
	- vypisuje stručnou nápovědu k jednotlivým příkazům drillu 
*/
void showhelp() {
	printf("c[x]<addr> [<count>] - show char(s)\n");
	printf("i[x]<addr> [<count>] - show 32-bit integer(s)\n");
	printf("d[x]<addr> [<count>] - show 64-bit double(s)\n");
	printf("s - available information on current file\n");
	printf("q|x - quit\n\n");
}

/**
	- zajišťuje provedení příkazu "c[x]<addr>[<count>]", tj. výpis jednoho znaku
	ze souboru na dané adrese
*/
void showchar(char *cmd) {
	int pos = 0, rep = 1, i, offs, curr;
    int fhex = 0;
	char buf[D_BUFFER_LEN] = {0};

	if (isalpha(cmd[0])) {
		switch(toupper(cmd[0])) {
			case 'X':
				/* nastavit vlajku výpisu v hexadecimální podobě */
				fhex = 1;
				break;
			default:
				printf("! Unknown switch \'%c\'... Ignoring... \n", cmd[0]);
		}
	
		cmd++;
	}

	/* načtení požadované adresy a počtu opakování z uživatelského příkazu */
	sscanf(cmd, "%d %d", &pos, &rep);

	/* výpis požadovaných dat v daném formátu na konzoli */
	for (i = 0; i < rep; i++) {
		offs = pos + i * D_CSIZE;
		memset(buf, 0, D_BUFFER_LEN);

		/* pokud chce uživatel tisknout znaky za koncem souboru, vypisovat otazníky */
		if (inbound(offs)) curr = (int) file[offs];
		else curr = '?';

		/* je-li na řádku již D_LINE_LEN znaků, začít na novém řádku (výpisem adresy) */
		if (i % D_LINE_LEN == 0) {
			if (i > 0) printf("\n");
			printf(D_ADDRF ":", offs);
		}

		/* zvolil-li uživatel výpis v hexadecimálním tvaru, vypsat znak jako hex číslo */
		if (fhex) printf("0x%02X", curr);
		else printf("%c", curr);

		/* je-li znaků nejvýše D_DETCH, pak je dost místa a ke každému hex číslu se
		   vypíše i znaková podoba ASCII hodnoty */
		if (fhex) {
			if (rep <= D_DETCH) printf(" \'%c\', ", curr);
			else printf(" ");
		}
	}

	printf("\n");
}

/**
	- zajišťuje provedení příkazu "i[x]<addr>[<count>]", tj. výpis jednoho integeru
	ze souboru na dané adrese
*/
void showint(char *cmd) {
	int pos = 0, rep = 1, i, offs;
	char fmt[32] = {0};

	/* vytvoření běžného formátovacího řetězce pro výpis int */
	strcpy(fmt, "%08d%c%11d\n");

	if (isalpha(cmd[0])) {
		switch(toupper(cmd[0])) {
			case 'X':
				/* změna formátovacího řetězce v případě, že uživatel
				   specifikoval výpis v hexadecimálním tvaru (přepínač 'x') */
				strcpy(fmt, "%08d%c0x%08X\n");
				break;
			default:
				printf("! Unknown switch \'%c\'... Ignoring... \n", cmd[0]);
		}
	
		cmd++;
	}

	/* načtení požadované adresy a počtu opakování z uživatelského příkazu */
	sscanf(cmd, "%d %d", &pos, &rep);

	/* výpis požadovaných dat v daném formátu na konzoli */
	for (i = 0; i < rep; i++) {
		offs = pos + i * D_ISIZE;
		/* data na pozici offs přetypovat na požadovaný typ, zde int */
		if (inbound(offs)) printf(fmt, offs, D_ADDRC, *((int *) (file + offs)));
		else printf("%08d%c<EOF>\n", offs, D_ADDRC);
	}

	printf("\n");
}

/**
	- zajišťuje provedení příkazu "d[x]<addr>[<count>]", tj. výpis jednoho double
	ze souboru na dané adrese
*/
void showdouble(char *cmd) {
	int pos = 0, rep = 1, i, offs;
	char fmt[32] = {0};

	/* vytvoření běžného formátovacího řetězce pro výpis double */
	strcpy(fmt, "%08d%c%e\n");

	if (isalpha(cmd[0])) {
		switch(toupper(cmd[0])) {
			case 'X':
				/* změna formátovacího řetězce v případě, že uživatel
				   specifikoval výpis v hexadecimálním tvaru (přepínač 'x') */
				strcpy(fmt, "%08d%c0x%016X\n");
				break;
			default:
				printf("! Unknown switch \'%c\'... Ignoring... \n", cmd[0]);
		}
	
		cmd++;
	}

	/* načtení požadované adresy a počtu opakování z uživatelského příkazu */
	sscanf(cmd, "%d %d", &pos, &rep);

	/* výpis požadovaných dat v daném formátu na konzoli */
	for (i = 0; i < rep; i++) {
		offs = pos + i * D_DSIZE;
		/* data na pozici offs přetypovat na požadovaný typ, zde double */
		if (inbound(offs)) printf(fmt, offs, D_ADDRC, *((double *) (file + offs)));
		else printf("%08d%c<EOF>\n", offs, D_ADDRC);
	}

	printf("\n");
}

/**
	- hlavní výkonný cyklus programu; načítá, interpretuje a provádí příkazy uživatele
	voláním funkcí příslušným k daným příkazům
*/
void run() {
    int fterm = 0;
	char buffer[D_COMMAND_LEN] = {0};

	printf("Listening... (type \'h\' to get help)\n\n");

	do {
		printf(D_PROMPT);

		/* načtení příkazu uživatele do bufferu */
        memset(buffer, 0, D_COMMAND_LEN);
		fgets(buffer, D_COMMAND_LEN, stdin);

		/* zpracování příkazu, resp. jeho prvního znaku */
		switch (toupper(buffer[0])) {
			case 'Q':
			case 'X':
				printf("Bye.\n");
                fterm = 1;
			    break;
            case 'C':
                showchar(buffer + 1);
                break;
			case 'I':
				showint(buffer + 1);
				break;
			case 'D':
				showdouble(buffer + 1);
				break;
			case 'H':
				showhelp();
				break;
			case 'S':
				printf("\'%s\', size = %d B\n\n", filename, fsize);
				break;
			default : printf("! Unknown command\n");
		}

	} while (!fterm);
}

/**
	- ukončení programu, dealokace paměti
*/
void shutdown() {
	if (filename != NULL) free(filename);
	if (file != NULL) free(file);
}

/**
	- hlavní funkce programu drill 
*/
int main(int argc, char *argv[]) {

	init(argc, argv);
	run();
	shutdown();

	return EXIT_SUCCESS;
}