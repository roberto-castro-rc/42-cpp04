// ============================================================================
// Animal.cpp
// Implementacao da classe base Animal.
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

// Som generico do Animal (sera sobrescrito pelas derivadas)
void Animal::makeSound(void) const
{
	std::cout << "* ... (some generic animal sound) ... *" << std::endl;
}

std::string Animal::getType(void) const
{
	return _type;
}
