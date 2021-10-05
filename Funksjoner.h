/**
 * Inneholder definisjoner av frittstående funksjoner
 *
 * @file Funksjoner.h
 */
#ifndef __FUNKSJONER_H
#define __FUNKSJONER_H

bool lesBool(const char* t);
void skrivMeny();
void kommandoHandtering(char forste, char andre, int tredje);
void kundeKommando(char andre, int tredje);
void soneKommando(char andre, int tredje);
void oppdragKommando(char andre, int tredje);

#endif
