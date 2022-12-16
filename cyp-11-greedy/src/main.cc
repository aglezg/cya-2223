/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #11: Algoritmos Voraces (Greedy). Cambio de monedas
* @author Adrián González Galván
* @date 22/11/2022
*
* Este archivo contiene el código principal del programa.
*/

#include <iostream>
#include <fstream>

#include "../include/GreedyChangeCoins.h"
#include "../include/coinCollection.h"

/**
 * Check if string is a number
 * @param string String to check
 * @return True if that string is a number
*/
bool is_number(const std::string& s) {
  try {
    std::stod(s);
  } catch(...) {
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {  

  // Checking correctly execution
  if (!argv[1]) {
    std::cout << "Usage: ";
    std::cout << "./main [-b] [coins]\n" ;
    std::cout << "Try './main --help' for more...\n";   
    return 1;
  }

  // In case of use "--help" option
  std::string help = "--help";
  if(argv[1] == help) {
    std::ifstream help_txt;
    help_txt.open("help.txt");
    if (!help_txt.fail()) {
      while (!help_txt.eof()) {
        std::getline(help_txt, help);
        std::cout << help << "\n";
      }
    }
    help_txt.close();
    return 1;
  }

  // Set of coins
  std::set<Coin> setOfCoins = {
    Coin("2€", 200),
    Coin("1€", 100),
    Coin("50¢", 50),
    Coin("20¢", 20),
    Coin("10¢", 10),
    Coin("5¢", 5),
    Coin("2¢", 2),
    Coin("1¢", 1)
  };

  // Set of bills
  std::set<Coin> setOfBills = {
    Coin("500€", 50000),
    Coin("200€", 20000),
    Coin("100€", 10000),
    Coin("50€", 5000),
    Coin("20€", 2000),
    Coin("10€", 1000),
    Coin("5€", 500)
  };

  // Options
  double n = 0.0;
  bool useBills = false;
  std::string billsOption = "-b";
  if (is_number(argv[1])) {
    n = std::stod(argv[1]);
  } else if (argv[1] == billsOption) {
    if (is_number(argv[2])) {
      useBills = true;
      n = std::stod(argv[2]);
    } else {
      std::cerr << "err: Invalid coins number...\n" << 
      "Usage: ./main [-b] [coins]\n";
      return 1;
    }
  } else {
    std::cerr << "err: Invalid parameters...\n" << 
      "Usage: ./main [-b] [coins]\n";
    return 1;
  }

  // Class GreedyChangeCoins
  try {
    GreedyChangeCoins greedyChangeCoins(setOfCoins);
    if (useBills == true) {
      for (Coin coin: setOfBills) {
        greedyChangeCoins.add(coin);
      }
    }
    CoinCollection result = greedyChangeCoins.getChange(n * 100.0);
    std::cout << "Solution: " << result << "\n";
    std::cout << "Number of coins used: " << result.length() << "\n";
  } catch(const char* mssg) {
    std::cerr << "err: " << mssg << "\n";
    return 1;
  } catch(...) {
    std::cout << "err: unknown\n";
    return 1;
  }

  return 0;
}