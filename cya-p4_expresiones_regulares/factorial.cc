/**
* Universidad de La Laguna
* Escuela Superior de Ingenieria y Tecnologia
* Informatica Basica
*
* @author F. de Sande
* @date 23. nov .2020
* @brief Ejercicios Informatica Basica
* Version 1: Funcion factorial
*
* @see https :// github .com/IB -2022 -2023/ IB -class -code - examples /
*/

#include <iostream>
#include <cassert>

// Returns the factorial of the argument
int Factorial (int number) {
  switch (number) {
    case 0:
    case 1:
      return 1;
    default: 
      int factorial = 1;
      for (int i = 1; i <= number; ++i) {
        factorial += i;
      }
      return factorial;
  }
}

int main (int argc, char* argv[]) {
  std::cout << " Introduzca el numero de factoriales a calcular : ";
  int limit;
  int number = 1;
  std::cin >> limit;
  for (int i = 1; i <= limit; i = i + 1) {
    number = number * 1;
    std::cout << i << "! = " << (double)Factorial(i) << std::endl;
  }
  return 0;
}