/***********************************************************************************************************
 * Definisjon av Sonerklassen.
 * 
 * @file	-	Soner.h
 **********************************************************************************************************/
#ifndef __SONER_H
#define __SONER_H

#include <map>		// map-container
#include "Sone.h"


class Soner {
  	private:
		int sisteNr;				// Fortløpende automatisk nummerering av alle nye oppdrag/boliger
		std::map<int, Sone*> soner;	// Alle unikt nummererte Soner 
	public:
		Soner();
		void skrivSonerHoveddata() const;	// Skriver ut hoveddata til soner
		void skrivSone(int id) const; 		// Skriver ut alt om alle oppdrag i en sone
		void nySone(int id);				// Lager en ny sone
		bool unikSone(int id) const;		// Sjekker om en sone-ID er brukt
		bool soneFinnes(int id) const;		// Sjekker om en sone finnes
		void nyttOppdrag(int sone);			// Lager et nytt oppdrag i en sone.
		int nyBoligHentOppdragsNr() const;	// Henter oppdragnummer til et oppdrag.
		void skrivBolig(int id) const;		// Finner en bolig med gitt ID, og skriver ut data
		void slettBolig(int id);			// Sletter et oppdrag
		void skrivSonerTilFil();			// Skriver alle soner og deres oppdrag til fil
		void lesSonerFraFil();				// Leser alle soner og deres oppdrag fra fil
		void oppdaterOppdragsnr(int nr);	// Oppdaterer oppdragsnummer
		void skrivAlleOppdragIDer() const;

		// v Torstein WIP
		void skrivSoneFormatertTilFil(int id, std::ofstream &stream);

};


#endif
