/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int Postman::nextID = 1;

Postman::Postman(): id(0) {}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

Postman::Postman(string name) : id(nextID), name(name){
	++nextID;
}

bool Postman::operator<(const Postman &p){
	vector<string> zipcodeMail1, zipcodeMail2;

	//Getting the mail zipcodes for each postman
	for(auto const &mail : this->getMail()){
		zipcodeMail1.push_back(mail->getZipCode());
	}

	for(auto const &mail : p.getMail()){
		zipcodeMail2.push_back(mail->getZipCode());
	}

	//Comparing the number of unique zipcodes in each postman's mail
	return numberDifferent(zipcodeMail1) < numberDifferent(zipcodeMail2);
}




