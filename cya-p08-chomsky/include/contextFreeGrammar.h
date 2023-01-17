/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #08: Gramáticas en forma normal de Chomsky
* @author Adrián González Galván
* @date 24/11/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de una gramática independiente del contexto.
*/

#pragma once

#include <iostream>
#include "production.h"
#include "alphabet.h"
#include "chain.h"

const std::vector<std::string> kCapitalLetters = {"A", "B", "C", "D", "E", "F",
  "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
  "V", "W", "X", "Y", "Z"};

class ContextFreeGrammar {
  public:
    // Constructor && Destructor
    ContextFreeGrammar(Symbol, Alphabet, Alphabet, std::set<Production> = {});
    ContextFreeGrammar();
    ~ContextFreeGrammar();

    // Getters
    Symbol getInitial();
    Alphabet getTerminals();
    Alphabet getNoTerminals();
    std::set<Production> getProductions();

    // Setters
    void setInitial(Symbol);
    void setTerminals(Alphabet);
    void setNoTerminals(Alphabet);
    void setProductions(std::set<Production>);

    // Operaciones
    bool existProduction(Production);
    bool addProduction(Production);
    bool deleteProduction(Production);
    bool existNonTerminal(Symbol);
    bool addNonTerminal(Symbol);
    bool deleteNonTerminal(Symbol);
    ContextFreeGrammar toChomsky();

    // Comprobaciones
    bool isRightRegular();
    bool isLeftRegular();
    bool isRegular();
    bool hasEmptyProductions();
    bool hasUnitProductions();

    // Compración de cadenas
    bool checkChain(Chain);

    // print
    void print();

    // E/S
    void read(std::istream& = std::cin);
    void write(std::ostream& = std::cout);
    
  private:
  Symbol initial_;
  Alphabet* terminals_;
  Alphabet* noTerminals_;
  std::set<Production> productions_;

  bool checkInitial();
  bool checkProductions();
};

// Sobrecarga de los operadores de E/S
std::istream& operator>>(std::istream&, ContextFreeGrammar&);
std::ostream& operator<<(std::ostream&, ContextFreeGrammar&);