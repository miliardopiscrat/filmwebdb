/*
 * FilmWebInfoParser.hpp
 *
 *  Created on: 12-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBINFOPARSER_HPP_
#define FILMWEBINFOPARSER_HPP_


#include "common.hpp"
#include "ParserBase.hpp"

class FilmWebInfoParser: public Parser<IFilmWebFileHandle, InfoResult >  {
public:
	FilmWebInfoParser();
	virtual ~FilmWebInfoParser();

	virtual void parse(IFilmWebFileHandle& handle, InfoResult& result);
};

#endif /* FILMWEBINFOPARSER_HPP_ */
