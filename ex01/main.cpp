// ============================================================================
// main.cpp (ex01)
// Testa Brain: array de Animals, deep copy, destruicao sem leaks.
// ============================================================================

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
	// --- Teste do subject ---
	std::cout << "=== Teste basico do subject ===" << std::endl;
	const Animal *j = new Dog();
	const Animal *i = new Cat();

	std::cout << std::endl;
	delete j;  // Nao deve causar leak
	delete i;

	// --- Array de Animals ---
	std::cout << std::endl << "=== Array de 10 Animals (5 Dogs + 5 Cats) ===" << std::endl;
	const int size = 10;
	Animal *animals[size];

	// Metade Dogs, metade Cats
	for (int k = 0; k < size; k++)
	{
		if (k < size / 2)
			animals[k] = new Dog();
		else
			animals[k] = new Cat();
	}

	// Deletar como Animals (destrutor virtual garante chamada correta)
	std::cout << std::endl << "=== Deletando array ===" << std::endl;
	for (int k = 0; k < size; k++)
		delete animals[k];

	// --- Teste de deep copy ---
	std::cout << std::endl << "=== Teste de DEEP COPY ===" << std::endl;
	Dog original;
	original.getBrain()->setIdea(0, "Chase the cat!");
	original.getBrain()->setIdea(1, "Eat the bone!");

	// Copia via construtor de copia
	Dog copy(original);

	std::cout << std::endl << "--- Ideias do original ---" << std::endl;
	std::cout << "Idea 0: " << original.getBrain()->getIdea(0) << std::endl;
	std::cout << "Idea 1: " << original.getBrain()->getIdea(1) << std::endl;

	std::cout << "--- Ideias da copia ---" << std::endl;
	std::cout << "Idea 0: " << copy.getBrain()->getIdea(0) << std::endl;
	std::cout << "Idea 1: " << copy.getBrain()->getIdea(1) << std::endl;

	// Mudar a ideia do original NAO deve afetar a copia (deep copy!)
	original.getBrain()->setIdea(0, "CHANGED!");
	std::cout << std::endl << "--- Apos mudar original ---" << std::endl;
	std::cout << "Original idea 0: " << original.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copia idea 0:    " << copy.getBrain()->getIdea(0) << std::endl;

	// Verificar que sao enderecos diferentes
	std::cout << std::endl << "--- Enderecos dos Brains (devem ser diferentes) ---" << std::endl;
	std::cout << "Original Brain: " << original.getBrain() << std::endl;
	std::cout << "Copia Brain:    " << copy.getBrain() << std::endl;

	std::cout << std::endl << "=== Destruicao automatica ===" << std::endl;
	return 0;
}
