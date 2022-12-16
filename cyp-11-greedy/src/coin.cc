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
* Este archivo contiene el desarrollo de los métodos de la clase Coin.
*/

#include "../include/coin.h"

/**
 * Constructor
 * @param name Coin name
 * @param int Coin value
*/
Coin::Coin(std::string name, int value): name_(name), value_(value) {}

/**
 * Destructor
*/
Coin::~Coin() {}

/**
 * Getter (name)
 * @return Coin name
*/
std::string
Coin::getName() {
  return name_;
}

/**
 * Getter (value)
 * @return Coin value
*/
int
Coin::getValue() {
  return value_;
}

/**
 * Setter (name)
 * @param string Coin name
*/
void
Coin::setName(std::string name) {
  name_ = name;
}

/**
 * Setter (value)
 * @param int Coin value
*/
void
Coin::setValue(int value) {
  value_ = value;
}

/**
 * Write method
 * @param ostream Write operator
*/
void
Coin::write(std::ostream& os) {
  os << name_;
}

/**
 * Overloading of write Coin operator
 * @param ostream Write operator
 * @param Coin Coin
*/
std::ostream& operator<<(std::ostream& os, Coin& coin) {
  coin.write(os);
  return os;
}