/**
* ULL - Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática - Curso 2
* 
* Asignatura: Computabilidad y Algoritmia
*
* @brief Práctica #12: Algoritmos Divide y Vencerás.
* @author Adrián González Galván
* @date 12/01/2023
* @link https://www.geeksforgeeks.org/bigint-big-integers-in-c-with-example/
*
* Este archivo contiene el desarrollo de los métodos de la clase BigInt.
*/

#include "../include/bigInt.h"

/**
 * Constructor
 * @param s String with numeric characters
*/
BigInt::BigInt(std::string & s){
	digits_ = "";
	int n = s.size();
	for (int i = n - 1; i >= 0;i--){
		if(!isdigit(s[i]))
			throw("characters must be numeric");
		digits_.push_back(s[i] - '0');
	}
}

/**
 * Constructor
 * @param unsigned long Long number to use
*/
BigInt::BigInt(unsigned long long nr){
	do{
		digits_.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}

/**
 * Constructor
 * @param char* Character pointer with numeric characters
*/
BigInt::BigInt(const char *s){
	digits_ = "";
	for (int i = strlen(s) - 1; i >= 0;i--)
	{
		if(!isdigit(s[i]))
			throw("characters must be numeric");
		digits_.push_back(s[i] - '0');
	}
}

/**
 * Constructor
 * @param BigInt Other BigInt
*/
BigInt::BigInt(BigInt & a){
	digits_ = a.digits_;
}

/**
 * Destructor
*/
BigInt::~BigInt() {
  digits_.clear();
}

/**
 * Check if a bigInt is zero
 */
bool Null(const BigInt& a){
    if(a.digits_.size() == 1 && a.digits_[0] == 0)
        return true;
    return false;
}

/**
 * Calculate the length of a BigInt
*/
int
Length(const BigInt & a){
    return a.digits_.size();
}

/**
 * Operator [] overloading
 * @param int Index
*/
int
BigInt::operator[](const int index) const{
	if(digits_.size() <= index || index < 0)
		throw("index cant be lower than zero or greater than size");
	return digits_[index];
}

/**
 * Operator '=' overloading
 * @param BigInt Assignement operand
*/
BigInt&
BigInt::operator=(const BigInt &a){
	digits_ = a.digits_;
	return *this;
}

/**
 * Operator '++' overloading
*/
BigInt &BigInt::operator++(){
	int i, n = digits_.size();
	for (i = 0; i < n && digits_[i] == 9;i++)
		digits_[i] = 0;
	if(i == n)
		digits_.push_back(1);
	else
		digits_[i]++;
	return *this;
}

/**
 * Operator '++' overloading with temp
 * @param int Temporal to difference
*/
BigInt BigInt::operator++(int temp){
	BigInt aux;
	aux = *this;
	++(*this);
	return aux;
}

/**
 * Operator '--' overloading
*/
BigInt &BigInt::operator--(){
	if(digits_[0] == 0 && digits_.size() == 1)
		throw("underflow");
	int i, n = digits_.size();
	for (i = 0; digits_[i] == 0 && i < n;i++)
		digits_[i] = 9;
	digits_[i]--;
	if(n > 1 && digits_[n - 1] == 0)
		digits_.pop_back();
	return *this;
}

/**
 * Operator '--' overloading with temp
 * @param int Temporal to difference

*/
BigInt BigInt::operator--(int temp){
	BigInt aux;
	aux = *this;
	--(*this);
	return aux;
}

/**
 * Operator '+=' overloading
*/
BigInt &operator+=(BigInt &a,const BigInt& b){
	int t = 0, s, i;
	int n = Length(a), m = Length(b);
	if(m > n)
		a.digits_.append(m - n, 0);
	n = Length(a);
	for (i = 0; i < n;i++){
		if(i < m)
			s = (a.digits_[i] + b.digits_[i]) + t;
		else
			s = a.digits_[i] + t;
		t = s / 10;
		a.digits_[i] = (s % 10);
	}
	if(t)
		a.digits_.push_back(t);
	return a;
}

/**
 * Operator '+' overloading
*/
BigInt operator+(const BigInt &a, const BigInt &b){
	BigInt temp;
	temp = a;
	temp += b;
	return temp;
}

/**
 * Operator '-=' overloading
*/
BigInt &operator-=(BigInt&a,const BigInt &b){
	if(a < b)
		throw("underflow");
    int n = Length(a), m = Length(b);
	int i, t = 0, s;
	for (i = 0; i < n;i++){
		if(i < m)
			s = a.digits_[i] - b.digits_[i]+ t;
		else
			s = a.digits_[i]+ t;
		if(s < 0)
			s += 10,
			t = -1;
		else
			t = 0;
		a.digits_[i] = s;
	}
	while(n > 1 && a.digits_[n - 1] == 0)
		a.digits_.pop_back(),
		n--;
	return a;
}
BigInt operator-(const BigInt& a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp -= b;
	return temp;
}

/**
 * Operator '==' overloading
*/
bool operator==(const BigInt &a, const BigInt &b){
	return a.digits_ == b.digits_;
}


bool operator!=(const BigInt & a,const BigInt &b){
	return !(a == b);
}
bool operator<(const BigInt&a,const BigInt&b){
	int n = a.digits_.size();
  int m = b.digits_.size();
	if(n != m)
		return n < m;
	while(n--)
		if(a.digits_[n] != b.digits_[n])
			return a.digits_[n] < b.digits_[n];
	return false;
}
bool operator>(const BigInt&a,const BigInt&b){
	return b < a;
}
bool operator>=(const BigInt&a,const BigInt&b){
	return !(a < b);
}
bool operator<=(const BigInt&a,const BigInt&b){
	return !(a > b);
}



BigInt &operator*=(BigInt &a, const BigInt &b)
{
	if(Null(a) || Null(b)){
		a = BigInt();
		return a;
	}
	int n = a.digits_.size(), m = b.digits_.size();
	std::vector<int> v(n + m, 0);
	for (int i = 0; i < n;i++)
		for (int j = 0; j < m;j++){
			v[i + j] += (a.digits_[i] ) * (b.digits_[j]);
		}
	n += m;
	a.digits_.resize(v.size());
	for (int s, i = 0, t = 0; i < n; i++)
	{
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.digits_[i] = v[i] ;
	}
	for (int i = n - 1; i >= 1 && !v[i];i--)
			a.digits_.pop_back();
	return a;
}
BigInt operator*(const BigInt&a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}

BigInt &operator/=(BigInt& a,const BigInt &b){
	if(Null(b))
		throw("division by 0");
	if(a < b){
		a = BigInt();
		return a;
	}
	if(a == b){
		a = BigInt(1);
		return a;
	}
	int i, lgcat = 0, cc;
  int n = Length(a), m = Length(b);
	std::vector<int> cat(n, 0);
	BigInt t;
	for (i = n - 1; t * 10 + a.digits_[i] < b;i--){
		t *= 10;
		t += a.digits_[i] ;
	}
	for (; i >= 0; i--){
		t = t * 10 + a.digits_[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a.digits_.resize(cat.size());
	for (i = 0; i < lgcat;i++)
		a.digits_[i] = cat[lgcat - i - 1];
	a.digits_.resize(lgcat);
	return a;
}
BigInt operator/(const BigInt &a,const BigInt &b){
	BigInt temp;
	temp = a;
	temp /= b;
	return temp;
}

BigInt &operator%=(BigInt& a,const BigInt &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		return a;
	}
	if(a == b){
		a = BigInt();
		return a;
	}
	int i, lgcat = 0, cc;
  int n = Length(a), m = Length(b);
	std::vector<int> cat(n, 0);
	BigInt t;
	for (i = n - 1; t * 10 + a.digits_[i] < b;i--){
		t *= 10;
		t += a.digits_[i];
	}
	for (; i >= 0; i--){
		t = t * 10 + a.digits_[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a = t;
	return a;
}
BigInt operator%(const BigInt &a,const BigInt &b){
	BigInt temp;
	temp = a;
	temp %= b;
	return temp;
}

BigInt &operator^=(BigInt & a,const BigInt & b){
	BigInt Exponent, Base(a);
	Exponent = b;
	a = 1;
	while(!Null(Exponent)){
		if(Exponent[0] & 1)
			a *= Base;
		Base *= Base;
		divide_by_2(Exponent);
	}
	return a;
}
BigInt operator^(BigInt & a,BigInt & b){
	BigInt temp(a);
	temp ^= b;
	return temp;
}

void divide_by_2(BigInt & a){
	int add = 0;
	for (int i = a.digits_.size() - 1; i >= 0;i--){
		int digit = (a.digits_[i] >> 1) + add;
		add = ((a.digits_[i] & 1) * 5);
		a.digits_[i] = digit;
	}
	while(a.digits_.size() > 1 && !a.digits_.back())
		a.digits_.pop_back();
}

BigInt sqrt(BigInt & a){
	BigInt left(1), right(a), v(1), mid, prod;
	divide_by_2(right);
	while(left <= right){
		mid += left;
		mid += right;
		divide_by_2(mid);
		prod = (mid * mid);
		if(prod <= a){
			v = mid;
			++mid;
			left = mid;
		}
		else{
			--mid;
			right = mid;
		}
		mid = BigInt();
	}
	return v;
}

BigInt NthCatalan(int n){
	BigInt a(1),b;
	for (int i = 2; i <= n;i++)
		a *= i;
	b = a;
	for (int i = n + 1; i <= 2 * n;i++)
		b *= i;
	a *= a;
	a *= (n + 1);
	b /= a;
	return b;
}

BigInt NthFibonacci(int n){
	BigInt a(1), b(1), c;
	if(!n)
		return c;
	n--;
	while(n--){
		c = a + b;
		b = a;
		a = c;
	}
	return b;
}

BigInt Factorial(int n){
	BigInt f(1);
	for (int i = 2; i <= n;i++)
		f *= i;
	return f;
}

std::istream &operator>>(std::istream &in,BigInt&a){
	std::string s;
	in >> s;
	int n = s.size();
	for (int i = n - 1; i >= 0;i--){
		if(!isdigit(s[i]))
			throw("INVALID NUMBER");
		a.digits_[n - i - 1] = s[i];
	}
	return in;
}

std::ostream &operator<<(std::ostream &out,const BigInt &a){
	for (int i = a.digits_.size() - 1; i >= 0;i--)
		std::cout << (short)a.digits_[i];
	return std::cout;
}

//Driver code with some examples
int main()
{
	BigInt first("12345");
	std::cout << "The number of digits_"
		<< " in first big integer = "
		<< Length(first) << '\n';
	BigInt second(12345);
	if (first == second) {
		std::cout << "first and second are equal!\n";
	}
	else
		std::cout << "Not equal!\n";
	BigInt third("10000");
	BigInt fourth("100000");
	if (third < fourth) {
		std::cout << "third is smaller than fourth!\n";
	}
	BigInt fifth("10000000");
	if (fifth > fourth) {
		std::cout << "fifth is larger than fourth!\n";
	}

	// Printing all the numbers
	std::cout << "first = " << first << '\n';
	std::cout << "second = " << second << '\n';
	std::cout << "third = " << third << '\n';
	std::cout << "fourth = " << fourth<< '\n';
	std::cout << "fifth = " << fifth<< '\n';

	// Incrementing the value of first
	first++;
	std::cout << "After incrementing the"
		<< " value of first is : ";
	std::cout << first << '\n';
	BigInt sum;
	sum = (fourth + fifth);
	std::cout << "Sum of fourth and fifth = "
		<< sum << '\n';
	BigInt product;
	product = second * third;
	std::cout << "Product of second and third = "
		<< product << '\n';

	// Print the fibonacci number from 1 to 100
	std::cout << "-------------------------Fibonacci"
		<< "------------------------------\n";
	for (int i = 0; i <= 100; i++) {
		BigInt Fib;
		Fib = NthFibonacci(i);
		std::cout << "Fibonacci " << i << " = " << Fib<<'\n';
	}
	std::cout << "-------------------------Catalan"
		<< "------------------------------\n";
	for (int i = 0; i <= 100; i++) {
		BigInt Cat;
		Cat = NthCatalan(i);
		std::cout << "Catalan " << i << " = " << Cat<<'\n';
	}

	// Calculating factorial of from 1 to 100
	std::cout << "-------------------------Factorial"
		<< "------------------------------\n";
	for (int i = 0; i <= 100; i++) {
		BigInt fact;
		fact = Factorial(i);
		std::cout << "Factorial of "
			<< i << " = ";
		std::cout << fact << '\n';
	}
}
