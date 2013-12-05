/*
 * ParameterApiDef.cpp
 *
 *  Created on: 11-10-2013
 *      Author: miliardopiscrat
 */

#include "ParameterApiDef.hpp"
#include "Debug.hpp"
#include <md5.hpp>
#include <sstream>
#include <curl/curl.h>

namespace {

const char * signature_key = "qjcGhW2JnvGT9dfCt3uT_jozR3s";
const std::string paramterNameTable[] = { "version", "appId", "methods", "signature" };
const std::string methodNameTable[] = { "getFilmDescription", "getFilmInfoFull", "getFilmPersons", "getFilmImages" };

}

template<ParameterType Type>
const std::string& SimpleParameterValue<Type>::getName() const {
	return paramterNameTable[Type];
}

template const std::string& SimpleParameterValue<VERSION>::getName() const;
template const std::string& SimpleParameterValue<APP_ID>::getName() const;


MethodParamterValue<GETFILMINFOFULL>::MethodParamterValue(const std::string& id) {

	std::stringstream ss;
	ss << methodNameTable[GETFILMINFOFULL] << " [" << id << "]\\n";
	this->property_value = ss.str();
	ss.clear();
	this->value = getName() + "=" + curl_escape(this->property_value.c_str(), this->property_value.length());
}

MethodParamterValue<GETFILMPERSONS>::MethodParamterValue(const std::string& id, PersonType pType, int startPage, int endPage) {

	std::stringstream ss;
	ss << methodNameTable[GETFILMPERSONS] << " [" << id << "," << pType << "," << 50 * startPage << "," << 50 * endPage << "]\\n";
	this->property_value = ss.str();
	this->value = getName() + "=" + curl_escape(this->property_value.c_str(), this->property_value.length());
}


MethodParamterValue<GETFILMIMAGES>::MethodParamterValue(const std::string& id, int startPage, int endPage) {

	std::stringstream ss;
	ss << methodNameTable[GETFILMIMAGES] << " [" << id << "," << 100 * startPage << "," << 100 * endPage << "]\\n";
	this->property_value = ss.str();
	this->value = getName() + "=" + curl_escape(this->property_value.c_str(), this->property_value.length());
}


MethodParamterValue<GETFILMDESCRIPTION>::MethodParamterValue(const std::string& id) {

	std::stringstream ss;
	ss << methodNameTable[GETFILMDESCRIPTION] << " [" << id << "]\\n";
	this->property_value = ss.str();
	this->value = getName() + "=" + curl_escape(this->property_value.c_str(), this->property_value.length());
}

signatureParameterValue::signatureParameterValue(const SimpleParameterValue<APP_ID>& appIdParam,
		const SimpleParameterValue<VERSION>& _versionParam, const SimpleParameterValue<METHODS>& methodParam) :
		SimpleParameterValue<SIGNATURE>::SimpleParameterValue(_versionParam.getPropertyValue()), appIdParam(appIdParam), methodParam(methodParam), versionParam(
				_versionParam) {

	this->value += "," + md5(methodParam.getPropertyValue() + appIdParam.getPropertyValue() + signature_key);
}



