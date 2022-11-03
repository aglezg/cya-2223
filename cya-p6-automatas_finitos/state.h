/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Simulación de autómatas finitos
* @author Adrián González Galván
* @date 10/10/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de un estado de un automata finito.
*/

#include <iostream>
#include <set>

#include "symbol.h"

class State {
  public:
    // Constructor & Destructor
    State(std::string, std::set<std::pair<Symbol, State*>> = {});
    ~State();

    // Getters
    std::string getName();
    std::set<std::pair<Symbol, State*>> getTransitions();
    
    // Setters
    void setName(std::string);
    void setTransitions(std::set<std::pair<Symbol, State*>>);

    // Operaciones
    bool checkTransition(std::pair<Symbol, State*>);
    bool addTransition(std::pair<Symbol, State*>);
    bool deleteTransition(std::pair<Symbol, State*>);
    bool isFinal();

    // at
    std::set<State*> at(Symbol);

    // Sobrecarga de operadores
    std::set<State*> operator[](Symbol);
    bool operator<(const State&) const;

    // E/S
    void read(std::istream& = std::cin);

  private:
    std::string name_;
    std::set<std::pair<Symbol, State*>> transitions_;
};