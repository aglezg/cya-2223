/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Simulación de autómatas finitos
* @author Adrián González Galván
* @date 10/11/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de una autómata finito.
*/

#pragma once

#include <iostream>
#include <cassert>
#include <bits/stdc++.h>
#include <list>

#include "chain.h"
#include "state.h"

class FiniteAutomata {
  public:
    // Constructor && Destructor
    FiniteAutomata(Alphabet*, State*);
    FiniteAutomata();
    ~FiniteAutomata();

    // Getters
    Alphabet* getAlphabet();
    State* getInitialState();

    // Setters
    void setInitialState(State*);

    // Otro
    std::set<State*> getStates();
    std::set<State*> getFinalStates();
    State* at(std::string);
    bool isEmpty();
    std::set<std::set<State*>> getEquivalents();

    // print
    void print();

    // Operaciones
    bool checkChain(Chain);

    // Sobrecarga de operadores
    State* operator[](std::string);

    // E/S
    void read(std::istream&);

  private:
    // Atributos
    Alphabet* alphabet_;
    State* initialState_;

    // Métodos privados
    bool checkStatesAlphabet();
  };

  // Sobrecarga de operadores de E/S
std::istream& operator>>(std::istream&, FiniteAutomata&);

// Encuentra el indice de un elemento de un vector
template<class T>
int getIndex(std::vector<T>, T);

// Transforma un string en una lista de string (separada por espacios)
std::list<std::string> stringToList(std::string);