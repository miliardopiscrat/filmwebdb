/*
 * FilmWebDescrParser.hpp
 *
 *  Created on: 13-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBDESCRPARSER_HPP_
#define FILMWEBDESCRPARSER_HPP_

#include "common.hpp"
#include "ParserBase.hpp"

class FilmWebDescrParser: public Parser<IFilmWebFileHandle, InfoResult > {
public:
	FilmWebDescrParser();
	virtual ~FilmWebDescrParser();

	virtual void parse(IFilmWebFileHandle& handle, InfoResult& result);
};

#endif /* FILMWEBDESCRPARSER_HPP_ */
