# Makefile slouží jako návod pro sestavení aplikace.

# Název výsledného binárního souboru.
BIN = tree

# Překládané objektové soubory
OBJ = bst.o tree.o

# Použitý překladač a jeho argumenty, které jsou nám již povědomé.
CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -ansi -g

# Samotné návody na sestavení aplikace.
# Součástí projektu samozřejmě může být více knihoven či spustitelných souborů.
all: $(BIN)

# Slinkováním vytvořených objectových souborů `tree.o` a `bst.o` vznikne spustitelný soubor `tree`.
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

# Návody na přeložení objektových souborů.
tree.o: tree.c
	$(CC) -c tree.c $(CCFLAGS)

bst.o: bst.c
	$(CC) -c bst.c $(CCFLAGS)

# Na Windows by cíl clean vypadal takto (to za nás příště vyřeší CMake):
#clean:
#	del -f *.o $(BIN)

clean:
	rm -f *.o $(BIN)