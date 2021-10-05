/***************************************************************************************************************
 * Prosjektoppgave i PROG1003 Objektorientert programmering vår 2020.
 *
 * Programmet behandler boliger/oppdrag til salgs i forskjellige soner, og
 * kunder som er interessert i disse sonene.
 *
 * main tar for seg innlesing og utskrift av filer og kommandoer.
 *
 * Hver hele kommando består av to bokstaver og i noen tilfeller, ett tall.
 * Kommandoer leses inn som en hel linje som så gjøres om til en stringstream,
 * slik at de individuelle tegnene kan hentes ut.
 * Disse individuelle kommandoene sendes til en funksjon som kjører de gjennom en switch.
 *
 * Denne løsnignen gjør det mulig å skrive inn en hel kommandosekvens uten mellomrom,
 * noe som kan virke spesielt, men vi har testet det grundig og ikke funnet noen feil.
 * Vi ser på det som en feature siden det gir (mikroskopisk) tidsbesparelse ;-)
 *
 * @date	-	Mars-April 2020
 * @author	-	Jørgen Mo Opsahl, Torstein Egge
 *
 * @file	-	main.cpp
 **************************************************************************************************************/

#include <iostream>			// cout, getline
#include <string>			// string-klasse
#include <sstream>			// stringstream-klasse
#include "Funksjoner.h"
#include "Kunde.h"
#include "Kunder.h"
#include "Soner.h"
using namespace std;

Kunder gKunder;		///< Globalt Kunder-objekt som styrer alle Kunde-objektene våre
Soner  gSoner;		///< Globalt Soner-objekt som styrer alle Sone-objektene våre

/**
 * Hovedprogrammet
 */
int main(){

	// Innlesing av Kunder og Soner fra filene KUNDER.DTA og SONER.DTA
	gSoner.lesSonerFraFil();
	gKunder.lesAlleKunderFraFil();

	cout << "\n\nVelkommen" << std::endl;
	skrivMeny();

	char forste = '\0';	// Første del av kommandoen
	while (toupper(forste) != 'Q')
	{
		cout << "\nSkriv inn kommando:" << std::endl;

		string buf;			// Lagrer en linje midlertidig
		getline(cin, buf);
		stringstream linje(buf);

		forste = '\0';		// Kommando-verdiene resettes for å øke forutsigbarhet
		char andre = '\0';		// Andre del av kommandoen
		int  tredje = -1;		// Eventuelt <knr>, <snr> eller <onr>.

		linje >> forste >> andre >> tredje;
		kommandoHandtering(forste, andre, tredje);
	}

	// Utskrift av Kunder og Soner til filene KUNDER.DTA og SONER.DTA
	gSoner.skrivSonerTilFil();
	gKunder.skrivAlleKunderTilFil();

	return 0;
}
