#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "zoo.h"
#include <fstream>

using namespace std;

void test_a_criarAnimais() {
	Animal *a1=new Cao("kurika",10,"estrela");  //nome, idade, raça
	Animal *a2=new Morcego("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima
	Animal *a3=new Cao("bobby",3,"rafeiro");
	Animal *a4=new Cao("fly",7,"dalmata");
	Animal *a5=new Morcego("timao",7,80,4);
	ASSERT_EQUAL("kurika", a1->getNome());
	ASSERT_EQUAL("bobo", a2->getNome());
	ASSERT_EQUAL("bobby", a3->getNome());
	ASSERT_EQUAL("fly", a4->getNome());
	ASSERT_EQUAL("timao", a5->getNome());
	ASSERT_EQUAL(true, a3->eJovem());
	ASSERT_EQUAL(false, a4->eJovem());
	ASSERT_EQUAL(true, a2->eJovem());
	ASSERT_EQUAL(false, a5->eJovem());
	ASSERT_EQUAL(2, Animal::getMaisJovem());
}


void test_b_adicionarAnimais() {
	Zoo z1;

	Animal *a1=new Cao("kurika",10,"estrela");  //nome, idade, raça
	Animal *a2=new Morcego("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima
	Animal *a3=new Cao("bobby",3,"rafeiro");
	Animal *a4=new Cao("fly",7,"dalmata");
	Animal *a5=new Morcego("timao",7,80,4);

	z1.adicionaAnimal(a1);
	z1.adicionaAnimal(a2);
	z1.adicionaAnimal(a3);
	z1.adicionaAnimal(a4);
	z1.adicionaAnimal(a5);

	ASSERT_EQUAL(5, z1.numAnimais());
}

void test_c_imprimirAnimais() {
	Zoo z1;

	Animal *a1=new Cao("kurika",10,"estrela");  //nome, idade, raça
	ASSERT_EQUAL("kurika, 10, estrela", a1->getInformacao());

	Animal *a2=new Morcego("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima
	ASSERT_EQUAL("bobo, 2, 70, 2", a2->getInformacao());

	z1.adicionaAnimal(a1);
	z1.adicionaAnimal(a2);

	cout << z1.getInformacao();

	ASSERT_EQUAL("kurika, 10, estrela\nbobo, 2, 70, 2\n", z1.getInformacao());
}

void test_d_verificarAnimalJovem() {
	Zoo z1;

	Animal *a1=new Cao("kurika",10,"estrela");  //nome, idade, raça
	Animal *a2=new Morcego("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima

	z1.adicionaAnimal(a1);
	z1.adicionaAnimal(a2);

	ASSERT_EQUAL(false, z1.animalJovem("kurika"));
	ASSERT_EQUAL(true, z1.animalJovem("bobo"));
}

void test_e_alocarVeterinarios() {
	Zoo z1;

	Animal *a1=new Cao("kurika",10,"estrela");  //nome, idade, raça
	Animal *a2=new Morcego("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima
	Animal *a3=new Cao("bobby",3,"rafeiro");
	Animal *a4=new Cao("fly",7,"dalmata");
	Animal *a5=new Morcego("timao",7,80,4);

	z1.adicionaAnimal(a1);
	z1.adicionaAnimal(a2);
	z1.adicionaAnimal(a3);
	z1.adicionaAnimal(a4);
	z1.adicionaAnimal(a5);

	//TODO trocar o caminho do ficheiro para o caminho correcto; caminho relativo não funciona!
	ifstream fVet("/home/miguel/Programação MIEIC FEUP/AEDA/clion-projects/AEDA-TP2/src/vets.txt"); //My path, apparently has to be hardcoded, thanks cute!
	//Also, had some problems with stoi and whatnot, try changing the txt file encoding, UTF-8 worked
	if (!fVet) cerr << "Ficheiro de veterinarios inexistente!\n";
	else z1.alocaVeterinarios(fVet);
	fVet.close();

	ASSERT_EQUAL(5, z1.numAnimais());
	ASSERT_EQUAL(3, z1.numVeterinarios());
	ASSERT_EQUAL("kurika, 10, Rui Silva, 1234, estrela", a1->getInformacao());
}

void test_f_removerVeterinario(){

	Zoo z1;

	Animal *a1 = new Cao("kurika", 10, "estrela");  //nome, idade, raça
	Animal *a2 = new Morcego("bobo", 2, 70, 2);  //nome, idade, velocidade_maxima, altura_maxima
	Animal *a3 = new Cao("bobby", 3, "rafeiro");
	Animal *a4 = new Cao("fly", 7, "dalmata");
	Animal *a5 = new Morcego("timao", 7, 80, 4);

	z1.adicionaAnimal(a1);
	z1.adicionaAnimal(a2);
	z1.adicionaAnimal(a3);
	z1.adicionaAnimal(a4);
	z1.adicionaAnimal(a5);

	//TODO trocar o caminho do ficheiro para o caminho correcto; caminho relativo não funciona!
	ifstream fVet("/home/miguel/Programação MIEIC FEUP/AEDA/clion-projects/AEDA-TP2/src/vets.txt");
	if(!fVet) cerr << "Ficheiro de veterinarios inexistente!\n";
	else z1.alocaVeterinarios(fVet);
	fVet.close();

	ASSERT_EQUAL(5, z1.numAnimais());
	ASSERT_EQUAL(3, z1.numVeterinarios());
	ASSERT_EQUAL("kurika, 10, Rui Silva, 1234, estrela", a1->getInformacao());

	z1.removeVeterinario("Rui Silva");

	ASSERT_EQUAL("kurika, 10, Artur Costa, 3542, estrela", a1->getInformacao());
}

//Answer to G:
/*
 * O vetor de veterinários pode ser um vetor de objetos e não de apontadores pois não usufrui de caraterísticas polimórficas.
 * Esta implementação será, porém, menos eficiente e mais volátil, pois grande parte das operações com vetores,
 * nomeadamenete o aumento do seu tamanho, quando ultrapassa a capacidade alocada, implica operações de cópia.
 * Para além de ser menos eficiente pois tem de haver criação de novos objetos, também é uma situação volátil pois apontadores
 * para elementos do vetor podem ficar inválidos, apontando para cópias antigas do objeto.
 * Elaboração:
 * Objeto está no vetor. Apontador é criado para o objeto no vetor.
 * Objeto é copiado quando o vetor precisa de ser realocado. Vetor antigo tem a sua memória desalocada.
 * Apontador previamente referido é agora inválido, tendo muitas vezes "undefined behaviour".
 * */

void test_h_compararZoos() {
	Zoo z1;

	Animal *a1=new Cao("kurika",10,"estrela");  //nome, idade, raça
	Animal *a2=new Morcego("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima
	Animal *a3=new Cao("bobby",3,"rafeiro");
	Animal *a4=new Cao("fly",7,"dalmata");
	Animal *a5=new Morcego("timao",7,80,4);

	z1.adicionaAnimal(a1);
	z1.adicionaAnimal(a2);
	z1.adicionaAnimal(a3);
	z1.adicionaAnimal(a4);
	z1.adicionaAnimal(a5);

	Zoo z2;

	Animal *b1=new Cao("kurika",10,"estrela");  //nome, idade, raça
	Animal *b2=new Morcego("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima
	Animal *b3=new Cao("bobby",3,"rafeiro");
	Animal *b4=new Cao("fly",7,"dalmata");

	z2.adicionaAnimal(b1);
	z2.adicionaAnimal(b2);
	z2.adicionaAnimal(b3);
	z2.adicionaAnimal(b4);

	ASSERT_EQUAL(true, z2 < z1);
}


void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_a_criarAnimais));
	s.push_back(CUTE(test_b_adicionarAnimais));
	s.push_back(CUTE(test_c_imprimirAnimais));
	s.push_back(CUTE(test_d_verificarAnimalJovem));
	s.push_back(CUTE(test_e_alocarVeterinarios));
	s.push_back(CUTE(test_f_removerVeterinario));
	s.push_back(CUTE(test_h_compararZoos));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2017/2018 - Aula Pratica 2");
}

int main(){
    runSuite();
    return 0;
}



