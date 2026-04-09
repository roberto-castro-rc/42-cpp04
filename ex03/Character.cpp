// ============================================================================
// Character.cpp
// Implementacao do Character: inventario de 4 slots com deep copy.
// ============================================================================

#include "Character.hpp"

// ============================================================================
// Construtores / Destrutor
// ============================================================================

Character::Character(void) : _name("unnamed"), _floorCount(0)
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; i++)
		_floor[i] = NULL;
}

Character::Character(const std::string &name) : _name(name), _floorCount(0)
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; i++)
		_floor[i] = NULL;
}

// Construtor de copia: deep copy do inventario
Character::Character(const Character &src) : _name(src._name), _floorCount(0)
{
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; i++)
		_floor[i] = NULL;
	_copyInventory(src);
}

// Operador de atribuicao: limpa inventario atual, deep copy do novo
Character &Character::operator=(const Character &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		_clearInventory();
		_copyInventory(rhs);
	}
	return *this;
}

// Destrutor: deleta todas as materias (inventario + chao)
Character::~Character(void)
{
	_clearInventory();
	// Deletar materias no chao
	for (int i = 0; i < _floorCount; i++)
	{
		delete _floor[i];
		_floor[i] = NULL;
	}
}

// ============================================================================
// Funcoes da interface ICharacter
// ============================================================================

std::string const &Character::getName(void) const
{
	return _name;
}

// equip: coloca materia no primeiro slot vazio (0 a 3)
void Character::equip(AMateria *m)
{
	if (m == NULL)
		return;
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i] == NULL)
		{
			_inventory[i] = m;
			return;
		}
	}
	// Inventario cheio: nao faz nada
}

// unequip: remove do slot SEM deletar. Salva no chao para evitar leak.
void Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4 || _inventory[idx] == NULL)
		return;
	// Salvar no chao para deletar depois (evita leak)
	if (_floorCount < 100)
	{
		_floor[_floorCount] = _inventory[idx];
		_floorCount++;
	}
	_inventory[idx] = NULL;
}

// use: usa a materia do slot idx no alvo
void Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= 4 || _inventory[idx] == NULL)
		return;
	_inventory[idx]->use(target);
}

// ============================================================================
// Helpers privados
// ============================================================================

// Limpa o inventario (deleta todas as materias)
void Character::_clearInventory(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i] != NULL)
		{
			delete _inventory[i];
			_inventory[i] = NULL;
		}
	}
}

// Deep copy do inventario de outro Character
void Character::_copyInventory(const Character &src)
{
	for (int i = 0; i < 4; i++)
	{
		if (src._inventory[i] != NULL)
			_inventory[i] = src._inventory[i]->clone();
		else
			_inventory[i] = NULL;
	}
}
