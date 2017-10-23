#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome) {
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome) {
	vector<InfoCartao>::iterator it;
	for (it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if (!it->presente) {
				clientes.erase(it);
				numClientes--;
				return true;
			}

			return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const {
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome) {
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if (clientes[pos].presente) return false;

	//Entrada do cliente no parque
	clientes[pos].presente = true;
	vagas--;
	//Uma entrada = +1 vez de utilização do parque = frequência++
	clientes[pos].frequencia++;

	return true;
}

bool ParqueEstacionamento::sair(const string & nome) {
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if (!clientes[pos].presente) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	//Temporary object to be able to use sequentialSearch and InfoCartao's overloaded == operator
	InfoCartao ic;
	ic.nome = nome;
	return sequentialSearch(this->clientes, ic);
}

//InfoCartao methods
bool InfoCartao::operator==(const InfoCartao &ic1) const{
	return this->nome == ic1.nome;
}

bool InfoCartao::operator<(const InfoCartao &ic1) const{
	if(this->frequencia == ic1.frequencia)
		return this->nome < ic1.nome;

	return this->frequencia > ic1.frequencia;
}
//End of InfoCartao methods


int ParqueEstacionamento::getFrequencia(const string &nome) const{
	int pos = posicaoCliente(nome);
	if(pos == -1)
		throw ClienteNaoExistente(nome);

	return clientes[pos].frequencia;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia(){
	insertionSort(clientes);
}

//ClienteNaoExistente "exception class"
ClienteNaoExistente::ClienteNaoExistente(const string &nome) : nome(nome){}

string ClienteNaoExistente::getNome() const{
	return this->nome;
}