/***********************************************************************************************************
 * Definisjon av Boligklassen.
 * 
 * @file	-	Bolig.h
 **********************************************************************************************************/
#ifndef __BOLIG_H
#define __BOLIG_H

#include <string>		// String-klassen
#include <fstream>		// Til og fra fil
#include "enumer.h"		// Boligtype

/**
 * Boligklassen.
 */
class Bolig {
	private:
		int oppdragNr,		// Unikt oppdrags-/bolignummer
			datoInnlagt,		// Dato innlagt. Format: ÅÅÅÅMMDD
			byggeaar,		// ÅÅÅÅ
			bruttoareal,		// I m²
			antallSoverom,
			pris;			// Angitt pris

		std::string saksbehandler,		// Intern saksbehandler hos eiendomsfirmaet
			eiersNavn,			// Nåværende eiers navn
			gateAdresse,			// Gate + nummer
			postAdresse,			// Postnummer + sted
			beskrivelse;			// Smålang beskrivelse av boligen

		Boligtype boligtype;


	public:
		Bolig(Boligtype temp);				// Constructor med boligtype
		Bolig(std::ifstream & stream, Boligtype temp);	// constructor, lese fra fil
		int hentOppdragNr() const;				// Henter oppdragNr
		virtual void lesData();				// Leser inn data
		virtual void skrivData() const;			// Skriver ut data
		virtual void skrivTilFil(std::ofstream & stream); // Skriver data til en fil
		virtual void skrivFormatertTilFil(std::ofstream &utfil);
		virtual ~Bolig();					// Destructor
};

#endif
