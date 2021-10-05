/**
 * Deklarasjoner av Kunder-funksjoner, variabler, constructorer o.l.
 *
 * @file Kunder.h
 */
#ifndef __KUNDER_H
#define __KUNDER_H

#include <list>		// list-container
#include "Kunde.h"	// Kunde-klasse

/**
 *
 */
class Kunder {
  private:
	int sisteNr;				// Fortløpende økende automatisk numemrering av alle nye kunder
	std::list<Kunde*> kunder;	// Sortert liste med de unikt nummererte kundene
  public:
	~Kunder();			// Destructor som deallokerer minnet brukt av Kunde-lista

	void nyKunde();	// Oppretter en ny Kunde-peker og legger den i listen.
	void skrivAlle() const;	// Skriver hoveddataene til alle kunder.
	void skrivEnKunde(int kundeNr);	// Skriver alle dataene til en Kunde.
	void endreEnKunde(int kundeNr);	// Legge til eller fjerne soner for en Kunde.
	void slettKunde(int kundeNr);	// Sletter en Kunde og deallokerer minne.
	void skrivEnKundesOversikt(int kundeNr);
	void skrivAlleKunderTilFil();
	void lesAlleKunderFraFil();
	std::list<Kunde*>::iterator finnKunde(int kundeNr);	// Returner en iterator til en Kunde
};

#endif
