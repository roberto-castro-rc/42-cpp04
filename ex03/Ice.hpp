// ============================================================================
// Ice.hpp
// Materia concreta: Ice. Tipo = "ice".
// ============================================================================

#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"

class Ice : public AMateria
{
public:
	Ice(void);
	Ice(const Ice &src);
	Ice &operator=(const Ice &rhs);
	virtual ~Ice(void);

	// Cria uma copia de si mesma (retorna new Ice)
	virtual AMateria *clone(void) const;

	// "* shoots an ice bolt at <name> *"
	virtual void use(ICharacter &target);
};

#endif
