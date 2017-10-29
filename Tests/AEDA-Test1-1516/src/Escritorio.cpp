#include "Escritorio.h"
#include <iostream>
#include <cmath>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+(const Documento &d) const{
	int npaginastotal = this->numPaginas + d.numPaginas;
	float pPretofinal = (this->pPreto*this->numPaginas + d.pPreto*d.numPaginas)/npaginastotal;
	float pAmarelofinal = (this->pAmarelo*this->numPaginas + d.pAmarelo*d.numPaginas)/npaginastotal;
	return Documento(npaginastotal, pPretofinal, pAmarelofinal);
}


//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1){
	if(this->numPagImprimir - doc1.getNumPaginas() >= 0){
		numPagImprimir -= doc1.getNumPaginas();
		this->docsImpressos.push_back(doc1);
		return true;
	}

	return false;
}

string ImpressoraPB::getType() const{return "PB";}


//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1){
	auto pagAmarelo = ceil(doc1.getNumPaginas() * doc1.getPercentagemPreto());
	auto pagPreto = ceil(doc1.getNumPaginas() * doc1.getPercentagemAmarelo());

	if(this->numPagImprimirPreto - pagPreto >= 0 && this->numPagImprimirAmarelo - pagAmarelo >= 0){
		numPagImprimirPreto -= pagPreto;
		numPagImprimirAmarelo -= pagAmarelo;
		this->docsImpressos.push_back(doc1);
		return true;
	}

	return false;
}

string ImpressoraCores::getType() const{return "Cores";}


//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const{
	unsigned int nImpressorasComResposavel = 0;

	for(const auto &funcionario : funcionarios) {
		nImpressorasComResposavel += funcionario.getImpressoras().size();
	}

	//The number of 'impressoras' without 'responsavel' is the number of impressoras - the number with 'responsavel'
	return impressoras.size() - nImpressorasComResposavel;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1){
	vector<Impressora *> output;

	for(auto it = impressoras.begin(); it != impressoras.end(); ++it){
		if((*it)->getAno() < ano1){
			output.push_back(*it);
			impressoras.erase(it);
			//Because removing shifts the elements of the vector
			--it;
		}
	}

	return output;
}

Impressora *Escritorio::imprimeDoc(Documento doc1) const{
	for(auto const &impressora : impressoras){
		if(impressora->imprime(doc1))
			return impressora;
	}

	return (new ImpressoraPB("inexistente", -1, 0));
}

vector<Impressora *> Escritorio::tonerBaixo() const{
	vector<Impressora *> output;
	for(auto const &impressora : impressoras){
		if(impressora->getType() == "Cores"){
			if(impressora->getNumPaginasImprimir() < 20)
				output.push_back(impressora);
		} else {
			//PB
			if(impressora->getNumPaginasImprimir() < 30)
				output.push_back(impressora);
		}
	}

	return output;
}

string Escritorio::operator()(string codimp) const{

	for(auto const &funcionario : funcionarios) {
		for(auto const &impressorafunc : funcionario.getImpressoras()) {
			if(impressorafunc->getCodigo() == codimp){
				return funcionario.getCodigo();
			}
		}
	}


	return "nulo";
}


