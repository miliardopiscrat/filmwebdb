/*
 * FilmWebImagesParser.hpp
 *
 *  Created on: 16-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBIMAGESPARSER_HPP_
#define FILMWEBIMAGESPARSER_HPP_
#include "common.hpp"
#include "ParserBase.hpp"


class FilmWebImagesParser: public Parser<IFilmWebFileHandle, InfoResult > {
public:
	FilmWebImagesParser();
	virtual ~FilmWebImagesParser();

	virtual void parse(IFilmWebFileHandle& handle, InfoResult& result);
};

#endif /* FILMWEBIMAGESPARSER_HPP_ */
