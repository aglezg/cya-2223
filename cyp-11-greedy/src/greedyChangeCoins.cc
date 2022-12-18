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

#include "../include/greedyChangeCoins.h"

/**
 * Class constructor
 * @param coins Set of coins
 */
GreedyChangeCoins::GreedyChangeCoins(std::set<Coin> coins): coins_(coins) {}

/**
 * Class destructor
 */
GreedyChangeCoins::~GreedyChangeCoins() {
  coins_.clear();
}

/**
 * Setter of coins 
 * @param coins Set of coins
 */
void
GreedyChangeCoins::setCoins(std::set<Coin> coins) {
  coins_ = coins;
}

/**
 * Getter of coins
 * @return The set of coins
 */
std::set<Coin>
GreedyChangeCoins::getCoins() {
  return coins_;
}

/**
 * Add coin to the collection
 * @param Coin Coin to add
*/
void
GreedyChangeCoins::add(Coin coin) {
  coins_.insert(coin);
}


/**
 * Calculate the list of coins to use for a specific change.
 * @param change Change to use to calculate
 * @return CoinColection generated, it's empty if there is no solution.
*/
CoinCollection
GreedyChangeCoins::getChange(unsigned change) {
  CoinCollection solution({});
  unsigned sum = 0;
  for (auto itr = coins_.rbegin(); itr != coins_.rend(); itr++) {
    Coin coin = *itr;
    unsigned nItems = (change - sum) / coin.getValue();
    if (nItems != 0) {
      for (unsigned i = 0; i < nItems; i++) {
        solution.add(coin);
      }
      sum += nItems * coin.getValue();
    }
  }
  if (sum == change) {
    return solution;
  } else {
    return CoinCollection({});
  }
}