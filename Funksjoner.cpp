/**
 * Inneholder definisjoner av frittstående funksjoner
 *
 * @file Funksjoner.cpp
 */
#include <iostream>	// cout
#include "Funksjoner.h"
#include "LesData3.h"
#include "Kunder.h"
#include "Kunde.h"
#include "Soner.h"

extern Soner gSoner;
extern Kunder gKunder;


/**
 * Skriver en enkel meny med brukerens valgmuligheter
 */
void skrivMeny() {
	std::cout << "Følgende kommandoer er tilgjengelige:\n";

	std::cout << " --- Kunder ---\n";
	std::cout << "  K N\t\t: Ny Kunde\n";
	std::cout << "  K 1 <knr>\t: Skriv alt om kunde nr <knr>\n";
	std::cout << "  K A\t\t: Skriv alt om alle kunder\n";
	std::cout << "  K E <knr>\t: Endre info om kunde nr <knr>\n";
	std::cout << "  K S <knr>\t: Slett kunde nr <knr>\n";
	std::cout << "  K O <knr>\t: Skriv alle kunde nr <knr> sine boligdata til fil\n";

	std::cout << " --- Soner ---\n";
	std::cout << "  S N <snr>\t: Ny sone\n";
	std::cout << "  S 1 <snr>\t: Skriv alt om sone nr <snr>\n";
	std::cout << "  S A\t\t: Skriv hoveddataene om alle soner\n";

	std::cout << " --- Oppdrag ---\n";
	std::cout << "  O N <snr>\t: Nytt oppdrag <snr>\n";
	std::cout << "  O 1 <onr>\t: Skriv alt om oppdrag nr <onr>\n";
	std::cout << "  O S <onr>\t: Slett oppdrag nr <onr>" << std::endl;

	std::cout << " ---------------\n";
	std::cout << " Trykk Q for å avslutte" << std::endl;
}


/**
 * Tolker kommandoene skrevet inn av brukeren og kaller på andre funksjoner
 * som tolker de videre.
 *
 * @param	forste	- Første del av kommandoen ('K', 'S', 'O', 'Q')
 * @param	andre	- Andre del. Sendes videre til Kunde, Sone, osv.
 * @param	trejde	- Tredje del. Sendes videre. 
 *
 * @see kundeKommando()
 * @see soneKommando()
 * @see oppdragKommando()
 */
void kommandoHandtering(char forste, char andre, int tredje) {
	switch(toupper(forste))
		{
		case 'K':
			kundeKommando(andre, tredje);
			break;
		case 'S':
			soneKommando(andre, tredje);
			break;
		case 'O':
			oppdragKommando(andre, tredje);
			break;
		case 'Q':
			std::cout << "Avslutter programmet" << std::endl;
			break;
		default:
			std::cout << "Ugyldig kommando" << std::endl;
			skrivMeny();
			break;
		}
}

/**
 * Tolker kommandoer relatert til kunder (forste = 'K')
 *
 * @param	andre	- Spesifikk kommando for Kunde/Kunder.
 * @param	tredje	- Eventuelt kundeNr
 *
 * @see Kunder::nyKunde()
 * @see Kunder::skrivEnKunde()
 * @see Kunder::skrivAlle()
 * @see Kunder::endreEnKunde()
 * @see Kunder::slettKunde()
 * @see Kunder::skrivEnKundesOversikt()
 */
void kundeKommando(char andre, int tredje) {
	switch(toupper(andre))
	{
	case 'N':
		gKunder.nyKunde();	// Opprett ny kunde og legg til i gKunder.
		break;

	case '1':
		if (tredje > 0)
			gKunder.skrivEnKunde(tredje);
		else
			std::cout << "Mangler <knr>" << std::endl;
		break;

	case 'A':
		gKunder.skrivAlle();
		break;

	case 'E':
		if (tredje > 0)
			gKunder.endreEnKunde(tredje);
		else
			std::cout << "Mangler <knr>" << std::endl;
		break;

	case 'S':
		if (tredje > 0)
			gKunder.slettKunde(tredje);
		else
			std::cout << "Mangler <knr>" << std::endl;
		break;

	case 'O':
		if (tredje > 0)
			gKunder.skrivEnKundesOversikt(tredje);
		else
			std::cout << "Mangler <knr>" << std::endl;
		break;

	default:
		std::cout << "Ugyldig kommando" << std::endl;
		break;
	}
}

/**
 * Tolker kommandoer relatert til soner (forste = 'S')
 *
 * @param	andre	- Spesifikk kommando for Sone/Soner
 * @param	tredje	- Eventuelt soneNr
 *
 * @see Soner::nySone()
 * @see Soner::skrivSone()
 * @see Soner::skrivSonerHoveddata()
 */
void soneKommando(char andre, int tredje) {
	switch(toupper(andre))
	{
	case 'N':
		gSoner.nySone(tredje);
		break;

	case '1':
		if (tredje > 0)
			gSoner.skrivSone(tredje);
		else
			std::cout << "Mangler <snr>" << std::endl;
		break;

	case 'A':
		gSoner.skrivSonerHoveddata();
		break;

	default:
		std::cout << "Ugyldig kommando" << std::endl;
		break;
	}
}

/**
 * Tolker kommandoer relatert til oppdrag/boliger (forste = 'O')
 *
 * @param	andre	- Spesifikk kommando for oppdrag
 * @param	tredje	- Eventuelt soneNr eller oppdragNr
 *
 * @see Soner::nyttOppdrag()
 * @see Soner::skrivBolig()
 * @see Soner::slettBolig()
 */
void oppdragKommando(char andre, int tredje) {
	switch(toupper(andre))
	{
	case 'N':
		if (tredje > 0)
			gSoner.nyttOppdrag(tredje);
		else
			std::cout << "Mangler <snr>";
		break;

	case '1':
		if (tredje > 0)
			gSoner.skrivBolig(tredje);
		else
			std::cout << "Mangler <onr>" << std::endl;
		break;

	case 'S':
		if (tredje > 0)
			gSoner.slettBolig(tredje);
		else
			std::cout << "Mangler <onr>" << std::endl;
		break;

	default:
		std::cout << "Ugyldig kommando" << std::endl;
		break;
	}
}

/**
 * Leser inn et svar om noe er sant eller ikke.
 * @param   -   Ledetekst
 * @return  -   False om bruker taster inn noe annet enn 'J'
 * @return  -   True om bruker taster inn 'J'
 * @see     -   lesChar(...)
 **/
bool lesBool(const char* t){
    char temp;
    std::cout << t << std::endl;
    temp = lesChar("N/j");
    if(temp == 'J'){
        return true;
    }
    else{
        return false;
    }
}
