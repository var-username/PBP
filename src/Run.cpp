#include "../include/Run.h"
#include "../include/Caesar.h"
using namespace std;

void printhelp() {
	printf("Yeah you need help\n");
}

void printlist() {
	printf("Currently accepted encryption methods:\n");
	printf("--caesar -c : Caesarian encryption\n");
}

int main(int argc, char **argv) {
    //return value from getopt_long
    int c;
    
    string flagInput, flagOutput;
    int flagDecrypt, flagHelp, flagList, flagStandardChars, flagVerbose, flagVersion;
    int flagCaesarian;

    //Input file, blank if none
    flagInput = "";

    //Output file, blank if none
    flagOutput = "";

    //Used as bool, int for compatibility with getopt_long
    //If >0, Caesar shift is being used
    flagCaesarian = 0;

    //Shift amount for Caesar cipher
    int shift = 0;

    //If no input file, this is the text that will be used in processes
    string msg = "";
    
    //int digit_optind = 0;
    while (1) {
    	//int this_option_optind = optind ? optind : 1;
    	int option_index = 0;
    	static struct option long_options[] = {
    		{ "list",		    	no_argument,		&flagList,			'l' },
			{ "inputFile",	    	required_argument,	0,					'i' },
			{ "outputFile",	    	required_argument,	0,					'o' },
			{ "caesar",		    	required_argument,  0,					'c' },
			{ "standardCharacters", no_argument,		&flagStandardChars,	's' },
			{ "decrypt",	    	no_argument,	 	&flagDecrypt,		'd' },
			{ "help",		    	no_argument,		&flagHelp,			'h' },
			{ "version",	    	no_argument,		&flagVersion,		'V' },
			{ "verbose",	    	no_argument,		&flagVerbose,		'v' },
			{ 0,		    		0,					0,	    		 	 0  }
	};

    	c = getopt_long(argc, argv, "li:o:c:sdhVv", long_options, &option_index);
    	if (c == -1) {
    		break;
    	}

    	switch (c) {
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
	    		flagInput = string(optarg);
	    		break;
	    	case 'o':
	    		flagOutput = string(optarg);
	    		break;
	    	case 'c':
	    		flagCaesarian = true;
	    		try {
	    			//Try setting string arg to next inputed argument
	    			string arg = string(optarg);

	    			//If character '-' is found in argument
	    			if (arg.find('-') != string::npos) {
	    				//Print error
	    				printf("Error: No positive int found after flag 'c'\n");
	    				printf("To use a negative shift, use flag 'd'\n");
			
	    				//Exit, status 1 (Error occured)
	    				exit(EXIT_FAILURE);
	    			}

	    			//If no '-' char in argument, set int shift to argument
	    			shift = stoi(arg);

	    		} catch (std::invalid_argument& e) {
	    			//Print error: no number for shift after flagc
	    			printf("Error: Only numerical values allowed for parameter 'shift'\n");
		    
	    			//Exit, status 1 (Error occured)
	    			exit(EXIT_FAILURE);
	    		}
	    		break;
	    	case 's':
	    		flagStandardChars = true;
	    		break;
	    	case '?':
	    		//Kinda temporary, mostly here to cover bases
	    		break;
	    	default:
	    		//This shouldnt happen. If this happens, getopt broke and it likely
	    		//is not my fault
	    		printf("?? getopt returned character code 0%o ??\n", c);
	    		break;
    	}
    }

    //If there are more arguments, but all flags have been parsed, last args are message
    if (optind < argc) {
    	msg += string(argv[argc - 1]);
    	optind = argc;
    }

    if(flagHelp) {
    	if(flagVerbose) {
    		printf("Displaying help message\n");
    	}

    	printhelp();

    	if(flagVerbose) {
    		printf("Exiting program...\n");
    	}

    	//Exit, status 0 (No error)
    	exit(EXIT_SUCCESS);
    }

    if(flagVersion) {
    	if(flagVerbose) {
    		printf("Printing version info\n");
    	}

    	std::cout << VERSION << " - " << AUTHOR;

    	if(flagVerbose) {
    		printf("Exiting program...\n");
    	}

    	exit(EXIT_SUCCESS);
    }

    if(flagList) {
    	if(flagVerbose) {
    		printf("Printing availible encryption schemes\n");
    	}

    	printlist();

    	if(flagVerbose) {
    		printf("Exiting program...\n");
    	}

    	exit(EXIT_SUCCESS);
    }

    if(!flagInput.empty() && flagVerbose) {
    	printf("drawing input from file '%s'\n", flagInput.c_str());
    }

    if(!flagOutput.empty() && flagVerbose) {
    	printf("printing output to file '%s'\n", flagOutput.c_str());
    }

    if(flagStandardChars && flagVerbose) {
    	printf("Using standard characters only\n");
    }

    //If caesar scheme is chosen
    if(flagCaesarian) {
    	if(flagVerbose) {
    		printf("Using caesarian cipher with shift '%i'\n", shift);
    	}
	
    	//Run encryption method (likely will be changed)
    	caesarFromCLI(msg, shift, flagDecrypt, !(flagInput.empty()), !flagOutput.empty(), flagInput, flagOutput, flagStandardChars);
    }

    //Exit, status 0 (no error)
    exit(EXIT_SUCCESS);
    
    /*
	if (argc < 2) {
	    printhelp();
	    return EXIT_SUCCESS;
	} else {
	    printf("Program ran successfully!");
	}
    */
}

