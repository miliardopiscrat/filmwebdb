/*
 * filmweb.cpp
 *
 *  Created on: 10-10-2013
 *      Author: miliardopiscrat
 */

#include "common.hpp"
#include "Debug.hpp"
#include "ArgumentsParser.hpp"

#include "fileParsers/FilmWebSearchHandle.hpp"

#include "ApiUrlRequestBuilder.hpp"
#include "FileDownloader.hpp"

#include "FilmWebApi.hpp"

#include <curl/curl.h>

namespace {

const std::string query_title = "http://www.filmweb.pl/search/live?q=";
const std::string api_url = "https://ssl.filmweb.pl/api?";

const char* query_file = "/tmp/query.data";

}

bool download_search_Result(const std::string& queryUrl, const std::string& keyword) {

	std::ofstream outFile;
	outFile.open(query_file, std::ios::out | std::ios::binary);

	if (!outFile.good()) {

		outFile.close();
		return false;
	}

	FileDownloader downloader(10);
	std::string query(queryUrl);
	std::string esc_keyword(curl_escape(keyword.c_str(), keyword.length()));

	downloader.downloadFile(query + esc_keyword, outFile);
	outFile.close();
	return true;
}

bool get_Elements_from_SearchFile(std::vector<Element>& elements) {

	std::ifstream in;
	in.open(query_file, std::ios::in | std::ios::binary);

	if (!in.good()) {

		in.close();
		return false;
	}

	FilmWebSearchHandle handle(in);
	in.close();
	handle.parse(elements);
	return true;
}

bool gen_search_result(const char* outputFile, const std::vector<Element>& elements) {

	std::ofstream outFile;
	outFile.open(outputFile, std::ios::out | std::ios::binary);

	if (!outFile.good()) {
		outFile.close();
		return false;
	}

	GenSearchResult(elements, outFile);
	outFile.close();
	return true;
}

bool get_info_result(const std::string& keyword, InfoResult& result) {

	FileDownloader downloader(20);

	std::stringstream fullInfoBuff;
	std::stringstream descrInfoFileBuff;
	std::stringstream imageInfoFileBuff;
	std::stringstream directorInfoFileBuff;
	std::stringstream actorsInfoFileBuff;

	ApiUrlRequestBuilder builder(api_url, keyword, (typeIdTrace<GETFILMINFOFULL>()));
	if (!downloader.downloadFile(builder, fullInfoBuff)) {

		return false;
	}

	builder = ApiUrlRequestBuilder(api_url, keyword, (typeIdTrace<GETFILMDESCRIPTION>()));
	if (!downloader.downloadFile(builder, descrInfoFileBuff)) {

		return false;
	}

	builder = ApiUrlRequestBuilder(api_url, keyword, 0, 2, (typeIdTrace<GETFILMIMAGES>()));
	if (!downloader.downloadFile(builder, imageInfoFileBuff)) {

		return false;
	}

	builder = ApiUrlRequestBuilder(api_url, keyword, DIRECTOR, 0, 1);
	if (!downloader.downloadFile(builder, directorInfoFileBuff)) {

		return false;
	}

	builder = ApiUrlRequestBuilder(api_url, keyword, ACTOR, 0, 1);
	if (!downloader.downloadFile(builder, actorsInfoFileBuff)) {

		return false;
	}

	FilmWebInfoHandle handleInfo(fullInfoBuff);
	handleInfo.parse(result);

	FilmWebDescrHandle handleDescr(descrInfoFileBuff);
	handleDescr.parse(result);

	FilmWebActorHandle handleActors(actorsInfoFileBuff);
	handleActors.parse(result);

	FilmWebDirectorHandle handleDirector(directorInfoFileBuff);
	handleDirector.parse(result);

	FilmWebImagesHandle handleImages(imageInfoFileBuff);
	handleImages.parse(result);

	return true;
}


int main(int argc, char ** argv) {

	TRACE("start filmweb!!")

	Arguments arguments(argc, argv);

	TRACE("output: " << arguments.getOutput() << ", isSearchOpt: " << arguments.isSearchOpt() << ", keyword: " << arguments.getKeyword())

	if (arguments.getOutput().empty() || arguments.getKeyword().empty()) {

		return -1;
	}

	if (arguments.isSearchOpt()) {

		std::vector<Element> elements;

		if (download_search_Result(query_title, arguments.getKeyword())) {

			get_Elements_from_SearchFile(elements);
		}

		TRACE(elements)

		if (!gen_search_result(arguments.getOutput().c_str(), elements)) {

			return -1;
		}
	} else {

		InfoResult result = { };

		if (!get_info_result(arguments.getKeyword(), result)) {

			return -1;
		}

		std::istringstream idContainer(arguments.getKeyword());
		idContainer >> result.filmweb_id;

		TRACE(result)

		std::ofstream outFile;

		outFile.open(arguments.getOutput().c_str(), std::ios::out | std::ios::binary);
		if (!outFile.good()) {
			outFile.close();
			return -1;
		}

		GenInfoResult(result, outFile);
		outFile.close();
	}

	TRACE("THE END");
	return 0;
}
