cc=g++
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

#------MYLOG-------
build/mylog.o: lib/mylog.cpp | build
	$(cc) $(flags) -c lib/mylog.cpp -I ./lib -o build/mylog.o

build/libmylog.a: build/mylog.o | build
	ar crs build/libmylog.a build/mylog.o

#------LIST-------
build/list.o: lib/list.cpp build/libmylog.a | build
	$(cc) $(flags) -c lib/list.cpp -I ./lib -o build/list.o

build/liblist.a: build/list.o | build
	ar crs build/liblist.a build/list.o

#------COMPANY-------
build/company.o: lib/company.cpp build/liblist.a | build
	$(cc) $(flags) -c lib/company.cpp -I ./lib -o build/company.o

build/libcompany.a: build/company.o | build
	ar crs build/libcompany.a build/company.o

#------JOB-------
build/job.o: lib/job.cpp build/libcompany.a | build
	$(cc) $(flags) -c lib/job.cpp -I ./lib -o build/job.o

build/libjob.a: build/job.o | build
	ar crs build/libjob.a build/job.o

#------WORKER-------
build/worker.o: lib/worker.cpp build/libcompany.a | build
	$(cc) $(flags) -c lib/worker.cpp -I ./lib -o build/worker.o

build/libworker.a: build/worker.o | build
	ar crs build/libworker.a build/worker.o

#------DATA BASE----------
build/data_base.o: lib/data_base.cpp build/libworker.a build/libjob.a | build
	$(cc) $(flags) -c lib/data_base.cpp -I ./lib -o build/data_base.o

build/libdata_base.a: build/data_base.o | build
	ar crs build/libdata_base.a build/data_base.o

#------NETWORK-------
build/network.o: lib/network.cpp build/libdata_base.a | build
	$(cc) $(flags) -c lib/network.cpp -I ./lib -o build/network.o

build/libnetwork.a: build/network.o | build
	ar crs build/libnetwork.a build/network.o

#------TEST------------
build/test.o: test/test.cpp build/libnetwork.a | build
	$(cc) $(flags) -c test/test.cpp -I ./lib -o build/test.o

build/test: build/test.o | build
	$(cc) build/test.o -Lbuild -lmylog -llist -lcompany -ljob -lworker -ldata_base -lnetwork -o build/test

#------RELEASE-------
