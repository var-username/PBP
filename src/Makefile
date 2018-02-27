# src/Makefile.  Generated from Makefile.in by configure.

srcdir	= .


CC		?= cc
CXX 	?= c++

STD 	?= c++11

run.o: run.cpp caesar.o vigenere.o
	$(CXX) -std=$(STD) -c $(srcdir)/run.cpp -o ../run.o

caesar.o vigenere.o:
	cd enc && $(MAKE) $@

Makefile: Makefile.in ../config.status
	cd .. && ./config.status src/$@

../config.status: ../configure
	cd .. && ./config.status --recheck
