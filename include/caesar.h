/*
 * caesar.h
 *
 *  Created on: Jan 26, 2018
 *      Author: variable
 */

#ifndef ENC_CAESAR_H_
#define ENC_CAESAR_H_

#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <bitset>
#include <stdlib.h>

int caesarEncrypt(std::string msg, int shift, int flags);
int caesarEncrypt(std::string msg, int shift, std::string inputFile,
		std::string outputFile, int flags);

#endif /* ENC_CAESAR_H_ */
