#include <iostream>

using namespace std;

// poner aqui los ejemplos como funciones con el siguiente formato,
// donde 'X' es el numero de ejemplo
int ejemploX(const int n)
{ 
  int suma = 0;
  for (int i = 1; i <= n - 1; i++)
    for (int j = i + 1; j <= n; j++)
      suma++;
  return suma;
}

int main()
{ // pedir el valor de n
  int n;
  cout << "Introducir n: ";
  cin >> n;

  // invocar a cada ejemplo
  cout << "Ejemplo X: " << ejemploX(n) << endl;
  return 0;
}