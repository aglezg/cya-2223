/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #03: Calculadora de lenguajes formales
* @author Adrián González Galván
* @date 20/10/2022
*
* Este archivo contiene el menú principal de la práctica.
*/

#include <iostream>
#include <fstream>
#include <regex>
#include "codeAnalyser.h"

int main(int argc, char* argv[]) {

/*

  std::string str1 = "int main (int argc, int archv) {";

  std::regex r1("^int\\smain\\s\\(.*\\)\\s\\{$");

  //std::regex r1("\\s*([a-zA-Z]+)\\s([a-zA-Z]+\\d*)+(\\s=\\s(.*))?;$");  CORREGIR !! Lee el return
  std::smatch m;
  std::cout << std::regex_match(str1, r1) << std::endl;
  std::regex_search(str1, m, r1);

  for (auto x: m)
    std::cout <<"[" << x << "] ";
  return 0;
*/
  

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

  CodeAnalyser cA(input);

  // Archivo de escritura
/*
  std::ofstream output;
  output.open(argv[2]);

  if (output.fail()) {
    std::cout << "No se pudo abrir el archivo de escritura, ";
    std::cout << "comprueba si se ingresó un nombre correcto.\n";
  }
*/
  cA.write();

  input.close();
//  output.close();

  return 0;
}