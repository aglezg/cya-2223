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
* Este archivo contiene el desarrollo de los métodos de la clase CoinCollection.
*/

#include "../include/coinCollection.h"

/**
 * Constructor
 * @param vector Vector of Coins
*/
CoinCollection::CoinCollection(std::vector<Coin> coinsVector): coinsVector_(coinsVector) {}

/**
 * Destructor
*/
CoinCollection::~CoinCollection() {
  coinsVector_.clear();
}

/**
 * Getter (coins)
 * @returns Vector of coins
*/
std::vector<Coin>
CoinCollection::getCoins() {
  return coinsVector_;
}

/**
 * Setter (coins)
 * @param coins Vector of coins
*/
void
CoinCollection::setCoins(std::vector<Coin> coins) {
  coinsVector_ = coins;
}

/**
 * Add coins
 * @param Coin Coin to add
*/
void
CoinCollection::add(Coin coin) {
  coinsVector_.push_back(coin);
}

/**
 * Size of colection
 * @param unsigned Number of coins in the collection
*/
unsigned
CoinCollection::length() {
  return coinsVector_.size();
}

/**
 * Write CoinCollection
 * @param os Output operator
*/
void
CoinCollection::write(std::ostream& os) {
  std::sort(coinsVector_.begin(), coinsVector_.end());
  unsigned counter = 1;
  os << "{";
  for (int i = coinsVector_.size() - 1; i >= 0; i--) {
    if (i != 0 && coinsVector_[i - 1] == coinsVector_[i]) {
      counter++;
    } else {
      if (counter != 1) {
        os << counter << "x" << coinsVector_[i];
        (i != 0)? std::cout << ", ": std::cout << "";
      } else {
        os << coinsVector_[i];
        (i != 0)? std::cout << ", ": std::cout << "";
      }
      counter = 1;
    }
  }
  os << "}";
}

/**
 * Write operator overloading
 * @param os Output operator
 * @param CoinCollection Coin Collection to use
*/
std::ostream&
operator<<(std::ostream& os, CoinCollection& coinCollection) {
  coinCollection.write(os);
  return os;
}