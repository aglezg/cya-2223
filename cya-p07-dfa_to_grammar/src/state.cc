/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #07: Gramática regular a partir de un DFA
* @author Adrián González Galván
* @date 17/11/2022
*
* Este archivo contiene el desarrollo de los métodos de la clase State.
*/

#include "../include/state.h"

// Constructor
State::State(std::string name, bool final, std::set<std::pair<Symbol, State*>> transitions) {
  name_ = name;
  finalState_ = final;
  transitions_ = transitions;
}

// Constructor por defecto
State::State() {
  name_ = "noName";
  finalState_ = false;
  transitions_ = {};
}

// Destructor
State::~State() {
  //transitions_.clear();
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

bool
State::getFinal() {
  return finalState_;
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

void
State::setFinal(bool final) {
  finalState_ = final;
}

// Impresión por pantalla
void
State::print() {
  std::cout << "State (" << getName() << "):\n";
  for (auto el: transitions_) {
    std::cout << " > (" << el.first << ") -> " <<el.second->getName();
    std::cout << "\n";
  }
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

// Comprueba si un estado es equivalente a otro
bool
State::isEquivalent(State state) {
  if (transitions_.size() != state.getTransitions().size()) {
    return false;
  }
  auto stateTransitions = state.getTransitions();
  auto ptr = stateTransitions.begin();
  for (auto tr: transitions_) {
    Symbol symbolAux = ptr->first;
    if (tr.first.getSymbol() != symbolAux.getSymbol() || tr.second != ptr->second) {
      return false;
    } else {
      ++ptr;
    }
  }
  return true;
}

// Comprueba si es un estado que corresponde a un DFA, esto es
// si no tiene transiciones que no consuman ningún símbolo y si
// no tiene diferentes transiciones que empleen el mismo símbolo
bool
State::isADFAState() {
  std::set<Symbol> visitedSymbols;
  for (auto tr: transitions_) {
    if (tr.first == Symbol(kEmptyTransitionSymbol)) {
      return false;
    }
    if (visitedSymbols.find(tr.first) != visitedSymbols.end()) {
      return false;
    }
    visitedSymbols.insert(tr.first);
  }
  return true;
}


// Metodo de indexación 'at'. Dado un simbolo devuelve el conjnto de estados
// resultante de la transición
std::set<State*>
State::at(Symbol symbol) {
  std::set<State*> visitedStates = {};
  std::set<State*> notVisitedStates = {this};
  std::set<State*> result = {};
  bool symbolUsed = false;
  while (!notVisitedStates.empty()) {
    auto itr = notVisitedStates.begin();
    State* state = *itr;
    visitedStates.insert(state);
    notVisitedStates.erase(state);
    for (auto tr: transitions_) {
      if (tr.first == symbol && !symbolUsed) {
        result.insert(tr.second);
        if (visitedStates.find(tr.second) == visitedStates.end()) {
          notVisitedStates.insert(tr.second);
        }
      } else if (tr.first == Symbol()) {
        if (visitedStates.find(tr.second) == visitedStates.end()) {
          notVisitedStates.insert(tr.second);
        }
      }
    }
  }
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

// Sobrecarga del operador "=="
bool
State::operator==(const State& state) const {
  return name_ == state.name_;
}

// Lectura
void
State::read(std::istream& is) {
  is >> name_;
  std::string isFinal;
  is >> isFinal;
  if (isFinal != "0" && isFinal != "1")
    throw "acceptance option is not 0 or 1";
  else
    finalState_ = stoi(isFinal);
  transitions_ = {};
}

// Busca un estado en un vector de punteros de estados dado su nombre
// Devuelve "NULL" si no se encontró
State* findState(std::vector<State*> v, std::string name) {
  for (State* state: v) {
    if (state != nullptr)
      if (state->getName() == name)
        return state;
  }
  return nullptr;
}


// Sobrecarga del operador de lectura
std::istream&
operator>>(std::istream& is, State& state) {
  state.read(is);
  return is;
}


// Comprueba si una cadena es un número
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}