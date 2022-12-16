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

#include "coin.h"

class GreedyChangeCoins {
  public:
    // Constructor && Destructor
    GreedyChangeCoins(std::set<Coin>);
    ~GreedyChangeCoins();

    // Getters
    std::set<Coin> getCoins();

    // Setters
    void setCoins(std::set<Coin>);

    // Calculate list of coins to use in a change
    std::list<Coin> getChange(double);
  private:
    std::set<Coin> coins_;

    // Obtiene el mejor candidato (el de valor más grande sin pasarse de 'n')
    Coin getBestCandidate(int n);
};