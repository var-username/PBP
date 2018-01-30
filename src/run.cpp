/*
 * run.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: variable
 */

#include "../include/run.h"
#include "../include/enc_types.h"
using namespace std;

int main(int argc, char **argv) {
	//return value from getopt_long
	int getopt_long_return = 0;

	string inputFile, outputFile;
	int flagDecrypt = 0;
	int flagHelp = 0;
	int flagList = 0;
	int flagStandardChars = 0;
	int flagVerbose = 0;
	int flagVersion = 0;

	int numberOfEncTypes = 0;

	//Used as bool, int for compatibility with getopt_long
	//If >0, Caesar shift is being used
	bool flagCaesarian = false;

	bool flagVigenere = false;

	//Input file, blank if none
	inputFile = "";

	//Output file, blank if none
	outputFile = "";

	//Shift amount for Caesar cipher
	int shift = 0;

	string vigenereShift = "";

	//If no input file, this is the text that will be used in processes
	string msg = "";

	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
				{ "list", 				no_argument, 		&flagList, 		'l' },
				{ "inputFile", 			required_argument, 	0, 				'i' },
				{ "outputFile", 		required_argument, 	0, 				'o' },
				{ "caesar", 			required_argument, 	0, 				'c' },
			    { "vigenere", 			required_argument, 	0, 				'p' },
				{ "standardCharacters",	optional_argument, 	0, 				's' },
				{ "decrypt", 			no_argument, 		&flagDecrypt,	'd' },
				{ "help", 				no_argument, 		&flagHelp, 		'h' },
				{ "version", 			no_argument, 		&flagVersion, 	'V' },
				{ "verbose", 			no_argument,		&flagVerbose, 	'v' },
				{ 0, 					0, 					0, 				 0 }
		};

		getopt_long_return = getopt_long(argc, argv, "li:o:c:p:s:dhVv", long_options, &option_index);
		if (getopt_long_return == -1) {
			break;
		}

		switch (getopt_long_return) {

		case 'v':
			flagVerbose = true;
			break;

		case 'h':
			flagHelp = true;
			break;

		case 'V':
			flagVersion = true;
			break;

		case 'd':
			flagDecrypt = true;
			break;

		case 'l':
			flagList = true;
			break;

		case 'i':
			inputFile = string(optarg);
			break;

		case 'o':
			outputFile = string(optarg);
			break;

		case 'c':
			flagCaesarian = true;
			try {
				//Try setting string arg to next inputed argument
				string arg = string(optarg);

				//If character '-' is found in argument
				if (arg.find('-') != string::npos) {
					//Print error
					cerr << "Error: No positive int found after flag 'c'" << endl;
					cerr << "To use a negative shift, use flag 'd'" << endl;

					//Exit, status 1 (Error occurred)
					exit(EXIT_FAILURE);
				}

				//If no '-' char in argument, set int shift to argument
				shift = stoi(arg.c_str());

			} catch (std::invalid_argument& e) {
				//Print error: no number for shift after flagc
				cerr << "Error: Only numerical values allowed for parameter 'shift'" << endl;

				//Exit, status 1 (Error occurred)
				exit(EXIT_FAILURE);
			}
			break;


		case 'p':
		   flagVigenere = true;
		   try {
		   	   string arg = string(optarg);
		  	   vigenereShift = arg.c_str();
		   } catch (std::invalid_argument& e) {
		   	   cerr << "An unknown error has occurred, the program will now exit" << endl;
		       exit(EXIT_FAILURE);
		   }
		   break;


		case 's':
			try {
				string arg = string(optarg).c_str();
				flagStandardChars = stoi(arg.c_str());
				if (flagStandardChars < 0 || flagStandardChars >= 3) {
					cerr << "Error: Standard characters argument must be between 0 and 2, inclusive" << endl;
					exit(EXIT_FAILURE);
				}
			} catch (std::invalid_argument& e) {
				cerr << "An unknown error has occurred, the program will now exit" << endl;
				exit(EXIT_FAILURE);
			}
			break;

		case '?':
			//Kinda temporary, mostly here to cover bases
			break;

		default:
			//This shouldn't happen. If this happens, getopt broke and it likely
			//is not my fault
			cerr << "?? getopt returned character code 0" << (int)getopt_long_return << "??" << endl;
			break;
		}
	}

	//If there are more arguments, but all flags have been parsed, last args are message
	if (optind < argc) {
		msg += string(argv[argc - 1]);
		optind = argc;
	}

	if(flagCaesarian) {
		numberOfEncTypes++;
	}

	if(flagVigenere) {
		numberOfEncTypes++;
	}


	if(!inputFile.empty() && flagVerbose) {
	    printf("drawing input from file '%s'\n", inputFile.c_str());
	}

	if(!outputFile.empty() && flagVerbose) {
	   	printf("printing output to file '%s'\n", outputFile.c_str());
	}

	if(flagStandardChars != 0 && flagVerbose) {
		switch (flagStandardChars) {
		case 1:
			printf("Using only ASCII printable characters\n");
			break;
		case 2:
			printf("Preserving non-alphabetical characters\n");
			break;
		case 3:
			printf("Ignoring non-alphabetical characters, outputting uppercase\n");
			break;
		}
	}

	if(numberOfEncTypes > 1) {
		cerr << "Warning: more than one primary encryption entered, program will now exit" << endl;
		exit(EXIT_FAILURE);
	}

	if(flagCaesarian) {
		if(flagVerbose) {
			printf("Using caesarian cipher with shift '%i'\n", shift);
		}

		if(flagDecrypt) {
			shift = 0 - shift;
		}

		return caesarEncrypt(msg.c_str(), shift, inputFile.c_str(), outputFile.c_str(), flagStandardChars);
	}

	if(flagVigenere) {
		if(flagVerbose) {
			printf("Using vigenere cipher with shift '%s'\n", vigenereShift.c_str());
		}
		return vigenereEncrypt(msg.c_str(), vigenereShift.c_str(), inputFile.c_str(), outputFile.c_str(), flagStandardChars, flagDecrypt);
		//caesarEncrypt(msg.c_str(), shift, inputFile.c_str(), outputFile.c_str(), flagStandardChars);
	}

	exit(EXIT_SUCCESS);

}

