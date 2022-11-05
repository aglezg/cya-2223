/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Simulación de autómatas finitos
* @author Adrián González Galván
* @date 11/10/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de un estado de un automata finito.
*/

#pragma once

#include <iostream>
#include <vector>
#include <set>

#include "symbol.h"

class State {
  public:
    // Constructor & Destructor
    State(std::string, bool = false, std::set<std::pair<Symbol, State*>> = {});
    State();
    ~State();

    // Getters
    std::string getName();
    std::set<std::pair<Symbol, State*>> getTransitions();
    bool getFinal();
    
    // Setters
    void setName(std::string);
    void setTransitions(std::set<std::pair<Symbol, State*>>);
    void setFinal(bool);

    // Operaciones
    bool checkTransition(std::pair<Symbol, State*>);
    bool addTransition(std::pair<Symbol, State*>);
    bool deleteTransition(std::pair<Symbol, State*>);

    // Lectura
    void read(std::istream&);

    // Print
    void print();

    // at
    std::set<State*> at(Symbol);

    // Sobrecarga de operadores
    std::set<State*> operator[](Symbol);
    bool operator<(const State&) const;
    bool operator==(const State&) const;

  private:
    std::string name_;
    bool finalState_;
    std::set<std::pair<Symbol, State*>> transitions_;
};

// Busca un estado en un vector de punteros de estados dado su nombre
State* findState(std::vector<State*>, std::string);

// Sobrecarga de los operadores de E/S
std::istream& operator>>(std::istream&, State&);

// Comprueba si una cadena es un número
bool is_number(const std::string&);