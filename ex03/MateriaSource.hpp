// ============================================================================
// MateriaSource.hpp
// MateriaSource: fabrica de materias. Aprende "templates" e pode cria-los.
//
// learnMateria: guarda uma COPIA da materia passada (maximo 4).
// createMateria: retorna um clone da materia aprendida cujo tipo bate.
// ============================================================================

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"
# include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
public:
	MateriaSource(void);
	MateriaSource(const MateriaSource &src);
	MateriaSource &operator=(const MateriaSource &rhs);
	virtual ~MateriaSource(void);

	virtual void learnMateria(AMateria *m);
	virtual AMateria *createMateria(std::string const &type);

private:
	AMateria *_templates[4];  // Maximo 4 materias aprendidas
};

#endif
