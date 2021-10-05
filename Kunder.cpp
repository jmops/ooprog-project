/**
 * Definisjoner av Kunder-funksjoner, constructorer o.l.
 *
 * @file Kunder.cpp
 */
#include <list>
#include <iostream>
#include <fstream>
#include "Kunder.h"
#include "Kunde.h"
#include "LesData3.h"
#include "Funksjoner.h"

/**
 * Destructor som deallokerer minne og fjerner alt fra Kunde-lista.
 */
Kunder::~Kunder() {
	for (auto &kunde : kunder)
		delete kunde;
	kunder.clear();
}

/**
 * Oppretter en peker til et nytt kundeobjekt og leser inn den nye kundens data.
 * Kundeobjektet legges så inn i Kunde-vectoren.
 * Oppdaterer samtidig sisteNr.
 *
 * @see Kunde::Kunde(int kundeNr)
 */
void Kunder::nyKunde() {
	Kunde *nyK = new Kunde(++sisteNr);		// Den nye kunden får kundeNr 1 høyere enn forrige Kunde
	kunder.push_back(nyK);
}

/**
 * Funksjon som finner en kunde og returnerer en iterator til dens posisjon i listen.
 * For å sjekke om kunden ble gyldig/ble funnet * kan man sammenligne return-iteratoren med kunder.end()
 *
 * @return - Iterator til kunde-pekeren i lista.
 */
std::list<Kunde*>::iterator Kunder::finnKunde(int kundeNr) {
	auto retIt = kunder.end();

	for (auto it = kunder.begin(); it != kunder.end(); ++it)
		if ((*it)->returnKundeNr() == kundeNr)
			retIt = it;

	return retIt;
}

/**
 * Skriver hoveddataene om alle kunder.
 * Utskriften pauses for hver tiende kunde.
 *
 * @see Kunde::skrivHovedData()
 */
void Kunder::skrivAlle() const {
	int i = 0;	// Teller
	for (const auto &kunde : kunder) {
		kunde->skrivHovedData();
		if ((++i % 10) == 0) {	// Pauser utskrift for hver 10. kunde
			std::cout << "Trykk ENTER for å fortsette utskrift" << std::endl;
			std::cin.get();
		}
	}
}

/**
 * Skriver ut all data om en kunde.
 *
 * @param kundeNr - kundenummeret til kunden som skal skrives ut.
 * @see Kunder::finnKunde()
 * @see Kunde::skrivAllData()
 */
void Kunder::skrivEnKunde(int kundeNr) {
	auto it = finnKunde(kundeNr);
	if (it != kunder.end())
		(*it)->skrivAllData();
	else
	 	std::cout << "Fant ikke kunde med ID " << kundeNr << std::endl;
}

/**
 * Finner en kunde med gitt kundeNr og kjører dens endre-funksjon.
 *
 * @param int kundeNr - Kundenummeret til kunden som skal endres.
 * @see Kunder::finnKunde()
 * @see Kunde::endreKunde()
 */
void Kunder::endreEnKunde(int kundeNr) {
	auto it = finnKunde(kundeNr);
	if (it != kunder.end())
		(*it)->endreKunde();
	else
	 	std::cout << "Fant ikke kunde med ID " << kundeNr << std::endl;
}

/**
 * Sletter en kunde fra kunde-lista og frigjør minnet som var allokert til den.
 *
 * Kunden slettes fra lista ved å bruke list::splice() for å flytte kunden på 'it'
 * sin posisjon bakerst i lista. Så brukes list::pop_back() for å fjerne den.
 *
 * @param kundeNr - Kundenummeret til kunden som skal fjernes
 * @see Kunder::finnKunde()
 * @see Funksjoner::lesBool()
 */
void Kunder::slettKunde(int kundeNr) {
	std::cout << "Ønsker du virkelig å fjerne kunde " << kundeNr << "?" << std::endl;
	bool svar = lesBool("");	// Bekreftelse fra brukeren
	if (svar) {
		auto it = finnKunde(kundeNr);
		if (it != kunder.end()) {
			std::cout << "Sletter kunde " << kundeNr << std::endl;
			delete *it;
			kunder.splice(kunder.end(), kunder, it);
			kunder.pop_back();
		} else {
			std::cout << "Fant ikke kunde med ID " << kundeNr << std::endl;
		}
	} else {
		std::cout << "Angrer sletting" << std::endl;
	}
}

/**
 * Skriver alle kunder til filen KUNDER.DTA.
 * Dette formatet er ikke menneskevennlig.
 * For pent formatert filutskrift, se Kunde::skrivFormatertTilFil()
 */
void Kunder::skrivAlleKunderTilFil() {
	std::ofstream utfil;
	utfil.open("KUNDER.DTA");
	if (utfil) {
		utfil << sisteNr << '\t' << kunder.size() << std::endl;
		for (const auto &kunde : kunder)
			kunde->skrivTilFil(utfil);
	} else {
		std::cout << "Feil ved åpning av fil" << std::endl;
	}
	utfil.close();
}

/**
 * Skriver en kundes info og boligdata til fil 
 * Brukes ifm. 'K O' (Kunde Oversikt).
 * 
 * @param	kundeNr	- Kundenummeret til kunden som skal skrives til fil.
 * @see Kunde::kundeOversikt()
 */
void Kunder::skrivEnKundesOversikt(int kundeNr) {
	auto it = finnKunde(kundeNr);
	if (it != kunder.end()) {
		std::cout << "Skriver kunde nr " << kundeNr << " sine boligdata til fil" << std::endl;
		(*it)->kundeOversikt();
	} else {
		std::cout << "Fant ikke kunde med ID: " << kundeNr << std::endl;
	}
}

/**
 * Leser inn kundedata fra fil og oppretter objekter.
 *
 * Kunde::Kunde(std::ifstream innfil)
 */
void Kunder::lesAlleKunderFraFil() {
	std::ifstream innfil;
	innfil.open("KUNDER.DTA");
	if (innfil) {
		int antKunder;	// Antall kunder lagret på fila (kunder.size())
		std::cout << "Leser kunder fra fil" << std::endl;
		innfil >> sisteNr >> antKunder;
		innfil.ignore();	// Skip newline
		for (int i = 0; i < antKunder; ++i){
			std::cout << "Oppretter kunde " << i+1 << std::endl;
			Kunde *nyKunde = new Kunde(innfil);
			kunder.push_back(nyKunde);
		}
	}
	innfil.close();
}
