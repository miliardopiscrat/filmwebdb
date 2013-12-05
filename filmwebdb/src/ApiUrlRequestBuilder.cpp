/*
 * ApiUrlRequestBuilder.cpp
 *
 *  Created on: 11-10-2013
 *      Author: miliardopiscrat
 */

#include "ApiUrlRequestBuilder.hpp"

#include "Debug.hpp"
#include <sstream>

template<MethodType type>
ApiUrlRequestBuilder::ApiUrlRequestBuilder(const std::string& hostUrl, const std::string& id, const typeIdTrace<type>&) :
		hostUrl(hostUrl) {

	static const SimpleParameterValue<VERSION> version("1.0");
	static const SimpleParameterValue<APP_ID> appId("android");
	MethodParamterValue<type> method(id);
	signatureParameterValue ssig(appId, version, method);

	std::stringstream ss;
	ss << version.getValue() << "&" << appId.getValue() << "&" << method.getValue() << "&" << ssig.getValue();

	this->hostUrl += ss.str();
	TRACE(this->hostUrl)
}

template<MethodType type>
ApiUrlRequestBuilder::ApiUrlRequestBuilder(const std::string& hostUrl, const std::string& id, int startPage, int endPage, const typeIdTrace<type>&)
: hostUrl(hostUrl)
{
	static const SimpleParameterValue<VERSION> version("1.0");
	static const SimpleParameterValue<APP_ID> appId("android");
	MethodParamterValue<type> method(id, 0, 1);
	signatureParameterValue ssig(appId, version, method);
	std::stringstream ss;
	ss << version.getValue() << "&" << appId.getValue() << "&" << method.getValue() << "&" << ssig.getValue();

	this->hostUrl += ss.str();
	TRACE(this->hostUrl)
}

ApiUrlRequestBuilder::ApiUrlRequestBuilder(const std::string& hostUrl, const std::string& id, PersonType pType, int startPage, int endPage) :
		hostUrl(hostUrl) {

	static const SimpleParameterValue<VERSION> version("1.0");
	static const SimpleParameterValue<APP_ID> appId("android");
	MethodParamterValue<GETFILMPERSONS> method(id, pType, startPage, endPage);
	signatureParameterValue ssig(appId, version, method);

	std::stringstream ss;
	ss << version.getValue() << "&" << appId.getValue() << "&" << method.getValue() << "&" << ssig.getValue();

	this->hostUrl += ss.str();
	TRACE(this->hostUrl);
}

ApiUrlRequestBuilder::~ApiUrlRequestBuilder() {

}

ApiUrlRequestBuilder& ApiUrlRequestBuilder::operator=(const ApiUrlRequestBuilder &otherBuilder)
{
	hostUrl = otherBuilder.hostUrl;
	return *this;
}

ApiUrlRequestBuilder::ApiUrlRequestBuilder(const ApiUrlRequestBuilder& otherBuilder) {

	hostUrl = otherBuilder.hostUrl;
}

// explicit inst. of template

template<MethodType type> ApiUrlRequestBuilder createBuilder(const std::string& hostUrl, const std::string& id) {

	return ApiUrlRequestBuilder(hostUrl, id, (typeIdTrace<type>()));
}

template<MethodType type> ApiUrlRequestBuilder createBuilder(const std::string& hostUrl, const std::string& id, int start, int end) {

	return ApiUrlRequestBuilder(hostUrl, id, start, end, (typeIdTrace<type>()));
}

template ApiUrlRequestBuilder createBuilder<GETFILMDESCRIPTION>(const std::string& hostUrl, const std::string& id);
template ApiUrlRequestBuilder createBuilder<GETFILMINFOFULL>(const std::string& hostUrl, const std::string& id);

template ApiUrlRequestBuilder createBuilder<GETFILMIMAGES>(const std::string& hostUrl, const std::string& id, int, int);

