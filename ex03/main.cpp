// ============================================================================
// main.cpp (ex03)
// Testa o sistema de materias, personagens e fabrica.
// Inclui o main exato do subject + testes adicionais.
// ============================================================================

#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

int main(void)
{
	// === Teste exato do subject ===
	std::cout << "=== Teste do subject ===" << std::endl;

	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *me = new Character("me");

	AMateria *tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter *bob = new Character("bob");

	me->use(0, *bob);  // * shoots an ice bolt at bob *
	me->use(1, *bob);  // * heals bob's wounds *

	delete bob;
	delete me;
	delete src;

	// === Testes adicionais ===
	std::cout << std::endl << "=== Testes adicionais ===" << std::endl;

	// Teste: unequip nao deleta a materia
	std::cout << std::endl << "--- Unequip ---" << std::endl;
	Character *alice = new Character("Alice");
	AMateria *ice = new Ice();
	alice->equip(ice);
	alice->use(0, *alice);   // usa o ice
	alice->unequip(0);       // remove sem deletar
	alice->use(0, *alice);   // nao faz nada (slot vazio)
	delete alice;            // o destrutor cuida da materia no chao

	// Teste: inventario cheio
	std::cout << std::endl << "--- Inventario cheio ---" << std::endl;
	Character *charlie = new Character("Charlie");
	charlie->equip(new Ice());
	charlie->equip(new Cure());
	charlie->equip(new Ice());
	charlie->equip(new Cure());

	// 5a materia: inventario cheio, nao equipa
	AMateria *extra = new Ice();
	charlie->equip(extra);
	// extra nao foi equipada, precisamos deletar manualmente
	delete extra;

	charlie->use(0, *charlie);
	charlie->use(1, *charlie);
	charlie->use(2, *charlie);
	charlie->use(3, *charlie);
	delete charlie;

	// Teste: deep copy de Character
	std::cout << std::endl << "--- Deep copy de Character ---" << std::endl;
	Character original("Original");
	original.equip(new Ice());
	original.equip(new Cure());

	Character copiedChar(original);  // Construtor de copia (deep)
	copiedChar.use(0, original);  // Deve funcionar independente
	copiedChar.use(1, original);

	std::cout << std::endl << "--- Tipo desconhecido ---" << std::endl;
	MateriaSource factory;
	factory.learnMateria(new Ice());
	AMateria *unknown = factory.createMateria("fire");
	std::cout << "createMateria(\"fire\"): " << (unknown == NULL ? "NULL" : "found") << std::endl;

	std::cout << std::endl << "=== Fim ===" << std::endl;
	return 0;
}
