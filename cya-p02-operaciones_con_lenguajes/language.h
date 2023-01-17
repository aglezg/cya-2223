/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #02: Operaciones con lenguajes
* @author Adrián González Galván
* @date 13/10/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de un lenguaje.
*/

#pragma once

#include <iostream>
#include <set>
#include <cassert>

#include "chain.h"
#include "alphabet.h"

class Language {

  public:
    // Constructor & Destructor
    Language(Alphabet*, std::set<Chain> = {});
    ~Language();
  
    // Getters & Setters
    std::set<Chain> getChains();
    Alphabet* getAlphabet();
    void setChains(std::set<Chain> = {});
    void setAlphabet(Alphabet*);

    // Impresión por pantalla
    void print();

    // Operaciones básicas
    bool check(Chain chain);
    bool add(Chain chain);
    bool remove(Chain chain);

    // Operaciones
    Language lConcat(Language);
    Language lPow(unsigned);
    Language lUnion(Language);
    Language lIntersection(Language);
    Language lDifference(Language);
    Language lInverse();
    Language subStrings();

    // E/S
    void write(std::ostream& = std::cout);
    void read(std::istream& = std::cin);
  
  private:
    std::set<Chain> chains_;
    Alphabet* alphabet_;
    bool checkChains();
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Language&);
std::istream& operator>>(std::istream&, Language&);