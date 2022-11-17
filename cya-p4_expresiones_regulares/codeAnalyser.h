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
* Este archivo contiene la declaración de la clase principal empleada en este
* programa. Esta analiza un archivo con código C++. 
*/

#include <iostream>
#include <set>
#include <utility>
#include <regex>
#include <vector>

#include "variable.h"
#include "operation.h"

const std::regex kVariableRE("\\s*(int|double)\\s([a-zA-Z]+\\d*)+(\\s=\\s(.*))?;$");
const std::regex kSingleCommentRE("\\s*\\/\\/.*");
const std::regex kMultiCommentRE("\\/\\*.*");
const std::regex kMultiCommentCloseRE(".*\\*\\/");
const std::regex kLoopRE("\\s*(for|while)\\s\\(.*\\)\\s\\{$");
const std::regex kMainRE("^int\\smain\\s\\(.*\\)\\s\\{$");
const std::regex kOperationRE(".*\\s=\\s(.*)\\s(\\+|\\*)\\s(.*)(\\)\\s\\{|;.*)$");

class CodeAnalyser {

  public:
    // Constructor && Destructor
    CodeAnalyser(std::istream&);
    ~CodeAnalyser();

    // Getters
    std::set<std::pair<std::pair<int, int>, std::string>> getComments();
    std::set<std::pair<int, Variable>> getVariables();
    std::set<std::pair<int, std::string>> getLoops();
    std::string getDescription();
    
    // Comprueba si existe un main
    bool haveMain();

    // Lectura && escritura
    void read(std::istream& = std::cin);
    void write(std::ostream& = std::cout);
  
  private:
    std::set<std::pair<std::pair<int, int>, std::string>> comments_;
    std::set<std::pair<int, Variable>> variables_;
    std::set<std::pair<int, std::string>> loops_;
    bool main_ = false;
    std::set<std::pair<int, Operation>> operations_;

    // Funciones privadas que determinan si una linea coincide con cierta
    // expresión regular
    bool isMultiLineComment(std::string);
    bool isVariable(std::string);
    bool isComment(std::string);
    bool isLoop(std::string);
    bool isMain(std::string);
    bool isOperation(std::string);
};

// Sobrecarga de operadores de E/S
std::ostream& operator<<(std::ostream&, CodeAnalyser&);
std::istream& operator>>(std::istream&, CodeAnalyser&);