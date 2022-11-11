/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #07: Gramática regular a partir de un DFA
* @author Adrián González Galván
* @date 17/11/2022
*
* Este archivo contiene el código principal del programa.
*/

#include <iostream>
#include <fstream>

#include "finiteAutomata.h"
#include "rightRegularGrammar.h"

int main(int argc, char* argv[]) {  

  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    std::cout << "Modo de empleo: ";
    std::cout << "./main [input.fa] [output.gra]\n" ;
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
    std::cout << "error: the finite automatan specification file ";
    std::cout << "could not be open.\n";
    return 1;
  }

  // Archivo de escritura de la gramática
  std::ofstream outputGra;
  outputGra.open(argv[2]);

  if (outputGra.fail()) {
    std::cout << "error: he grammar write file could not be open.\n";
    return 1;
  }

  // Finite automatan
  try {
    FiniteAutomata fa;
    inputFA >> fa;
  } catch(const char* mssg) {
    std::cout << "error: " << mssg << "\n";
    return 1;
  }

  Symbol sS("S");
  Symbol sA("A");
  Symbol sB("B");

  Alphabet noTerminals({sS, sA});

  Symbol s0("0");
  Symbol s1("1");

  Alphabet terminals({s0, s1});

  Production p1(sS, std::vector<Symbol>({s0, sA}));
  Production p2(sA, std::vector<Symbol>({s1, s0, sA}));
  Production p3(sA);
  std::set<Production> setP({p1, p2, p3});

  try {
    RightRegularGrammar rRG(sS, terminals, noTerminals, setP);
    std::cout << rRG;
  } catch(const char* msg) {
    std::cerr << "error: " << msg << "\n";
  }

  // Cerramos archivos
  inputFA.close();
  outputGra.close();

  return 0;
}