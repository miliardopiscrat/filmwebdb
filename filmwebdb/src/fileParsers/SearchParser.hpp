/*
 * SearchParser.h
 *
 *  Created on: 10-10-2013
 *      Author: miliardopiscrat
 */

#ifndef SEARCHPARSER_HPP_
#define SEARCHPARSER_HPP_

#include <vector>

#include "common.hpp"
#include "ParserBase.hpp"


class SearchParser: public Parser<IFilmWebFileHandle, std::vector<Element> >  {
public:
	SearchParser();
	virtual ~SearchParser();

	virtual void parse(IFilmWebFileHandle& handle, std::vector<Element>& searchList);

private:

};

#endif /* SEARCHPARSER_HPP_ */
