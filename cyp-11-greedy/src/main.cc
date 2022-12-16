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
    Coin("0,50€", 50),
    Coin("0,20€", 20),
    Coin("0,10€", 10),
    Coin("0,05€", 5),
    Coin("0,02€", 2),
    Coin("0,01€", 1)
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

  // Class GreedyChangeCoins
  try {
    GreedyChangeCoins greedyChangeCoins(setOfCoins);
    std::list<Coin> result = greedyChangeCoins.getChange(743.0);
    for (Coin coin: result) {
      std::cout << coin << "\n";
    }
  } catch(...) {
    std::cout << "Malos momentos\n";
  }
  return 0;
}