/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #11: Algoritmos Voraces (Greedy). Cambio de monedas
* @author Adrián González Galván
* @date 22/12/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de una moneda
*/

#include <iostream>

class Coin {
  public:
    // Constructor && Destructor
    Coin(std::string, int);
    ~Coin();

    // Getters
    std::string getName();
    int getValue();

    // Setters
    void setName(std::string);
    void setValue(int);

    // Operators overloading
    bool operator<(const Coin&) const;
    bool operator==(const Coin&);
    Coin& operator=(Coin);


    // W/R
    void write(std::ostream&);

  private:
    std::string name_;
    int value_;
};

// Overloading of write operator
std::ostream& operator<<(std::ostream&, Coin&);