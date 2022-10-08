#include <iostream>

#include <iostream>
#include <vector>
#include "alphabet.h"

const std::string kEmptyChain = "&";

class Chain {
  public:
    // Constructor & Destructor
    Chain(std::vector<Symbol>);
    ~Chain();

    // Getters
    std::vector<Symbol> getSymbols();

    // Setters
    void setSymbols(std::vector<Symbol>);

    // Impresión por pantalla
    void print();

    // Operaciones
    unsigned length();
    Chain inverse();
    std::vector<Chain> prefixes();
    std::vector<Chain> suffixes();
    std::vector<Chain> substrings();
    Chain concat(Chain);
    bool isPalindrome();

    // Sobrecarga de operadores
    bool operator==(Chain&);
    bool operator<(const Chain&) const;

    // E/S
    void write(std::ostream&);
    void read(std::istream&);

  private:
    std::vector<Symbol> symbols_;
};

// Comprueba si una determinada cadena está formada con símbolos de un
// determinado alfabeto
bool checkChain(Alphabet*, Chain);

// Operaciones sobrecargados de E/S
std::istream& operator>>(std::istream&, Chain&);
std::ostream& operator<<(std::ostream&, Chain&);

// Conversión de string a vector
std::vector<std::string> stringToVector(std::string);

// Comprueba si un determinado elemento pertenece a un vector
template <class T>
bool include(std::vector<T>, T);