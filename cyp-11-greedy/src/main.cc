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

  // Set of coins to use
  std::set<int> setOfCoins = {200, 100, 50, 20, 10, 5, 2, 1};
  std::set<int> setOfBills = {50000, 20000, 10000, 5000, 2000, 1000, 500};

  

  return 0;
}