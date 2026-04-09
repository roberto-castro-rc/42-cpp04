// ============================================================================
// main.cpp (ex02)
// Testa que Animal e abstrato (nao pode ser instanciado diretamente).
// Dog e Cat continuam funcionando normalmente.
// ============================================================================

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
	// A linha abaixo NAO compila (Animal e abstrato):
	//Animal a;      // ERRO: cannot declare variable 'a' of abstract type
	//Animal *a = new Animal();  // ERRO: idem

	std::cout << "=== Animal e abstrato — so Dog e Cat podem ser criados ===" << std::endl;

	// Ponteiro de base (Animal*) continua funcionando para polimorfismo
	const Animal *dog = new Dog();
	const Animal *cat = new Cat();

	std::cout << std::endl;
	std::cout << "Dog type: " << dog->getType() << std::endl;
	std::cout << "Cat type: " << cat->getType() << std::endl;

	std::cout << std::endl << "--- Sons ---" << std::endl;
	dog->makeSound();
	cat->makeSound();

	std::cout << std::endl << "--- Deletando ---" << std::endl;
	delete dog;
	delete cat;

	// --- Teste com array ---
	std::cout << std::endl << "=== Array de Animals ===" << std::endl;
	const int size = 4;
	Animal *animals[size];

	for (int i = 0; i < size / 2; i++)
		animals[i] = new Dog();
	for (int i = size / 2; i < size; i++)
		animals[i] = new Cat();

	std::cout << std::endl << "--- Deletando array ---" << std::endl;
	for (int i = 0; i < size; i++)
		delete animals[i];

	// --- Teste de deep copy ---
	std::cout << std::endl << "=== Deep copy com Dog ===" << std::endl;
	Dog original;
	original.getBrain()->setIdea(0, "I love bones!");

	Dog copy(original);

	// Modificar original nao afeta a copia
	original.getBrain()->setIdea(0, "CHANGED!");
	std::cout << "Original: " << original.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copia:    " << copy.getBrain()->getIdea(0) << std::endl;

	std::cout << std::endl << "=== Fim ===" << std::endl;
	return 0;
}
