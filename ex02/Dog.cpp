// ============================================================================
// Dog.cpp (ex01)
// Dog com Brain: cria com new, deleta com delete, deep copy obrigatorio.
// ============================================================================

#include "Dog.hpp"

Dog::Dog(void)
{
	_type = "Dog";
	_brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

// Construtor de copia: cria um NOVO Brain com o conteudo do original.
// Isso e DEEP COPY — cada Dog tem seu proprio Brain independente.
Dog::Dog(const Dog &src) : Animal(src)
{
	_brain = new Brain(*src._brain);
	std::cout << "Dog copy constructor called" << std::endl;
}

// Operador de atribuicao: deleta o Brain antigo, cria um novo com o conteudo do rhs.
Dog &Dog::operator=(const Dog &rhs)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		Animal::operator=(rhs);
		delete _brain;
		_brain = new Brain(*rhs._brain);
	}
	return *this;
}

// Destrutor: deleta o Brain para evitar leak.
Dog::~Dog(void)
{
	delete _brain;
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
	std::cout << "* Woof! Woof! *" << std::endl;
}

Brain *Dog::getBrain(void) const
{
	return _brain;
}
