SRCFILES = src/*
IDIR = include/

CXX ?= g++

pbp: 
	if [ -d "build" ]; then \
	cd build; \
	elif [ -e "build" ]; then \
	rm build && mkdir build; \
	elif [ ! [ -d "build" ] ]; then \
	mkdir build && cd build; \
	fi; \
	CXX -o pbp ../$(SRCFILES) -I ../$(IDIR)

.PHONY: clean
clean:
	rm -f build/pbp
