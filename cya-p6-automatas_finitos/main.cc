/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #04: Simulación de autómatas finitos
* @author Adrián González Galván
* @date 10/10/2022
*
* Este archivo contiene el código principal del programa.
*/

#include <iostream>
#include <fstream>

#include "symbol.h"

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

  Symbol s1("a");
  Symbol s2("b");
  std::cout << s1 << ", " << s2 << std::endl;
  try {
    Symbol s3("sa");
    std::cin >> s3;
  } catch (const char* message) {
    std::cerr << "Hubo un error pibe: " << message << std::endl;
  }
/*
  // Leemos las cadenas del archivo correspondiente
  std::vector<Chain> vChain = {};

  std::string line;
  Chain chainAux({Symbol("aux")});
  while (!input.eof()) {
    input >> chainAux;
    vChain.push_back(chainAux);
  }

  // Archivo de escritura
  std::ofstream output;
  output.open(argv[2]);

  if (output.fail()) {
    std::cout << "No se pudo abrir el archivo de escritura, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    return 1;
  }

  // Operaciones
  if (argv[3] == std::string("--length")) { // Length
    for (unsigned i = 0; i < vChain.size(); i++)
      output << vChain[i].length() << '\n';
  } else if (argv[3] == std::string("--inverse")) { // Inverse
    for (unsigned i = 0; i < vChain.size(); i++) {
      Chain inverseChain = vChain[i].inverse();
      output << inverseChain << '\n';
    }
  } else if (argv[3] == std::string("--prefixes")) { // Prefixes
    for (unsigned i = 0; i < vChain.size(); i++) {
      std::vector<Chain> prefixes = vChain[i].prefixes();
      for (unsigned j = 0; j < prefixes.size() - 1; j++)
        output << prefixes[j] << ", ";
      output << prefixes[prefixes.size() - 1] << "\n";
    } 
  } else if (argv[3] == std::string("--suffixes")) { // Suffixes
    for (unsigned i = 0; i < vChain.size(); i++) {
      std::vector<Chain> suffixes = vChain[i].suffixes();
      for (unsigned j = 0; j < suffixes.size() - 1; j++)
        output << suffixes[j] << ", ";
      output << suffixes[suffixes.size() - 1] << "\n";
    } 
  } else if (argv[3] == std::string("--substrings")) { // Substrings
    for (unsigned i = 0; i < vChain.size(); i++) {
      std::vector<Chain> substrings = vChain[i].substrings();
      for (unsigned j = 0; j < substrings.size() - 1; j++)
        output << substrings[j] << ", ";
      output << substrings[substrings.size() - 1] << "\n";
    } 
  } else if (argv[3] == std::string("--palindrome")) { // Palindrome
    for (unsigned i = 0; i < vChain.size(); i++)
      if(vChain[i].isPalindrome())
        output << "true\n";
      else
        output << "false\n";
  } else {
    std::cout << "Opción inválida: Introduzca una opción válida\n";
    input.close();
    output.close();
    return 1;
  }

  // Cerramos archivos
  input.close();
  output.close();
*/

  return 0;
}