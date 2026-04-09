// ============================================================================
// Cure.cpp
// ============================================================================

#include "Cure.hpp"
#include "ICharacter.hpp"

Cure::Cure(void) : AMateria("cure")
{
}

Cure::Cure(const Cure &src) : AMateria(src)
{
}

Cure &Cure::operator=(const Cure &rhs)
{
	(void)rhs;
	return *this;
}

Cure::~Cure(void)
{
}

AMateria *Cure::clone(void) const
{
	return new Cure(*this);
}

// use: cura as feridas do alvo
void Cure::use(ICharacter &target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
