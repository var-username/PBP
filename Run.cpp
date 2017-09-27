#include "Run.h"
#include "Caesar.h"
using namespace std;

void printhelp() {
	printf("Yeah you need help");
}

int main(int argc, char **argv) {
	int c;
	int flagl = 0;
	string flagi = "";
	string flago = "";
	int flagc = 0;
	int flags = 0;
	int flagd = 0;
	int shift = 0;
	string msg = "";
	//int digit_optind = 0;

	while (1) {
		//int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{ "list",				no_argument,	   &flagl, 'l' },
			{ "inputFile",			required_argument, 0,      'i' },
			{ "outputFile",			required_argument, 0,      'o' },
			{ "caesar",             required_argument, 0,	   'c' },
			{ "standardCharacters", no_argument,       &flags, 's' },
			{ "decrypt",			no_argument,	   0,      'd' },
			{ "help",				no_argument,	   0,      'h' },
			{ 0,                    0,                 0,       0  }
		};

		c = getopt_long(argc, argv, "lc:si:o:d", long_options, &option_index);
		if (c == -1) {
			break;
		}

		switch (c) {
			case 'h':
				printhelp();
				exit(EXIT_SUCCESS);
			case 'd':
				flagd = true;
				break;
			case 'l':
				flagl = true;
				printf("Listing options \n");
				exit(EXIT_SUCCESS);
				break;
			case 'i':
				flagi = string(optarg);
				printf("drawing input from file '%s'\n", flagi.c_str());
				break;
			case 'o':
				flago = string(optarg);
				printf("printing output to file '%s'\n", flago.c_str());
				break;
			case 'c':
				flagc = true;
				try {
					string arg = string(optarg);
					if (arg.find('-') != string::npos) {
						printf("Error: No positive int found after flag 'c'\n");
						exit(EXIT_FAILURE);
					}
					shift = stoi(arg);
				} catch (std::invalid_argument& e) {
					printf("Error: Only numerical values allowed for parameter 'shift'\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 's':
				flags = true;
				printf("Using standard characters only\n");
				break;
			case '?':
				break;
			default:
				printf("?? getopt returned character code 0%o ??\n", c);
		}
	}

	if (optind < argc) {
		msg += string(argv[argc -1]);
		optind = argc;
	}

	if(flagc) {
		printf("Using caesarian cipher with shift '%i'\n", shift);
		runFromCLI(msg, shift, flagd, !(flagi.empty()), !flago.empty(), flagi, flago, flags);
	}

	exit(EXIT_SUCCESS);

	/*if (argc < 2) {
		printhelp();
		return EXIT_SUCCESS;
	} else {
		printf("Program ran successfully!");
	}*/
}

