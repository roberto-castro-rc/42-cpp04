// ============================================================================
// WrongAnimal.hpp
// WrongAnimal: classe base SEM virtual em makeSound.
// Quando chamamos makeSound via ponteiro WrongAnimal*, o compilador
// chama a versao do WrongAnimal (nao a do WrongCat).
// Isso demonstra por que "virtual" e essencial para polimorfismo.
// ============================================================================

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <string>
# include <iostream>

class WrongAnimal
{
public:
	WrongAnimal(void);
	WrongAnimal(const WrongAnimal &src);
	WrongAnimal &operator=(const WrongAnimal &rhs);
	virtual ~WrongAnimal(void);

	// SEM virtual! Isso e o ponto do exercicio.
	// Chamadas via ponteiro de base nao usam polimorfismo.
	void makeSound(void) const;

	std::string getType(void) const;

protected:
	std::string _type;
};

#endif
