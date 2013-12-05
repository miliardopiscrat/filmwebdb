/*
 * ParameterApiDef.hpp
 *
 *  Created on: 11-10-2013
 *      Author: miliardopiscrat
 */

#ifndef PARAMETERAPIDEF_HPP_
#define PARAMETERAPIDEF_HPP_

#include <string>

enum ParameterType
{
	VERSION = 0, APP_ID = 1, METHODS = 2, SIGNATURE = 3
};

enum MethodType
{
	GETFILMDESCRIPTION = 0, GETFILMINFOFULL = 1, GETFILMPERSONS = 2, GETFILMIMAGES = 3
};

enum PersonType
{
	DIRECTOR = 1, ACTOR = 6, PRODUCER = 7
};


class ParameterValue
{
public:
	virtual const std::string& getValue() const = 0;
	virtual ParameterType getType() const = 0;

	virtual ~ParameterValue(){};
};

template<ParameterType Type>
class SimpleParameterValue: public ParameterValue {
protected:

	std::string value;
	std::string property_value;
	const std::string& getName() const;

	SimpleParameterValue() {

	};

public:

	SimpleParameterValue(const std::string& paramterValue):
	value(getName() + "=" + paramterValue), property_value(paramterValue){

	};

	const std::string& getPropertyValue() const
	{
		return property_value;
	}


	virtual const std::string& getValue() const
	{
		return value;
	}

	virtual ParameterType getType() const
	{
		return Type;
	}

private:

	SimpleParameterValue& operator =(const SimpleParameterValue&);
};

template<MethodType type>
class MethodParamterValue: public SimpleParameterValue<METHODS>
{

};

template<>
class MethodParamterValue<GETFILMINFOFULL>: public SimpleParameterValue<METHODS>
{
public:
	MethodParamterValue(const std::string& id);
};

template<>
class MethodParamterValue<GETFILMPERSONS>: public SimpleParameterValue<METHODS>
{
public:
	MethodParamterValue(const std::string& id, PersonType pType, int startPage, int endPage);
};

template<>
class MethodParamterValue<GETFILMIMAGES>: public SimpleParameterValue<METHODS>
{
public:
	MethodParamterValue(const std::string& id, int startPage, int endPage);
};

template<>
class MethodParamterValue<GETFILMDESCRIPTION>: public SimpleParameterValue<METHODS>
{
public:
	MethodParamterValue(const std::string& id);
};


class signatureParameterValue: public SimpleParameterValue<SIGNATURE> {

	const SimpleParameterValue<APP_ID> appIdParam;
	const SimpleParameterValue<METHODS>& methodParam;
	const SimpleParameterValue<VERSION> versionParam;
public:

	signatureParameterValue(const SimpleParameterValue<APP_ID>& appIdParam,
			const SimpleParameterValue<VERSION>& versionParam, const SimpleParameterValue<METHODS>& methodParam);

};


#endif /* PARAMETERAPIDEF_HPP_ */
