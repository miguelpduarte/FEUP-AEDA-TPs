#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	// a alterar
	return palavra < ps1.palavra;
}


void Dicionario::lerDicionario(ifstream &fich) {
	string tempstring;
	string pal, sig;
	bool flag = true;

	while(getline(fich, tempstring)){
		if(flag){
			pal = tempstring;
		}else{
			sig = tempstring;
			PalavraSignificado ps(pal, sig);
			palavras.insert(ps);
		}

		flag = !flag;
	}
}


string Dicionario::consulta(string palavra) const
{
     // a alterar
	return "";
}


bool Dicionario::corrige(string palavra, string significado)
{
	// a alterer
		return true;
}


void Dicionario::imprime() const
{
	// a alterar
     return;
}
