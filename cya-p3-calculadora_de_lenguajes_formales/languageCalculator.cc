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
* Este archivo contiene el desarrollo de los métodos de la clase LanguageCalculator.
*/

#include "languageCalculator.h"

// Constructor
LanguageCalculator::LanguageCalculator(std::vector<Language> languages,
  std::vector<std::string> languageNames, std::vector<std::string> operations) {
  assert(languages.size() == languageNames.size());
  languages_ = languages;
  languageNames_ = languageNames;
  operations_ = operations;
}

// Constructor por defecto
LanguageCalculator::LanguageCalculator() {
  languages_ = std::vector<Language>({});
  languageNames_ = std::vector<std::string>({});
  operations_ = std::vector<std::string>({});
}

// Destructor
LanguageCalculator::~LanguageCalculator() {
  languages_.clear();
  languageNames_.clear();
  operations_.clear();
}

// Getters
std::vector<Language>
LanguageCalculator::getLanguages() {
  return languages_;
}

std::vector<std::string>
LanguageCalculator::getLanguageNames() {
  return languageNames_;
}

std::vector<std::string>
LanguageCalculator::getOperations() {
  return operations_;
}

// Impresión por pantalla
void
LanguageCalculator::print() {
  for (unsigned i = 0; i < languages_.size(); i++)
    std::cout << languageNames_[i] << " = " << languages_[i] << "\n";
  for (unsigned i = 0; i < operations_.size(); i++)
    std::cout << operations_[i] << "\n";
}

// Lectura
void
LanguageCalculator::read(std::istream& is) {
  std::string read = "";
  while(!is.eof()) {
    getline(is, read);
    if (read.find('=') != std::string::npos) { // Leemos un lenguaje
      std::vector<std::string> readVector = stringToVector(read);
      languageNames_.push_back(readVector[0]);
      std::set<Chain> chainSetAux = {};
      bool isEmptyLanguage = true;
      for (unsigned i = 2; i < readVector.size(); i++) {
        std::vector<Symbol> symbolSetAux = {};
        for (unsigned j = 0; j < readVector[i].size(); j++) {
          if (readVector[i][j] == '&')
            isEmptyLanguage = false;
          else if (readVector[i][j] != '{' && readVector[i][j] != '}' &&
            readVector[i][j] != ',') {
            isEmptyLanguage = false;
            std::string symbolString(1, readVector[i][j]);
            symbolSetAux.push_back(Symbol(symbolString));
          }
        }
        if (!isEmptyLanguage)
          chainSetAux.insert(Chain(symbolSetAux));
      }
      languages_.push_back(Language(chainSetAux));
    } else { // Leemos una operación
      operations_.push_back(read);
    }
  }
}