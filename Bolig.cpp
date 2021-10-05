/***********************************************************************************************************
 * Definisjon av member funksjoner til Bolig.
 * 
 * @file	-	Bolig.cpp
 ***********************************************************************************************************/

#include <iostream>
#include "conster.h"
#include "Bolig.h"
#include "Soner.h"
#include "Sone.h"
#include "LesData3.h"

extern Soner gSoner;



/**
 * Constructor med boligtype som param.
 * @param	-	Boligtype
 **/
Bolig::Bolig(Boligtype temp){
	boligtype = temp;
	oppdragNr = gSoner.nyBoligHentOppdragsNr();
	std::cout << "\tOppdrag-ID: " << oppdragNr << std::endl;
	lesData();
}

/**
 * Constructor, leser fra fil.
 * @param	-	Stream til fil.
 * @param	-	boligtype
 **/
Bolig::Bolig(std::ifstream & stream, Boligtype temp){
	boligtype = temp;
	stream >> oppdragNr >> datoInnlagt >> byggeaar >> bruttoareal >> antallSoverom >> pris;
	stream.ignore(); // ignorerer newline
	getline(stream, saksbehandler);
	getline(stream, eiersNavn);
	getline(stream,gateAdresse);
	getline(stream, postAdresse);
	getline(stream, beskrivelse);

	if(oppdragNr > gSoner.nyBoligHentOppdragsNr() ){ // Oppdaterer oversikten over siste oppdrag i soner
		gSoner.oppdaterOppdragsnr(oppdragNr);
	}
}

/**
 * Leser inn data til Boligobjekter.
 **/
void Bolig::lesData() {
	datoInnlagt = lesInt("\tDato innlagt(ÅÅÅÅMMDD)", gTIDLIGSTINNLAGT, gSENESTINNLAGT);
	byggeaar = lesInt("\tByggeår", gTIDLIGSTBYGGEAAR, gSENESTBYGGEAAR);
	bruttoareal = lesInt("\tAreal til bolig", gMINBRUTTOAREAL, gMAXBRUTTOAREAL);
	antallSoverom = lesInt("\tAntall soverom", gMINANTALLSOVEROM, gMAXANTALLSOVEROM);
	pris = lesInt("\tBoligpris", gMINPRIS, gMAXPRIS);

	std::cout << "\tNavn på saksbehandler: ";
	getline(std::cin, saksbehandler);
	std::cout << "\tNavn på eier: ";
	getline(std::cin, eiersNavn);
	std::cout << "\tGateadresse: ";
	getline(std::cin, gateAdresse);
	std::cout << "\tPostadresse: ";
	getline(std::cin, postAdresse);
	std::cout << "\tBeskrivelse av oppdrag: ";
	getline(std::cin, beskrivelse);
}

/**
 * Skriver ut data til Boligobjekter.
 **/
void Bolig::skrivData() const{
	std::cout << "\n\n\tOppdrag-ID:\t" << oppdragNr << std::endl;
	std::cout << "\tType:\t\t" << (boligtype == eLeilighet ? "Leilighet" : "Enebolig") << std::endl;
	std::cout << "\tEier:\t\t" << eiersNavn << std::endl;	
	std::cout << "\tGateadresse:\t" << gateAdresse << std::endl;
	std::cout << "\tPostaddresse:\t" << postAdresse << std::endl;
	std::cout << "\tSaksbehandler:\t" << saksbehandler << std::endl;
	std::cout << "\tDato lagt inn:\t" << datoInnlagt << std::endl;
	std::cout << "\tByggeår:\t" << byggeaar << std::endl;
	std::cout << "\tBruttoareal:\t" << bruttoareal << std::endl;
	std::cout << "\tAntall soverom:\t" << antallSoverom << std::endl;
	std::cout << "\tPris:\t\t" << pris << std::endl;
	std::cout << "\tBeskrivelse:\t" << beskrivelse << std::endl;
}


/**
 * Leser Boligdata til en fil.
 * @param	-	stream til fil
 **/
void Bolig::skrivTilFil(std::ofstream & stream){
	stream << boligtype << std::endl;
	stream << oppdragNr << ' ' << datoInnlagt << ' ' << byggeaar
			<< ' ' << bruttoareal << ' ' << antallSoverom << ' ' << pris << std::endl;

	stream << saksbehandler << std::endl
			<< eiersNavn << std::endl
			<< gateAdresse << std::endl
			<< postAdresse << std::endl
			<< beskrivelse << std::endl;

}

/**
 * Skriver ut boligdata på et leselig format.
 * Brukes ifm 'K O'
 *
 * @param	utfil	-	Fila som skrives til (KXXX.DTA)
 */
void Bolig::skrivFormatertTilFil(std::ofstream &utfil) {
	utfil << "\nOppdragnummer:\t" << oppdragNr;
	utfil << "\nBoligtype:\t" << (boligtype ? "enebolig" : "leilighet");	// Funker gitt at enebolig = 1 og leilighet = 0
	utfil << "\nDato lagt inn:\t" << datoInnlagt;
	utfil << "\nByggeår:\t"<< byggeaar;
	utfil << "\nBruttoareal:\t" << bruttoareal << " kvadratmeter";
	utfil << "\nAntall soverom:\t" << antallSoverom;
	utfil << "\nPris:\t\tNOK " << pris;
	utfil << "\nSaksbehandler:\t" << saksbehandler;
	utfil << "\nEiers navn:\t" << eiersNavn;
	utfil << "\nGateadresse:\t" << gateAdresse;
	utfil << "\nPostadresse:\t" << postAdresse;
	utfil << "\nBeskrivelse:\t" << beskrivelse;
	utfil << std::endl;
}


/**
 * Returnerer oppdragsnummeret. 
 **/
int Bolig::hentOppdragNr() const{
	return oppdragNr;
}

/**
 * Deconstructor til Boliger.
 **/
Bolig::~Bolig(){
	std::cout << "\tSletter oppdrag: " << oppdragNr << std::endl;
}