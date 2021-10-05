/**
 * Deklarasjoner av Kunde-relaterte funksjoner, variabler og constructorer
 *
 * @file Kunde.h
 */
#ifndef __KUNDE_H
#define __KUNDE_H

#include <vector>		// vector-klassen
#include <string>		// string-klassen
#include <fstream>		// ofstream-klassen
#include "enumer.h"		// Boligtype

class Kunde {
  private:
	int kundeNr,	// Kundens unike nummer
		telefonNr;	// Kundens telefonnummer

	std::string navn,	 	// Kundens navn: Fornavn [Mellomnavn] Etternavn
		gateadresse,		// Gate + nummer
		postadresse,		// Nummer + sted
		epostadresse;		// olanordmann@eksempel.no

	enum Boligtype boligtype;	// Om kunden er interessert i eneboliger eller leiligheter

	std::vector<int> sonenummere;	// Sonenumrene kunden er interessert i

  public:
    Kunde(int kundeNr);					// Constructor som brukes av kommando 'K N'
	Kunde(std::ifstream &innfil);		// Constructor som brukes når kunder leser inn fra fil

	bool soneErIVektor(int soneID);		// Returner om en sone er i sonenummere eller ikke
	int  returnKundeNr() const;			// Returnerer kundeNr-et til kunden
    void lesData();						// Leser inn data om kunden fra brukeren
    void skrivHovedData() const;		// Skriver ut hoveddata om kunden
    void skrivAllData() const;			// Skriver ut all data om kunden
	void endreKunde();					// Legge til eller fjerne soner
	void skrivTilFil(std::ofstream &utfil);	// Skriver kundens data til fil
	void skrivFormatertTilFil(std::ofstream &utfil);	// Skriver kundens data til fil på et leselig format
	void kundeOversikt();	// Skriver alle boligdataene til en kunde til fil
};

#endif
