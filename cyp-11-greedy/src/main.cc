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

#include "../include/greedyChangeCoins.h"
#include "../include/coinCollection.h"

/**
 * Check if string is a number
 * @param string String to check
 * @return True if that string is a number
*/
bool
isNumber(const std::string& s) {
  try {
    std::stod(s);
  } catch(...) {
    return false;
  }
  return true;
}

/**
 * Check if string is an option
 * @param string Option
 * @return Option string if it's an option, else return the string 'nonOption'
*/
std::string
isAnOption(const std::string& s) {
  std::string billsOption = "-b";
  std::string moreOptimusOption = "-o";
  if(s == billsOption) {
    return billsOption;
  } else if (s == moreOptimusOption) {
    return moreOptimusOption;
  } else {
    return "nonOption";
  }
}

int main(int argc, char* argv[]) {  

  // Checking correctly execution
  if (!argv[1]) {
    std::cout << "Usage: ";
    std::cout << "./main [-b] [-o] [coins]\n" ;
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

  // Parameters
  double n = 0.0;
  bool useBills = false;
  bool useMoreOptimus = false;

  // Options
  for (unsigned i = 1; i < argc; i++) {
    std::string reader = argv[i];
    std::string option = isAnOption(reader);
    if (isNumber(reader)) {
      n = std::stod(reader);
      break;
    } else if (option != "nonOption") {
      if (option == "-b") {
        useBills = true;
      } else if (option == "-o") {
        useMoreOptimus = true;
      }
    } else {
      std::cerr << "err: Invalid parameters...\n" << 
        "Usage: ./main [-b] [-o] [coins]\n";
      return 1;
    }
  }

  // Print 'n'
  std::cout << "n: " << n << "\n";

  // Class GreedyChangeCoins
  try {
    GreedyChangeCoins greedyChangeCoins(setOfCoins);
    if (useBills == true) {
      for (Coin coin: setOfBills) {
        greedyChangeCoins.add(coin);
      }
    }
    CoinCollection result({});
    if (useMoreOptimus) {
      result = greedyChangeCoins.getChangeMoreOptimus(n * 100.0);
    } else {
      result = greedyChangeCoins.getChange(n * 100.0);
    }
    if (result.length() != 0) {
      std::cout << "Solution: " << result << "\n";
      std::cout << "Number of coins used: " << result.length() << "\n";
    } else {
      std::cout << "Solution: " << "there is no solution.\n";
    }
  } catch(const char* mssg) {
    std::cerr << "err: " << mssg << "\n";
    return 1;
  } catch(...) {
    std::cout << "err: unknown\n";
    return 1;
  }

  return 0;
}