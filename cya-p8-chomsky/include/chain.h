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
* a la representación de una cadena.
*/

#pragma once

#include <iostream>
#include <vector>

#include "alphabet.h"

class Chain {
  public:
    // Constructor & Destructor
    Chain(std::vector<Symbol>);
    Chain();
    ~Chain();

    // Getters
    std::vector<Symbol> getSymbols();

    // Setters
    void setSymbols(std::vector<Symbol>);

    // Impresión por pantalla
    void print();

    // Operaciones
    unsigned length();
    Chain inverse();
    std::set<Chain> prefixes();
    std::set<Chain> suffixes();
    std::set<Chain> substrings();
    Chain concat(Chain);
    bool isPalindrome();
    bool belongsToAlphabet(Alphabet);

    // Sobrecarga de operadores
    bool operator==(const Chain&) const;
    bool operator<(const Chain&) const;

    // E/S
    void write(std::ostream&);
    void read(std::istream&);

  private:
    std::vector<Symbol> symbols_;
};

// Operaciones sobrecargados de E/S
std::istream& operator>>(std::istream&, Chain&);
std::ostream& operator<<(std::ostream&, Chain&);

// Comprueba si un determinado elemento pertenece a un vector
template <class T>
bool include(std::vector<T>, T);

// Comprueba si una cadena es un número
bool is_number(const std::string& s);