/*
 * vigenere.h
 *
 *  Created on: Jan 30, 2018
 *      Author: variable
 */

#ifndef ENC_VIGENERE_H_
#define ENC_VIGENERE_H_

#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <fstream>

int vigenereEncrypt(std::string msg, std::string shift, int flags, bool flagd);
int vigenereEncrypt(std::string msg, std::string shift, std::string inputFile, std::string outputFile, int flags, bool flagd);

#endif /* ENC_VIGENERE_H_ */
