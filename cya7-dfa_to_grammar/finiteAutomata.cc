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
* Este archivo contiene el desarrollo de los métodos de la clase FiniteAutomata.
*/

#include "finiteAutomata.h"

// Constructor
FiniteAutomata::FiniteAutomata(Alphabet* alphabet, State* initialState) {
  if (!isEmpty()) {
    alphabet_ = alphabet;
    initialState_ = initialState;
    if (!checkStatesAlphabet())
      throw "finite automata alphabet doesnt coincide with states transitions";
  } else {
    alphabet_ = nullptr;
    initialState_ = nullptr;
  }
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
  if (!isEmpty()) {
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
        if (!alphabet_->checkSymbol(transition.first) && transition.first.getSymbol() != "~")
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

// Devuelve un puntero a un estado del autómata según su nombre
// el puntero es "nullptr" si dicho estado no existe
State*
FiniteAutomata::at(std::string name) {
  State* result = nullptr;
  for (State* st: getStates())
    if (st->getName() == name)
      result = st;
  return result;
}

// Comprueba si el automata finito reconoce el lenguaje vacío
bool
FiniteAutomata::isEmpty() {
  return alphabet_ == nullptr || initialState_ == nullptr;
}

std::set<std::set<State*>>
FiniteAutomata::getEquivalents() {
  std::set<State*> notVisitedStates = getStates();
  std::set<std::set<State*>> result = {};
  for (State* state: getStates()) {
    notVisitedStates.erase(state);
    for (State* state2: notVisitedStates) {
      State stateAux(state2->getName(), state2->getFinal(), state2->getTransitions());
      if (state->isEquivalent(stateAux)) {
        result.insert(std::set<State*>({state, state2}));
      }
    }
  }
  return result;
}

// Impresión por pantalla
void
FiniteAutomata::print() {
  if (!isEmpty()) {
    std::cout << "Alphabet: " << *getAlphabet() << "\n";
    std::cout << "S = " << initialState_->getName() << "\n";
  } else {
    std::cout << "Empty FA\n";
  }
}

// Comprueba si una cadena es reconocida por el autómata
bool
FiniteAutomata::checkChain(Chain chain) {
  if (isEmpty() || !chain.belongsToAlphabet(*alphabet_)) {
    return false;
  }
  std::set<State*> result = initialState_->at(Symbol("~"));
  result.insert(initialState_);
  for (Symbol symbol: chain.getSymbols()) {
    std::set<State*> aux;
    for (State* state: result) {
      for (State* dest: state->at(symbol))
        aux.insert(dest);
    }
    result = aux;
  }
  for (State* state: result) {
    if (state->getFinal())
      return true;
  }
  return false;
}

// Sobrecarga del operador "[]"
State*
FiniteAutomata::operator[](std::string name) {
  return at(name);
}

// Lectura
void
FiniteAutomata::read(std::istream& is) {
  Alphabet alphabet({Symbol("aux")});
  is >> alphabet; // Alfabeto
  alphabet_ = new Alphabet(alphabet);
  std::string nTransitions;
  is >> nTransitions; // Nº transiciones
  if (!is_number(nTransitions) || stoi(nTransitions) < 0)
    throw "number of transitions is NaN or negative ( " + nTransitions + ")";
  std::string initialStateName;
  is >> initialStateName; // Nombre del estado inicial
  std::vector<State*> vStates;
  std::vector<std::string> vTransitions;
  std::string reader = "";
  for (unsigned i = 0; i < stoi(nTransitions); i++) { // Lectura transiciones
    State stateAux;
    is >> stateAux;
    vStates.push_back(new State(stateAux.getName(), stateAux.getFinal()));
    getline(is, reader);
    vTransitions.push_back(reader);
  }

  for (unsigned i = 0; i < vTransitions.size(); i++) { // Establecemos transiciones
    std::vector<std::string> vStr = stringToVector(vTransitions[i]);
    if (!is_number(vStr[0]) || stoi(vStr[0]) != vStr.size() / 2) {
      throw "number of an especific state transitions is NaN or incorrect";
    }
    for (unsigned j = 1; j < vStr.size(); j+=2) {
      Symbol symbolAux(vStr[j]);
      if (!alphabet_->checkSymbol(symbolAux) && symbolAux.getSymbol() != "~") {
        throw "a symbol especified in a transition doesnt exist in the finite automatan";
      }
      State *stateAux = findState(vStates, vStr[j+1]);
      if (stateAux == nullptr)
        throw "a state especifed in a transition doesnt exist in the finite automatan";
      vStates[i]->addTransition(std::pair<Symbol, State*>(symbolAux, stateAux));
    }
  }

  initialState_ = findState(vStates, initialStateName); // Estado inicial
  if (initialState_ == nullptr && stoi(nTransitions) != 0)
    throw "initial state doesnt exist in the finite automatan";
}

// Sobrecarga del operador de lectura
std::istream&
operator>>(std::istream& is, FiniteAutomata& fa) {
  fa.read(is);
  return is;
}

// Dado un vector y un elemento, devuelve (si se encuentra) el índice de
// dicho elemento en el vector
template<class T>
int getIndex(std::vector<T> v, T K) {
  auto it = find(v.begin(), v.end(), K);
  if (it != v.end()) 
      return it - v.begin();
  else
    return -1;
}

// Transforma un string en una lista de strings, separadndolos por espacios
std::list<std::string>
stringToList(std::string str) {
  std::list<std::string> result = {};
  std::string aux;
  for (unsigned i = 0; i < str.size(); i++) {
    if (str[i] != ' ') {
      aux += str[i];
    } else {
      result.push_back(aux);
      aux = "";
    }
  }
  if (aux != "")
    result.push_back(aux);
  return result;
}