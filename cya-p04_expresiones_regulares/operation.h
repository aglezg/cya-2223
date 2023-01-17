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
* Este archivo contiene la declaración de la clase Operacion, empleada para
* representar la estructura de una operacion (operando 1, 2 y operacion).
*/

#include <iostream>
#include <cassert>
#include <tuple>

class Operation {

  public:
    // Constructor && Destructor
    Operation(std::tuple<std::string, std::string>, std::string);
    ~Operation();

    // Getters
    std::tuple<std::string, std::string> getOperands();
    std::string getOperation();

    // Setters
    void setOperands(std::tuple<std::string, std::string>);
    void setOperation(std::string);

    // Escritura
    void write(std::ostream&);

    // Sobrecarga de operadores
    bool operator<(const Operation&) const;
  
  private:
    std::tuple<std::string, std::string> operands_;
    std::string operation_;
};

// Sobrecarga del operador de escritura
std::ostream& operator<<(std::ostream&, Operation&);