# 'make' for å kompilere med g++
# 'make clean' for å slette .o-filer. Gjør dette før 'make debug' og 'make clang=1'
# 'make debug' for å legge til debug flags for gdb
# 'make clang=1' (eller hvilket som helst tall) kompilerer clang og debug options

ifdef clang
	CXX = clang++ -Wall -g -glldb -v
else
	CXX = g++ -Wall $(DEBUG)
endif

all: main.o Funksjoner.o Bolig.o Kunde.o Kunder.o Sone.o Soner.o LesData3.o Enebolig.o 
	$(CXX) main.o Funksjoner.o Bolig.o Kunde.o Kunder.o Sone.o Soner.o LesData3.o Enebolig.o


debug: DEBUG = -g
	
debug: all

main.o: main.cpp
	$(CXX) -c main.cpp

Funksjoner.o: Funksjoner.cpp Funksjoner.h
	$(CXX) -c Funksjoner.cpp 

Bolig.o: Bolig.cpp Bolig.h
	$(CXX) -c Bolig.cpp

Kunde.o: Kunde.cpp Kunde.h
	$(CXX) -c Kunde.cpp

Kunder.o: Kunder.cpp Kunder.h
	$(CXX) -c Kunder.cpp

Sone.o: Sone.cpp Sone.h
	$(CXX) -c Sone.cpp

Soner.o: Soner.cpp Soner.h
	$(CXX) -c Soner.cpp

Enebolig.o: Enebolig.cpp Enebolig.h
	$(CXX) -c Enebolig.cpp

LesData3.o: LesData3.cpp LesData3.h
	$(CXX) -c LesData3.cpp

clean:
	rm *.o
