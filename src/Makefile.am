bin_PROGRAMS = pbp 
pbp_SOURCES = run.cpp caesar.cpp vigenere.o
pbp_CFLAGS = -std=c++11
check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)

greptest.sh:
	echo './pbp -c 10 -s 1 "Hello" | grep "Rovvy"' > greptest.sh
	echo './pbp -c 10 -s 2 "Hello" | grep "ROVVY"' > greptest.sh
	chmod +x greptest.sh

CLEANFILES = greptest.sh
