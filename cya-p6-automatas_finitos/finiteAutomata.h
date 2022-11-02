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
* a la representación de una autómata finito.
*/

#include <iostream>

#include "chain.h";
#include "state.h";

class FiniteAutomata {
  public:
    // Constructor && Destructor
    FiniteAutomata(Alphabet, std::set<State> = {}, std::string = "");
    FiniteAutomata();
    ~FiniteAutomata();

    // Getters
    Alphabet getAlphabet();
    std::set<State> getStates();
    unsigned getInitialState();

    // Otro
    std::set<unsigned> finalStates();

    // Operaciones
    bool checkChain(Chain);

    // E/S
    void read(std::istream&);

  private:
    Alphabet alphabet_;
    std::string initialState_;
    std::set<State> states_;
  };