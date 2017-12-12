/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
	BookCatalogItem itemNotFound = BookCatalogItem("", "", 0);

	for(auto const &bookptr : books) {
		auto temp = BookCatalogItem(bookptr->getTitle(), bookptr->getAuthor(), bookptr->getYear());
		auto result = catalogItems.find(temp);
		if(result == itemNotFound) {
			//If item is not in the BST, add it after adding the book to the catalogItem
			temp.addItems(bookptr);
			catalogItems.insert(temp);
		} else {
			//If found, add the book to the catalog
			catalogItems.remove(result);
			result.addItems(bookptr);
			catalogItems.insert(result);
		}
	}

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	BookCatalogItem searcher(book->getTitle(), book->getAuthor(), book->getYear());
	vector<Book*> temp;
	auto found = catalogItems.find(searcher);
	if(found == BookCatalogItem("", "", 0)){
		return temp;
	}

	auto catalog_books = found.getItems();

	for(auto const &bookptr : catalog_books) {
		if(bookptr->getReader() == nullptr){
			temp.push_back(bookptr);
		}
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	BookCatalogItem searcher(book->getTitle(), book->getAuthor(), book->getYear());
	vector<Book*> temp;
	auto found = catalogItems.find(searcher);
	if(found == BookCatalogItem("", "", 0)){
		return false;
	}

	auto catalog_books = found.getItems();

	for(auto const &bookptr : catalog_books) {
		if(bookptr->getReader() == nullptr){
			//Available book found, allocating to user
			bookptr->setReader(reader);
			//assigned = true; break;
			//
			catalogItems.remove(found);
			found.setItems(catalog_books);
			catalogItems.insert(found);
			return true;
		}
	}

	/* //Was doing this but put it inside the loop (had until '//') to simplify
	//Have to be outside the loop to do this (?)
	if(assigned) {
		catalogItems.remove(found);
		found.setItems(catalog_books);
		catalogItems.insert(found);
	}
	*/

	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	HashTabUserRecord::iterator it = userRecords.find(user);
	//Since the iterator access to elements of a unordered_set is always const,
	// removing a re-inserting is the best way to do this
	if(it != userRecords.end()) {
		userRecords.erase(it);
		user->setEMail(newEMail);
		userRecords.insert(user);
	}
	//In this test only calling user->setEmail
	// would work since we are working with pointer but better safe than sorry
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for(auto const &candidate : candidates) {
		if(candidate.numReadings() >= min) {
			readerCandidates.push(candidate);
		}
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
	if(readerCandidates.size() >= 2){
		priority_queue<User> aux(readerCandidates);

		auto champ1 = aux.top();
		aux.pop();
		auto champ2 = aux.top();
		if(champ1.numReadings() != champ2.numReadings()) {
			//Different readings, champ1 is winner
			champion = champ1;
			return readerCandidates.size();
		}

	} else if(!readerCandidates.empty()) {
		champion = readerCandidates.top();
		return 1;
	}

	//If the readings are the same or there are no candidates, then there is no winner, return 0
	return 0;
}
























