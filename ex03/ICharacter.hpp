// ============================================================================
// ICharacter.hpp
// Interface ICharacter: define o contrato para personagens.
//
// CONCEITO: INTERFACE (classe abstrata pura)
// Todas as funcoes sao virtuais puras (= 0).
// Nenhuma implementacao — so define "o que" o personagem deve saber fazer.
// O destrutor virtual tem corpo vazio {} para permitir delete via interface.
// ============================================================================

#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include <string>

class AMateria;

class ICharacter
{
public:
	virtual ~ICharacter(void) {}

	virtual std::string const &getName(void) const = 0;
	virtual void equip(AMateria *m) = 0;
	virtual void unequip(int idx) = 0;
	virtual void use(int idx, ICharacter &target) = 0;
};

#endif
