/*
 * Caesar.h
 *
 *  Created on: Aug 4, 2017
 *      Author: variable
 */

#ifndef CAESAR_H_
#define CAESAR_H_

#include <iostream>
#include <fstream>
#include <iterator>
#include <bitset>
#include <stdlib.h>

void caesarFromCLI(std::string msg, int shift, bool flagd, std::string inputFile, std::string outputFile, bool flags);

std::string caesarEncrypt(std::string message, int shift, bool loopChars);

#endif /* CAESAR_H_ */
