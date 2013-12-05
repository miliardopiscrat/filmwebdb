/*
 * FilmWebInfoParser.cpp
 *
 *  Created on: 12-10-2013
 *      Author: miliardopiscrat
 */

#include "FilmWebInfoParser.hpp"
#include "Debug.hpp"
#include <sstream>

static const std::string image_host_addr = "http://1.fwcdn.pl/po";
static const std::string nullValue = "null";

FilmWebInfoParser::FilmWebInfoParser() {

}

FilmWebInfoParser::~FilmWebInfoParser() {

}

void FilmWebInfoParser::parse(IFilmWebFileHandle& handle, InfoResult& infoResult) {

	std::vector<std::string> line;

	if (handle.getNextLine(line) && !line.empty()) {
		TRACE(line)
		infoResult.name = line[0];

		std::istringstream valueContainer(line[2]);
		double rate = 0.0;
		valueContainer >> rate;
		infoResult.rate = rate * 10;

		infoResult.genres = split(line[4].c_str(), ',');

		valueContainer.clear();
		valueContainer.str(line[5]);
		valueContainer >> infoResult.year;

		valueContainer.clear();
		valueContainer.str(line[6]);
		valueContainer >> infoResult.runtime;

		if (line[line.size() - 1] != nullValue) {

			infoResult.summary = line[line.size() - 1];
		}

		if (line[11] != nullValue) {

			Cover cover;
			cover.setCoverPreview(image_host_addr + line[11]);
			std::string::size_type position = line[11].find('.', 0);

			if (position != std::string::npos) {

				cover.setCover(image_host_addr + line[11].substr(0, position) + ".3.jpg");
			}

			infoResult.cover.push_back(cover);
		}
	}
}
