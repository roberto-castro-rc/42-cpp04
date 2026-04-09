// ============================================================================
// main.cpp (ex00)
// Testa polimorfismo: Animal (virtual) vs WrongAnimal (sem virtual).
// ============================================================================

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
	std::cout << "=== Animal (COM virtual) ===" << std::endl;
	const Animal *meta = new Animal();
	const Animal *j = new Dog();
	const Animal *i = new Cat();

	std::cout << std::endl;
	std::cout << "j->getType(): " << j->getType() << std::endl;
	std::cout << "i->getType(): " << i->getType() << std::endl;

	std::cout << std::endl << "--- Sons (via ponteiro Animal*) ---" << std::endl;
	// Graças ao virtual, chama o makeSound da classe DERIVADA
	i->makeSound();   // Meow (Cat)
	j->makeSound();   // Woof (Dog)
	meta->makeSound(); // som generico

	std::cout << std::endl;
	delete meta;
	delete j;
	delete i;

	std::cout << std::endl << "=== WrongAnimal (SEM virtual) ===" << std::endl;
	const WrongAnimal *wrongMeta = new WrongAnimal();
	const WrongAnimal *wrongCat = new WrongCat();

	std::cout << std::endl;
	std::cout << "wrongCat->getType(): " << wrongCat->getType() << std::endl;

	std::cout << std::endl << "--- Sons (via ponteiro WrongAnimal*) ---" << std::endl;
	// SEM virtual: chama makeSound do WrongAnimal, nao do WrongCat!
	wrongCat->makeSound();  // Wrong generic (NAO Wrong Meow!)
	wrongMeta->makeSound(); // Wrong generic

	std::cout << std::endl;
	delete wrongMeta;
	delete wrongCat;

	return 0;
}
