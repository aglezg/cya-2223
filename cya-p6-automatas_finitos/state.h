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
    State(std::string, bool = false, std::set<std::pair<Symbol, std::string>> = {});
    ~State();

    // Getters
    std::string getName();
    std::set<std::pair<Symbol, std::string>> getTransitions();
    
    // Setters
    void setName(std::string);
    void setTransitions(std::set<std::pair<Symbol, std::string>>);
    void setFinal(bool);

    // Operaciones
    bool checkTransition(std::pair<Symbol, std::string>);
    bool addTransition(std::pair<Symbol, std::string>);
    bool deleteTransition(std::pair<Symbol, std::string>);
    bool isFinal();

    // at
    std::set<std::string> at(Symbol);

    // Sobrecarga de operadores
    std::set<std::string> operator[](Symbol);
    bool operator<(const State&) const;

    // E/S
    void read(std::istream& = std::cin);

  private:
    std::string name_;
    bool final_;
    std::set<std::pair<Symbol, std::string>> transitions_;
};