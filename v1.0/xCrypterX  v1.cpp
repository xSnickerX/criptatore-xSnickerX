#include <cstdio>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <tuple>
#include <stdlib.h>

using namespace std;

// richiamo funzioni
tuple<string, string> double_ctrl(string);
string hex_crypt(string);

int main() {
	// settaggio finestra cmd
	system("echo off");
	system("title xSnickerX ENCRYPTOR");
	system("color 0c");

	string stin, stin_copy;

	cout << "Enter string to be encrypted [100]: ";
	getline(cin, stin); // utilizzo getline perche' cin stoppa l'acquisizione della stringa in input quando viene inserito lo spazio (32)

	// copio la stringa di ingresso in una stringa nuova
	stin_copy = stin;

	char day[10];
	char hour[10];
	
	// pulisco il terminale e avvio la procedura di crittazione
	system("cls");
	cout << "ENCRYPTING ... " << endl;

	// ottengo ora e mese corrente utilizzando la libreria ctime
	time_t currentTime;
	time(&currentTime);
	tm* localTime = localtime(&currentTime);
	strftime(day, 10, "%d", localTime); 
	strftime(hour, 10, "%I", localTime);

	// a partire dalle variabili char di ora (hh) e mese (mm) ottengo h1 h2 e m1 m2 in decimale secondo la tabella ascii 
	int hour0 = int(hour[0]); // esempio: assegno ad hour0 il valore decimale rispettivo ad hour[0] che corrisponde alla prima cifra delle ore
	int hour1 = int(hour[1]);
	int day0 = int(day[0]);
	int day1 = int(day[1]);
	/*
		le seguenti variabili sono la base dell'algoritmo di crittatura
		la stringa in ingresso verra' divisa in due parti a meta' (nel caso di stringhe dispari la divisione verra' fatta per difetto)
		la prima parte di stringa verra' elaborata con la variabile ku , mentre la seconda parte verra' elaborata con kd
		entrambe le variabili dipendono da ora e mese correnti al momento della crittatura e dalla lunghezza della stringa
		pertanto inserendo la stessa stringa in input a distanza di un'ora l'algoritmo dara' in output una stringa diversa 
	*/
	int ku = day1 - (hour0 / 2) + stin.length(); 
	int kd = day0 - (hour1 / 2) + stin.length();

	/*
		la funzione double_ctrl esegue una modifica della stringa in input nel caso questa avesse delle doppie
		ogni carattere doppio verra' sostituto con un carattere quale n carattaeri dopo esso in base a quante volte viene ripetuto
		esempio se si inserisce in input la stringa sass, in output della funzione si otterra' satu dove t e' s+1 e u e' s+2
		gli indici di modifica delle doppie vengono stampati in una stringa a se quale addon in formato posizione-lettera originale
		la somma delle due stringhe in output della funzione quindi, prendendo sempre per esempio la stringa sass in input, sara' satu2s3s
	*/

	tuple<string, string> sas = double_ctrl(stin);
	stin = get<0>(sas);
	string addon = get<1>(sas);

	char crt[150] = ""; // char per la creazione della stringa criptata
	int x = 0;

	// le cifre delle ore espresse nel loro rispettivo carattere dec della ascii vengono convertite stringa per essere stampate
	string _hour0c = to_string(hour0);
	string _hour1c = to_string(hour1);
	string _day0c = to_string(day0);
	string _day1c = to_string(day1);
	
	// processo di criptatura della stringa (prendendo in considerazione la stringa senza lettere doppie)

	for (int i = 0; i < stin.length() / 2; i++) {	// considero meta' stringa, in caso di stringhe pari meta' per difetto
		int cnum = int(stin[i]) - ku;				// creo una variabile contenente un valore int pari al dec del carattere [i] della stringa (ascii) sottratto a kd
		char out_st = char(cnum);					// creo una variabile char contenente il carattere rispettivo al numero ottenuto in cnum
		crt[x] = char(out_st);						// assegno alla variabile char crt in posizione [i] il carattere ottenuto precedentemente
		x = x + 1;	
	}
	for (int i = stin.length() / 2; i < stin.length(); i++) {		// considero la seconda meta' della stringa
		int cnum = int(stin[i]) - kd;								// con la stessa logica del ciclo for precedente creo la variabile cnum, sottrando kd invece che ku
		char out_st = char(cnum);							
		crt[x] = char(out_st);
		x = x + 1;
	}

	// somma delle stringe precedentemente create per ottenere la stringa finale 
	string sumString = _hour0c + _hour1c + crt + _day0c + _day1c + addon;

	// conversione della stringa in esadecimale
	stringstream ss;
	string in_stg = sumString; // eseguo una copia della stringa precedentemente creata per la conversione
	string hex_stg;

	ss.str("");
	for (unsigned int i = 0; i < in_stg.length(); i++) {
		ss << hex << (int)in_stg[i];
	}
	hex_stg = ss.str(); // ottengo la stringa in esadecimale

	cout << "Entered string: " << stin_copy << endl;			// stampa la stringa in ingresso iniziale
	cout << "Encrypted string CHR: " << sumString << endl;		// stampa la stringa criptata senza conversione esadecimale
	cout << "Encrypted string HEX: " << hex_stg << endl;		// stampa la stringa criptata e convertita in hex

	system("pause");

	return 0;
}

// funzione per la ricerca e sostituzione delle doppie nella stringa di partenza
tuple<string, string> double_ctrl(string str) { 

	// eseguo la copia della stringa in ingresso 2 volte
	string strCopy1 = str;
	string strCopy2 = str;
	string addon = "";

	for (char _c : strCopy2) {	// eseguo un for each
		if (_c != '\0') {		// filtro caratteri ripetuti nella stringa
			bool first = true;	// non modifico il primo carattere della serie
			int count = 0;
			size_t nPos = strCopy2.find(_c, 0);		// cerco la prima volta che ricompare il carattere _c e lo scrivo in nPos
			while (nPos != string::npos) {			// verifico che il carattere _c sia doppio, la funzione 
													// while si ripete finche tutti i caratteri sono diversi tra loro
				count++;

				if (!first) {										
					addon += to_string(nPos) + strCopy2[nPos];		//assemblo addon 
					strCopy1[nPos] = _c + count - 1;				//modifico il carattere in base alla sua ripetizione nella stringa
					strCopy2[nPos] = '\0';							//elimino carattere modificato dalla stringa di conteggio
				}
				else {
					first = false;
				}

				nPos = strCopy2.find(_c, nPos + 1);					//controllo lettera successiva escludendo i risultati gia ottenuti
			}
		}
	}

	return make_tuple(strCopy1, addon);
}
