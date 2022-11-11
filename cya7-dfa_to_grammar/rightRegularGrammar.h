/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #07: Gramática regular a partir de un DFA
* @author Adrián González Galván
* @date 17/11/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de una gramática regular.
*/

#pragma once

#include <iostream>
#include "production.h"
#include "alphabet.h"

class RightRegularGrammar {
  public:
    // Constructor && Destructor
    RightRegularGrammar(Symbol, Alphabet*, Alphabet*, std::set<Production> = {});
    ~RightRegularGrammar();

    // Getters
    Symbol getInitial();
    Alphabet* getTerminals();
    Alphabet* getNoTerminals();
    std::set<Production> getProductions();

    // Setters
    void setInitial(Symbol);
    void setTerminals(Alphabet*);
    void setNoTerminals(Alphabet*);
    void setProductions(std::set<Production>);

    // Operaciones
    bool checkProduction(Production);
    bool addProduction(Production);
    bool deleteProduction(Production);

    // print
    void print();

    // E/S
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
std::ostream& operator<<(std::ostream&, RightRegularGrammar&);