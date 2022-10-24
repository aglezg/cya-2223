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

#include <iostream>
#include <set>
#include <utility>
#include <regex>
#include <vector>

#include "variable.h"

class CodeAnalyser {

  public:
    CodeAnalyser(std::istream&);
    ~CodeAnalyser();

    void write(std::ostream& = std::cout);
  
  private:
    //std::string description_;
    std::set<std::pair<int, std::string>> comments_;
    std::set<std::pair<int, Variable>> variables_;
    std::set<std::pair<int, std::string>> loops_;
    bool main_ = false;

    //bool isDescription(std::string);
    std::vector<std::string> isVariable(std::string);
    std::string isComment(std::string);
    std::string isLoop(std::string);
    bool isMain(std::string);
};