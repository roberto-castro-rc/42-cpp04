# CPP Module 04

> École 42 — C++ Module 04
> **Tema**: Polimorfismo de Subtipo, Classes Abstratas e Interfaces

## Exercises

| Exercise | Name | Description |
|----------|------|-------------|
| ex00 | Polymorphism | Animal/Dog/Cat com `virtual`, WrongAnimal/WrongCat sem `virtual`. |
| ex01 | Brain | Dog e Cat com `Brain*`. Deep copy obrigatório. Array de Animals. |
| ex02 | Abstract class | Animal com `makeSound() = 0`. Não pode ser instanciado. |
| ex03 | Interface & recap | AMateria/Ice/Cure, ICharacter/Character, IMateriaSource/MateriaSource. |

## Compile

```bash
cd ex0X
make
```

## Run

```bash
./animal         # ex00
./animal_brain   # ex01
./abstract       # ex02
./materia        # ex03
```

## Test

```bash
bash run_tests.sh
```
