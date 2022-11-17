/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Expresiones regulares
* @author Adrián González Galván
* @date 27/10/2022
*
* Este archivo contiene el desarrollo de los métodos declarados en "operation.h"
*/

#include "operation.h"

// Constructor
Operation::Operation(std::tuple<std::string, std::string> operands, std::string operation) {
  operands_ =  operands;
  operation_ = operation;
}

// Destructor
Operation::~Operation() {}

// Getters
std::tuple<std::string, std::string>
Operation::getOperands() {
  return operands_;
}

std::string
Operation::getOperation() {
  return operation_;
}

// Setters
void
Operation::setOperands(std::tuple<std::string, std::string> operands) {
  operands_ = operands;
}

void
Operation::setOperation(std::string operation) {
  operation_ = operation;
}

// Método de escritura
void
Operation::write(std::ostream& os) {
  os << operation_ << " " << std::get<0>(operands_) << " " << std::get<1>(operands_);
}

// Sobrecarga del operador '<'
bool
Operation::operator<(const Operation& o) const {
  return operation_ < o.operation_;
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, Operation& o) {
  o.write(os);
  return os;
}