/*
 * pizzaria.h
 *
 *  Created on: Oct 21, 2015
 *      Author: RRossetti
 */

#ifndef PIZZERIA_H_
#define PIZZERIA_H_

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <set>

#include "sequentialSearch.h"
#include "insertionSort.h"

using namespace std;

class Menu {
	static int nextID;
	int id;
	string name;
	int likes;
	vector<string> ingredients;
public:
	Menu();
	Menu(string n1, vector<string> is1);
	Menu(int id1, string n1, vector<string> is1, int lks1);
	int getId() const;
	void setId(int id1);
	string getName() const;
	void setName(string n1);
	vector<string> getIngredients() const;
	void addLike() { ++likes; }
	int getLikes() const { return likes; }

	void setIngredients(const vector<string> &is1);

	void removeIngredient(const string &ingredient);

	class ExceptionIngredientsRepeated{
		//ExceptionIngredientsRepeated(){}
	};

	class ExceptionIngredientNotPresent{
		string ingname;
	public:
		string getIngredient() const {return ingname;}
		ExceptionIngredientNotPresent(string iname) : ingname(std::move(iname)){}
	};
};

class Customer {
	int nif;
	string name;
public:
	Customer(int nif1, string n1);
	int getNIF() const;
	string getName() const;
};

class Pizzeria {
	vector<Menu> menus;
	vector<Customer*> customers;
public:
	Pizzeria();
	Pizzeria(vector<Menu> ms1);
	vector<Menu> getMenus() const;
	vector<Customer*> getCustomers() const;
	int addCustomer(Customer* c1);

	vector<Menu> optionsWithinIngredientLimits(int i1, int i2) const;
	vector<Menu> popularityRank() const;
	Customer* chefCustomer();
	double getCustomerCreativeness(Customer * c) const;
	Menu& removeIngredient(vector<string> is1, string i1);

	class ExceptionInvalidIngredientLimits{
		//Once again no constructor needed so omission defines the default lol
	};

	class ExceptionInexistentMenu{
		//
	};
};

template <class Comparable>
bool isSet(const vector<Comparable> &v1){
	set<Comparable> temp;

	for(auto const &elem : v1){
		temp.insert(elem);
	}

	return temp.size() == v1.size();
}


#endif /* PIZZERIA_H_ */
