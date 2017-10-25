#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>
#include <algorithm>

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

ostream &operator<<(ostream &os, const InfoCartao &ic){
	os << ic.nome << ", " << (ic.presente ? "presente, " : "não presente, ")
	   << "usou o parque " << ic.frequencia << " vezes.";

	return os;
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

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2){
	ordenaClientesPorFrequencia();

	vector<string> output;

	//Iterating from most frequency to least frequency and selecting the elements with frequency >=n1 and <=n2
	for(auto const &cliente : clientes){
		if(cliente.frequencia > n2 || cliente.frequencia < n1) {
			break;
		} else {
			output.emplace_back(cliente.nome);
		}
	}

	return output;
}

//Function to help sort InfoCartao(s) by their names
bool infoCartaoNameSort(const InfoCartao &ic1, const InfoCartao &ic2){
	return ic1.nome < ic2.nome;
}

void ParqueEstacionamento::ordenaClientesPorNome(){
	sort(clientes.begin(), clientes.end(), infoCartaoNameSort);
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const{
	if(p < 0 || p > clientes.size())
		throw PosicaoNaoExistente(p);
	else
		return clientes[p];
}

ostream &operator<<(ostream &os, const ParqueEstacionamento &pe){
	for(auto const &cliente : pe.clientes){
		os << cliente << endl;
	}

	return os;
}

//ClienteNaoExistente "exception class"
ClienteNaoExistente::ClienteNaoExistente(const string &nome) : nome(nome){}

string ClienteNaoExistente::getNome() const{
	return this->nome;
}

//PosicaoNaoExistente "exception class"
PosicaoNaoExistente::PosicaoNaoExistente(const int &pos) : pos(pos) {}

int PosicaoNaoExistente::getValor() const{return pos;}
