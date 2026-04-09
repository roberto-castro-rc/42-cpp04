// ============================================================================
// Character.hpp
// Classe concreta Character: implementa ICharacter.
//
// INVENTARIO: 4 slots (indices 0 a 3).
// equip: coloca materia no primeiro slot vazio.
// unequip: remove do slot SEM deletar a materia (ela fica "no chao").
// use: usa a materia do slot idx no alvo.
//
// DEEP COPY: ao copiar um Character, as materias sao clonadas (nao compartilhadas).
//
// GERENCIAMENTO DE MEMORIA:
// Guardamos materias "no chao" (unequipped) para deletar no destrutor,
// evitando leaks. Usamos um array auxiliar _floor[] para isso.
// ============================================================================

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"

class Character : public ICharacter
{
public:
	Character(void);
	Character(const std::string &name);
	Character(const Character &src);
	Character &operator=(const Character &rhs);
	virtual ~Character(void);

	virtual std::string const &getName(void) const;
	virtual void equip(AMateria *m);
	virtual void unequip(int idx);
	virtual void use(int idx, ICharacter &target);

private:
	std::string _name;
	AMateria *_inventory[4];     // 4 slots de materia
	AMateria *_floor[100];       // Materias deixadas no chao (para evitar leak)
	int _floorCount;

	// Limpa todo o inventario (usado no destrutor e antes de copiar)
	void _clearInventory(void);

	// Copia o inventario de outro Character (deep copy)
	void _copyInventory(const Character &src);
};

#endif
