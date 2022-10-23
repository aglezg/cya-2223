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
  std::string my_line = "";
  unsigned lineNumber = 1;

  while (!is.eof()) {
    getline(is, my_line);
    std::cout << ">> " << my_line << std::endl;

//    if (!isVariable(my_line).empty()) { // Es una variable

//    } else if (!isComment(my_line).empty()) { // Es un comentario

    /*} else*/ if (!isLoop(my_line).empty()) {
      loops_.insert(std::pair<int, std::string>(lineNumber, isLoop(my_line)));
    } else if(isMain(my_line)) {
      main_ = true;
    }
      
    lineNumber++;
  }

}

// Destructor
CodeAnalyser::~CodeAnalyser() {}

// Comprueba si una línea de código es la declaración de una variable
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
  os << "STATEMENTS:\n";
  for (auto element: loops_) {
    os << "[Line " << element.first << "] LOOP: " << element.second << "\n";
  }
  os << "\nMAIN:\n";
  if (main_)
    os << "True\n";
  else
    os << "False\n";
}