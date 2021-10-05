/***********************************************************************************************************
 * Definisjon av Eneboligklassen.
 * 
 * @file	-	Enebolig.h
 **********************************************************************************************************/
#ifndef __ENEBOLIG_H
#define __ENEBOLIG_H

#include "Bolig.h"

/**
 * Klasse for Enebolig.
 */
class Enebolig : public Bolig {
	private:
		int areal;				// Målt i kvadratmeter
		bool selveid;			// Om tomten er selveiet eller ikke (festetomt)

	public:
		Enebolig(Boligtype tmp);
		Enebolig(std::ifstream & stream, Boligtype temp); // Constructor, lese fra fil
		void lesData();			// Leser inn data til objektet
		void skrivData() const; // Skriver ut data.
		void skrivTilFil(std::ofstream & stream);	// Leser data til en fil
		void skrivFormatertTilFil(std::ofstream &utfil);
		void test();
		~Enebolig();
};

#endif
