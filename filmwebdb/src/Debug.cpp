/*
 * Debug.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: ubuntu
 */

#include "Debug.hpp"

#if defined _DEBUG

#include <sstream>
#include <algorithm>
#include <iterator>

std::string debug(const InfoResult& result) {

	std::stringstream in;
	in << "InfoResult:\n" << std::endl;
	in << "\t\tid: " << result.filmweb_id << std::endl;
	in << "\t\trate: " << result.rate << std::endl;
	in << "\t\tname: " << result.name << std::endl;
	in << "\t\tdirector: " << result.director << std::endl;
	in << "\t\tvotes: " << result.votes << std::endl;
	in << "\t\toverview: " << result.overview << std::endl;
	in << "\t\tdescr: " << result.summary << std::endl;
	in << "\t\tgenres: ";

	std::copy(result.genres.begin(), result.genres.end(), std::ostream_iterator<std::string>(in, ", "));
	in << std::endl;

	in << "\t\tyear: " << result.year << std::endl;

	if(!result.cover.empty()) {
		in << "\t\tcover: " << result.cover[0].getCover() << ", size: " << result.cover.size() << std::endl;
	}

	if(!result.fanart.empty()) {
		for(std::vector<Fanart>::const_iterator it = result.fanart.begin(); it < result.fanart.end(); ++it)
		in << "\t\tfanart: " << it->getFanart() << std::endl;
	}

	in << "\t\tactors: ";
	std::copy(result.name_actor.begin(), result.name_actor.end(), std::ostream_iterator<std::string>(in, ", "));

	return in.str();
}


Trace &Trace::GetTrace() {

	static Trace trace;
	return trace;
}

Trace &Trace::operator <<(int value) {

	outFile << value;
	outFile.flush();
	return *this;
}

Trace &Trace::operator <<(std::string::size_type value){

	outFile << value;
	outFile.flush();
	return *this;
}

Trace &Trace::operator <<(char value) {

	outFile << value;
	outFile.flush();
	return *this;
}

Trace &Trace::operator <<(Trace &(*function)(Trace &trace)){
	return function(*this);
}

Trace &Trace::Endl(Trace &trace) {

	std::ofstream& outFile = Trace::GetTrace().outFile;
	outFile << '\n';
	outFile.flush();
	return trace;
}

Trace &Trace::operator <<(const std::string& texts) {

	outFile << texts;
	outFile.flush();
	return *this;
}

Trace &Trace::operator <<(const char* texts) {

	outFile << texts;
	outFile.flush();
	return *this;
}

Trace &Trace::operator <<(std::istream& input) {

	outFile << input;
	outFile.flush();
	return *this;
}

Trace &Trace::operator <<(const InfoResult& input) {

	outFile << debug(input);
	outFile.flush();
	return *this;
}

Trace &Trace::operator <<(const Element& input)
{
	outFile << "Element:\n"<< std::endl;
	outFile << "\t\ttitle: " << input.title << std::endl;
	outFile << "\t\tpower: " << input.power << std::endl;
	outFile << "\t\tKeywordsDiff: " << input.KeywordsDiff << std::endl;
	outFile << "\t\tyear: " << input.year << std::endl;
	outFile.flush();
	return *this;
}


Trace &Trace::operator <<(const std::vector<Element>& input)
{
	for(std::vector<Element>::const_iterator itElement = input.begin(); itElement != input.end(); ++itElement)
	{
		*this << *itElement;
	}
	return *this;
}

Trace &Trace::operator <<(const std::vector<std::string>& input)
{
	for(std::vector<std::string>::const_iterator itElement = input.begin(); itElement != input.end(); ++itElement)
	{
		*this << *itElement << Endl;
	}
	return *this;
}

Trace::Trace() {
	initialize();
}

void Trace::initialize() {

	outFile.open("/tmp/webfilm.debug", std::ios::out | std::fstream::app);
}

Trace::~Trace() {
	outFile.close();
}



#endif
