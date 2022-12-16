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

#pragma once

#include <iostream>
#include <set>
#include <list>

#include "coinCollection.h"

class GreedyChangeCoins {
  public:
    // Constructor && Destructor
    GreedyChangeCoins(std::set<Coin>);
    ~GreedyChangeCoins();

    // Getters
    std::set<Coin> getCoins();

    // Setters
    void setCoins(std::set<Coin>);

    // Operations
    void add(Coin);

    // Calculate list of coins to use in a change
    CoinCollection getChange(unsigned);
  private:
    std::set<Coin> coins_;
};