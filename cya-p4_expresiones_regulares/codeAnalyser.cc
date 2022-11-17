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
* Este archivo contiene el desarrollo de los métodos declarados en
* "codeAnalyser.h"
*/

#include "codeAnalyser.h"

// Constructor
CodeAnalyser::CodeAnalyser(std::istream& is) {
  read(is);
}

// Destructor
CodeAnalyser::~CodeAnalyser() {}

// Getters
std::set<std::pair<std::pair<int, int>, std::string>>
CodeAnalyser::getComments() {
  return comments_;
}

std::set<std::pair<int, Variable>>
CodeAnalyser::getVariables() {
  return variables_;
}

std::set<std::pair<int, std::string>>
CodeAnalyser::getLoops() {
  return loops_;
}

std::string
CodeAnalyser::getDescription() {
  for (auto element: comments_) {
    if (element.first.first == 1 && element.first.second != 0)
      return element.second;
  }
  return "";
}

// Comprueba, devolviendo el correspondiente atributo privado
// si el código analizado contiene un "main"
bool
CodeAnalyser::haveMain() {
  return main_;
}

// Comprueba si una línea es el comienzo de una descripción
bool
CodeAnalyser::isMultiLineComment(std::string str) {
  return bool(std::regex_match(str, kMultiCommentRE));
}

// Comprueba si una línea de código es la declaración de una variable
bool
CodeAnalyser::isVariable(std::string str) {
  return bool(std::regex_match(str, kVariableRE));
}

// Comprueba si una línea de código es un comentario
bool
CodeAnalyser::isComment(std::string str) {
  return bool(std::regex_match(str, kSingleCommentRE));
}

// Comprueba si una línea de código es la declaración de un bucle
bool
CodeAnalyser::isLoop(std::string str) {
  return bool(std::regex_match(str, kLoopRE));
}

// Comprueba si una línea de código es la función del main
bool
CodeAnalyser::isMain(std::string str) {
  return bool(std::regex_match(str, kMainRE));
}

// Comprueba si una línea de codigo es la declaración de una operacion (+|*)
bool
CodeAnalyser::isOperation(std::string str) {
  return bool(std::regex_match(str, kOperationRE));
}

// Lectura
void
CodeAnalyser::read(std::istream& is) {
  std::string reader = "";
  unsigned line = 1;

  while (!is.eof()) {
    getline(is, reader);
    if (isMultiLineComment(reader)) { // Es un comentario múltiple
      int startLine = line;
      std::string content = reader + "\n";
      do {
        getline(is, reader);
        content += reader + "\n";
        line++;
      } while (!bool(std::regex_match(reader, kMultiCommentCloseRE)));
      comments_.insert(std::pair<std::pair<int, int>,
        std::string>(std::pair<int, int>(startLine, line), content));
    } else if (isVariable(reader)) { // Es una variable
      std::smatch m;
      std::regex_search(reader, m, kVariableRE);
      variables_.insert(std::pair<int, Variable>(line, Variable(m[1], m[2], m[4])));
    } else if (isComment(reader)) { // Es un comentario
      comments_.insert(std::pair<std::pair<int, int>,
        std::string>(std::pair<int, int>(line, 0), reader));
    } else if (isLoop(reader)) { // Es un bucle
      std::smatch m;
      std::regex_search(reader, m, kLoopRE);
      loops_.insert(std::pair<int, std::string>(line, m[1]));
      if (isOperation(reader)) {
        std::regex_match(reader, m, kOperationRE);
        std::tuple<std::string, std::string> operands(m[1], m[3]);
        operations_.insert(std::pair<int, Operation>(line, Operation(operands, m[2])));
      }
    } else if (isMain(reader)) { // Es la declaración del  main
      main_ = true;
    } else if (isOperation(reader)) {
      std::smatch m;
      std::regex_search(reader, m, kOperationRE);
      std::tuple<std::string, std::string> operands(m[1], m[3]);
      operations_.insert(std::pair<int, Operation>(line, Operation(operands, m[2])));
    }
    line++;
  }
}

// Escritura
void
CodeAnalyser::write(std::ostream& os) {
  os << "DESCRIPTION:\n";
  os << getDescription();
  os << "\nVARIABLES:\n";
  for (auto element: variables_) {
    os << "[Line " << element.first << "] " << element.second << "\n"; 
  }
  os << "\nSTATEMENTS:\n";
  for (auto element: loops_) {
    os << "[Line " << element.first << "] LOOP: " << element.second << "\n";
  }
  os << "\nMAIN:\n";
  if (main_)
    os << "True\n";
  else
    os << "False\n";
  os << "\nCOMMENTS:\n";
  for (auto element: comments_) {
    if (element.first.second == 0) {
      os << "[Line " << element.first.first << "] " << element.second << "\n";
    } else {
      os << "[Line " << element.first.first << "-" << element.first.second << "]";
      if (element.second == getDescription()) {
         os << " DESCRIPTION\n";
      }
      else {
        os << "\n" << element.second;
      }
    }
  }
  os << "\nOPERATIONS:\n";
  for (auto element: operations_) {
    os << "[Line " << element.first << "]: " << element.second << "\n";
  }
}

// Sobrecarga del operador de escritura
std::ostream&
operator<<(std::ostream& os, CodeAnalyser& ca) {
  ca.write(os);
  return os;
}

// Sobrecarga del operador de lectura
std::istream&
operator>>(std::istream& is, CodeAnalyser& ca) {
  ca.read(is);
  return is;
}