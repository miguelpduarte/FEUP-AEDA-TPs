#include <queue>
#include <cstdlib>
#include "Balcao.h"

using namespace std;


Cliente::Cliente() {
	//Generates random number between 1 and 5
	numPresentes = rand() * 5 + 1;
}


int Cliente::getNumPresentes() const {
	return numPresentes;
}


Balcao::Balcao(int te)
		: tempo_embrulho(te), tempo_atual(0), prox_chegada(rand()*20+1), prox_saida(0) {}


void Balcao:: proximoEvento() {
	// a alterar
}


void Balcao::chegada() {
	//Create new client and insert in queue
	Cliente c;

	//If queue was previoulsy empty,
	if(clientes.empty()){
		prox_saida = tempo_atual + c.getNumPresentes()*tempo_embrulho;
	}

	prox_chegada = rand() * 20 + 1;

	clientes.push(c);

	cout << "tempo= " << tempo_atual << endl << "chegou novo cliente com " << c.getNumPresentes() << " presentes";
}   


void Balcao::saida() {
	// a alterar
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1) {
	// a alterar
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