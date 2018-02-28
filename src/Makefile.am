bin_PROGRAMS = pbp 
pbp_SOURCES = run.cpp caesar.cpp vigenere.cpp
pbp_CFLAGS = -std=c++11
check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)

greptest.sh:
	echo './pbp -c 10 -s 1 "Hello" | grep "Rovvy"' > greptest.sh
	echo './pbp -c 10 -s 2 "Hello" | grep "ROVVY"' > greptest.sh
	echo './pbp -c 10 -s 1 -d "Rovvy" | grep "Hello"' > greptest.sh
	echo './pbp -p "Hi" -s 1 "Hello" | grep "1oUvX"' > greptest.sh
	echo './pbp -p "Hi" -s 1 "1oUvX" | grep "Hello"' > greptest.sh
	chmod +x greptest.sh

CLEANFILES = greptest.sh
