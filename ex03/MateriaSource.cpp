// ============================================================================
// MateriaSource.cpp
// Implementacao da fabrica de materias.
// ============================================================================

#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void)
{
	for (int i = 0; i < 4; i++)
		_templates[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &src)
{
	for (int i = 0; i < 4; i++)
	{
		if (src._templates[i] != NULL)
			_templates[i] = src._templates[i]->clone();
		else
			_templates[i] = NULL;
	}
}

MateriaSource &MateriaSource::operator=(const MateriaSource &rhs)
{
	if (this != &rhs)
	{
		// Limpar templates atuais
		for (int i = 0; i < 4; i++)
		{
			delete _templates[i];
			_templates[i] = NULL;
		}
		// Deep copy dos novos
		for (int i = 0; i < 4; i++)
		{
			if (rhs._templates[i] != NULL)
				_templates[i] = rhs._templates[i]->clone();
			else
				_templates[i] = NULL;
		}
	}
	return *this;
}

MateriaSource::~MateriaSource(void)
{
	for (int i = 0; i < 4; i++)
	{
		delete _templates[i];
		_templates[i] = NULL;
	}
}

// learnMateria: guarda a materia passada no primeiro slot vazio.
// O subject diz "Copies the Materia passed as a parameter and stores it".
// Mas no main do subject faz src->learnMateria(new Ice()), entao a materia
// ja foi alocada com new — guardamos o ponteiro direto e assumimos ownership.
void MateriaSource::learnMateria(AMateria *m)
{
	if (m == NULL)
		return;
	for (int i = 0; i < 4; i++)
	{
		if (_templates[i] == NULL)
		{
			_templates[i] = m;
			return;
		}
	}
	// Se ja tem 4 templates, deleta a materia recebida (evita leak)
	delete m;
}

// createMateria: retorna um clone do template cujo tipo bate.
// Retorna NULL (0) se o tipo nao e conhecido.
AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; i++)
	{
		if (_templates[i] != NULL && _templates[i]->getType() == type)
			return _templates[i]->clone();
	}
	return NULL;
}
