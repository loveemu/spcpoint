
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

bool both_are_spaces(char lhs, char rhs)
{
	return (lhs == rhs) && (lhs == ' ');
}

void replace_all(std::string& str, const std::string& from, const std::string& to)
{
	std::string::size_type pos = 0;
	while (pos = str.find(from, pos), pos != std::string::npos) {
		str.replace(pos, from.length(), to);
		pos += to.length();
	}
}

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
	bool title_from_filename = false;

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
			else if (strcmp(argv[argi], "-tf") == 0) {
				title_from_filename = true;
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

		std::map<std::string, std::string> psf_tags(opt_tags);
		if (title_from_filename) {
			std::string title(argv[argi]);

			// remove extension
			std::string::size_type offset_dot = title.find_last_of('.');
			if (offset_dot != std::string::npos) {
				title = title.substr(0, offset_dot);
			}

			// trim some beginning characters
			std::string::size_type offset_start = title.find_first_not_of(" _%0123456789-");
			if (offset_start != std::string::npos) {
				title = title.substr(offset_start);
			}

			// replace some other stuff
			replace_all(title, "%20", " ");
			replace_all(title, "_", " ");

			// replace multiple spaces with one space
			std::string::iterator new_end = std::unique(title.begin(), title.end(), both_are_spaces);
			title.erase(new_end, title.end());

			psf_tags["title"] = title;
			puts(title.c_str());
		}

		spc->ImportPSFTag(psf_tags);
		spc->Save(argv[argi]);

		delete spc;
	}

	return EXIT_SUCCESS;
}
