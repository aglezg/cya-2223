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
* a la representación de una gramática regular por la derecha.
*/

#pragma once

#include <iostream>
#include "production.h"
#include "alphabet.h"
#include "chain.h"

class Grammar {
  public:
    // Constructor && Destructor
    Grammar(Symbol, Alphabet, Alphabet, std::set<Production> = {});
    Grammar();
    ~Grammar();

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

    // Comprobaciones
    bool isRightRegular();
    bool isLeftRegular();
    bool isRegular();

    // Modificación
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
std::istream& operator>>(std::istream&, Grammar&);
std::ostream& operator<<(std::ostream&, Grammar&);