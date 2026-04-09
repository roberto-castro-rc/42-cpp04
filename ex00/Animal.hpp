// ============================================================================
// Animal.hpp
// Classe base Animal com polimorfismo.
//
// CONCEITO: POLIMORFISMO DE SUBTIPO
// Em C++, para que o compilador chame a funcao da classe DERIVADA
// (e nao da base) atraves de um ponteiro/referencia de base, a
// funcao deve ser declarada como "virtual".
//
// Sem "virtual":  Animal* a = new Dog();  a->makeSound(); -> som de Animal
// Com "virtual":  Animal* a = new Dog();  a->makeSound(); -> som de Dog
//
// O destrutor tambem deve ser virtual para que, ao deletar via
// ponteiro de base, o destrutor correto (da derivada) seja chamado.
// ============================================================================

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>
# include <iostream>

class Animal
{
public:
	// Forma Canonica Ortodoxa
	Animal(void);
	Animal(const Animal &src);
	Animal &operator=(const Animal &rhs);

	// Destrutor VIRTUAL: essencial para heranca!
	// Sem virtual, deletar um Dog* via Animal* nao chama ~Dog().
	virtual ~Animal(void);

	// makeSound e virtual para polimorfismo de subtipo.
	// Cada classe derivada tera seu proprio som.
	virtual void makeSound(void) const;

	// Getter para o tipo do animal
	std::string getType(void) const;

protected:
	std::string _type;
};

#endif
