/*
 * FilmWebActorsParser.hpp
 *
 *  Created on: 13-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBACTORSPARSER_HPP_
#define FILMWEBACTORSPARSER_HPP_

#include "common.hpp"
#include "ParserBase.hpp"


class FilmWebActorsParser: public Parser<IFilmWebFileHandle, InfoResult > {
public:
	FilmWebActorsParser();
	virtual ~FilmWebActorsParser();

	virtual void parse(IFilmWebFileHandle& handle, InfoResult& result);
};

#endif /* FILMWEBACTORSPARSER_HPP_ */
