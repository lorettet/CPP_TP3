RM=rm
COMP=g++
EDL=g++
RMFLAGS=-f
COMPFLAGS = -ansi -pedantic  -Wall -std=c++11 -g
#retirez yes pour compiler en release
DEBUG=yes
EXE=Catalogue
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

ifeq ($(DEBUG),yes)
	DEFINE=-D MAP	
else
	DEFINE=
endif

all:$(EXE)

$(EXE): $(OBJ)
	$(EDL) -o $(EXE) $(OBJ)

Catalogue.o: Catalogue.h TrajetSimple.h TrajetCompose.h Trajet.h

TrajetSimple.o: Trajet.h  TrajetSimple.h

TrajetCompose.o: Trajet.h  TrajetCompose.h

%.o: %.cpp
	$(COMP) -c $< $(COMPFLAGS) $(DEFINE)

main.o: main.cpp Catalogue.h
	$(COMP) -c $< $(COMPFLAGS)
	
.PHONY:clean

clean:
	$(RM) $(RMFLAGS) *.o $(EXE)
