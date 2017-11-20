/*
 * pizzeria.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: RRossetti
 */

#include <algorithm>
#include "pizzeria.h"

/*
 * CLASS MENU
 */

int Menu::nextID = 0;

Menu::Menu() {
	id = 0;
	name = "";
	likes = 0;
}

Menu::Menu(int id1, string n1, vector<string> is1, int lks1) {
	id = id1;
	name = n1;
	ingredients = is1;
	likes = lks1;
}

int Menu::getId() const { return id; }
void Menu::setId(int id1) { id = id1; }
string Menu::getName() const { return name; }
void Menu::setName(string n1) { name = n1; }
vector<string> Menu::getIngredients() const { return ingredients; }

Menu::Menu(string n1, vector<string> is1) : name(n1), ingredients(is1), id(++nextID), likes(0){}

void Menu::setIngredients(const vector<string> &is1){
	if(!isSet(is1)){
		throw ExceptionIngredientsRepeated();
	}

	this->ingredients = is1;
}

void Menu::removeIngredient(const string &ingredient){
	auto it = std::find(ingredients.begin(), ingredients.end(), ingredient);
	if(it != ingredients.end()){
		ingredients.erase(it);
	} else {
		throw ExceptionIngredientNotPresent(ingredient);
	}
}


/*
 * CLASS CUSTOMER
 */

Customer::Customer(int nif1, string n1) {
	nif = nif1;
	name = n1;
}

int Customer::getNIF() const {
	return nif;
}

string Customer::getName() const {
	return name;
}


/*
 * CLASS PIZZERIA
 */

Pizzeria::Pizzeria() { }

Pizzeria::Pizzeria(vector<Menu> ms1) {
	menus = ms1;
}

vector<Menu> Pizzeria::getMenus() const { return menus; }

vector<Customer*> Pizzeria::getCustomers() const { return customers; }

int Pizzeria::addCustomer(Customer* c1) {
	customers.push_back(c1);
	return customers.size();
}

vector<Menu> Pizzeria::optionsWithinIngredientLimits(int i1, int i2) const{

	if(i1<1 || i2<1 || i1 > i2){
		throw ExceptionInvalidIngredientLimits();
	}

	vector<Menu> output;

	copy_if(menus.begin(), menus.end(), std::back_inserter(output), [i1, i2](const Menu &m){
		//To avoid getting the vector twice (I think the compiler couldn't optimize that)
		//(The real solution would be to have a Menu::getNumIngredients but oh well
		unsigned int ningredients = m.getIngredients().size();
		//if the number of ingredients is between i1 and i2 then copy
		return ningredients <= i2 && i1 <= ningredients;
	});

	return output;
}

vector<Menu> Pizzeria::popularityRank() const{
	vector<Menu> output(menus);

	sort(output.begin(), output.end(), [](const Menu &m1, const Menu &m2){
		if(m1.getLikes() == m2.getLikes()){
			return m1.getName() < m2.getName();
		} else {
			return m1.getLikes() > m2.getLikes();
		}
	});

	return output;
}

Customer *Pizzeria::chefCustomer(){

	//Just in case there are no customers
	if(customers.empty())
		return nullptr;

	//Starting at the first customer to not dereferecne invalid address
	Customer * output = customers[0];

	for_each(customers.begin(), customers.end(), [&output, this](Customer * c){
		if(getCustomerCreativeness(output) < getCustomerCreativeness(c)){
			output = c;
		}
	});

	return output;

}

double Pizzeria::getCustomerCreativeness(Customer * c) const{
	unsigned int nlikes = 0, nmenus = 0;

	for_each(menus.begin(), menus.end(), [&nlikes, &nmenus, c](const Menu &m){
		if(m.getName() == c->getName()){
			nlikes += m.getLikes();
			++nmenus;
		}
	});

	return (double) nlikes/nmenus;
}

Menu & Pizzeria::removeIngredient(vector<string> is1, string i1){
	auto it = find_if(menus.begin(), menus.end(), [&](const Menu &m){
		return m.getIngredients() == is1;
	});

	if(it == menus.end()){
		throw ExceptionInexistentMenu();
	}

	//Menu successfully found, deleting ingredient, but rethrowing any exception it throws
	try {
		it->removeIngredient(i1);
	} catch(...){
		//Rethrowing thrown exceptions
		throw;
	}

	//Returning altered menu through its iterator
	return *it;
}




