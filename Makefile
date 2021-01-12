CC = g++ # le compilateur à utiliser
CFLAGS =  # les options du compilateur
LDFLAGS = -Wall -lncurses # les options pour l’éditeur de liens
SRC = simulation.cpp # les fichiers sources
PROG = simulation # nom de l’exécutable
OBJS = $(SRC:.cpp=.o) # les .o qui en découlent
.SUFFIXES: .cpp .o # lien entre les suffixes

all: $(PROG)

# étapes de compilation et d’édition de liens
# $@ la cible $^ toutes les dépendances
$(PROG): $(OBJS)
		$(CC) -o $@ $^ $(LDFLAGS)

simulation.o: Client.hpp FileChainee.hpp Guichet.hpp Poste.hpp
# le lien entre .o et .c
# $< dernière dépendance
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# pour faire propre
.PHONY: clean
clean:
		rm -f *.o *~ core $(PROG)
