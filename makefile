cc = clang++
cflags = -Wall -pedantic -Werror --debug

.DEFAULT_GOAL := all

.PHONY: clean check app

all: build/test build/app

# Make the build dir
build:
	mkdir -p build

# Remove the build dir
clean:
	rm -rf build

# Launch the tests
check: build/test
	./build/test

# Launch the application
app: build/app
	./build/app

#------LIBS CREATION-------
#------MYLOG-------
build/mylog.o: lib/mylog.cpp lib/mylog.h | build
	$(cc) $(cflags) -c lib/mylog.cpp -I ./lib -o build/mylog.o

build/libmylog.a: build/mylog.o | build
	ar crs build/libmylog.a build/mylog.o

#------LIST-------
build/list.o: lib/list.cpp lib/list.h build/libmylog.a | build
	$(cc) $(cflags) -c lib/list.cpp -I ./lib -o build/list.o

build/liblist.a: build/list.o | build
	ar crs build/liblist.a build/list.o

#------COMPANY-------
build/company.o: lib/company.cpp lib/company.h build/liblist.a | build
	$(cc) $(cflags) -c lib/company.cpp -I ./lib -o build/company.o

build/libcompany.a: build/company.o | build
	ar crs build/libcompany.a build/company.o

#------JOB-------
build/job.o: lib/job.cpp lib/job.h build/libcompany.a | build
	$(cc) $(cflags) -c lib/job.cpp -I ./lib -o build/job.o

build/libjob.a: build/job.o | build
	ar crs build/libjob.a build/job.o

#------WORKER-------
build/worker.o: lib/worker.cpp lib/worker.h build/libcompany.a | build
	$(cc) $(cflags) -c lib/worker.cpp -I ./lib -o build/worker.o

build/libworker.a: build/worker.o | build
	ar crs build/libworker.a build/worker.o

#------DATA BASE----------
build/data_base.o: lib/data_base.cpp lib/data_base.h build/libworker.a build/libjob.a | build
	$(cc) $(cflags) -c lib/data_base.cpp -I ./lib -o build/data_base.o

build/libdata_base.a: build/data_base.o | build
	ar crs build/libdata_base.a build/data_base.o

#------SEARCH-------
build/search.o: lib/search.cpp lib/search.h build/libdata_base.a | build
	$(cc) $(cflags) -c lib/search.cpp -I ./lib -o build/search.o

build/libsearch.a: build/search.o | build
	ar crs build/libsearch.a build/search.o

#------UI-------
build/UI.o: lib/UI.cpp lib/UI.h build/libsearch.a | build
	$(cc) $(cflags) -c lib/UI.cpp -I ./lib -o build/UI.o

build/libUI.a: build/UI.o | build
	ar crs build/libUI.a build/UI.o

#------BIN CREATION-------
#------TEST------------
build/test.o: test/test.cpp build/libsearch.a | build
	$(cc) $(cflags) -c test/test.cpp -I ./lib -o build/test.o

build/test: build/test.o | build
	$(cc) build/test.o -L ./build -lsearch -ldata_base -ljob -lworker -lcompany -llist -lmylog -o build/test --debug

#------APPLICATION-------
build/app.o: app/app.cpp build/libUI.a | build
	$(cc) $(cflags) -c app/app.cpp -I ./lib -o build/app.o

build/app: build/app.o | build
	$(cc) build/app.o -L ./build -lUI -lsearch -ldata_base -ljob -lworker -lcompany -llist -lmylog -o build/app --debug
