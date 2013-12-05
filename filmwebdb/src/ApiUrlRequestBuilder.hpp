/*
 * ApiUrlRequestBuilder.hpp
 *
 *  Created on: 11-10-2013
 *      Author: miliardopiscrat
 */

#ifndef APIURLREQUESTBUILDER_HPP_
#define APIURLREQUESTBUILDER_HPP_

#include "ParameterApiDef.hpp"
#include <sstream>
#include <string>


template<MethodType T> struct typeIdTrace {};

class ApiUrl{

public:
	virtual const std::string& getUrl() const = 0;

	virtual ~ApiUrl(){};
};

/*
 * can copy and assign,
 * Works as builder and API URL-request container.
 */
class ApiUrlRequestBuilder: public ApiUrl {

public:
	template<MethodType type>
	ApiUrlRequestBuilder(const std::string& hostUrl, const std::string& id, const typeIdTrace<type>&);

	template<MethodType type>
	ApiUrlRequestBuilder(const std::string& hostUrl, const std::string& id, int startPage, int endPage, const typeIdTrace<type>&);

	ApiUrlRequestBuilder(const std::string& hostUrl, const std::string& id, PersonType pType, int startPage, int endPage);
	virtual ~ApiUrlRequestBuilder();

	virtual const std::string& getUrl() const
	{
		return hostUrl;
	};

	ApiUrlRequestBuilder& operator=(const ApiUrlRequestBuilder &);
	ApiUrlRequestBuilder(const ApiUrlRequestBuilder&);

private:
	std::string hostUrl;
};

#endif /* APIURLREQUESTBUILDER_HPP_ */
