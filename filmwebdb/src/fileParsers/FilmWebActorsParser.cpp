/*
 * FilmWebActorsParser.cpp
 *
 *  Created on: 13-10-2013
 *      Author: miliardopiscrat
 */

#include "FilmWebActorsParser.hpp"

static const std::string nullValue = "null";

FilmWebActorsParser::FilmWebActorsParser() {
	// TODO Auto-generated constructor stub

}

FilmWebActorsParser::~FilmWebActorsParser() {
	// TODO Auto-generated destructor stub
}

void FilmWebActorsParser::parse(IFilmWebFileHandle& handle, InfoResult& result) {

	std::vector<std::string> line;

	while (handle.getNextLine(line)) {

		if (line[3] != nullValue) {

			result.name_actor.push_back(line[3]);
		}

		line.clear();
	}
}
