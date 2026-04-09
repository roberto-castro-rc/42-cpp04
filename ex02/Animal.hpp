// ============================================================================
// Animal.hpp (ex02)
// Classe ABSTRATA Animal — nao pode ser instanciada diretamente.
//
// CONCEITO: CLASSE ABSTRATA
// Uma classe abstrata tem pelo menos uma funcao "virtual pura" (= 0).
// Isso impede que objetos da classe base sejam criados diretamente.
//
//   virtual void makeSound(void) const = 0;   // "= 0" = funcao pura
//
// POR QUE?
// Faz sentido criar um "Animal" generico? Nao! Que som ele faria?
// So faz sentido criar Dog ou Cat (concretos).
// A classe abstrata serve apenas como "contrato" para as derivadas.
//
// Prefixo "A" (AAnimal) e opcional conforme o subject. Mantemos "Animal".
// ============================================================================

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>
# include <iostream>

class Animal
{
public:
	Animal(void);
	Animal(const Animal &src);
	Animal &operator=(const Animal &rhs);
	virtual ~Animal(void);

	// Funcao virtual PURA (= 0): torna Animal uma classe abstrata.
	// Nao pode mais fazer: Animal a;  -> ERRO de compilacao!
	// Obriga Dog e Cat a implementarem makeSound.
	virtual void makeSound(void) const = 0;

	std::string getType(void) const;

protected:
	std::string _type;
};

#endif
