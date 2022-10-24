/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Expresiones regulares
* @author Adrián González Galván
* @date 27/10/2022
*
* Este archivo contiene el menú principal de la práctica.
*/

#include <iostream>
#include <fstream>
#include <regex>
#include "codeAnalyser.h"

int main (int argc, char* argv[]) {

  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    std::cout << "Modo de empleo: ";
    std::cout << "./main [input.cc] [output.txt]\n" ;
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
    return 0;
  }

  // Archivo de lectura
  std::ifstream input;
  input.open(argv[1]);

  if (input.fail()) {
    std::cout << "No se pudo abrir el archivo de lectura, ";
    std::cout << "comprueba si se ingresó un nombre correcto.\n";
    return 1;
  }

  // Clase analizadora
  CodeAnalyser cA(input);

  // Archivo de escritura
  std::ofstream output;
  output.open(argv[2]);

  if (output.fail()) {
    std::cout << "No se pudo abrir el archivo de escritura, ";
    std::cout << "comprueba si se ingresó un nombre correcto.\n";
  }

  // Escritura
  output << cA;

  // Cierre de ficheros
  input.close();
  output.close();

  return 0;
}