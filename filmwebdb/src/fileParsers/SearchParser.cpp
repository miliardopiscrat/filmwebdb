/*
 * SearchParser.cpp
 *
 *  Created on: 10-10-2013
 *      Author: miliardopiscrat
 */

#include "SearchParser.hpp"

#include <vector>
#include <string>
#include <sstream>
#include "Debug.hpp"
#include "ParserBase.hpp"

SearchParser::SearchParser() {

}

SearchParser::~SearchParser() {

}

void SearchParser::parse(IFilmWebFileHandle& handle, std::vector<Element>& searchList) {

	std::vector<std::string> line;
	while (handle.getNextLine(line) && !line.empty() && searchList.size() < MAX_SEARCH_RESULT) {
		TRACE(line)
		Element element = { };
		element.id = line[1];

		if (line.size() > 6 && !line[6].empty()) {
			std::istringstream ss(line[6]);
			ss >> element.year;
		}

		element.title = line[3];

		searchList.push_back(element);
		line.clear();
	}
}
