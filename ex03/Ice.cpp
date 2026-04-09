// ============================================================================
// Ice.cpp
// ============================================================================

#include "Ice.hpp"
#include "ICharacter.hpp"

Ice::Ice(void) : AMateria("ice")
{
}

Ice::Ice(const Ice &src) : AMateria(src)
{
}

Ice &Ice::operator=(const Ice &rhs)
{
	(void)rhs;
	return *this;
}

Ice::~Ice(void)
{
}

// clone: retorna uma nova copia de Ice
AMateria *Ice::clone(void) const
{
	return new Ice(*this);
}

// use: dispara um projetil de gelo no alvo
void Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
