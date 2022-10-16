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

const std::string kConcatOp = "+";
const std::string kUnionOp = "|";
const std::string kIntersectionOp = "^";
const std::string kDifferenceOp = "-";
const std::string kInverseOP = "!";

bool
isLanguageOperation(std::string op) {
  return op == kConcatOp || op == kUnionOp || op == kIntersectionOp ||
    op == kDifferenceOp || op == kInverseOP;
}

bool
operateLanguageStack(std::stack<Language>& languageStack, std::string op) {
  if (isLanguageOperation(op) && !languageStack.empty()) {
    Language l1 = languageStack.top();
    languageStack.pop();
    if (op == kConcatOp) {
      if (languageStack.empty())
        return false;
      Language l2 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lConcat(l2));
    } else if (op == kUnionOp) {
      if (languageStack.empty())
        return false;
      Language l2 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lUnion(l2));
    } else if (op == kIntersectionOp) {
      if (languageStack.empty())
        return false;
      Language l2 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lIntersection(l2));
    } else if (op == kDifferenceOp) {
      if (languageStack.empty())
        return false;
      Language l2 = languageStack.top();
      languageStack.pop();
      languageStack.push(l1.lDifference(l2));
    } else if (op == kInverseOP) {
      languageStack.push(l1.lInverse());
    }
  }
  return isLanguageOperation(op);
}

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

int main(int argc, char* argv[]) {

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
    // Calculo de la operacion "i"
    std::vector<std::string> opV = stringToVector(operation);
    for (std::string element: opV) {
      if (isLanguageOperation(element)) {
        if (!operateLanguageStack(languageStack, element)) {
          std::cout << "Error en el cálculo de la operación: compruebe la notación escrita.\n";
          return 1;
        }
      } else {
        int index = getIndexOfElement(languageNamesVector, element);
        if (index != -1)
          languageStack.push(languageVector[index]);
        else {
          std::cout << "Error: Operando inexistente en las operaciones.\n";
          return 1;
        }
      }
    }
    if (languageStack.size() == 1)
      resultVector.push_back(languageStack.top());
    else {
      std::cout << "ERROR: La pila no se vació, cantidad de lenguajes excesiva." << std::endl;
      return 1;
    }
  }

  for (Language element: resultVector) {
    std::cout << ">> " << element << std::endl;
  }

  input.close();
  return 0;
}