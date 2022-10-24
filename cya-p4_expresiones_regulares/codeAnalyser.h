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

const std::regex kVariableRE("\\s*(int|double)\\s([a-zA-Z]+\\d*)+(\\s=\\s(.*))?;$");
const std::regex kSingleCommentRE("\\s*\\/\\/.*");
const std::regex kMultiCommentRE("\\/\\*.*");
const std::regex kMultiCommentCloseRE(".*\\*\\/");
const std::regex kLoopRE("\\s*(for|while)\\s\\(.*\\)\\s\\{$");
const std::regex kMainRE("^int\\smain\\s\\(.*\\)\\s\\{$");

class CodeAnalyser {

  public:
    CodeAnalyser(std::istream&);
    ~CodeAnalyser();

    std::string getDescription();

    void write(std::ostream& = std::cout);
  
  private:
    std::set<std::pair<std::pair<int, int>, std::string>> comments_;
    std::set<std::pair<int, Variable>> variables_;
    std::set<std::pair<int, std::string>> loops_;
    bool main_ = false;

    bool isMultiLineComment(std::string);
    bool isVariable(std::string);
    bool isComment(std::string);
    bool isLoop(std::string);
    bool isMain(std::string);
};