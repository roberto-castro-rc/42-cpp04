// ============================================================================
// AMateria.hpp
// Classe abstrata AMateria: base para todas as materias (Ice, Cure).
//
// CONCEITO: CLASSE ABSTRATA como "INTERFACE"
// Em C++98, nao existem interfaces como em Java.
// Mas uma classe abstrata com funcoes puramente virtuais e usada
// como interface — define um contrato que as derivadas devem cumprir.
//
// clone() = 0: cada materia concreta deve saber se clonar.
// use(): acao da materia sobre um personagem.
// ============================================================================

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <string>
# include <iostream>

// Forward declaration: ICharacter sera definido em ICharacter.hpp.
// Necessario porque AMateria menciona ICharacter e vice-versa.
class ICharacter;

class AMateria
{
public:
	AMateria(void);
	AMateria(std::string const &type);
	AMateria(const AMateria &src);
	AMateria &operator=(const AMateria &rhs);
	virtual ~AMateria(void);

	// Retorna o tipo da materia ("ice" ou "cure")
	std::string const &getType(void) const;

	// Funcao virtual PURA: cada materia concreta cria uma copia de si mesma.
	virtual AMateria *clone(void) const = 0;

	// Usa a materia contra um personagem alvo.
	virtual void use(ICharacter &target);

protected:
	std::string _type;
};

#endif
