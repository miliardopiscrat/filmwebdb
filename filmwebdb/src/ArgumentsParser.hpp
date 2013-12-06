/*
 * ArgumentsParser.hpp
 *
 *  Created on: Oct 4, 2013
 *      Author: user
 */

#ifndef ARGUMENTSPARSER_HPP_
#define ARGUMENTSPARSER_HPP_

#include <string>
#include <getopt.h>
#include <curl/curl.h>

class ArgumentsParser {

public:
	ArgumentsParser(int argc, char ** argv) :
			_argc(argc), _argv(argv) {
	}

	void parse(std::string &language, std::string &output, std::string &keyword,
			bool &searchOpt, bool &versionInfo) {

		searchOpt = false;
		versionInfo = false;
		char c;
		while ((c = getopt(_argc, _argv, "svVl:k:o:")) != -1) {
			switch (c) {
			case 's':
				searchOpt = true;
				break;
			case 'l':
				language = std::string(optarg);
				break;
			case 'k':
				keyword = std::string(optarg);
				keyword = curl_unescape(keyword.c_str() , keyword.length());
				break;
			case 'o':
				output = std::string(optarg);
				break;
			case 'v':
			case 'V':
					versionInfo =  true;
					break;
			}
		}
	}

private:
	int _argc;
	char ** _argv;

	ArgumentsParser(const ArgumentsParser&); // no implementation
	ArgumentsParser operator=(const ArgumentsParser &); // no implementation
};

class Arguments {

public:
	Arguments(int argc, char ** argv) {

		ArgumentsParser parser(argc, argv);
		parser.parse(language, output, keyword, searchOpt, versionInfo);
	}

	bool isSearchOpt() const {

		return searchOpt;
	}

	bool isVersionInfo() const {

		return versionInfo;
	}

	const std::string& getLanguage() const {

		return language;
	}

	const std::string& getKeyword() const {

		return keyword;
	}

	const std::string& getOutput() const {

		return output;
	}

private:
	bool searchOpt, versionInfo;
	std::string language;
	std::string keyword;
	std::string output;
};

#endif /* ARGUMENTSPARSER_HPP_ */
