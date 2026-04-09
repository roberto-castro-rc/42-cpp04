// ============================================================================
// Cure.hpp
// Materia concreta: Cure. Tipo = "cure".
// ============================================================================

#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

class Cure : public AMateria
{
public:
	Cure(void);
	Cure(const Cure &src);
	Cure &operator=(const Cure &rhs);
	virtual ~Cure(void);

	virtual AMateria *clone(void) const;
	virtual void use(ICharacter &target);
};

#endif
