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
* Este archivo contiene la declaración de la clase Variable, empleada para
* representar la estructura de una variable (tipo, nombre y valor).
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

    // Sobrecarga de operadores
    bool operator<(const Variable&) const;
  
  private:
    std::string type_;
    std::string name_;
    std::string value_;
};

// Sobrecarga del operador de escritura
std::ostream& operator<<(std::ostream&, Variable&);