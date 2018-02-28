/*
 * caesar.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: variable
 */

#include "../include/caesar.h"
using namespace std;

int caesarEncrypt(string msg, int shift, int flags) {
	return caesarEncrypt(msg, shift, "", "", flags);
}

int caesarEncrypt(string msg, int shift, string inputFile, string outputFile,
		int flags) {
	
	bool flagi = !(inputFile.empty());
	ifstream in;

	if (flagi) {
		try {
			ifstream in(inputFile.c_str());
		} catch (fstream::failure::exception& e) {
			cerr << "Error: Input file not found" << endl;
			return 1;
		}
	}
	
	bool flago = !(outputFile.empty());
	ofstream out;
	
	if (flago) {
		try {
			ofstream out(outputFile.c_str());
		} catch (ostream::failure::exception& e) {
			return 1;
		}
	}
	
	bool loop = true;
	char nextChar;
	int iNextChar;
	char cNextChar;
	int i = -1;
	
	if (!flagi) {
		i = msg.length();
	}
	
	while (loop) {
		if (flagi) {
			if (in.eof()) {
				nextChar = '\0';
				in.close();
			} else {
				in >> nextChar;
			}
		} else {
			nextChar = msg[msg.length() - i];
			i--;
		}
		
		if (nextChar == '\0') {
			cNextChar = '\0';
		} else {
			iNextChar = (int) nextChar;
			switch (flags) {
			case 1:
				iNextChar += shift;
				while (iNextChar < 32) {
					iNextChar += 95;
				}

				if (iNextChar > 126) {
					iNextChar = ((iNextChar - 32) % 95) + 32;
				}
				
				break;
			
			//TODO: Take another look at this, see if it can be done better
			case 2:
				iNextChar = (int)toupper((char) iNextChar);
				if (iNextChar >= 'A' && iNextChar <= 'Z') {
					iNextChar += shift;
 					while (iNextChar < 'A' || iNextChar > 'Z') {
						iNextChar = ((iNextChar - 'A') % ('Z' - 'A')) + 'A';
					} 
				} 
				break;
			}
			
			cNextChar = (char) iNextChar;
		}
		
		if (flago) {
			out << cNextChar;
		} else {
			cout << cNextChar;
		}
		
		if (cNextChar == '\0') {
			if (out) {
				out.close();
			}
			loop = false;
		}
	}
	cout << endl;
	return 0;
}
