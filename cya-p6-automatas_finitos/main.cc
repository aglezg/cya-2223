/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Simulación de autómatas finitos
* @author Adrián González Galván
* @date 10/11/2022
*
* Este archivo contiene el código principal del programa.
*/

#include <iostream>
#include <fstream>

#include "finiteAutomata.h"

int main(int argc, char* argv[]) {  

  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    std::cout << "Modo de empleo: ";
    std::cout << "./main [input.fa] [input.txt] [operation]\n" ;
    std::cout << "Pruebe './main --help' para más información.\n";   
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

  // Archivo de lectura del FA
  std::ifstream inputFA;
  inputFA.open(argv[1]);

  if (inputFA.fail()) {
    std::cout << "No se pudo abrir archivo de lectura del FA, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    return 1;
  }

  // Archivo de lectura de cadenas
  std::ifstream inputTxt;
  inputTxt.open(argv[2]);

  if (inputTxt.fail()) {
    std::cout << "No se pudo abrir archivo de lectura de las cadenas, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    return 1;
  }

  // Lectura de cadenas
  std::vector<Chain> chains;
  while (!inputTxt.eof()) {
    Chain chainAux;
    inputTxt >> chainAux;
    chains.push_back(chainAux);
  }

  // Lectura del FA
  try {
    FiniteAutomata fa;
    fa.read(inputFA);
    for (Chain chain: chains) {
      std::cout << chain << " --- ";
      if (fa.checkChain(chain))
        std::cout << "Accepted\n";
      else
        std::cout << "Rejected\n";
    }
  } catch(const char* mssg) {
    std::cout << "error: " << mssg << "\n";
    return 1;
  }

  // Cerramos archivos
  inputFA.close();
  inputTxt.close();

  return 0;
}