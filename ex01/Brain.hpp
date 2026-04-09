// ============================================================================
// Brain.hpp
// Classe Brain: contem um array de 100 std::string chamado "ideas".
//
// Dog e Cat terao um Brain* privado (ponteiro para Brain).
// Isso exige deep copy no construtor de copia e operador de atribuicao,
// caso contrario dois objetos compartilhariam o MESMO Brain.
// ============================================================================

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>
# include <iostream>

class Brain
{
public:
	Brain(void);
	Brain(const Brain &src);
	Brain &operator=(const Brain &rhs);
	~Brain(void);

	// Acesso a ideias individuais
	void setIdea(int index, const std::string &idea);
	std::string getIdea(int index) const;

	// Array publico de ideias (100 entradas)
	std::string ideas[100];
};

#endif
