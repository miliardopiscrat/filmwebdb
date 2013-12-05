/*
 * FilmWebApiHandle.hpp
 *
 *  Created on: 12-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILMWEBAPIHANDLE_HPP_
#define FILMWEBAPIHANDLE_HPP_

#include "ParserBase.hpp"
#include "Debug.hpp"

template<class P>
class FilmWebApiHandle: public Handler<IFilmWebFileHandle, P> {

public:
	FilmWebApiHandle(std::istream& in);
	virtual ~FilmWebApiHandle();

	virtual bool getNextLine(std::vector<std::string>& splits);
	virtual void getContent(std::ostream& out) const;

private:
	void parseLines(const std::string& content);

	std::vector<std::string> lines;
	std::vector<std::string>::const_iterator position;
};

// ===============================================

template<class P>
FilmWebApiHandle<P>::FilmWebApiHandle(std::istream& in) {

	std::string buffer;
	this->IFilmWebFileHandle::fillStringBuf(in, buffer);
	parseLines(buffer);

	position = lines.begin();
}

template<class P>
FilmWebApiHandle<P>::~FilmWebApiHandle() {

}

template<class P>
bool FilmWebApiHandle<P>::getNextLine(std::vector<std::string>& splits) {

	if (position == lines.end()) {

		return false;
	}

	std::string line = *position++;

	if (line.empty()) {

		return false;
	}

	TRACE("line to split: " << line)

	char delimiter = line[0] == '"' ? '"' : ',';

	std::string::size_type start = delimiter == ',' ? 0 : 1;
	std::string::size_type end = 0;
	std::string::size_type subStrStart = start;

	while ((end = line.find(delimiter, start)) != std::string::npos) {

		bool foundEnd = true;
		if (delimiter == '"') {
			foundEnd = line[end - 1] != '\\' && (line[end + 1] == ',' || line[end + 1] == '\0');
		}

		if (foundEnd) {
			std::string sub = line.substr(subStrStart, end - subStrStart);
			splits.push_back(sub);

			subStrStart = end + (delimiter == '"' ? 3 : 2);
			delimiter = line[subStrStart - 1] == '"' ? '"' : ',';
			subStrStart -= delimiter == ',' ? 1 : 0;
			end = subStrStart;
		}

		start = end + 1;
	}

	return !splits.empty();
}

template<class P>
void FilmWebApiHandle<P>::getContent(std::ostream& out) const {
}

template<class P>
void FilmWebApiHandle<P>::parseLines(const std::string& content) {

	TRACE(content)
	static const std::string query_ok_result = "ok\n";

	std::string::size_type begin = content.find(query_ok_result, 0) + query_ok_result.size() + (content[4] == '[' ? 1 : 0);

	std::string::size_type cursor = begin - 1;

	int line_mark_counter = 100;

	while (++cursor < content.size()) {
		if (content[cursor] == '[') {

			line_mark_counter--;
			continue;
		} else if (content[cursor] == ']') {

			line_mark_counter++;
		}

		if (line_mark_counter == 100) {

			std::string sub = content.substr(begin + 1, cursor - begin - 1);
			TRACE(sub)
			lines.push_back(sub);

			if (content[++cursor] != ',')
				break;

			begin = cursor + 1;
		}
	}
}

#endif /* FILMWEBAPIHANDLE_HPP_ */
