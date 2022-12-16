/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #08: Gramáticas en forma normal de Chomsky
* @author Adrián González Galván
* @date 24/11/2022
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación del algoritmo voraz de intercambio de monedas
*/

#include <iostream>
#include <set>
#include <list>

class GreedyChangeCoins {
  public:
    // Constructor && Destructor
    GreedyChangeCoins(std::set<int>);
    ~GreedyChangeCoins();

    // Getters
    std::set<int> getCoins();

    // Setters
    void setCoins(std::set<int>);

    // Calculate list of coins to use in a change
    std::list<int> getChange(double);
  private:
    std::set<int> coins_;
};