/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #03: Calculadora de lenguajes formales
* @author Adrián González Galván
* @date 20/10/2022
*
* Este archivo contiene la declaración de la clase principal empleada en este
* programa. Esta analiza un archivo con código C++. 
*/

#include "variable.h"

// Constructor
Variable::Variable(std::string type, std::string name, std::string value) {
  type_ = type;
  name_ = name;
  value_ = value;
}

// Destructor
Variable::~Variable() {}

// Getters
std::string
Variable::getType() {
  return type_;
}

std::string
Variable::getName() {
  return name_;
}

std::string
Variable::getValue() {
  return value_;
}

// Setters
void
Variable::setType(std::string type) {
  type_ = type;
}

void
Variable::setName(std::string name) {
  name_ = name;
}

void
Variable::setValue(std::string value) {
  value_ = value;
}

// Método de escritura
void
Variable::write(std::ostream& os) {
  os << type_ << ": " << name_;
  if (value_ != "")
    os << " = " << value_;
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Variable& v) {
  v.write(os);
  return os;
}