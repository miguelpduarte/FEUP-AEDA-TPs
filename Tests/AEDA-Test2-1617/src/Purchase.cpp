/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article* art = new Article(this->client, barCode);
	art->setPresent(present);
	art->setDeliverHome(deliverHome);

	return art;
}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
	//Checking if the last bag is full or if the bags list is empty
	if(bags.empty() || bags.back().size() == Purchase::BAG_SIZE){
		//If it is, insert a new bag at the end of the list (push_back)
		std::stack<Article*> l;
		l.push(article);
		bags.push_back(l);
		return;
	}

	//If it isn't simply insert into the last bag
	bags.back().push(article);
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> output;

	//& captures the necessary variables by reference, in this case is equivalent to &output
	for_each(bags.begin(), bags.end(), [&](stack<Article *> &s){
		//Must alter each bag (stack s) and insert the Articles that are presents in the output vector
		//The alteration to the stack is removing the Articles that are presents, aka keeping the others
		//For that the easiest is creating an auxiliar stack and pushing the non presents to there, then in the end pushing the stack into the original one
		stack<Article*> tempstack;
		Article* currentelem;

		while(!s.empty()){
			currentelem = s.top();
			//If the element is a present
			if(currentelem->getPresent()){
				output.push_back(currentelem);
			} else {
				tempstack.push(currentelem);
			}

			s.pop();
		}

		//Setting the current stack in bags to the modified stack
		//Direct push and not using swap since pushing the top of a stack into another successively inverts the stack
		while(!tempstack.empty()){
			//To ensure that the item to push is an rvalue, unnecessary basically
			//s.push(reinterpret_cast<Article *&&>(tempstack.top()));

			//Now using emplace, compiler does not complain at all
			s.emplace(tempstack.top());
			tempstack.pop();
		}
	});

	return output;
}

