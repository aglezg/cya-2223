/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #12: Algoritmos Divide y Vencerás.
* @author Adrián González Galván
* @date 12/01/2023
*
* Este archivo contiene la implementación de una clase correspondiente
* a la representación de un numero entero grande
*/

#include <bits/stdc++.h>

class BigInt{
  public:
	  //Constructors
	  BigInt(unsigned long long n = 0);
	  BigInt(std::string &);
	  BigInt(const char *);
	  BigInt(BigInt &);

    //Destructor
    ~BigInt();

	  //Helper Functions
	  friend void divide_by_2(BigInt &a);
    friend bool Null(const BigInt &);
    friend int Length(const BigInt &);
	  int operator[](const int)const;

	  //Direct assignment
	  BigInt &operator=(const BigInt &);

	  //Post/Pre - Incrementation
	  BigInt &operator++();
	  BigInt operator++(int temp);
	  BigInt &operator--();
	  BigInt operator--(int temp);

	  //Addition and Subtraction
	  friend BigInt &operator+=(BigInt &, const BigInt &);
	  friend BigInt operator+(const BigInt &, const BigInt &);
	  friend BigInt operator-(const BigInt &, const BigInt &);
	  friend BigInt &operator-=(BigInt &, const BigInt &);

	  //Comparison operators
	  friend bool operator==(const BigInt &, const BigInt &);
	  friend bool operator!=(const BigInt &, const BigInt &);

	  friend bool operator>(const BigInt &, const BigInt &);
	  friend bool operator>=(const BigInt &, const BigInt &);
	  friend bool operator<(const BigInt &, const BigInt &);
	  friend bool operator<=(const BigInt &, const BigInt &);

	  //Multiplication and Division
	  friend BigInt &operator*=(BigInt &, const BigInt &);
	  friend BigInt operator*(const BigInt &, const BigInt &);
	  friend BigInt &operator/=(BigInt &, const BigInt &);
	  friend BigInt operator/(const BigInt &, const BigInt &);

	  //Modulo
	  friend BigInt operator%(const BigInt &, const BigInt &);
	  friend BigInt &operator%=(BigInt &, const BigInt &);

	  //Power Function
	  friend BigInt &operator^=(BigInt &,const BigInt &);
	  friend BigInt operator^(BigInt &, const BigInt &);
  
	  //Square Root Function
	  friend BigInt sqrt(BigInt &a);

	  //Read and Write
	  friend std::ostream &operator<<(std::ostream &,const BigInt &);
	  friend std::istream &operator>>(std::istream &, BigInt &);

	  //Others
	  friend BigInt NthCatalan(int n);
	  friend BigInt NthFibonacci(int n);
	  friend BigInt Factorial(int n);
  
  private:
    std::string digits_;
};