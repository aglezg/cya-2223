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
* Este archivo contiene el desarrollo de los métodos de la clase GreedyChangeCoins.
*/

#include "../include/GreedyChangeCoins.h"

/**
 * Class constructor
 */
GreedyChangeCoins::GreedyChangeCoins(std::set<int> coins): coins_(coins) {
  if (coins_.empty()) {
    throw 'set of coins cant be empty';
  }
}

/**
 * Class destructor
 */
GreedyChangeCoins::~GreedyChangeCoins() {
  coins_.clear();
}

/**
 * Setter of coins 
 */
void
GreedyChangeCoins::setCoins(std::set<int> coins) {
  if (coins.empty()) {
    throw 'set of coins cant be empty';
  }
  coins_ = coins;
}

/**
 * Getter of coins
 */
std::set<int>
GreedyChangeCoins::getCoins() {
  return coins_;
}

/**
 * Calculate the list of coins to use for a specific change 
*/
std::list<int>
GreedyChangeCoins::getChange(double change) {
  std::list<int> solution = {};
  return solution;
}