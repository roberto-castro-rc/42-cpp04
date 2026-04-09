// ============================================================================
// IMateriaSource.hpp
// Interface IMateriaSource: fabrica de materias.
// learnMateria: aprende um "template" para clonar depois.
// createMateria: cria uma nova materia do tipo especificado.
// ============================================================================

#ifndef IMATERIASOURCE_HPP
# define IMATERIASOURCE_HPP

# include <string>

class AMateria;

class IMateriaSource
{
public:
	virtual ~IMateriaSource(void) {}

	virtual void learnMateria(AMateria *m) = 0;
	virtual AMateria *createMateria(std::string const &type) = 0;
};

#endif
