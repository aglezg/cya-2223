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
#include <stack>

#include "language.h"

// Dados un vector y un elemento, devuelve la posición en la que se
// encuentra el mismo (si no se encuentra retorna -1)
template <class T>
int
getIndexOfElement(std::vector<T> v, T element) {
  int index = -1;
  for (unsigned i = 0; i < v.size(); i++)
    if (element == v[i]) {
      index = i;
      break;
    }
  return index;
}

// Comprueba si un string es un número
bool isNumber(std::string& str)
{
    for (char const &c : str) {
       
        // using the std::isdigit() function
        if (std::isdigit(c) == 0)
          return false;
    }
    return true;
}

int main (int argc, char* argv[]) {

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

  // Vector de nombres de los lenguajes
  std::vector<std::string> languageNamesVector = {};

  // Vector de lenguajes
  std::vector<Language> languageVector = {};

  // Vector de cadenas de operaciones
  std::vector<std::string> operationsVector = {};

  // Lectura
  std::string read = "";
  while (!input.eof()) {
    std::streampos inputStart = input.tellg();
    getline(input, read);
    if (read.find('=') != std::string::npos) { // Es un lenguaje
      input.seekg(inputStart);
      input >> read; // Nombre del lenguaje
      languageNamesVector.push_back(read);
      input >> read; // =
      Language languageAux;
      input >> languageAux; // Lectura del lenguaje
      languageVector.push_back(languageAux);
    } else {                                  // Es una operación
      if (read != "")
        operationsVector.push_back(read);      
    }
  }

  // Vector de resultados
  std::vector<Language> resultVector = {};

  // Cálculo
  for (std::string operation: operationsVector) {
    // Pila de lenguajes
    std::stack<Language> languageStack = {};
    // Pila de números para la potencia
    std::stack<int> intStack = {};
    // Calculo de la operacion "i"
    std::vector<std::string> opV = stringToVector(operation);
    for (unsigned i = 0; i < opV.size(); i++) {
      if (isLanguageOperation(opV[i])) {
        if (!operateLanguageStack(languageStack, intStack, opV[i])) {
          std::cout << "Error en el cálculo de la operación: compruebe la notación escrita.\n";
          return 1;
        }
      } else if (isNumber(opV[i]) ) {
        if (opV[i + 1] == "*")
          intStack.push(stoi(opV[i]));
        else {
          std::cout << "ERROR: Se encontró un número seguido de una operación";
          std::cout << " que no es '*'.\n";
          return 1;
        }
      } else {
        int index = getIndexOfElement(languageNamesVector, opV[i]);
        if (index != -1)
          languageStack.push(languageVector[index]);
        else {
          return 1;
        }
      }
    }
    if (languageStack.size() == 1)
      resultVector.push_back(languageStack.top());
    else {
      std::cout << languageStack.size();
      std::cout << "ERROR: La pila no se vació, cantidad de lenguajes excesiva." << std::endl;
      return 1;
    }
  }

  // Resultados
  std::cout << ">> Alphabet\tLanguage\n";
  for (Language element: resultVector) {
    std::cout << ">> " << element << std::endl;
  }

  input.close();
  return 0;
}
