cc=gcc
flags=-Wall -pedantic -Werror

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

#------LIBLISTE-------
build/liste.o: lib/liste.c | build
	$(cc) $(flags) -c lib/liste.c -I ./lib -o build/liste.o

build/libliste.a: build/liste.o | build
	ar crs build/libliste.a build/liste.o

#------LIBGROUPE-------
build/groupe.o: lib/groupe.c build/libliste.a | build
	$(cc) $(flags) -c lib/groupe.c -I ./lib -lliste -o build/groupe.o

build/libgroupe.a: build/groupe.o | build
	ar crs build/libgroupe.a build/groupe.o

#------LIBLOG-------
build/mylog.o: lib/mylog.c | build
	$(cc) $(flags) -c lib/mylog.c -I ./lib -o build/mylog.o

build/libmylog.a: build/mylog.o | build
	ar crs build/libmylog.a build/mylog.o

#------LIBWORKER-------
build/worker.o: lib/worker.c build/libliste.a build/libmylog.a | build
	$(cc) $(flags) -c lib/worker.c -I ./lib -o build/worker.o

build/libworker.a: build/worker.o | build
	ar crs build/libworker.a build/worker.o

#------TESTS-------
build/test.o: test/main.c | build
	$(cc) $(flags) -c test/main.c -I ./lib -o build/test.o

build/test: build/test.o build/libgroupe.a build/libmylog.a build/libworker.a | build
	$(cc) build/test.o -Lbuild -lgroupe -lliste -lmylog -lworker -o build/test
