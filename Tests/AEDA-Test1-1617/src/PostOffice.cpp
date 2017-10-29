/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){
	for(unsigned int i = 0; i < postmen.size(); ++i){
		if(postmen[i].getName() == name){
			//If the postman with the given name was found, save the mail to be able to return it later,
			//free the memory and delete from the vector
			auto lostMail = postmen[i].getMail();
			postmen.erase(postmen.begin() + i);
			return lostMail;
		}
	}

	return vector<Mail *>();
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance){

	balance = 0;

	vector<Mail *> mailForOtherPOs;

	for(auto const &mail : mailToSend){
		//Adding to the balance
		balance += mail->getPrice();

		if(mail->getZipCode() >= firstZipCode && mail->getZipCode() <= lastZipCode){
			addMailToDeliver(mail);
		}else{
			mailForOtherPOs.push_back(mail);
		}
	}

	//Clearing the now sorted vector
	mailToSend.clear();

	//Returning the mail for other Post Offices
	return mailForOtherPOs;
}

Postman PostOffice::addMailToPostman(Mail *m, string name){
	for(auto &postman : postmen) {
		if(postman.getName() == name){
			postman.addMail(m);
			return postman;
		}
	}

	throw NoPostmanException(name);
}

NoPostmanException::NoPostmanException(string name) : name(name){}

string NoPostmanException::getName() const{
	return name;
}
