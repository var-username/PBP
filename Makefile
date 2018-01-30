SRCDIR ?= src
BUILDDIR ?= build

CXX ?= g++-7.0
STD ?= c++11

pbp: prepare run.o caesar.o vigenere.o
	if [ -d "$(BUILDDIR)" ]; then \
		cd $(BUILDDIR); \
	fi; \
	$(CXX) -o pbp run.o caesar.o vigenere.o -std=$(STD)

.PHONY: prepare 
prepare:
	if [ -d "$(BUILDDIR)" ]; then \
		echo ""; \
	elif [ -e "$(BUILDDIR)" ]; then \
		rm $(BUILDDIR) && mkdir $(BUILDDIR); \
	elif [ ! -d "$(BUILDDIR)" ]; then \
		mkdir $(BUILDDIR); \
	fi

run.o:
	$(CXX) -c -o $(BUILDDIR)/run.o $(SRCDIR)/run.cpp -std=$(STD)

caesar.o:
	$(CXX) -c -o $(BUILDDIR)/caesar.o $(SRCDIR)/enc/caesar.cpp -std=$(STD)

vigenere.o:
	$(CXX) -c -o $(BUILDDIR)/vigenere.o $(SRCDIR)/enc/vigenere.cpp -std=$(STD)

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/pbp
