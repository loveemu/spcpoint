
#define NOMINMAX

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

#include "SPCFile.h"

#define APP_NAME    "spcpoint"
#define APP_VER     "[2015-04-09]"
#define APP_URL     "http://github.com/loveemu/spcpoint"

static void usage(const char * progname)
{
	printf("%s %s\n", APP_NAME, APP_VER);
	printf("<%s>\n", APP_URL);
	printf("\n");
	printf("Usage: `%s [-tf] [-variable=value ...] spc-file(s)`\n", progname);
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	std::map<std::string, std::string> opt_tags;

	int argi = 1;
	while (argi < argc && argv[argi][0] == '-')
	{
		char * p_equal = strchr(argv[argi], '=');

		if (p_equal != NULL) {
			// tag option
			std::string name(argv[argi], 1, p_equal - argv[argi] - 1);
			std::string value(p_equal + 1);
			opt_tags[name] = value;
		}
		else {
			// regular option
			if (strcmp(argv[argi], "--help") == 0) {
				usage(argv[0]);
				return EXIT_FAILURE;
			}
			else {
				fprintf(stderr, "Error: Unknown option \"%s\"\n", argv[argi]);
				return EXIT_FAILURE;
			}
		}

		argi++;
	}

	int argnum = argc - argi;
	if (argnum == 0) {
		fprintf(stderr, "Error: No input files\n");
		return EXIT_FAILURE;
	}

	int num_errors = 0;
	for (; argi < argc; argi++) {
		SPCFile * spc = SPCFile::Load(argv[argi]);
		if (spc == NULL) {
			continue;
		}

#ifdef _DEBUG
		printf("Current tags:\n");
		printf("\n");
		printf("```\n");

		std::map<std::string, std::string> tags = spc->ExportPSFTag(true);
		for (auto itr = tags.begin(); itr != tags.end(); ++itr) {
			const std::string & name = (*itr).first;
			const std::string & value = (*itr).second;
			printf("%s=%s\n", name.c_str(), value.c_str());
		}

		printf("```\n");
		printf("\n");
#endif

		spc->ImportPSFTag(opt_tags);
		spc->Save(argv[argi]);

		delete spc;
	}

	return EXIT_SUCCESS;
}
