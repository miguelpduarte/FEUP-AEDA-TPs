#include "zoo.h"

int Animal::maisJovem = -1;

string Animal::getNome() const {
	return nome;
}

Animal::Animal(string nome, int idade) : nome(nome), idade(idade), vet(nullptr){
	//if no animal was added - maisJovem is still at -1 OR the new animal is younger, update maisJovem
	if(Animal::getMaisJovem() == -1 || idade < Animal::getMaisJovem())
		Animal::maisJovem = idade;
}

int Animal::getMaisJovem(){
	return Animal::maisJovem;
}

string Animal::getInformacao() const{
	if(vet != nullptr)
		return this->nome + ", " + to_string(this->idade) + ", " + this->vet->getInformacao();

	return this->nome + ", " + to_string(this->idade);
}

void Animal::setVet(Veterinario *v){
	this->vet = v;
}

const Veterinario *Animal::getVet() const{
	return vet;
}

int Animal::getIdade() const{
	return this->idade;
}


string Veterinario::getNome() const {
	return nome;
}

Veterinario::Veterinario(string nome, long codOrdem) : nome(nome), codOrdem(codOrdem){}

string Veterinario::getInformacao() const{
	return nome + ", " + to_string(codOrdem);
}

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1){
	animais.push_back(a1);
}

string Zoo::getInformacao() const{
	string output;

	for(const auto &animal : animais){
		output += animal->getInformacao() + "\n";
	}

	return output;
}

bool Zoo::animalJovem(string nomeA){
	int pos = encontrarAnimalporNome(nomeA);
	return (pos != -1 && animais.at(pos)->eJovem());
}

int Zoo::encontrarAnimalporNome(string nome) const{
	for(unsigned int i = 0; i < animais.size(); ++i)
		if(animais[i]->getNome() == nome)
			return i;

	return -1;
}

void Zoo::alocaVeterinarios(istream &isV){

	//Getting veterinarios from the text file

	string temp;
	string name, codOrdem_s;
	//The input is alternated in new lines with name or text, thus the need to have an indicator to know which one we are inputting
	bool isName = true;

	while(getline(isV, temp)){
		if(isName)
			name = temp;
		else {
			codOrdem_s = temp;
			Veterinario* tempVet = new Veterinario(name, stoi(codOrdem_s));
			veterinarios.push_back(tempVet);
		}

		isName = !isName;
	}

	//Allocating veterinarios

	int numVeterinarios = veterinarios.size();

	for(unsigned int i = 0; i < animais.size(); ++i){
		//assings the animal at i with the vet at i mod nVets, thus allowing for uniform distribution
		animais.at(i)->setVet(veterinarios.at(i % numVeterinarios));
	}

}

bool Zoo::removeVeterinario(string nomeV){
	int pos = encontrarVetporNome(nomeV);
	if(pos == -1)
		return false;

	//The position to reassign the animals' vets to
	int reassignpos = pos + 1;

	//The vet to remove was the last one of the vector so we wrap around and reassign to the first one
	if(pos == veterinarios.size() - 1)
		reassignpos = 0;

	for(auto const &animal : animais){
		//If the vet is the one that is beign removed, reassign
		if(animal->getVet()->getNome() == nomeV)
			animal->setVet(veterinarios.at(reassignpos));
	}

	//At last, remove the vet
	veterinarios.erase(veterinarios.begin() + pos);
	return true;
}

int Zoo::encontrarVetporNome(string nome) const{
	for(unsigned int i = 0; i < veterinarios.size(); ++i)
		if(veterinarios.at(i)->getNome() == nome)
			return i;

	return -1;
}

bool Zoo::operator<(Zoo &zoo2) const{
	return this->getZooAnimalAgeSum() < zoo2.getZooAnimalAgeSum();
}

long int Zoo::getZooAnimalAgeSum() const{
	long int ageSum = 0;

	for(auto const &animal : animais){
		ageSum += animal->getIdade();
	}
}

Cao::Cao(string nome, int idade, string raca) : Animal(nome, idade), raca(raca) {}

bool Cao::eJovem() const{
	return (idade < 5);
}

string Cao::getInformacao() const{
	return Animal::getInformacao() + ", " + raca;
}

Voador::Voador(int vmax, int amax) : velocidade_max(vmax), altura_max(amax){}

string Voador::getInformacao() const{
	return to_string(velocidade_max) + ", " + to_string(altura_max);
}

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade), Voador(vmax, amax){}

bool Morcego::eJovem() const{
	return (idade < 4);
}

string Morcego::getInformacao() const{
	return Animal::getInformacao() + ", " + Voador::getInformacao();
}
