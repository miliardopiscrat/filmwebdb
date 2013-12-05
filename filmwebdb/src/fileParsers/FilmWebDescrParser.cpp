/*
 * FilmWebDescrParser.cpp
 *
 *  Created on: 13-10-2013
 *      Author: miliardopiscrat
 */

#include "FilmWebDescrParser.hpp"
#include "Debug.hpp"


#include <string>

static const std::string nullValue = "null";

void convert_unicode_QUOTATION_marks(std::string& content)
{
	std::string::size_type start = 0;
	while((start = content.find("\\u", start)) != std::string::npos)
	{
		std::string begin = content.substr(0, start - 1);
		content = begin + "'" + content.substr(start + 6, content.length() - start + 6);
	}
}

FilmWebDescrParser::FilmWebDescrParser() {

}

FilmWebDescrParser::~FilmWebDescrParser() {

}

void FilmWebDescrParser::parse(IFilmWebFileHandle& handle, InfoResult& result) {

	std::vector<std::string> line;

	if (handle.getNextLine(line) && !line.empty() && line[0] != nullValue) {

		convert_unicode_QUOTATION_marks(line[0]);
		result.overview = line[0];
	} else {

		result.overview = result.summary;
	}
}
