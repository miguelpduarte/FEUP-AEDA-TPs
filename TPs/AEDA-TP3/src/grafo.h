#include <iostream>
#include <vector>

using namespace std;

/**
 * Versão da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N> class NoRepetido;

template <class N> class NoInexistente;

template <class N> class ArestaRepetida;

template <class N> class ArestaInexistente;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A>
class Grafo {
	vector< No<N,A> *> nos;
  public:
    Grafo();
    ~Grafo();
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const;
};

//My separate implementations :)

template <class N, class A>
Grafo<N, A>::Grafo(){}

template <class N, class A>
Grafo<N, A>::~Grafo(){
	for(auto &no : nos){
		delete no;
	}

	nos.clear();
}

template <class N, class A>
int Grafo<N, A>::numArestas(void) const{
	int counter = 0;

	for(auto const &no : nos) {
		counter += no->arestas.size();
	}

	return counter;
}

template <class N, class A>
int Grafo<N, A>::numNos(void) const{
	return nos.size();
}

template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirNo(const N &dados){

	//Searching to see if the No already exists
	for(auto const &no : nos){
		if(no->info == dados)
			throw NoRepetido<N>(dados);
	}

	//Allocating a new No
	No<N, A> * temp_no = new No<N, A>(dados);
	//Pushing back to the vector
	nos.push_back(temp_no);

	return *this;
}

template <class N, class A>
Grafo<N, A> &Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val){

	No<N,A> *startNo = nullptr, *endNo = nullptr;

	//Searching for the start and end No
	for(auto const &no : nos){
		if(no->info == inicio)
			startNo = no;
		if(no->info == fim)
			endNo = no;
	}

	//Start No was not found
	if(startNo == nullptr)
		throw NoInexistente<N>(inicio);

	//End No was not found
	if(endNo == nullptr)
		throw NoInexistente<N>(fim);

	//Detecting if there is a repeated Aresta
	for(auto const &aresta : startNo->arestas)
		//Only needs to compare destination as there are no multiple paths between Nos even if they have different values
		//(In this implementation, might make sense for there to be in another)
		if(aresta.destino == endNo)
			throw ArestaRepetida<N>(inicio, fim);

	//Inserting the new Aresta
	//Using emplace_back for efficiency
	startNo->arestas.emplace_back(endNo, val);

	return *this;
}

template <class N, class A>
A &Grafo<N, A>::valorAresta(const N &inicio, const N &fim){

	No<N,A> *startNo = nullptr, *endNo = nullptr;

	//Searching for the start and end No
	for(auto const &no : nos) {
		if(no->info == inicio)
			startNo = no;
		if(no->info == fim)
			endNo = no;
	}

	//Start No was not found
	if(startNo == nullptr)
		throw NoInexistente<N>(inicio);

	//NOTE: Depending on the tests, this might not work or not be necessary
	// (if it is only desired to search within the Arestas and not necessarily the Nos)
	//End No was not found
	if(endNo == nullptr)
		throw NoInexistente<N>(fim);

	//Searching for the correct aresta in the start No, and searching for a pointer to the end No
	for(auto &aresta : startNo->arestas){
		if(aresta.destino == endNo)
			return aresta.valor;
	}

	//If the Aresta was not found throw ArestaInexistente exception
	throw ArestaInexistente<N>(inicio, fim);

}

template <class N, class A>
Grafo<N, A> &Grafo<N, A>::eliminarAresta(const N &inicio, const N &fim){

	No<N,A> *startNo = nullptr, *endNo = nullptr;

	//Searching for the start and end No
	for(auto const &no : nos){
		if(no->info == inicio)
			startNo = no;
		if(no->info == fim)
			endNo = no;
	}

	//Start No was not found
	if(startNo == nullptr)
		throw NoInexistente<N>(inicio);

	/*
	 * As expected, it does not work in E, because the correction does not expect throwing an exception
	 * for not finding the end No in the whole Grafo, which I am doing in this block of code
	//NOTE: Depending on the tests, this might not work or not be necessary
	// (if it is only desired to search within the Arestas and not necessarily the Nos)
	//End No was not found
	if(endNo == nullptr)
		throw NoInexistente<N>(fim);
	 */

	//Searching for the desired aresta in the start No, and searching for a pointer to the end No
	for(unsigned int i = 0; i < startNo->arestas.size(); ++i){
		if(endNo == startNo->arestas.at(i).destino) {
			//If found, delete it
			startNo->arestas.erase(startNo->arestas.begin() + i); //Deleting the element at the i position
			//Returning the changed Grafo
			return *this;
		}
	}

	//If the Aresta was not found throw ArestaInexistente exception
	throw ArestaInexistente<N>(inicio, fim);
}

template <class N, class A>
void Grafo<N, A>::imprimir(std::ostream &os) const{

	//Going through every No
	for(auto const &no : nos){
		os << "( " << no->info;
		//And in each No go through every Aresta
		for(auto const &aresta : no->arestas){
			os << "[ " << aresta.destino->info << " " << aresta.valor << "] ";
		}
		os << ") ";
	}
}

template <class N, class A>
std::ostream & operator<<(std::ostream &os, const Grafo<N,A> &g){
	g.imprimir(os);
	return os;
}

//My separate implementations :) end

// excecao  NoRepetido
template <class N>
class NoRepetido {
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

// exceção ArestaRepetida
template <class N>
class ArestaRepetida {
public:
	N startInfo;
	N destinationInfo;
	ArestaRepetida(N startInfo, N destInfo) : startInfo(startInfo), destinationInfo(destInfo){}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar){
	out << "Aresta repetida: " << ar.startInfo << " , " << ar.destinationInfo;
	return out;
};

// exceção ArestaInexistente
template <class N>
class ArestaInexistente{
public:
	N startInfo;
	N destinationInfo;
	ArestaInexistente(N startInfo, N destInfo) : startInfo(startInfo), destinationInfo(destInfo){}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai){
	out << "Aresta inexistente: " << ai.startInfo << " , " << ai.destinationInfo;
	return out;
};