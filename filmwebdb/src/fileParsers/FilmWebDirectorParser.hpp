/*
 * FilmWebDirectorParser.hpp
 *
 *  Created on: 13-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBDIRECTORPARSER_HPP_
#define FILMWEBDIRECTORPARSER_HPP_

#include "common.hpp"
#include "ParserBase.hpp"


class FilmWebDirectorParser: public Parser<IFilmWebFileHandle, InfoResult > {
public:
	FilmWebDirectorParser();
	virtual ~FilmWebDirectorParser();

	virtual void parse(IFilmWebFileHandle& handle, InfoResult& result);
};

#endif /* FILMWEBDIRECTORPARSER_HPP_ */
