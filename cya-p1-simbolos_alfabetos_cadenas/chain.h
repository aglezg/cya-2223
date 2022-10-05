/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #01: Símbolos, alfabetos y cadenas
* @author Adrián González Galván
* @date 06/10/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de una cadena.
*/

#pragma once

#include <iostream>

#include "alphabet.h"

const std::string kEmptyChain = "&";

class Chain {
  public:
    // Constructor & Destructor
    Chain(std::vector<Symbol>);
    Chain(std::vector<Symbol>, Alphabet*);
    ~Chain();

    // Getters
    std::vector<Symbol> getSymbols();
    Alphabet* getAlphabet();

    // Setters
    void setSymbols(std::vector<Symbol>);
    void setAlphabet(Alphabet*);

    // Impresión por pantalla
    void print();

    // Operaciones
    unsigned length();
    Chain inverse();
    std::vector<Chain> prefixes();
    std::vector<Chain> suffixes();
    std::vector<Chain> substrings();
    Chain concat(Chain);

    // Sobrecarga de operadores
    bool operator==(Chain&);

    // E/S
    void write(std::ostream&);
    void read(std::istream&);
    
  private:
    Alphabet* alphabet_;
    std::vector<Symbol> symbols_;
    bool checkChain();
};

// Operaciones sobrecargados de E/S
std::istream& operator>>(std::istream&, Chain&);
std::ostream& operator<<(std::ostream&, Chain&);

// Conversión de string a vector
std::vector<std::string> stringToVector(std::string);

// Comprueba si un determinado elemento pertenece a un vector
template <class T>
bool include(std::vector<T>, T);