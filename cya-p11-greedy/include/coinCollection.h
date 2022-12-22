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
* a la representación de una colección de monedas
*/

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "coin.h"

class CoinCollection {
  public:
    // Constructor && Destructor
    CoinCollection(std::vector<Coin>);
    ~CoinCollection();

    // Getters
    std::vector<Coin> getCoins();

    // Setters
    void setCoins(std::vector<Coin>);

    // Operations
    void add(Coin coin);
    unsigned length();
    Coin getMostFrequentCoin();

    // W/R
    void write(std::ostream&);

  private:
    std::vector<Coin> coinsVector_;
};

// Overloading of write operator
std::ostream& operator<<(std::ostream&, CoinCollection&);