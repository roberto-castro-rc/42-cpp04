# Tutorial C++ Módulo 04 — Polimorfismo de Subtipo, Classes Abstratas e Interfaces

> Guia didático completo para entender os conceitos do Módulo 04.
> Este módulo é mais denso — cobre polimorfismo, virtual, abstrações e interfaces.
> Ideal para estudar antes da avaliação.

---

## Índice

1. [Polimorfismo de Subtipo](#1-polimorfismo-de-subtipo)
2. [A palavra-chave `virtual`](#2-a-palavra-chave-virtual)
3. [Destrutor Virtual](#3-destrutor-virtual)
4. [Por que `virtual` é necessário — O Caso WrongAnimal](#4-por-que-virtual-é-necessário--o-caso-wronganimal)
5. [Alocação Dinâmica e Gerenciamento de Memória](#5-alocação-dinâmica-e-gerenciamento-de-memória)
6. [Deep Copy vs Shallow Copy](#6-deep-copy-vs-shallow-copy)
7. [Classes Abstratas (Funções Virtuais Puras)](#7-classes-abstratas-funções-virtuais-puras)
8. [Interfaces em C++98](#8-interfaces-em-c98)
9. [O Padrão Prototype (clone)](#9-o-padrão-prototype-clone)
10. [Resumo de cada Exercício](#10-resumo-de-cada-exercício)
11. [Resumo para Avaliação](#11-resumo-para-avaliação)

---

## 1. Polimorfismo de Subtipo

### O que é?
Polimorfismo de subtipo permite tratar objetos de classes derivadas como se fossem da classe base, mas executando o comportamento correto de cada derivada.

```cpp
Animal *a = new Dog();   // Dog armazenado como Animal*
a->makeSound();          // Chama Dog::makeSound, não Animal::makeSound!
```

### Como funciona internamente?
Quando uma função é `virtual`, o C++ cria uma **vtable** (tabela de funções virtuais) para cada classe. Cada objeto tem um ponteiro oculto (**vptr**) que aponta para a vtable da sua classe real.

```
Animal* a = new Dog();

  Ponteiro a ──┐
               ▼
         ┌──────────┐       ┌─────────────────┐
         │  Dog obj  │──vptr──>│ Dog::makeSound  │  ← vtable do Dog
         │ _type     │       │ Dog::~Dog        │
         └──────────┘       └─────────────────┘
```

Quando chamamos `a->makeSound()`, o compilador consulta a vtable via vptr e chama a função correta.

### Exercício relacionado: ex00

---

## 2. A palavra-chave `virtual`

### Sem virtual (binding estático):
```cpp
class Animal {
public:
    void makeSound() const;  // SEM virtual
};

Animal *a = new Dog();
a->makeSound();  // Chama Animal::makeSound (errado!)
```
O compilador olha o TIPO DO PONTEIRO (Animal*) e chama a função do Animal.

### Com virtual (binding dinâmico):
```cpp
class Animal {
public:
    virtual void makeSound() const;  // COM virtual
};

Animal *a = new Dog();
a->makeSound();  // Chama Dog::makeSound (correto!)
```
O compilador olha o TIPO DO OBJETO REAL (Dog) e chama a função do Dog.

### Regra de ouro:
> Se uma função pode ser sobrescrita por derivadas E é chamada via ponteiro/referência de base, ela **DEVE** ser `virtual`.

### Exercício relacionado: ex00

---

## 3. Destrutor Virtual

### O problema sem destrutor virtual:
```cpp
class Animal {
public:
    ~Animal();  // SEM virtual
};

class Dog : public Animal {
    Brain *_brain;
public:
    ~Dog() { delete _brain; }  // NUNCA seria chamado!
};

Animal *a = new Dog();
delete a;  // Chama ~Animal() mas NÃO ~Dog()!
           // _brain nunca é deletado → MEMORY LEAK!
```

### A solução:
```cpp
class Animal {
public:
    virtual ~Animal();  // COM virtual → ~Dog() será chamado primeiro
};
```

### Regra universal:
> **SEMPRE** declare o destrutor como `virtual` em classes que serão usadas como base para herança. Não custa nada e previne leaks.

### Exercício relacionado: ex00, ex01

---

## 4. Por que `virtual` é necessário — O Caso WrongAnimal

O subject pede para implementar WrongAnimal e WrongCat **SEM** virtual em makeSound:

```cpp
class WrongAnimal {
public:
    void makeSound() const;  // SEM virtual (de propósito)
};

class WrongCat : public WrongAnimal {
public:
    void makeSound() const;  // Existe, mas sem virtual na base
};

WrongAnimal *w = new WrongCat();
w->makeSound();  // Chama WrongAnimal::makeSound, NÃO WrongCat::makeSound!
```

**Resultado**: o WrongCat faz o som genérico do WrongAnimal, não o miado.
Isso prova que **sem virtual, não existe polimorfismo** — o compilador usa o tipo do ponteiro, não o tipo do objeto.

### Exercício relacionado: ex00

---

## 5. Alocação Dinâmica e Gerenciamento de Memória

### new e delete
```cpp
Brain *b = new Brain();   // Aloca na HEAP (memória dinâmica)
// ... usa b ...
delete b;                 // Libera a memória — OBRIGATÓRIO!
```

### Por que usar ponteiros (Brain*) e não objetos diretos (Brain)?
- **Polimorfismo**: ponteiros de base podem apontar para objetos derivados
- **Vida útil controlada**: objetos na heap sobrevivem ao escopo da função
- **Composição flexível**: Dog pode ter ou não ter um Brain

### A regra do ownership:
> Quem faz `new`, é responsável pelo `delete`. Em Dog/Cat, o construtor faz `new Brain()`  e o destrutor faz `delete _brain`.

### Exercício relacionado: ex01, ex03

---

## 6. Deep Copy vs Shallow Copy

### Shallow Copy (raso) — PERIGOSO:
```cpp
Dog a;
Dog b = a;  // b._brain = a._brain  (MESMO ponteiro!)

// a e b compartilham o MESMO Brain:
//   a._brain ──┐
//              ├── Brain (mesmo objeto!)
//   b._brain ──┘
//
// Quando a é destruído: delete _brain ✓
// Quando b é destruído: delete _brain ✗ DOUBLE FREE! CRASH!
```

### Deep Copy (profundo) — CORRETO:
```cpp
Dog::Dog(const Dog &src) : Animal(src)
{
    _brain = new Brain(*src._brain);  // Cria um NOVO Brain com os mesmos dados
}

//   a._brain ─── Brain (objeto A)
//
//   b._brain ─── Brain (objeto B, cópia independente)
//
// Cada um tem seu próprio Brain. Sem problemas na destruição.
```

### Onde implementar deep copy:
1. **Construtor de cópia**: `Dog(const Dog &src)`
2. **Operador de atribuição**: `Dog &operator=(const Dog &rhs)`
   - Deletar o Brain antigo antes de criar o novo!
   - Verificar auto-atribuição (`this != &rhs`)

### Como testar:
```cpp
Dog original;
original.getBrain()->setIdea(0, "Idea A");

Dog copy(original);
original.getBrain()->setIdea(0, "CHANGED");

// Se deep copy: copy.getBrain()->getIdea(0) == "Idea A" (não mudou)
// Se shallow:   copy.getBrain()->getIdea(0) == "CHANGED" (bug!)
```

### Exercício relacionado: ex01, ex02

---

## 7. Classes Abstratas (Funções Virtuais Puras)

### O que é uma função virtual pura?
```cpp
virtual void makeSound(void) const = 0;  // O "= 0" torna a função PURA
```

### O que ela causa?
- A classe que a declara se torna **ABSTRATA**
- Objetos dessa classe **NÃO PODEM ser criados** diretamente
- Classes derivadas são **OBRIGADAS** a implementá-la

### Diagrama:
```
         Animal (ABSTRATA)         ← NÃO pode: Animal a;
        makeSound() = 0;
       /                \
    Dog                  Cat       ← PODEM: Dog d; Cat c;
    makeSound() { Woof }  makeSound() { Meow }
```

### Por que usar?
- Faz sentido criar um "Animal" genérico? **NÃO!** Que som faria?
- A classe abstrata define o **contrato**: "todo Animal DEVE ter makeSound"
- As derivadas concretas fornecem a **implementação** real

### Exercício relacionado: ex02

---

## 8. Interfaces em C++98

### O conceito
C++98 não tem a palavra-chave `interface` (Java/C# têm). Mas usamos **classes abstratas puras** como interfaces:

```cpp
class ICharacter
{
public:
    virtual ~ICharacter() {}                                    // destrutor virtual
    virtual std::string const &getName() const = 0;             // pura
    virtual void equip(AMateria *m) = 0;                        // pura
    virtual void unequip(int idx) = 0;                          // pura
    virtual void use(int idx, ICharacter &target) = 0;          // pura
};
```

### Características de uma interface:
| Aspecto | Interface | Classe abstrata | Classe concreta |
|---------|-----------|-----------------|-----------------|
| Tem funções puras? | Todas | Pelo menos 1 | Nenhuma |
| Tem atributos? | Não (geralmente) | Pode ter | Sim |
| Instanciável? | Não | Não | Sim |
| Prefixo convencional | `I` (ICharacter) | `A` (AMateria) | Nenhum (Character) |

### Hierarquia do ex03:
```
  ICharacter ─────── IMateriaSource
  (interface)         (interface)
      |                    |
  Character           MateriaSource
  (concreto)           (concreto)

  AMateria
  (abstrata)
   /      \
  Ice    Cure
```

### Exercício relacionado: ex03

---

## 9. O Padrão Prototype (clone)

### O problema:
Se você tem um ponteiro `AMateria*`, você não sabe se é Ice ou Cure. Como criar uma cópia?

```cpp
AMateria *m = ???;       // Pode ser Ice, Cure, ou qualquer tipo futuro
AMateria *copia = ???;   // Como copiar sem saber o tipo?
```

### A solução — Padrão Prototype:
```cpp
class AMateria {
public:
    virtual AMateria *clone() const = 0;  // Cada derivada sabe se clonar
};

class Ice : public AMateria {
    AMateria *clone() const {
        return new Ice(*this);   // Cria cópia de si mesmo
    }
};
```

### Uso:
```cpp
AMateria *m = ice_ptr;
AMateria *copia = m->clone();  // Funciona! Retorna new Ice, mesmo via AMateria*
```

O MateriaSource usa esse padrão: guarda "templates" e usa `clone()` para criar novos.

### Exercício relacionado: ex03

---

## 10. Resumo de cada Exercício

### ex00 — Polymorphism
- **Foco**: entender `virtual` e polimorfismo
- **Classes**: Animal (base), Dog, Cat (derivadas), WrongAnimal, WrongCat
- **Ponto-chave**: com `virtual`, `Animal* a = new Dog(); a->makeSound();` chama Dog::makeSound. Sem `virtual`, chama Animal::makeSound.
- **Arquivos**: Animal.hpp/cpp, Dog.hpp/cpp, Cat.hpp/cpp, WrongAnimal.hpp/cpp, WrongCat.hpp/cpp, main.cpp

### ex01 — I don't want to set the world on fire
- **Foco**: gerenciamento de memória com `new`/`delete`, deep copy
- **Classes**: Animal, Dog, Cat (com Brain*), Brain (100 ideias)
- **Ponto-chave**: Dog e Cat criam Brain com `new` no construtor e `delete` no destrutor. Cópia deve ser **deep** (novo Brain, não compartilhado).
- **Teste crítico**: array de Animal*, metade Dog, metade Cat, deletar como Animal* — destrutor virtual garante chamada correta.

### ex02 — Abstract class
- **Foco**: funções virtuais puras, classes abstratas
- **Mudança**: `makeSound` passa a ser `= 0` em Animal
- **Ponto-chave**: `Animal a;` não compila mais. Dog e Cat continuam funcionando. Tudo igual ao ex01, só Animal é abstrato agora.

### ex03 — Interface & recap
- **Foco**: interfaces (ICharacter, IMateriaSource), padrão Prototype (clone), composição
- **Classes**: AMateria (abstrata), Ice, Cure, ICharacter (interface), Character, IMateriaSource (interface), MateriaSource
- **Pontos-chave**:
  - Character: inventário de 4 slots, equip/unequip/use
  - `unequip` NÃO deleta a materia (salva "no chão" para evitar leak)
  - `clone()` permite criar cópias sem saber o tipo concreto
  - Deep copy de Character clona todas as materias do inventário
  - MateriaSource: fábrica que aprende templates e cria cópias

---

## 11. Resumo para Avaliação

### ex00: "O que é polimorfismo de subtipo?"
> É a capacidade de tratar objetos derivados como se fossem da classe base, mas executando o comportamento da derivada. Em C++, isso requer a palavra-chave `virtual`.

### ex00: "O que faz a palavra 'virtual'?"
> `virtual` ativa o **binding dinâmico** (late binding). Sem virtual, o compilador decide qual função chamar em tempo de compilação baseado no tipo do ponteiro. Com virtual, a decisão é feita em tempo de execução baseada no tipo real do objeto, usando a vtable.

### ex00: "Por que WrongCat não mia?"
> Porque `WrongAnimal::makeSound` não é virtual. Quando chamamos `wrongAnimal->makeSound()`, o compilador usa o tipo do ponteiro (WrongAnimal*), não o tipo do objeto (WrongCat). Resultado: chama WrongAnimal::makeSound.

### ex01: "Por que o destrutor de Animal deve ser virtual?"
> Para que ao fazer `delete animalPtr` (onde animalPtr aponta para um Dog), o destrutor do Dog seja chamado primeiro, deletando o Brain. Sem virtual, só ~Animal seria chamado, causando leak nos Brains de Dog e Cat.

### ex01: "O que é deep copy e por que é necessário aqui?"
> Deep copy cria uma cópia independente dos dados apontados por ponteiros. Dog e Cat têm `Brain*`. Se copiarmos apenas o ponteiro (shallow copy), dois objetos compartilham o mesmo Brain, causando double free na destruição. Com deep copy, cada objeto tem seu próprio Brain.

### ex02: "O que é uma classe abstrata?"
> Uma classe com pelo menos uma função virtual pura (`= 0`). Não pode ser instanciada diretamente. Serve como contrato: obriga as derivadas a implementarem as funções puras. Animal com `makeSound() = 0` é abstrato — só Dog e Cat podem ser criados.

### ex02: "Qual a diferença entre virtual e virtual pura?"
> `virtual void f()` — pode ter implementação, classes derivadas podem sobrescrever, classe base pode ser instanciada.
> `virtual void f() = 0` — SEM implementação, derivadas DEVEM implementar, classe base NÃO pode ser instanciada.

### ex03: "O que é uma interface em C++?"
> Uma classe abstrata pura — TODAS as funções são virtuais puras, sem atributos. Define apenas "o que" fazer, não "como". ICharacter e IMateriaSource são interfaces. Prefixo `I` é convenção.

### ex03: "O que é o padrão Prototype?"
> Um design pattern onde objetos sabem se clonar. `clone()` retorna `new Tipo(*this)`. Permite copiar objetos sem saber seu tipo concreto — essencial quando trabalhamos com ponteiros de base (AMateria*).

### ex03: "Por que unequip NÃO deleta a matéria?"
> Porque o subject diz explicitamente. A matéria fica "no chão". No nosso design, salvamos o ponteiro num array auxiliar (_floor) para deletar no destrutor do Character, evitando leaks.

### ex03: "O que acontece ao equipar uma 5ª matéria?"
> Nada. O inventário tem 4 slots fixos. Se todos estão ocupados, equip() simplesmente retorna sem fazer nada.

---

> **Dica para avaliação**: este módulo é conceitual. O avaliador pode pedir para explicar vtable, binding dinâmico, ou adicionar uma nova matéria. Entenda os mecanismos — não decore código.
