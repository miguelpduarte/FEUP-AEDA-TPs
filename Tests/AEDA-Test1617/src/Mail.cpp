/*
 * Mail.cpp
 */

#include "Mail.h"

Mail::Mail(string send, string rec, string zcode):
			sender(send),receiver(rec), zipCode(zcode)
{ }

Mail::~Mail()
{ }

string Mail::getZipCode() const {
	return zipCode;
}

RegularMail::RegularMail(string send, string rec, string zcode, unsigned int w):
			Mail(send, rec, zcode), weight(w)
{ }

unsigned int RegularMail::getPrice() const{
	if(weight <= 20)
		return 50;
	if(weight <= 100)
		return 75;
	return weight <= 500 ? 140 : 325;
}

GreenMail::GreenMail(string send, string rec, string zcode, string t):
			Mail(send, rec, zcode), type(t)
{ }

unsigned int GreenMail::getPrice() const{
	if(type == "envelope")
		return 80;
	if(type == "bag")
		return 200;
	if(type == "box")
		return 240;
}







