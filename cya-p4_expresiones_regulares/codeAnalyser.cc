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

#include "codeAnalyser.h"

// Constructor
CodeAnalyser::CodeAnalyser(std::istream& is) {
  std::string reader = "";
  unsigned line = 1;

  while (!is.eof()) {
    getline(is, reader);
    std::cout << ">> " << reader << std::endl;

    if (!isVariable(reader).empty()) { // Es una variable
      std::vector<std::string> result = isVariable(reader);
      Variable var(result[0], result[1], result[2]);
      variables_.insert(std::pair<int, Variable>(line, var));
    } else if (!isComment(reader).empty()) { // Es un comentario
      comments_.insert(std::pair<int, std::string>(line, isComment(reader)));
    } else if (!isLoop(reader).empty()) { // Es un bucle
      loops_.insert(std::pair<int, std::string>(line, isLoop(reader)));
    } else if(isMain(reader)) { // Es la declaración del  main
      main_ = true;
    }
      
    line++;
  }

}

// Destructor
CodeAnalyser::~CodeAnalyser() {}


// Comprueba si una línea es el comienzo de una descripción
//bool
//CodeAnalyser::isDescription(std::string str) {
//  std::regex re("\\/\\")
//}

// Comprueba si una línea de código es la declaración de una variable
std::vector<std::string>
CodeAnalyser::isVariable(std::string str) {
  std::vector<std::string> result;
  std::regex re("\\s*(int|double)\\s([a-zA-Z]+\\d*)+(\\s=\\s(.*))?;$");
  std::smatch m;
  if (std::regex_match(str, re)) {
    std::smatch m;
    std::regex_search(str, m, re);
    result.push_back(m[1]); // type
    result.push_back(m[2]); // name
    result.push_back(m[4]); // value
  }
  return result;
}

// Comprueba si una línea de código es un comentario
std::string
CodeAnalyser::isComment(std::string str) {
  std::string result = "";
  std::regex re("\\s*\\/\\/.*");
  if (std::regex_match(str, re)) {
    result = str;
  }
  return result;
}

// Comprueba si una línea de código es la declaración de un bucle
std::string
CodeAnalyser::isLoop(std::string str) {
  std::string result = "";
  std::regex re("\\s*(for|while)\\s\\(.*\\)\\s\\{$");
  std::smatch m;
  if (std::regex_match(str, re)) {
    std::smatch m;
    std::regex_search(str, m, re);
    result = m[1];
  }
  return result;
}

// Comprueba si una línea de código es la función del main
bool
CodeAnalyser::isMain(std::string str) {
  std::regex re("^int\\smain\\s\\(.*\\)\\s\\{$");
  return bool(std::regex_match(str, re));
}

// Escritura
void
CodeAnalyser::write(std::ostream& os) {
  os << "VARIABLES:\n";
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
    os << "[Line " << element.first << "] " << element.second << "\n";
  }
}