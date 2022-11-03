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
* Este archivo contiene el desarrollo de los métodos de la clase State.
*/

#include "state.h"

// Constructor
State::State(std::string name, std::set<std::pair<Symbol, State*>> transitions) {
  name_ = name;
  transitions_ = transitions;
}

// Destructor
State::~State() {
  transitions_.clear();
}

// Getters
std::string
State::getName() {
  return name_;
}

std::set<std::pair<Symbol, State*>>
State::getTransitions() {
  return transitions_;
}

// Setters
void
State::setName(std::string name) {
  name_ = name;
}

void
State::setTransitions(std::set<std::pair<Symbol, State*>> transitions) {
  transitions_ = transitions;
}


// Comprueba si una transición está presente en el estado
bool
State::checkTransition(std::pair<Symbol, State*> transition) {
  for (auto t: transitions_)
    if (t == transition)
      return true;
  return false;
}

// Añade una transición al estado
bool
State::addTransition(std::pair<Symbol, State*> transition) {
  if (checkTransition(transition))
    return false;
  transitions_.insert(transition);
  return true;
}

// Elimina una transición del estado
bool
State::deleteTransition(std::pair<Symbol, State*> transition) {
  if (!checkTransition(transition))
    return false;
  transitions_.erase(transition);
  return true;
}

// Metodo de indexación 'at'. Dado un simbolo devuelve el conjnto de estados
// resultante de la transición
std::set<State*>
State::at(Symbol symbol) {
  std::set<State*> result;
  for (auto el: transitions_)
    if (el.first == symbol)
      result.insert(el.second);
  return result;
}

// Sobrecarga del operador "[]"
std::set<State*>
State::operator[](Symbol symbol) {
  return at(symbol);
}

// Sobrecarga del operador "<"
bool
State::operator<(const State& state) const {
  return name_ < state.name_;
}

// Lectura
void
State::read(std::istream& is) {

}