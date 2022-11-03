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
* Este archivo contiene el desarrollo de los métodos de la clase FiniteAutomata.
*/

#include "finiteAutomata.h"

// Constructor
FiniteAutomata::FiniteAutomata(Alphabet* alphabet, State* initialState) {
  alphabet_ = alphabet;
  initialState_ = initialState;
  if (!checkStatesAlphabet())
    throw "finite automata alphabet doesnt coincide with states transitions";
}

// Constructor por defecto
FiniteAutomata::FiniteAutomata() {
  alphabet_ = nullptr;
  initialState_ = nullptr;
}

// Destructor
FiniteAutomata::~FiniteAutomata() {}

// Getters
Alphabet*
FiniteAutomata::getAlphabet() {
  return alphabet_;
}

State*
FiniteAutomata::getInitialState() {
  return initialState_;
}

// Setters
void
FiniteAutomata::setInitialState(State* state) {
  initialState_ = state;
}

// Devuelve el conjunto de todos los estados del autómata
std::set<State*>
FiniteAutomata::getStates() {
  std::set<State*> visitedStates = {};
  std::set<State*> notVisitedStates = {initialState_};
  while (!notVisitedStates.empty()) {
    auto itr = notVisitedStates.begin();
    State* state = *itr;
    visitedStates.insert(state);
    notVisitedStates.erase(itr);
    for (auto el: state->getTransitions()) {
      if (visitedStates.find(el.second) == visitedStates.end()) {
        notVisitedStates.insert(el.second);
      }
    }
  }
  return visitedStates;
}

// Comprueba si los estados transitan unicamente con los simbolos definidos
// en el alfabeto del autómata
bool
FiniteAutomata::checkStatesAlphabet() {
    std::set<State*> states = getStates();
    for (State* state: states) {
      for (std::pair<Symbol, State*> transition: state->getTransitions()) {
        if (!alphabet_->checkSymbol(transition.first))
          return false;
      }
    }
  return true;
}

// Devuelve el conjunto de estados de aceptación
std::set<State*>
FiniteAutomata::getFinalStates() {
    std::set<State*> result;
    for (State* st: getStates()) {
       if (st->getFinal())
        result.insert(st);
    }
  return result;
}

// Comprueba si una cadena es reconocida por el autómata
bool
FiniteAutomata::checkChain(Chain chain) {
  if (alphabet_ == nullptr || !chain.belongsToAlphabet(Alphabet(alphabet_->getSymbols())))
    return false;
  std::set<State*> result = {initialState_};
  for (Symbol symbol: chain.getSymbols()) {
    std::set<State*> aux;
    for (State* state: result) {
      for (State* dest: state->at(symbol))
        aux.insert(dest);
    }
    result = aux;
  }

  for (State* state: result)
    if (state->getFinal())
      return true;

  return false;
}