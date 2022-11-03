/*
  Assignment 1 Polynomial
  By Aditya Duggirala
*/

#include <iostream>
#include <cmath>

using namespace std;
class Poly
{
private:
	int degree;
	int *coefficients;

public:
	Poly();
	Poly(int coeff, int degree);
	Poly(int coeff);
	Poly(const Poly &p);
	~Poly();

	void resize(int new_degree);
	void setCoeff(int exp, int coeff);
	int getCoeff(int exp);

	void display();

	Poly operator=(Poly p);
	Poly operator+(Poly p);
	Poly operator-(Poly p);
	Poly operator*(Poly p);
	Poly operator+=(Poly p);
	Poly operator-=(Poly p);
	Poly operator*=(Poly p);
	bool operator==(Poly p);
	bool operator!=(Poly p);
	friend ostream &operator<<(ostream &out, const Poly &p);
	friend istream &operator>>(istream &in, Poly &p);
};