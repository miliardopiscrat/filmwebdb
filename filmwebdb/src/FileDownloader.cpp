/*
 * FileDownloader.cpp
 *
 *  Created on: 11-10-2013
 *      Author: miliardopiscrat
 */

#include "FileDownloader.hpp"
#include "Debug.hpp"
#include <curl/curl.h>


FileDownloader::FileDownloader(unsigned int timeout) :_timeout(timeout) {

}

FileDownloader::~FileDownloader() {

}

bool FileDownloader::downloadFile(const std::string& url, std::ostream& out)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* const curl = curl_easy_init();

	if(curl && setParameters(url, curl, out))
	{
		code = curl_easy_perform(curl);
	}

	if(code != CURLE_OK)
		TRACE("download failed!")

	curl_easy_cleanup(curl);

	return code == CURLE_OK;
}


bool FileDownloader::downloadFile(const ApiUrl& url, std::ostream& out)
{
	return this->downloadFile(url.getUrl(), out);
}


bool FileDownloader::setParameters(const std::string& url, CURL* const curl, std::ostream& ostream) const {

	bool isSSLconnection = url.substr(0, 5) == "https";
	TRACE(url)
		return CURLE_OK == curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_FILE, &ostream)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_TIMEOUT, _timeout)
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_URL, url.c_str())
		&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_ENCODING, "")
		&& (!isSSLconnection || (CURLE_OK == curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L)
    	&& CURLE_OK == curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L)));
}

size_t FileDownloader::data_write(void* buf, size_t size, size_t nmemb, void* userp) {

	if (userp) {

		const std::streamsize len = size * nmemb;
		if (static_cast<std::ostream*>(userp)->write(static_cast<const char*>(buf), len)) {

			return len;
		}
	}
	return 0;
}


