/*
 * Caesar.cpp
 *
 *  Created on: Aug 4, 2017
 *      Author: variable
 */

#include "../include/Caesar.h"

using namespace std;


void caesarFromCLI(string msg, int shift, bool flagd, string inputFile, string outputFile, bool flags) {
	bool flagi = !(inputFile.empty());
	bool flago = !(outputFile.empty());

	if (flagd) {
		shift = 0 - shift;
	}

	if (flagi) {
		try {
			std::ifstream in(inputFile.c_str());
			if (in) {
				// get length of file:
				in.seekg(0, in.end);
				int length = in.tellg();
				in.seekg(0, in.beg);
				char * buffer = new char[length];
				// read data as a block:
				in.read(buffer, length);
				if (in) {
					std::cout << "all characters read successfully."
							  << endl;
				} else {
					std::cout << "error: only " << in.gcount()
							  << " could be read";
				}
				in.close();
				msg = string(buffer);
				// ...buffer contains the entire file...
				delete[] buffer;
			}

		} catch (std::fstream::failure::exception& e) {
			printf("Error: Input file not found");
			exit(EXIT_FAILURE);
		}
	}

	if (flago) {
		std::ofstream out(outputFile.c_str());
		out << caesarEncrypt(msg, shift, flags).c_str();
		out.close();
	} else {
		//If not inputing from file
		//Run function, print result to stout
		printf("%s\n", caesarEncrypt(msg, shift, flags).c_str());
	}
}

string caesarEncrypt(string message, int shift, bool loopChars) {
	for (int i = 0; i < message.length(); i++) {
		if (loopChars) {
			message[i] += shift;

			while (message[i] > 126) {
				message[i] = ((message[i] - 32) % 95) + 32;
			}

			while (message[i] < 32) {
				message[i] = ((message[i] - 32) + 95) % 95;
			}
		} else {
			message[i] += shift;
		}
	}

	return message;
}
