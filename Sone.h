/***********************************************************************************************************
 * Definisjon av Soneklassen.
 *
 * @file	-	Sone.h
 **********************************************************************************************************/

#ifndef __SONE_H
#define __SONE_H

#include <string>
#include <vector>
#include "Bolig.h"
#include "Enebolig.h"

class Sone {
  	private:
		int soneID;						// Sonens unike nummer
		std::string beskrivelse; 		// Kort og generell beskrivelse av sonen/området/bydel
		std::vector<Bolig*> boligerISone; //Boliger i sonen
	public:
		Sone(int id); 					// Constructor, tar med en sjekket sone-ID som param
		Sone(std::ifstream & stream, int id);		// Constructor, leser fra fil
		void lesData();					// leser inn data (beskrivelse)
		void nyBolig();					// Ny bolig i sonen
		void skrivOppdragData() const; 	// Skriver ut alle oppdrag, 5 om gangen
		void skrivHoveddata() const; 	// Skriver ut hoveddataene til en sone
		Bolig* hentBolig(int id) const; // Finner en bolig i en sone, og returnerer peker, evt. nullptr
		bool slettBolig(int id);
		void skrivTilFil(std::ofstream & stream); // Skriver til en fil
		void skrivFormatertTilFil(std::ofstream &utfil);	// Skriver til fil på et brukervennlig format
		void skrivOppdragIDer() const;
};

#endif
