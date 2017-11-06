/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <random>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;


unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  int pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo() {}

Jogo::Jogo(list<Crianca>& lc2) : criancas(lc2) {}

void Jogo::insereCrianca(const Crianca &c1) {
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const {
	return criancas;
}


string Jogo::escreve() const {
	string output;

	for_each(criancas.begin(), criancas.end(), [&output](const Crianca &c){output += c.escreve() + "\n";});

	//Oldskool method, for_each and lambdas are nicer
	/*
	for(const auto &crianca : criancas) {
		output += crianca.escreve() + "\n";
	}
	*/

	//Iterators are even worse, ewww
	/*
	for(auto it = criancas.begin(); it != criancas.end(); ++it){
		output += it->escreve() + "\n";
	}
	*/

	return output;
}


Crianca& Jogo::perdeJogo(string frase) {
	unsigned int npalavras = numPalavras(frase);

	list<Crianca> temp(criancas);

	unsigned long iToRemove;

	while(temp.size() > 1){
		iToRemove = (npalavras % temp.size()) + 1;
		auto it = temp.begin();
		advance(it, iToRemove);
		temp.erase(it);
	}

	return temp.front();
}


list<Crianca>& Jogo::inverte() {
	criancas.reverse();
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id) {
	list<Crianca> output;

	//Lambda magic <3
	criancas.remove_if([&output, id](Crianca &c){
		if(c.getIdade() > id){
			output.push_back(c);
			return true;
		}
		return false;
	});

	//Using iterators (clearly worse even though it is basically the same thing xD)
	/*
	for(auto it = criancas.begin(); it != criancas.end(); ++it){
		if(it->getIdade() > id){
			output.push_back(*it);
			criancas.erase(it);
		}
	}
	*/

	return output;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1) {
	criancas = l1;
}


bool Jogo::operator==(Jogo& j2) {
	//This is probably the best and only way, since the functions that exist iterate over one container only
	//That or have other uses (stuff from <algorithm>, like copy

	if(this->criancas.size() != j2.criancas.size()){
		return false;
	}

	auto it1 = this->criancas.begin();
	auto it2 = j2.criancas.begin();
	for( ; it1 != criancas.end(); ++it1, ++it2){
		if(!(*it1 == *it2)){
			return false;
		}
	}

	return true;
}


list<Crianca> Jogo::baralha() const {

	//Magic STL stuff, but don't know the complexity of shuffle
	vector<Crianca> tempvec(criancas.begin(), criancas.end());

	//Same as random_shuffle, auto fixed by clion, thanks
	shuffle(tempvec.begin(), tempvec.end(), std::mt19937(std::random_device()()));

	list<Crianca> output(tempvec.begin(), tempvec.end());
	/*
	//Teacher's recommended resolution, something like this:
	list<Crianca> temp(criancas);
	list<Crianca> output;
	unsigned long chosenIndex;

	while(!temp.empty()){
		chosenIndex = rand() * temp.size();
		auto it = temp.begin();
		advance(it, chosenIndex);
		output.push_back(*it);
		temp.erase(it);
	}
	*/
	return output;
}
