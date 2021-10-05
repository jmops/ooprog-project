/************************************************************************************************************
 * Definisjon av member funksjoner til Soner.
 * 
 * @file    -   Soner.cpp
 ***********************************************************************************************************/

#include <iostream>
#include <fstream>
#include "conster.h"
#include "Soner.h"
#include "LesData3.h"
#include <map>

Soner::Soner(){
    sisteNr = gMINOPPDRAG -1;
}

/**
 * Skriver ut hoveddataene til alle soner.
 **/
void Soner::skrivSonerHoveddata() const{
    for(auto & it : soner){ //looper igjennom map
        (it.second)->skrivHoveddata();
    }
}

/**
 * Skriver ut alt om alle oppdragene i en sone.
 * @param   -   SoneID.
 **/
void Soner::skrivSone(int id) const{
    if(soneFinnes(id) ) //Sjekker at det faktisk er en sone.
        soner.at(id)->skrivOppdragData();
    else
        std::cout << "\tIngen sone med denne IDen...\n";
}

/**
 * Leser inn en sone-ID, sjekker denne, og lager ny sone.
 * @param id  -   ID-nummeret.
 **/
void Soner::nySone(int id){
    while (id < 0 || id > gMAXSONER || !unikSone(id) ){ //looper til sone ID er unik og godkjent.
		id = lesInt("\tSoneID (0 for aa slutte): ", 0, gMAXSONER);
    }

    if (id != 0){ // 0 for å avslutte
        std::cout << "\tLager ny sone...\n";
        soner[id] = new Sone(id);
    }
    else{
        std::cout << "\tAvslutter...\n";
    }

}

/**
 * Sjekker om en sone-ID er i bruk.
 * Egentlig samme funksjon som Soner::unikSone, men printer ikke tekst.
 */
bool Soner::soneFinnes(int id) const {
	return (soner.find(id) != soner.end());		// Hvis true betyr det at den er i bruk (ikke unik)
}

/**
 * Sjekker om en sone-ID er ledig.
 * @param	-	sone-ID som skal sjekkes
 * @return  -   false om IDen allerede er brukt
 * @return  -   true om den er unik
 **/
bool Soner::unikSone(int id)const{
	if(soneFinnes(id)){
        std::cout << "\tDenne IDen er ikke unik.\n";
        return false;
    }
    else{
        std::cout << "\tDenne IDen er unik.\n";
        return true;
    }
}

/**
 * Lager et nytt oppdrag, sjekker om sonen finnes, og lager nytt oppdrag.
 * @param	-	Oppdrag-ID
 *
 **/
void Soner::nyttOppdrag(int sone){
	if(soneFinnes(sone) ){ //Sjekker om det er i en gyldig sone
        sisteNr++;  //Den nye boligen har oppdrag-ID som er én høyere enn forrige oppdrag
		soner.at(sone)->nyBolig();
	}
	else{
		std::cout << "\tDenne sonen finnes ikke, du kan lage den med kommandoen: S N " << sone << ".\n";
	}
}

/**
 * Henter oppdrag-ID til en bolig (+1 fra forrige oppdrag).
 * @return  -   oppdrag-ID
 **/
int Soner::nyBoligHentOppdragsNr() const{
    return sisteNr;
}

/**
 * Finner en bolig med gitt ID, og skriver ut dataene til denne.
 *
 * @param int id - ID-en til boligen som skal skrives ut
 **/
void Soner::skrivBolig(int id) const{
    bool fortsett = true;
    Bolig* temp = nullptr;
    if(id >= gMINOPPDRAG && id <= sisteNr){ // sjekker om IDen er gyldig
        for(auto it = soner.begin(); it != soner.end() && fortsett; it++){
            temp = (*it).second->hentBolig(id); //Henter peker til oppdrag, eventuelt nullptr.
            if(temp){ // hvis temp er noe annet enn nullptr
                fortsett = false;
                temp->skrivData();
            }
        }
    }
    else{
        std::cout << "\tBrukte IDer er innenfor: " << gMINOPPDRAG << " : " << sisteNr << std::endl;
    }
    if(fortsett){
        std::cout << "\tIkke en brukt ID.\n\tBrukte IDer er:\n";
        skrivAlleOppdragIDer();
    }
}

/**
 * Sletter et oppdrag.
 * @param   -   oppdrag-ID
 **/
void Soner::slettBolig(int id){
    bool fortsett = true;
    if(id >= gMINOPPDRAG && id <= sisteNr){ // sjekker om IDen er gyldig
        for(auto it = soner.begin(); it != soner.end() && fortsett; it++){
            fortsett = !(*it).second->slettBolig(id);
        }

    }
    else{
        std::cout << "\tBrukte IDer er: " << gMINOPPDRAG << " : " << sisteNr << std::endl;
    }
    if(fortsett){
        std::cout << "\tIkke en brukt ID.\n\tBrukte IDer er:\n";
        skrivAlleOppdragIDer();
    }


}

/**
 * Skriver alle soner og deres oppdrag til en fil, etter formatet beskrevet i SONERFILFORMAT.txt.
 *@see  -   SONERFILFORMAT.txt 
 **/
void Soner::skrivSonerTilFil(){
    std::ofstream stream;
    stream.open("SONER.dta");
    if(stream){
        std::cout << "Skriver soner til fil...\n";
        stream << soner.size() << std::endl;
        for(auto & it : soner){
            it.second->skrivTilFil(stream);
        }
    }
    else{
        std::cout << "Får ikke lest til fil...\n";
    }
    stream.close();

}

/**
 * Leser alle soner og deres oppdrag fra fil (SONER.dta).
 * @see -   SONERFILFORMAT.txt
 **/
void Soner::lesSonerFraFil(){
    int antallSoner, soneID;
    std::ifstream stream;
    stream.open("SONER.dta");
    if(stream){ // Sjekker om filen finnes/får åpnet
        stream >> antallSoner;
        stream.ignore();
        stream >> soneID;
        while(!stream.eof() ){ // Så lenge ikke slutten er nådd.
            //stream.ignore();
            std::cout << "Setter opp sonenummer: " << soneID << std::endl;
            soner[soneID] = new Sone(stream, soneID);
            stream >> soneID;

        }

    }
    else{
        std::cout << "ERROR, får ikke lest fra fil...\n";
    }
}


/**
 * 
 */
void Soner::skrivSoneFormatertTilFil(int id, std::ofstream &utfil) {
	if (soneFinnes(id))
		soner[id]->skrivFormatertTilFil(utfil);	// Sone::skrivFormatertTilFil()
	else
		std::cout << "Kunne ikke skrive ut sone " << id << std::endl;
}

/**
 * Oppdaterer det høyeste oppdragsnummer (ID).
 **/
void Soner::oppdaterOppdragsnr(int nr){
	sisteNr = nr;
}


/**
 * Skriver ut alle oppdrag-IDer.
 **/
void Soner::skrivAlleOppdragIDer() const{
    for(auto & it : soner){
        (it.second)->skrivOppdragIDer();
        
    }
}
