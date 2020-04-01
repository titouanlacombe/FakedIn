.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all:

# Lance le programme de test.
check: build/test
	./build/test

#-------------IMPORTED--------------
cc=gcc

build/liste.o: lib/liste.c | build
	$(cc) -Wall -pedantic -g -c lib/liste.c -I ./lib -o build/liste.o

build/groupe.o: lib/groupe.c build/libliste.a | build
	$(cc) -Wall -pedantic -g -c lib/groupe.c -I ./lib -lliste -o build/groupe.o

build/libliste.a: build/liste.o | build
	ar crs build/libliste.a build/liste.o

build/libgroupe.a: build/groupe.o | build
	ar crs build/libgroupe.a build/groupe.o

build/test.o: test/main.c | build
	$(cc) -Wall -pedantic -g -c test/main.c -I ./lib -o build/test.o

build/test: build/test.o build/libgroupe.a | build
	$(cc) build/test.o -Lbuild -lgroupe -lliste -o build/test
