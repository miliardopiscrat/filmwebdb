/*
 * FilmWebSearchHandle.cpp
 *
 *  Created on: 10-10-2013
 *      Author: miliardopiscrat
 */

#include "FilmWebSearchHandle.hpp"
#include <iterator>

#include "Debug.hpp"
#include "common.hpp"

static const std::string lineDelimiter = "\\a";
static const std::string cellDelimiter = "\\c";

FilmWebSearchHandle::FilmWebSearchHandle(std::istream& in) {

	std::string buffer;
	fillStringBuf(in, buffer);
	TRACE(buffer)
	if (!buffer.empty()) {

		parseLines(buffer);
	}

	position = lines.begin();
}

void FilmWebSearchHandle::parseLines(const std::string& content) {

	std::string::size_type start = 0, end = 0;

	if (content.find(lineDelimiter, start) == std::string::npos) {

		lines.push_back(content.substr(start, content.length()));
	} else
		while ((end = content.find(lineDelimiter, start)) != std::string::npos) {

			if (start != end) {

				std::string line = content.substr(start, end - start);
				lines.push_back(line);
				TRACE(line)
			}

			start = end + lineDelimiter.length();
		}
}

bool FilmWebSearchHandle::getNextLine(std::vector<std::string>& splits) {

	if (position == lines.end()) {

		return false;
	}

	std::string line = *position++;

	if (line.empty() || (line[0] != 's' && line[0] != 'f')) {

		return true; // skip parse
	}

	TRACE("line to split: " << line)

	std::string::size_type start = 0, end = 0;
	while ((end = line.find(cellDelimiter, start)) != std::string::npos) {

		if (end != 0) {

			std::string cell = line.substr(start, end - start);
			splits.push_back(cell);
		}
		start = end + cellDelimiter.length();
	}

	return true;
}

void FilmWebSearchHandle::getContent(std::ostream& out) const {
	std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(out, "\n"));
}

FilmWebSearchHandle::~FilmWebSearchHandle() {

}

