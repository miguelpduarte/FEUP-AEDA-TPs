#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot = 0, unsigned int nMaxCli = 0)
		: lotacao(lot), numMaximoClientes(nMaxCli), vagas(lot){}

unsigned int ParqueEstacionamento::getNumLugares() const{
	return this->lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
	return this->numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const{
	for(unsigned int i = 0; i < clientes.size(); ++i){
		if(clientes.at(i).nome == nome)
			return i;
	}

	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome){
	if(this->posicaoCliente(nome) != -1 || clientes.size() + 1 > numMaximoClientes)
		return false;

	InfoCartao ic;
	ic.nome = nome;
	ic.presente = false;

	clientes.push_back(ic);

	return true;
}

bool ParqueEstacionamento::entrar(const string &nome){
	//No more vagas - client not registered - client already in the park
	int pos = posicaoCliente(nome);
	if(this->vagas == 0 || pos == -1 || clientes.at(pos).presente)
		return false;

	clientes.at(pos).presente = true;
	vagas--;

	return true;
}

bool ParqueEstacionamento::retiraCliente(const string &nome){
	int pos = posicaoCliente(nome);
	if(pos == -1)
		return false;
	if(clientes.at(pos).presente)
		return false;

	clientes.erase(clientes.begin() + pos);

	return true;
}

bool ParqueEstacionamento::sair(const string &nome){
	int pos = posicaoCliente(nome);
	if(pos == -1 || !clientes.at(pos).presente)
		return false;

	clientes.at(pos).presente = false;
	vagas++;
	return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size();
}

const ParqueEstacionamento &ParqueEstacionamento::operator+=(const ParqueEstacionamento &p2){

	for(unsigned int i = 0; i < p2.clientes.size(); ++i){
		if(this->vagas == 0 || this->clientes.size() == this->numMaximoClientes)
			break;

		this->adicionaCliente(p2.clientes.at(i).nome);
		if(p2.clientes.at(i).presente)
			this->entrar(p2.clientes.at(i).nome);
	}

	return *this;
}
