#!/bin/bash
# ============================================================================
# run_tests.sh — Tester automatizado para o Modulo 04 de C++
# Polimorfismo, Classes Abstratas e Interfaces
# ============================================================================

GREEN="\033[0;32m"; RED="\033[0;31m"; YELLOW="\033[0;33m"; CYAN="\033[0;36m"; NC="\033[0m"
PASS=0; FAIL=0
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

pass() { echo -e "  ${GREEN}✅ PASS${NC}: $1"; PASS=$((PASS + 1)); }
fail() { echo -e "  ${RED}❌ FAIL${NC}: $1"; FAIL=$((FAIL + 1)); }
info() { echo -e "${CYAN}$1${NC}"; }

HAS_VALGRIND=0; command -v valgrind &> /dev/null && HAS_VALGRIND=1
check_leaks() {
    if [ $HAS_VALGRIND -eq 1 ]; then
        local output
        output=$(valgrind --leak-check=full --error-exitcode=42 "$@" 2>&1)
        if echo "$output" | grep -q "no leaks are possible\|All heap blocks were freed"; then
            pass "Sem vazamento de memoria"
        else
            fail "Possivel vazamento de memoria"
        fi
    fi
}

# ============================================================================
# EX00 - Polimorfismo (Animal com virtual vs WrongAnimal sem virtual)
# ============================================================================
info "\n══════════════════════════════════════════"
info "  EX00 - Polimorfismo (virtual vs sem virtual)"
info "══════════════════════════════════════════"

make -C "$SCRIPT_DIR/ex00" re > /dev/null 2>&1
[ $? -eq 0 ] && pass "Compilacao" || fail "Compilacao"

OUTPUT=$("$SCRIPT_DIR/ex00/animal" 2>&1)

# Construtores/destrutores com mensagens especificas
echo "$OUTPUT" | grep -q "Animal default constructor called" \
    && pass "Animal constructor msg" || fail "Animal constructor msg"
echo "$OUTPUT" | grep -q "Dog default constructor called" \
    && pass "Dog constructor msg" || fail "Dog constructor msg"
echo "$OUTPUT" | grep -q "Cat default constructor called" \
    && pass "Cat constructor msg" || fail "Cat constructor msg"
echo "$OUTPUT" | grep -q "Animal destructor called" \
    && pass "Animal destructor msg" || fail "Animal destructor msg"
echo "$OUTPUT" | grep -q "Dog destructor called" \
    && pass "Dog destructor msg" || fail "Dog destructor msg"
echo "$OUTPUT" | grep -q "Cat destructor called" \
    && pass "Cat destructor msg" || fail "Cat destructor msg"

# getType retorna tipo correto
echo "$OUTPUT" | grep -q "Dog$" \
    && pass "Dog type = Dog" || fail "Dog type = Dog"
echo "$OUTPUT" | grep -q "Cat$" \
    && pass "Cat type = Cat" || fail "Cat type = Cat"

# Polimorfismo COM virtual: sons corretos via ponteiro Animal*
echo "$OUTPUT" | grep -q "Meow" \
    && pass "Cat faz Meow (virtual funciona)" || fail "Cat faz Meow"
echo "$OUTPUT" | grep -q "Woof" \
    && pass "Dog faz Woof (virtual funciona)" || fail "Dog faz Woof"

# WrongAnimal SEM virtual: WrongCat faz som do WrongAnimal
WRONG_SOUNDS=$(echo "$OUTPUT" | grep -A2 "via ponteiro WrongAnimal" | grep -c "Wrong generic animal sound")
[ "$WRONG_SOUNDS" -ge 2 ] \
    && pass "WrongCat faz som do WrongAnimal (sem virtual)" \
    || fail "WrongCat deveria fazer som do WrongAnimal"

check_leaks "$SCRIPT_DIR/ex00/animal"

# ============================================================================
# EX01 - Brain (deep copy)
# ============================================================================
info "\n══════════════════════════════════════════"
info "  EX01 - Brain (new/delete, deep copy)"
info "══════════════════════════════════════════"

make -C "$SCRIPT_DIR/ex01" re > /dev/null 2>&1
[ $? -eq 0 ] && pass "Compilacao" || fail "Compilacao"

OUTPUT=$("$SCRIPT_DIR/ex01/animal_brain" 2>&1)

# Brain criado e destruido
echo "$OUTPUT" | grep -q "Brain default constructor called" \
    && pass "Brain constructor chamado" || fail "Brain constructor chamado"
echo "$OUTPUT" | grep -q "Brain destructor called" \
    && pass "Brain destructor chamado" || fail "Brain destructor chamado"

# Deep copy: ideias copiadas corretamente
echo "$OUTPUT" | grep "Copia idea 0" | grep -q "Chase the cat!" \
    && pass "Deep copy preserva ideia original" || fail "Deep copy preserva ideia"

# Deep copy: alterar original NAO afeta copia
echo "$OUTPUT" | grep "Copia idea 0:" | grep -q "Chase the cat!" \
    && pass "Alterar original nao afeta copia" || fail "Alterar original afeta copia"

# Brain copy constructor chamado (deep copy)
echo "$OUTPUT" | grep -q "Brain copy constructor called" \
    && pass "Brain copy constructor (deep copy)" || fail "Brain copy constructor"

# Enderecos dos Brains sao diferentes
ORIGINAL_BRAIN=$(echo "$OUTPUT" | grep "Original Brain:" | awk '{print $3}')
COPY_BRAIN=$(echo "$OUTPUT" | grep "Copia Brain:" | awk '{print $3}')
if [ -n "$ORIGINAL_BRAIN" ] && [ -n "$COPY_BRAIN" ] && [ "$ORIGINAL_BRAIN" != "$COPY_BRAIN" ]; then
    pass "Enderecos dos Brains sao diferentes"
else
    fail "Enderecos dos Brains deveriam ser diferentes"
fi

# Destruindo por Animal* chama destrutor correto
DOG_DESTR=$(echo "$OUTPUT" | grep -c "Dog destructor called")
[ "$DOG_DESTR" -ge 2 ] \
    && pass "Dog destructor chamado (delete via Animal*)" \
    || fail "Dog destructor via Animal*"

check_leaks "$SCRIPT_DIR/ex01/animal_brain"

# ============================================================================
# EX02 - Classe Abstrata
# ============================================================================
info "\n══════════════════════════════════════════"
info "  EX02 - Classe Abstrata (Animal nao instanciavel)"
info "══════════════════════════════════════════"

make -C "$SCRIPT_DIR/ex02" re > /dev/null 2>&1
[ $? -eq 0 ] && pass "Compilacao" || fail "Compilacao"

# Teste: Animal nao pode ser instanciado diretamente
ABSTRACT_TEST=$(cat << 'EOF'
#include "Animal.hpp"
int main() { Animal a; return 0; }
EOF
)
echo "$ABSTRACT_TEST" > "$SCRIPT_DIR/ex02/_test_abstract.cpp"
COMPILE_OUTPUT=$(c++ -Wall -Wextra -Werror -std=c++98 \
    -c "$SCRIPT_DIR/ex02/_test_abstract.cpp" \
    -o "$SCRIPT_DIR/ex02/_test_abstract.o" \
    -I"$SCRIPT_DIR/ex02" 2>&1)
if [ $? -ne 0 ]; then
    pass "Animal nao pode ser instanciado (classe abstrata)"
else
    fail "Animal deveria ser abstrato (nao instanciavel)"
fi
rm -f "$SCRIPT_DIR/ex02/_test_abstract.cpp" "$SCRIPT_DIR/ex02/_test_abstract.o"

OUTPUT=$("$SCRIPT_DIR/ex02/abstract" 2>&1)

# Dog e Cat ainda funcionam normalmente
echo "$OUTPUT" | grep -q "Woof" \
    && pass "Dog funciona normalmente" || fail "Dog funciona"
echo "$OUTPUT" | grep -q "Meow" \
    && pass "Cat funciona normalmente" || fail "Cat funciona"

# Deep copy ainda funciona
echo "$OUTPUT" | grep "Copia:" | grep -q "I love bones!" \
    && pass "Deep copy ainda funciona" || fail "Deep copy"

check_leaks "$SCRIPT_DIR/ex02/abstract"

# ============================================================================
# EX03 - Interface & recap (AMateria, Character, MateriaSource)
# ============================================================================
info "\n══════════════════════════════════════════"
info "  EX03 - Interface & Recap (Materia system)"
info "══════════════════════════════════════════"

make -C "$SCRIPT_DIR/ex03" re > /dev/null 2>&1
[ $? -eq 0 ] && pass "Compilacao" || fail "Compilacao"

OUTPUT=$("$SCRIPT_DIR/ex03/materia" 2>&1)

# Saida exata do subject
echo "$OUTPUT" | grep -q "shoots an ice bolt at bob" \
    && pass "Ice::use correto (ice bolt at bob)" || fail "Ice::use"
echo "$OUTPUT" | grep -q "heals bob's wounds" \
    && pass "Cure::use correto (heals bob)" || fail "Cure::use"

# Unequip nao deleta (usa depois de unequip nao faz nada)
echo "$OUTPUT" | grep -q "shoots an ice bolt at Alice" \
    && pass "Use antes de unequip funciona" || fail "Use antes de unequip"

# Inventario cheio (4 materias equipadas, todas usaveis)
echo "$OUTPUT" | grep -q "shoots an ice bolt at Charlie" \
    && pass "Inventario cheio: ice funciona" || fail "Inventario cheio ice"
echo "$OUTPUT" | grep -q "heals Charlie's wounds" \
    && pass "Inventario cheio: cure funciona" || fail "Inventario cheio cure"

# Deep copy de Character
echo "$OUTPUT" | grep -q "shoots an ice bolt at Original" \
    && pass "Deep copy: Character clonado usa ice" || fail "Deep copy Character"
echo "$OUTPUT" | grep -q "heals Original's wounds" \
    && pass "Deep copy: Character clonado usa cure" || fail "Deep copy Character cure"

# Tipo desconhecido retorna NULL
echo "$OUTPUT" | grep -q 'createMateria("fire"): NULL' \
    && pass "Tipo desconhecido retorna NULL" || fail "Tipo desconhecido"

check_leaks "$SCRIPT_DIR/ex03/materia"

# ============================================================================
# Limpeza
# ============================================================================
info "\n══════════════════════════════════════════"
info "  Limpeza (make fclean)"
info "══════════════════════════════════════════"
for ex in ex00 ex01 ex02 ex03; do
    make -C "$SCRIPT_DIR/$ex" fclean > /dev/null 2>&1
done
echo -e "  Todos limpos."

# ============================================================================
# Resumo
# ============================================================================
info "\n══════════════════════════════════════════"
TOTAL=$((PASS + FAIL))
echo -e "  ${GREEN}✅ PASS: $PASS${NC}  |  ${RED}❌ FAIL: $FAIL${NC}  |  Total: $TOTAL"
if [ $FAIL -eq 0 ]; then
    echo -e "  ${GREEN}🎉 Todos os testes passaram!${NC}"
else
    echo -e "  ${YELLOW}⚠️  $FAIL teste(s) falharam. Revise acima.${NC}"
fi
info "══════════════════════════════════════════\n"
exit $FAIL
