// ============================================================================
// Dog.hpp (ex01)
// Dog agora tem um Brain* privado, alocado com new no construtor.
//
// CONCEITO: DEEP COPY vs SHALLOW COPY
// Quando um Dog e copiado, precisamos criar um NOVO Brain (deep copy).
// Se apenas copiassemos o ponteiro (shallow copy), dois Dogs
// compartilhariam o mesmo Brain, causando double-free na destruicao.
// ============================================================================

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal
{
public:
	Dog(void);
	Dog(const Dog &src);
	Dog &operator=(const Dog &rhs);
	virtual ~Dog(void);

	virtual void makeSound(void) const;

	// Acesso ao Brain (para testes)
	Brain *getBrain(void) const;

private:
	Brain *_brain;  // Ponteiro para Brain, alocado com new
};

#endif
