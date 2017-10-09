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

	for(auto const &no : nos){
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

//My separate implementations :) end

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

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

