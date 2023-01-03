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

  try {
    std::cout << "Hello world!\n";
    
  } catch(const char* mssg) {
    std::cerr << "err: " << mssg << "\n";
    return 1;
  } catch(...) {
    std::cout << "err: unknown\n";
    return 1;
  }

  return 0;
}