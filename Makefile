__start__: obj libs __lines_for_space__ obj/Scene.o obj/Sender.o obj/LibInterface.o obj/xmlinterp.o obj/Reader.o obj/Set4LibInterfaces.o interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj
libs:
	mkdir libs


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall




interp: obj/main.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/Scene.o obj/Sender.o obj/LibInterface.o obj/Reader.o obj/Set4LibInterfaces.o obj/xmlinterp.o -ldl -lxerces-c -pthread

obj/main.o: src/main.cpp inc/Interp4Command.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Set4LibInterfaces.o: src/Set4LibInterfaces.cpp inc/Set4LibInterfaces.hh inc/Interp4Command.hh inc/LibInterface.hh
	g++ -c ${CPPFLAGS} -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

obj/Reader.o: src/Reader.cpp inc/Reader.hh inc/xmlinterp.hh inc/Configuration.hh
	g++ -c ${CPPFLAGS} -o obj/Reader.o src/Reader.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh inc/Configuration.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh inc/Interp4Command.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/Sender.o: src/Sender.cpp inc/Sender.hh inc/Scene.hh inc/Port.hh
	g++ -c ${CPPFLAGS} -o obj/Sender.o src/Sender.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh inc/MobileObj.hh inc/AccessControl.hh inc/Configuration.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
