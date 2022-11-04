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
  if (isEmpty() || !chain.belongsToAlphabet(*alphabet_))
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
    throw "number of transitions is NaN or negative";
  std::string initialStateName;
  is >> initialStateName; // Nombre del estado inicial
  std::vector<State*> vStates; // Estados
  std::vector<std::string> vStatesNames; // Nombres de los etados
  std::vector<std::list<std::string>> vectorList; // Transiciones
  for (unsigned i = 0; i < stoi(nTransitions); i++) { 
    std::string reader = "";
    getline(is, reader);
    if (reader != "") {
      std::list<std::string> readerList = stringToList(reader);
      std::string stateName = readerList.front();
      readerList.pop_front();
      std::string isFinal = readerList.front();
      readerList.pop_front();
      if (isFinal != "0" && isFinal != "1")
        throw "acceptance option is not 0 or 1";
      State *stateAux = new State(stateName, stoi(isFinal));
      if (getIndex(vStates, stateAux) == -1) {
        vStates.push_back(stateAux);
        vStatesNames.push_back(stateName);
      } else {
        throw "a state is defined twice or more";
      }
      vectorList.push_back(readerList);
    } else {
      i--;
    }
  }

  for (unsigned i = 0; i < vectorList.size(); i++) {
    if(!is_number(vectorList[i].front()) || stoi(vectorList[i].front()) < 0)
      throw "number of an especific state transitions is NaN or negative";
    else {
      unsigned stateTransitions = stoi(vectorList[i].front());
      vectorList[i].pop_front();
      for (unsigned j = 0; j < stateTransitions; j++) {
        Symbol symbolAux(vectorList[i].front());
        vectorList[i].pop_front();
        if (!alphabet_->checkSymbol(symbolAux)) {
          throw "symbol defined in a transition doesnt exist in the finite automatan";
        }
        std::string stateName = vectorList[i].front();
        vectorList[i].pop_front();
        int index = getIndex(vStatesNames, stateName);
        if (index == -1)
          throw "state defined in a transition doesnt exist in the finite automatan";
        else
          vStates[i]->addTransition(std::pair<Symbol, State*>(symbolAux, vStates[index]));
      }
    }
  }

  initialState_ = nullptr; // Estado inicial
  if (stoi(nTransitions) != 0) {
    for (State* state: vStates) {
      if (state->getName() == initialStateName) {
        initialState_ = state;
        break;
      }
    }
    if (initialState_ == nullptr)
      throw "initial state doesnt exist";
  }
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