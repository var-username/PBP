#include "../include/Run.h"
#include "../include/Caesar.h"
using namespace std;

void printhelp() {
	printf("Yeah you need help");
}

int main(int argc, char **argv) {
    //return value from getopt_long
    int c;

    //Used as bool, made int for compatability with getopt_long
    //If >0, list encryption methods
    int flagl = 0;

    //Input file, blank if none
    string flagi = "";

    //Output file, blank if none
    string flago = "";

    //Used as bool, int for compatability with getopt_long
    //If >0, Caesar shift is being used
    int flagc = 0;

    //Used as bool, int for compatability with getopt_long
    //If >0, wrap ASCII codes to typically visable characters
    int flags = 0;

    //Used as bool, int for compatability with getopt_long
    //If >0, run encryption scheme backwards to return cleartext from
    //ciphertext input.
    int flagd = 0;

    //Shift amount for Caesar cipher
    int shift = 0;

    //If no input file, this is the text that will be used in processes
    string msg = "";
    
    //int digit_optind = 0;
    while (1) {
	//int this_option_optind = optind ? optind : 1;
	int option_index = 0;
	static struct option long_options[] = {
	    { "list",		    no_argument,	&flagl,	'l' },
	    { "inputFile",	    required_argument,	0,	'i' },
	    { "outputFile",	    required_argument,	0,	'o' },
	    { "caesar",		    required_argument,	0,	'c' },
	    { "standardCharacters", no_argument,	&flags,	's' },
	    { "decrypt",	    no_argument,	0,	'd' },
	    { "help",		    no_argument,	0,	'h' },
	    { "version",	    no_argument,	0,	'V' },
	    { 0,		    0,			0,	 0  }
	};

	c = getopt_long(argc, argv, "lc:si:o:d", long_options, &option_index);
	if (c == -1) {
	    break;
	}

	switch (c) {
	    case 'h':
		//Print help message
		printhelp();
		
		//Exit, status 0 (no error)
		exit(EXIT_SUCCESS);

		//Break, to make sure switch statement is correct
		break;
	    case 'V':
		//Print version message
		std::cout << VERSION << " - " << AUTHOR;

		//Exit, status 0 (no error)
		exit(EXIT_SUCCESS);

		//Break, to make sure switch statement is corrent
		break;
	    case 'd':
		//Set flagd (decryption mode)
		flagd = true;

		//Break statement
		break;
	    case 'l':
		//Set flagl (List schemes)
		flagl = true;

		//Temporary list output
		printf("Listing options \n");
		
		//Exit, status 0 (no error)
		exit(EXIT_SUCCESS);

		//Break, to make sure switch statement is correct
		break;
	    case 'i':
		//Set flagi (input file location) to inputed argument
		flagi = string(optarg);

		//Print to be verbose
		printf("drawing input from file '%s'\n", flagi.c_str());
		
		//Break statement
		break;
	    case 'o':
		//Set flago (output file location) to inputed argument
		flago = string(optarg);

		//Print to be verbose
		printf("printing output to file '%s'\n", flago.c_str());
		
		//Break statement
		break;
	    case 'c':
		//Set flagc (caesarian encryption)
		flagc = true;
		
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

		//Break statement
		break;
	    case 's':
		//Set flags (wrap standard characters)
		flags = true;

		//Print to be verbose
		printf("Using standard characters only\n");
		
		//Break statement
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

    //If caesar scheme is chosen
    if(flagc) {
	//Print to be verbose
	printf("Using caesarian cipher with shift '%i'\n", shift);
	
	//Run encryption method (likely will be changed)
	caesarFromCLI(msg, shift, flagd, !(flagi.empty()), !flago.empty(), flagi, flago, flags);
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

