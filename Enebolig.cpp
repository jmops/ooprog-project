/***********************************************************************************************************
 * Definisjon av member funksjoner til Bolig.
 * 
 * @file    -   Enebolig.cpp
 **********************************************************************************************************/


#include <iostream>
#include "conster.h"
#include "Enebolig.h"
#include "LesData3.h"
#include "Funksjoner.h"



/**
 * Constructor med boligtype som param.
 **/
Enebolig::Enebolig(Boligtype tmp) : Bolig(tmp){
    lesData();
}

/**
 * Constructor, leser fra fil.
 * @param   -   stream til fil
 * @param   -   boligtype
 **/
Enebolig::Enebolig(std::ifstream & stream, Boligtype temp) : Bolig(stream, temp){
    stream >> areal >> selveid;
    stream.ignore();    //fjerner newline
}

/**
 * Leser inn data til Eneboligobjekter.
 **/
void Enebolig::lesData(){
    areal = lesInt("\tHvor stort areal (i kvadratmeter) er tomten?", gMINAREALENEBOLIG,
                                                                    gMAXAREALENEBOLIG);
    selveid = lesBool("\tEr eneboligen selveid?");
}
/**
 * Skriver ut data til Eneboligobjekter.
 **/
void Enebolig::skrivData() const{
    Bolig::skrivData();
    std::cout << "\tTomten er på:\t" << areal << " Kvadratmeter\n";
    std::cout << "\tTomten er " << (selveid ? "" : "ikke ") << "selveid.\n";   
}

/**
 * Leser Eneboligdata til en fil.
 * @param   -   stream til fil
 **/
void Enebolig::skrivTilFil(std::ofstream & stream){
    Bolig::skrivTilFil(stream);
    stream << areal << ' ' << selveid << std::endl; 

}

/**
 *
 *
 */
void Enebolig::skrivFormatertTilFil(std::ofstream &utfil) {
	if (utfil) {
		Bolig::skrivFormatertTilFil(utfil);
		utfil << "Areal:\t\t" << areal << " kvadratmeter" << std::endl;
		utfil << "Boligen er " << (selveid ? "selveid" : "en festetomt") << std::endl;
	} else {
		std::cout << "Feil ved aksessering av fil." << std::endl;
	}

}

/**
 * Deconstructor. 
 **/
Enebolig::~Enebolig(){

}
