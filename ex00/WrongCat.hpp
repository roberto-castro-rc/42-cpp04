// ============================================================================
// WrongCat.hpp
// WrongCat herda de WrongAnimal. Tem makeSound proprio, mas como
// WrongAnimal::makeSound NAO e virtual, chamadas via ponteiro de base
// nao ativam polimorfismo.
// ============================================================================

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
public:
	WrongCat(void);
	WrongCat(const WrongCat &src);
	WrongCat &operator=(const WrongCat &rhs);
	virtual ~WrongCat(void);

	// makeSound existe aqui, mas sem virtual na base, nao tem polimorfismo
	void makeSound(void) const;
};

#endif
