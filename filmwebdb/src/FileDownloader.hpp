/*
 * FileDownloader.hpp
 *
 *  Created on: 11-10-2013
 *      Author: miliardopiscrat
 */

#ifndef FILEDOWNLOADER_HPP_
#define FILEDOWNLOADER_HPP_

#include "ApiUrlRequestBuilder.hpp"

#include <iostream>
#include <curl/curl.h>

class FileDownloader {
public:
	FileDownloader(unsigned int timeout);

	bool downloadFile(const ApiUrl& url, std::ostream& out);
	bool downloadFile(const std::string& url, std::ostream& out);
	virtual ~FileDownloader();

private:
	bool setParameters(const std::string& url, CURL* const curl, std::ostream& ostream) const;
	static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);

	const unsigned int _timeout;
};

#endif /* FILEDOWNLOADER_HPP_ */
