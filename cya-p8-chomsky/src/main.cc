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
* Este archivo contiene el código principal del programa.
*/

#include <iostream>
#include <fstream>

#include "../include/grammar.h"

int main(int argc, char* argv[]) {  

  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    std::cout << "Usage: ";
    std::cout << "./main [input.gra] [output.gra]\n" ;
    std::cout << "Try './main --help' for more...\n";   
    return 1;
  }

  // En caso de usar como parámetro "--help"
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

  // Archivo de lectura
  std::ifstream input;
  input.open(argv[1]);

  if (input.fail()) {
    std::cout << "error: the input file ";
    std::cout << "could not be open.\n";
    return 1;
  }

  // Archivo de escritura
  std::ofstream output;
  output.open(argv[2]);

  if (output.fail()) {
    std::cout << "error: the output file could not be open.\n";
    input.close();
    return 1;
  }

  // Conversión a gramática en FNC
  try {
    Grammar grammar;
    input >> grammar;
    std::cout << grammar << "\n";
  } catch(const char* mssg) {
    std::cout << "error: " << mssg << "\n";
    input.close();
    output.close();
    return 1;
  }

  // Cerramos archivos
  input.close();
  output.close();

  return 0;
}