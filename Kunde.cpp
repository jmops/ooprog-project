/**
 * Definisjoner av Kunde-funskjoner og constructorer
 *
 * @file Kunde.cpp
 */
#include <iostream>		// cout, cin
#include <sstream>		// stringstream
#include <fstream>		// ifstream, ofstream
#include <string>		// string
#include <algorithm>	// sort, remove
#include "Kunde.h"
#include "Kunder.h"
#include "Soner.h"
#include "LesData3.h"
#include "enumer.h"

extern Kunder gKunder;
extern Soner gSoner;


/**
 * Constructor som oppretter et kundeobjekt og sørger for at data leses inn.
 *
 * @param kundeNr - Kundenummeret Kunden skal bli tildelt.
 * @see Kunde::lesData()
 */
Kunde::Kunde(int kundeNr) {
    std::cout << "Lager kunde med kundenummer " << kundeNr << std::endl;
	this->kundeNr = kundeNr;
	Kunde::lesData();
}

/**
 * Constructor som lager et Kunde-objekt vha en fil.
 *
 * @param innfil - File-streamen som det leses fra (del av KUNDER.DTA)
 */
Kunde::Kunde(std::ifstream &innfil) {

	int tmp;			// Midlertidig lagring av boligtype og sonenummere
	std::string buf;	// Midlertidig lagring av linje som gjøres om til stringstream

	if (innfil) {
		std::getline(innfil, navn);
		innfil >> kundeNr;
		innfil >> tmp; boligtype = static_cast<Boligtype>(tmp);
		innfil.ignore();	// Skip '\n'

		std::getline(innfil, buf);	// Ved å bruke denne metoden trenger man ikke
		std::stringstream ss(buf);	// å vite hvor mange sonenummere som skal lastes inn på forhånd.
		while (ss >> tmp) {
			if (gSoner.soneFinnes(tmp))
				sonenummere.push_back(tmp);
			else
				std::cout << "Kunne ikke legge inn sone " << tmp << std::endl;
		}

		innfil >> telefonNr;
		innfil.ignore();	// Skip '\n'
		std::getline(innfil, gateadresse);
		std::getline(innfil, postadresse);
		std::getline(innfil, epostadresse);
	} else {
		std::cout << "Feil ved aksessering av fil" << std::endl;
	}
}

/**
 * Sier om en sone allerede er registrert (i sonenummere-vectoren til kunden)
 *
 * @return - true om sonen allerede er i sonenummere. False ellers
 */
bool Kunde::soneErIVektor(int soneID) {
	bool iVektor = false;
	if (find(sonenummere.begin(), sonenummere.end(), soneID) != sonenummere.end())
		iVektor = true;
	return iVektor;
}

/**
 * Returnerer kundenummeret til en kunde.
 *
 * @return kundeNr - kundenummeret
 */
int Kunde::returnKundeNr() const{
	return kundeNr;
}

/**
 * Leser inn informasjon fra brukeren om en kunde.
 * Sonenummere leses inn som en linje som deles opp i individuelle inter med stringstream.
 * Så sjekkes gyldigheten til hvert sonenummer før det legges inn i vectoren.
 * Til slutt sorteres sonenummere-vectoren fra lavest til høyest
 *
 * @see Soner::soneFinnes()
 */
void Kunde::lesData() {
	std::cout << "Leser inn data om kunde" << std::endl;
	std::cout << "Navn: "; getline(std::cin, this->navn);
	std::cout << "Telefonnummer: "; this->telefonNr = lesInt("", 10000000, 99999999);
	std::cout << "Gateadresse: "; getline(std::cin, this->gateadresse);
	std::cout << "Postadresse: "; getline(std::cin, this->postadresse);
	std::cout << "Epostadresse: "; getline(std::cin, this->epostadresse);
	std::cout << "Leilighet (1) eller enebolig (2)? "; this->boligtype = static_cast<Boligtype>(lesInt("", 1, 2) - 1);

	std::cout << "Hvilke soner er kunden interessert i? ";
	std::string buf;	// Lagrer en linje midlertidig
	int tmp;	// Holder et sonenummer midlertidig før det legges i vectoren
	std::getline(std::cin, buf);
	std::stringstream ss(buf);
	while (ss >> tmp)
		if (gSoner.soneFinnes(tmp) && !(soneErIVektor(tmp)))
			sonenummere.push_back(tmp);
		else
			std::cout << "Sone " << tmp << " finnes ikke, eller er allerede lagt inn." << std::endl;
	sort(sonenummere.begin(), sonenummere.end());
}

/**
 * Skriver hoveddataene om en kunde til skjermen.
 * Hoveddata: kundeNr, navn, boligtype, antall soner kunden er interessert i og nummeret på disse
 */
void Kunde::skrivHovedData() const {
	std::cout << "\nSkriver data om kunde " << kundeNr << std::endl;
    std::cout << "\n\tKundenummer: " << kundeNr << std::endl;
    std::cout << "\tNavn: " << navn << std::endl;
    std::cout << "\tBoligtype: ";
	if (boligtype == eLeilighet)
		std::cout << "leilighet" << std::endl;
	else if (boligtype == eEnebolig)
		std::cout << "enebolig" << std::endl;
	std::cout << "\tAntall soner interessert i: " << sonenummere.size() << std::endl;
	std::cout << "\tSonenummere: ";
	for (const auto &val : sonenummere)
		std::cout << val << " ";
	std::cout << std::endl;
}

/**
 * Skriver alle kundens data til skjermen.
 *
 * @see Kunde::skrivHovedData()
 */
void Kunde::skrivAllData() const {
    Kunde::skrivHovedData();
	std::cout << "\tTelefonnummer: " << telefonNr << std::endl;
    std::cout << "\tGateadresse: " << gateadresse << std::endl;
    std::cout << "\tPostadresse: " << postadresse << std::endl;
    std::cout << "\tEpostadresse: " << epostadresse << std::endl;
}

/**
 * Lar brukeren legge til eller fjerne sonene til en Kunde.
 *
 * Endringen leses inn som en linje bestående av selve endringen som skal gjøres,
 * 'F' for fjerne eller 'L' for å legge til.
 * Kommandoen behandles med en switch.
 *
 * Ved fjerning av soner:
 * std::remove flytter elementene som ikke matcher 'sone' framover og returner en iterator til den nye slutten av rangen.
 * Denne iteratoren blir starten på en range som std::erase bruker for å slette sonenummeret.
 *
 * @see Kunde::skrivAlleData()
 */
void Kunde::endreKunde() {
	Kunde::skrivAllData();
	std::cout << "\nEndrer kunde " << returnKundeNr() << std::endl;
	std::cout << "Skriv 'F' (fjern) eller 'L' (legg til) etterfulgt av sonenummerne som skal endres" << std::endl;
	std::cout << "Eksempel: F 1 2 3 (fjern soner 1, 2 og 3)" << std::endl;

	std::string buf;		// Midlertidig string-buffer
	char kommando = '\0';	// 'F' for fjerne eller 'L' for legge til
	std::vector<int> vecsoner;	// Resten av linja lagres her
	int tmp;				// Holder en sone midlertidig før den legges inn i vecsoner

	std::getline(std::cin, buf);	// Les linje
	std::stringstream ss(buf);		// Gjør om til stringstream
	ss >> kommando;					// Extract kommando

	while (ss >> tmp)		// Extract alle sonene og legger de til i vectoren
		vecsoner.push_back(tmp);

	switch(toupper(kommando))
	{
	case 'F':
		for (const auto &sone : vecsoner) {
			if (soneErIVektor(sone)) {
				std::cout << "Fjerner sone nr " << sone << std::endl;
				auto fjernIt = std::remove(sonenummere.begin(), sonenummere.end(), sone);
				sonenummere.erase(fjernIt, sonenummere.end());
			} else {
				std::cout << "Fant ikke sone nr " << sone << std::endl;
			}
		}
		break;
	case 'L':
		for (const auto &sone : vecsoner) {
			if (gSoner.soneFinnes(sone) && !(soneErIVektor(sone))) {
				std::cout << "Legger til sone " << sone << std::endl;
				sonenummere.push_back(sone);
			} else {
				std::cout << "Sone " << sone << " finnes ikke eller er allerede lagt inn." << std::endl;
			}
		}
		break;
	default:
		std::cout << "Ugyldig kommando" << std::endl;
		break;
	}
	sort(sonenummere.begin(), sonenummere.end());
}

/**
 * Genererer filnavn basert på kundeNr og skriver kundens boligdata til fil på et leselig format.
 * Brukes ifm. 'K O' (Kunde Oversikt)
 *
 * @see Kunde::skrivFormatertTilFil() - brukes for å skrive kundens info til fil.
 * @see Soner::skrivSoneFormatertTilFil() - brukes for å skrive hver sones boligdata til fil.
 */
void Kunde::kundeOversikt() {
	std::ofstream utfil;
	std::string filnavn = "K" + std::to_string(kundeNr) + ".DTA";
	utfil.open(filnavn);

	if (utfil) {
		Kunde::skrivFormatertTilFil(utfil);
		for (const auto &sone : sonenummere)
			gSoner.skrivSoneFormatertTilFil(sone, utfil);
	} else {
		std::cout << "Kunne ikke åpne " << filnavn << " for skriving" << std::endl;
	}

	utfil.close();
}

/**
 * Skriver kundeinformasjon til en fil på et leselig format.
 * Brukes ifm. 'K O' (Kunde Oversikt)
 *
 * @param	utfil -	filen kundeinfoen blir skrevet til
 */
void Kunde::skrivFormatertTilFil(std::ofstream &utfil) {
	if (utfil) {
		utfil << "\nKunde-ID:\t" << kundeNr;
		utfil << "\nNavn:\t" << navn;
		utfil << "\nBoligtype:\t";
		if (boligtype == eLeilighet)
			utfil << "leilighet";
		else if (boligtype == eEnebolig)
			utfil << "enebolig";
		utfil << "\nInteressante soner:\t";
		for (const auto &sone : sonenummere)
			utfil << sone << " ";
		utfil << "\nTelefonnummer:\t" << telefonNr;
		utfil << "\nAdresse:\t" << gateadresse;
		utfil << "\nPostadresse:\t" << postadresse;
		utfil << "\nEpostadresse:\t" << epostadresse;
		utfil << std::endl;
	} else {
		std::cout << "Feil ved aksessering av fil" << std::endl;
	}
}

/**
 * Skriver kundens info til fil på ikke-menneske-vennlig format.
 * For formatert filutskrift, se Kunde::skrivFormatertTilFil():
 *
 * @param	utfil -	Filen kundeinfoen skrives til
 */
void Kunde::skrivTilFil(std::ofstream &utfil) {
	if (utfil) {
		utfil << navn << std::endl;
		utfil << kundeNr << std::endl;
		utfil << boligtype << std::endl;
		for (const auto &sone : sonenummere)
			utfil << sone << "\t";
		utfil << std::endl;
		utfil << telefonNr << std::endl;
		utfil << gateadresse << std::endl;
		utfil << postadresse << std::endl;
		utfil << epostadresse << std::endl;
	} else {
		std::cout << "Feil ved aksessering av fil" << std::endl;
	}
}
