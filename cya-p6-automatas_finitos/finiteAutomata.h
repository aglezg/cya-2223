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
#include <cassert>

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

    // Operaciones
    bool checkChain(Chain);

    // E/S
    void read(std::istream&);

  private:
    // Atributos
    Alphabet* alphabet_;
    State* initialState_;

    // Métodos privados
    bool checkStatesAlphabet();
  };