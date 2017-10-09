SRCFILES = src/*
IDIR = include/

pbp: 
	if [ -d "build" ]; then cd build; elif [ -e "build" ]; then rm build && mkdir build; elif [ ! [ -d "build" ] ]; then mkdir build && cd build; fi; g++ -o pbp ../$(SRCFILES) -I ../$(IDIR)

clean:
	rm -f build/pbp
