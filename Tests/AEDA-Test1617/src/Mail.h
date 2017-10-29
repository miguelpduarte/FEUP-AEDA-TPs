/*
 * Mail.h
 */

#ifndef SRC_MAIL_H_
#define SRC_MAIL_H_

#include <string>
#include <vector>
#include <set>

using namespace std;


class Mail {
	string sender;
	string receiver;
	string zipCode;
public:
	Mail(string send, string rec, string zcode);
	virtual ~Mail();
	string getZipCode() const;
	virtual unsigned int getPrice() const = 0;
};


class RegularMail: public Mail {
	unsigned int weight;
public:
	RegularMail(string send, string rec, string code, unsigned int w);
	unsigned int getPrice() const;
};


class GreenMail: public Mail {
	string type;  // "envelope", "bag", "box"
public:
	GreenMail(string send, string rec, string code, string t);
	unsigned int getPrice() const;
};

template <class T>
unsigned int numberDifferent(const vector<T> &v1){
	set<T> output;

	for(auto const &elem: v1) {
		output.insert(elem);
	}

	return output.size();
}

#endif /* SRC_MAIL_H_ */
