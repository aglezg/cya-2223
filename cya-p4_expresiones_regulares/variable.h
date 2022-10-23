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
#include <cassert>

class Variable {

  public:
    // Constructor && Destructor
    Variable(std::string, std::string, std::string = "");
    ~Variable();

    // Getters
    std::string getType();
    std::string getName();
    std::string getValue();

    // Setters
    void setType(std::string);
    void setName(std::string);
    void setValue(std::string);

    // Escritura
    void write(std::ostream&);
  
  private:
    std::string type_;
    std::string name_;
    std::string value_;
};

// Sobrecarga del operador de escritura
std::ostream& operator<<(std::ostream&, Variable&);