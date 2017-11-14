#include <queue>
#include <cstdlib>
#include "Balcao.h"

using namespace std;


Cliente::Cliente() {
	//Generates random number between 1 and 5
	numPresentes = rand() % 5 + 1;
}


int Cliente::getNumPresentes() const {
	return numPresentes;
}

//Does not say explicitly to set clientes_atendidos to 0 but apparently that was being a problem in the tests lol
Balcao::Balcao(int te)
	: tempo_embrulho(te), tempo_atual(0), prox_chegada(rand()%20+1), prox_saida(0), clientes_atendidos(0){}


void Balcao:: proximoEvento() {
	//Sees which event comes first and executes it!
	//(If the queue is empty should always execute chegada tho...)

	//As such, hardcoded for that here:
	if(clientes.empty()){
		tempo_atual = prox_chegada;
		chegada();
		return;
	}

	//Priority is on chegada
	if(prox_chegada <= prox_saida){
		tempo_atual = prox_chegada;
		chegada();
	} else {
		tempo_atual = prox_saida;
		saida();
	}
}


void Balcao::chegada() {
	//Create new client and insert in queue
	Cliente c;

	//If queue was previoulsy empty,
	if(clientes.empty()){
		prox_saida = tempo_atual + c.getNumPresentes()*tempo_embrulho;
	}

	prox_chegada = tempo_atual + rand() % 20 + 1;

	clientes.push(c);

	cout << "tempo= " << tempo_atual << endl << "chegou novo cliente com " << c.getNumPresentes() << " presentes\n";
}   


void Balcao::saida() {
	//Get the client that will be removed from the queue
	auto proxCliente = getProxCliente();

	//Remove the Cliente
	clientes.pop();

	//Update prox_saida
	prox_saida = tempo_atual + proxCliente.getNumPresentes()*tempo_embrulho;

	//Writing info
	//(There is no format for this one so I kinda made it up)
	cout << "tempo= " << tempo_atual << endl << "saiu cliente com " << proxCliente.getNumPresentes() << " presentes\n";

	//Incrementing the count of customers serviced
	++clientes_atendidos;
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1) {
	out << "Nr de clientes atendidos: " << b1.clientes_atendidos << endl;
	out << "Nr de clientes em espera: " << b1.clientes.size() << endl;
	return out;
}


int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {
	if(clientes.empty()){
		throw FilaVazia();
	}

	return clientes.front();
}