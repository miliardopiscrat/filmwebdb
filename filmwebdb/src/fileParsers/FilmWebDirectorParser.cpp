/*
 * FilmWebDirectorParser.cpp
 *
 *  Created on: 13-10-2013
 *      Author: miliardopiscrat
 */

#include "FilmWebDirectorParser.hpp"

#include <sstream>

static const std::string nullValue = "null";

FilmWebDirectorParser::FilmWebDirectorParser() {
	// TODO Auto-generated constructor stub

}

FilmWebDirectorParser::~FilmWebDirectorParser() {
	// TODO Auto-generated destructor stub
}

void FilmWebDirectorParser::parse(IFilmWebFileHandle& handle, InfoResult& result) {

	std::vector<std::string> line;
	std::stringstream ss;

	if (handle.getNextLine(line)) {

		if (line[3] != nullValue) {

			ss << line[3];
		}
	}

	while (handle.getNextLine(line)) {

		if (line[3] != nullValue) {
			ss << ", " << line[3];
		}
		line.clear();
	}

	result.director = ss.str();
}
