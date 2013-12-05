/*
 * FilmWebImagesParser.cpp
 *
 *  Created on: 16-10-2013
 *      Author: miliardopiscrat
 */

#include "FilmWebImagesParser.hpp"
#include "Debug.hpp"

FilmWebImagesParser::FilmWebImagesParser() {
	// TODO Auto-generated constructor stub

}

FilmWebImagesParser::~FilmWebImagesParser() {
	// TODO Auto-generated destructor stub
}

void FilmWebImagesParser::parse(IFilmWebFileHandle& handle, InfoResult& result) {

	std::vector<std::string> line;
	while (handle.getNextLine(line) && result.fanart.size() < JB_SCPR_MAX_IMAGE) {

		if(!line.empty() && !line.front().empty())
		{
			Fanart fanart;
			std::string photo_icon_path = "http://1.fwcdn.pl/ph" + line.front();
			fanart.setFanart(photo_icon_path);
			fanart.setFanartPreview(photo_icon_path);

			std::string::size_type nameEnd = line.front().find(".", 0);

			if(nameEnd != std::string::npos)
			{
				//photo_icon_path = "http://1.fwcdn.pl/ph" + line.front().substr(0, nameEnd + 1) + "2.jpg";

				photo_icon_path = "http://1.fwcdn.pl/ph" + line.front().substr(0, nameEnd + 1) + "1.jpg";
				fanart.setFanart(photo_icon_path);
				fanart.setFanartPreview(photo_icon_path);
			}
			TRACE(photo_icon_path);

			result.fanart.push_back(fanart);
		}
		line.clear();
	}
}
