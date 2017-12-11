RM=rm
COMP=g++
EDL=g++
RMFLAGS=-f
COMPFLAGS = -ansi -pedantic  -Wall -std=c++11 -g
DEBUG=yes
EXE=Catalogue

ifeq ($(DEBUG),yes)
	DEFINE=-D MAP
else
	DEFINE=
endif

.PHONY=clean

$(EXE): main.o Catalogue.o TrajetCompose.o TrajetSimple.o
	$(EDL) -o $(EXE) main.o Catalogue.o TrajetCompose.o TrajetSimple.o 

Catalogue.o: Catalogue.cpp Catalogue.h TrajetSimple.h TrajetCompose.h
	$(COMP) -c Catalogue.cpp $(COMPFLAGS) $(DEFINE)

TrajetSimple.o: Trajet.h  TrajetSimple.h TrajetSimple.cpp
	$(COMP) -c TrajetSimple.cpp $(COMPFLAGS) $(DEFINE)

TrajetCompose.o: Trajet.h  TrajetCompose.h TrajetCompose.cpp
	$(COMP) -c TrajetCompose.cpp $(COMPFLAGS) $(DEFINE)

main.o: main.cpp Catalogue.h
	$(COMP) -c main.cpp $(COMPFLAGS)

clean:
	$(RM) $(RMFLAGS) *.o $(EXE)
