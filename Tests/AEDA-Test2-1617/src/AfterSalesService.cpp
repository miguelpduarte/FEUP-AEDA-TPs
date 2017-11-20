/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {
	vector<Article*> output;

	//Can't use auto if I want to not re create the variable :(
	vector<Article*>::iterator it;

	while(true) {
		it = find_if(presentsTable.begin(), presentsTable.end(), [=](Article * art){
			return art->getClient() == client;
		});

		if(it != presentsTable.end()){
			output.push_back(*it);
			presentsTable.erase(it);
		} else {
			break;
		}
	}

	return output;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
void AfterSalesService::sortArticles() {
	//Defining the comparison function
	auto compFunc = [](Article * a1, Article * a2){
		//Checking if one of the presents is to deliver home and the other not
		if(a1->getDeliverHome() != a2->getDeliverHome()){
			//If so, instead of checking separately for each case we can just return the negation of a1's deliverHome, or a2's without negation
			return !a1->getDeliverHome();
		}

		//If we got here both are equal, must check if they are both to deliver home
		if(a1->getDeliverHome()){
			//If they are both to deliver home this is mostly irrelevant I believe but we can just return false
			return false;
		}

		//If we got here then both are to not deliver home
		//If the difference of the present numbers is more than 2
		if(abs(a1->getPresentNumber() - a2->getPresentNumber()) > 2) {
			//The biggest wins
			return a1->getPresentNumber() < a2->getPresentNumber();
		}

		//If nothing else applies, then the order is preserved (using the arrival number)
		return a1->getArrivalNumber() < a2->getArrivalNumber();
	};

	if(presentsTable.size() < 10){
		//Less than 10 items, can sort the whole vector
		sort(presentsTable.begin(), presentsTable.end(), compFunc);
	} else {
		sort(presentsTable.begin(), presentsTable.begin() + 10, compFunc);
	}

}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {

	while(toWrap.size() < toWrapQueueSize && !presentsTable.empty()){
		//Inserts the first element on the table into the queue
		toWrap.emplace(presentsTable.front());
		//Removes the element inserted
		presentsTable.erase(presentsTable.begin());
	}

}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {

	//If the queue is not empty
	if(!toWrap.empty()){
		//Getting the next item and removing it from the queue
		auto next = toWrap.front();
		toWrap.pop();

		//If it is not supposed to be delivered home, return it
		if(!next->getDeliverHome()){
			return next;
		}

		//Otherwise push it to the toDeliver queue
		toDeliver.push(next);
	}

	//And return NULL (also returns NULL when toWrap is empty)
	return NULL;

}

