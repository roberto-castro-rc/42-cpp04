// ============================================================================
// AMateria.cpp
// ============================================================================

#include "AMateria.hpp"

AMateria::AMateria(void) : _type("unknown")
{
}

AMateria::AMateria(std::string const &type) : _type(type)
{
}

AMateria::AMateria(const AMateria &src) : _type(src._type)
{
}

// Na atribuicao, NAO copiar o tipo — conforme subject:
// "While assigning a Materia to another, copying the type doesn't make sense."
AMateria &AMateria::operator=(const AMateria &rhs)
{
	(void)rhs;
	return *this;
}

AMateria::~AMateria(void)
{
}

std::string const &AMateria::getType(void) const
{
	return _type;
}

// Implementacao padrao de use (pode ser sobrescrita)
void AMateria::use(ICharacter &target)
{
	(void)target;
}
