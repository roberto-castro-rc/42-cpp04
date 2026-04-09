// ============================================================================
// Animal.cpp (ex02)
// Implementacao da classe abstrata Animal.
// Nao implementamos makeSound aqui (e pura virtual).
// ============================================================================

#include "Animal.hpp"

Animal::Animal(void) : _type("Animal")
{
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal &src) : _type(src._type)
{
	std::cout << "Animal copy constructor called" << std::endl;
}

Animal &Animal::operator=(const Animal &rhs)
{
	std::cout << "Animal copy assignment operator called" << std::endl;
	if (this != &rhs)
		_type = rhs._type;
	return *this;
}

Animal::~Animal(void)
{
	std::cout << "Animal destructor called" << std::endl;
}

// makeSound NAO e implementado aqui — e funcao pura virtual.
// Dog e Cat sao OBRIGADOS a implementa-lo.

std::string Animal::getType(void) const
{
	return _type;
}
