/*
 * parserBase.hpp
 *
 *  Created on: 12-10-2013
 *      Author: miliardopiscrat
 */

#ifndef PARSERBASE_HPP_
#define PARSERBASE_HPP_

#include <istream>
#include <ostream>
#include <vector>
#include <string>

class IFilmWebFileHandle {

public:
	/* next pre-parsed words*/
	virtual bool getNextLine(std::vector<std::string>& splits) = 0;
	/* for store outside */
	virtual void getContent(std::ostream& out) const = 0;
	virtual ~IFilmWebFileHandle() {
	}

protected:

	void fillStringBuf(std::istream& in, std::string& buffer) const {

		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		buffer.resize(size);
		in.seekg(0);
		in.read(&buffer[0], size);
	}
};

template<class Handler, class Out>
class Parser {
public:
	virtual void parse(Handler& handler, Out& out) = 0;
	virtual ~Parser() {
	}
};

template<class H, class P>
class Handler: public H {
public:

	template<class O>
	void parse(O& out) {

		getParser<O>().parse(*this, out);
	}

protected:

	template<class O>
	Parser<H, O>& getParser() {

		return parser;
	}

	P parser;
};

#endif /* PARSERBASE_HPP_ */
