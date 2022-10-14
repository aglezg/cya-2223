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

#include "language.h"

int main(int argc, char* argv[]) {



  /*
  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    std::cout << "Modo de empleo: ";
    std::cout << "./main [input.txt]\n" ;
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
  
  // Archivo de lectura
  std::ifstream input;
  input.open(argv[1]);

  if (input.fail()) {
    std::cout << "No se pudo abrir archivo de lectura, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    return 1;
  }

  // Leemos los lenguajes del primer archivo
  std::vector<Language> vLanguage = {};
  Language languageAux(new Alphabet(std::set<Symbol>({Symbol("aux")})));
  while (!input.eof()) {
    input >> languageAux;
    vLanguage.push_back(languageAux);
  }

  // Archivos && código de operación
  std::ifstream input2;
  std::ofstream output;
  std::string opcode = "";

  // Segundo vector de lenguajes
  std::vector<Language> vLanguage2 = {};

  // Leemos el número de parámetros introducidos
  if (argc == 4) { // 3 Argumentos
    output.open(argv[2]);
    opcode = argv[3];
  } else { // Más de 3 argumentos
    input2.open(argv[2]);

    if (input2.fail()) {
      std::cout << "No se pudo abrir archivo de escritura, ";
      std::cout << "comprueba si se ingresó un nombre correcto\n";
      return 1;
    }

    // Lectura de los lenguajes del segundo archivo
    while (!input2.eof()) {
      input2 >> languageAux;
      vLanguage2.push_back(languageAux);
    }

    output.open(argv[3]);
    opcode = argv[4];
  }

  if (output.fail()) {
    std::cout << "No se pudo abrir archivo de escritura, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    return 1;
  }

  // Operaciones a realizar
  if (opcode == "--concatenation" && argc > 4) { // CONCATENACIÓN
    assert(vLanguage.size() == vLanguage2.size());
    for (unsigned i = 0; i < vLanguage.size(); i++) {
      Language concatLanguage = vLanguage[i].lConcat(vLanguage2[i]);
      output << concatLanguage << "\n";
    }
  } else if (opcode == "--power") { // POTENCIA
    int pow = -1;
    while (pow < 0) {
      std::cout << "Introduzca un número positivo para la potencia >> ";
      std::cin >> pow;
    }
    for (unsigned i = 0; i < vLanguage.size(); i++) {
      Language powLanguage = vLanguage[i].lPow(pow);
      output << powLanguage << "\n";
    }
  } else if (opcode == "--union" && argc > 4) { // UNIÓN
    assert(vLanguage.size() == vLanguage2.size());
    for (unsigned i = 0; i < vLanguage.size(); i++) {
      Language unionLanguage = vLanguage[i].lUnion(vLanguage2[i]);
      output << unionLanguage << "\n";
    }
  } else if (opcode == "--intersection" && argc > 4) { // INTERSECCIÓN
    assert(vLanguage.size() == vLanguage2.size());
    for (unsigned i = 0; i < vLanguage.size(); i++) {
      Language intersectionLanguage = vLanguage[i].lIntersection(vLanguage2[i]);
      output << intersectionLanguage << "\n";
    }
  } else if (opcode == "--difference" && argc > 4) { // DIFERENCIA
    assert(vLanguage.size() == vLanguage2.size());
    for (unsigned i = 0; i < vLanguage.size(); i++) {
      Language differenceLanguage = vLanguage[i].lDifference(vLanguage2[i]);
      output << differenceLanguage << "\n";
    }
  } else if (opcode == "--inverse") { // INVERSA
    for (unsigned i = 0; i < vLanguage.size(); i++) {
      Language inverseLanguage = vLanguage[i].lInverse();
      output << inverseLanguage << "\n";
    }
  } else {
    std::cout << "Opción inválida: Introduzca una opción válida o revise los ficheros.\n";
    input.close();
    input2.close();
    output.close();
    return 1;
  }

  input.close();
  input2.close();
  output.close();
  */
  return 0;
}