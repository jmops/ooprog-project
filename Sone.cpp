/***********************************************************************************************************
 * Definisjon av member funksjoner til Sone.
 * 
 * @file    -   Sone.cpp
 **********************************************************************************************************/
#include <iostream>
#include <fstream>
#include "Sone.h"
#include "LesData3.h"
#include "Funksjoner.h"

/**
 * Constructor
 * @param   -   IDnr, denne skal være sjekket og unik.
 **/
Sone::Sone(int id){
    soneID = id;
    lesData();

}

/**
 * Constructor, leser fra fil.
 * @param   -   stream til fil
 * @param   -   sone-ID
 **/
Sone::Sone(std::ifstream & stream, int id){
    int type;
    Bolig* temp = nullptr;
    int antallOppdrag;
    soneID = id;
    stream.get();   // Fjerner whitespace mellom sone-ID og beskrivelsen
    getline(stream, beskrivelse); // Leser inn beskrivelsen, leser med, men ignorerer newline

    stream >> antallOppdrag;
    stream.ignore(); // ignorer newline
    for(int i = 0; i < antallOppdrag; i++){
        stream >> type;
        switch (type){
        case (0)    : temp = new Bolig(stream, eLeilighet);
            break;
        case(1)     : temp = new Enebolig(stream, eEnebolig);
            break;
        default: std::cout << "ERROR, feil i lesing av fil...\n";
            break;
        }
        boligerISone.push_back(temp);
    }



}


/**
 * Leser inn all data til en sone. 
 **/
void Sone::lesData(){
    std::cout << "\tBeskrivelse: ";
    getline(std::cin, beskrivelse);
}

/**
 * Lager en nytt oppdrag i en sone.
 **/
void Sone::nyBolig(){
    Bolig* temp = nullptr;
    std::cout << "\n\t---Nytt oppdrag---\n";
    if(lesBool("\tEr det en enebolig?") ){
        temp = new Enebolig(eEnebolig);
    }
    else{
        temp = new Bolig(eLeilighet);
    }
    boligerISone.push_back(temp);   
}


/**
 * Skriver ut 5 oppdrag i en sone om gangen, 
 **/
void Sone::skrivOppdragData() const{
    int counter = 0;
    std::cout << "\n\tBeskrivelse av sone: " << beskrivelse << std::endl;
    for( auto & it : boligerISone){
        it->skrivData();
        counter++;
        if(counter % 5 == 0){ // Hver femte element
            std::cout << "\n\tENTER...\n";
            std::cin.get(); // Leser inn enter
        }
    }
}
/**
 * Skriver ut hoveddataene til sonen.
 **/
void Sone::skrivHoveddata() const{
    std::cout << "\n\tSone ID: " << soneID << std::endl
              << "\tAntall oppdrag: " << boligerISone.size() 
              << "\tBeskrivelse: " << beskrivelse << std::endl;
}

/**
 * Finner en bolig med gitt oppdrag-ID, returnerer denne, om den ikke finnes returneres nullptr.
 * @param   -   Gitt oppdrag-ID
 * @return  -   Peker til boligobjektet med gitt ID
 * @return  -   Nulltpr om boligen ikke finnes i sonen.
 **/
Bolig* Sone::hentBolig(int id) const{
    for(auto & it : boligerISone){
        if(it->hentOppdragNr() == id){ // Sjekker om oppdraget har den gitte IDen
            return it;
        }
    }
    return nullptr; // Om oppdraget ikke finnes i sonen, returneres nullptr.
}

/**
 * Sletter en bolig om den finnes i sonen.
 * @param   -   oppdrag-ID
 * @return  -   true om boligen ble slettet
 * @return  -   false om ingen oppdrag ble slettet
 **/
bool Sone::slettBolig(int id){
    for(auto it = boligerISone.begin(); it != boligerISone.end(); it++){
        if( (*it)->hentOppdragNr() == id){
            std::cout << "\tSletter oppdrag: " << id << std::endl;
            if(lesBool("\tEr du sikker?") ){
                delete (*it);
                boligerISone.erase(it);
                std::cout << "\tOppdrag: " << id << " er slettet.\n";
                return true;
            }
            else{
                std::cout << "\tSletter ingenting.\n" << std::endl;
                return true;    // Returnerer true, slik at man ikke trenger å loope videre for å se etter oppdraget
            }
        }


    }
    return false;
}

/**
 * Skriver Sonedata til en fil.
 * @param   -   stream til fil
 **/
void Sone::skrivTilFil(std::ofstream & stream){
	if (stream) {
		stream << soneID << " " << beskrivelse << std::endl;
		stream << boligerISone.size() << std::endl;
		for(auto & it : boligerISone){
			it->skrivTilFil(stream);
		}
	}
}

/**
 *
 */
void Sone::skrivFormatertTilFil(std::ofstream &utfil) {
	if (utfil) {
		utfil << "\n\nSone-ID: " << this->soneID;
		utfil << "\nBeskrivelse: " << beskrivelse << std::endl;
		for(auto & it : boligerISone){
			it->skrivFormatertTilFil(utfil);	// Bolig::skrivFormatertTilFil
		}
	}
}

void Sone::skrivOppdragIDer() const{
    std::cout << "\n\tSone-ID: " << soneID << " :\n";
    for(auto & it : boligerISone){
        std::cout << "\t\tID: " << it->hentOppdragNr() << std::endl;
    }
}
