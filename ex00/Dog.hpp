// ============================================================================
// Dog.hpp
// Dog herda de Animal. Tipo = "Dog". makeSound emite latido.
// ============================================================================

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

class Dog : public Animal
{
public:
	Dog(void);
	Dog(const Dog &src);
	Dog &operator=(const Dog &rhs);
	virtual ~Dog(void);

	// Sobrescreve makeSound do Animal
	virtual void makeSound(void) const;
};

#endif
