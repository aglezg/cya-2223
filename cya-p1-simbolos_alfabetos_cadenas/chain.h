/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #01: Símbolos, alfabetos y cadenas
* @author Adrián González Galván
* @date _/_/2022
*
* Este archivo ...
*/

#pragma once

#include <iostream>

#include "alphabet.h"

class Chain {
  public:
    Chain(std::vector<Symbol>);
    Chain(std::vector<Symbol>, Alphabet*);
    ~Chain();

    std::vector<Symbol> getSymbols();
    Alphabet* getAlphabet();

    void print();

    unsigned length();
    Chain inverse();
    std::vector<Chain> prefixes();
    std::vector<Chain> suffixes();

    Chain concat(Chain);

    void write(std::ostream&);
    void read(std::istream&);
    
  private:
    Alphabet* alphabet_;
    std::vector<Symbol> symbols_;
    bool checkChain();
};

std::istream& operator>>(std::istream&, Chain&);
std::ostream& operator<<(std::ostream&, Chain&);

std::vector<std::string> stringToVector(std::string);