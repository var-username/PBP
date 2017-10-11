/*
 * Caesar.cpp
 *
 *  Created on: Aug 4, 2017
 *      Author: variable
 */

#include "../include/Caesar.h"

using namespace std;

void caesarFromCLI(string msg, int shift, bool flagd, bool flagi, bool flago,
		string inputFile, string outputFile, bool flags) {
	switch (flagd) {
	case true:
		shift = 0 - shift;
		break;
	case false:
		break;
	}

	if (!flago) {
		if (!flagi) {
			printf("%s\n", caesarEncrypt(msg, shift, flags).c_str());
		} else {
			try {
				std::ifstream in(inputFile, std::ifstream::binary);
				//in.open(inputFile, ios::in);
				string input;
				if (in) {
					// get length of file:
					in.seekg(0, in.end);
					int length = in.tellg();
					in.seekg(0, in.beg);
					char * buffer = new char[length];
					// read data as a block:
					in.read(buffer, length);
					if (in)
						std::cout << "all characters read successfully."
								<< endl;
					else
						std::cout << "error: only " << in.gcount()
								<< " could be read";
					in.close();
					input = string(buffer);
					// ...buffer contains the entire file...
					delete[] buffer;
				}
				printf("%s\n", caesarEncrypt(input, shift, flags).c_str());
			} catch (std::fstream::failure::exception& e) {
				printf("Error: Input file not found");
				exit(EXIT_FAILURE);
			}
		}
	} else {
		if (!flagi) {
			ofstream out(outputFile);
			out << caesarEncrypt(msg, shift, flags).c_str();
			out.close();
		} else {
			try {
				std::ifstream in(inputFile, std::ifstream::binary);
				std::ofstream out(outputFile);
				//in.open(inputFile, ios::in);
				string input;
				if (in) {
					// get length of file:
					in.seekg(0, in.end);
					int length = in.tellg();
					in.seekg(0, in.beg);
					char * buffer = new char[length];
					// read data as a block:
					in.read(buffer, length);
					if (in)
						std::cout << "all characters read successfully."
								<< endl;
					else
						std::cout << "error: only " << in.gcount()
								<< " could be read";
					in.close();
					input = string(buffer);
					// ...buffer contains the entire file...
					delete[] buffer;
				}
				out << (caesarEncrypt(input, shift, flags).c_str());
				out.close();
			} catch (std::fstream::failure::exception& e) {
				printf("Error: Input file not found");
				exit(EXIT_FAILURE);
			}
		}
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
