/*
 * FilmWebSearchHandle.h
 *
 *  Created on: 10-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBSEARCHHANDLE_HPP_
#define FILMWEBSEARCHHANDLE_HPP_

#include <string>
#include <vector>
#include <ostream>
#include <istream>
#include "SearchParser.hpp"


class FilmWebSearchHandle: public Handler<IFilmWebFileHandle, SearchParser> {
public:
	FilmWebSearchHandle(std::istream& in);
	virtual ~FilmWebSearchHandle();

	virtual bool getNextLine(std::vector<std::string>& splits);

	virtual void getContent(std::ostream& out) const;

private:

	void parseLines(const std::string& content);

	std::vector<std::string> lines;
	std::vector<std::string>::const_iterator position;
};

#endif /* FILMWEBSEARCHHANDLE_HPP_ */
