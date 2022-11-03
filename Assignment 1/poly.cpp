/*
  Assignment 1 Polynomial
  By Aditya Duggirala
*/

#include <iostream>
#include <math.h>
#include "poly.h"

using namespace std;

// default constructor to create a polynomial with constant 0
Poly::Poly()
{
	// set degree to 0
	degree = 0;
	// create an array of size 1
	coefficients = new int[degree + 1];
	coefficients[0] = 0;
}

// parameterized constructor to create a polynomial with degree degree whose coefficient is coeff
Poly::Poly(int coeff, int degree)
{
	this->degree = degree;
	// create an array of size degree+1
	coefficients = new int[degree + 1];
	// loop to set all the entries to 0
	for (int i = 0; i < degree; i++)
		coefficients[i] = 0;
	// set coefficient of degree to coeff
	coefficients[degree] = coeff;
}

// parameterized constructor to create a polynomial with constant coeff
Poly::Poly(int coeff)
{
	// set degree to 0
	degree = 0;
	// create an array of size 1
	coefficients = new int[degree + 1];
	// set coefficients of constant to coeff
	coefficients[0] = coeff;
}

// copy constructor to create a Polynomial same as p
Poly::Poly(const Poly &p)
{
	// set degree
	degree = p.degree;
	// create a new array of size degree+1
	coefficients = new int[degree + 1];
	// loop to copy the coefficients
	for (int i = 0; i <= degree; i++)
		coefficients[i] = p.coefficients[i];
}

// destructor to release the memory allocated
Poly::~Poly()
{
	delete[] coefficients;
}

// function to resize the polynomial to new_degree if new_degree > degree
void Poly::resize(int new_degree)
{
	if (new_degree > degree) // validate new_degree > degree
	{
		// create a new temporary array of size new_degree+1
		int *temp = new int[new_degree + 1];
		// loop to copy coefficients to temp
		for (int i = 0; i <= degree; i++)
			temp[i] = coefficients[i];

		// loop to set the coefficients entries to 0
		for (int i = degree + 1; i <= new_degree; i++)
			temp[i] = 0;

		// release memory of existing array
		delete[] coefficients;
		// update degree
		degree = new_degree;
		// set coefficients to point to temp
		coefficients = temp;
	}
}

// function to set coefficient of exp to coeff
void Poly::setCoeff(int exp, int coeff)
{
	// validate exp to be between [0,degree]
	if (exp >= 0 && exp <= degree)
		coefficients[exp] = coeff;
}

// function to return the coefficient of exp
int Poly::getCoeff(int exp)
{
	// validate exp to be between [0,degree]
	if (exp >= 0 && exp <= degree)
		return coefficients[exp];

	return 0; // invalid exp, return 0
}

// function to display the polynomial
void Poly::display()
{
	bool firstTermDisplayed = false;

	// loop from degree to 0
	for (int i = degree; i >= 0; i--)
	{
		if (coefficients[i] != 0) // ith coefficients is non-zero
		{
			if (firstTermDisplayed) // first term displayed
			{
				if (coefficients[i] > 0) // display sign between terms
					cout << " + ";
				else
					cout << " - ";
				cout << abs(coefficients[i]); // display absolute value of coefficient
			}
			else // first term being displayed
			{
				cout << coefficients[i];
				firstTermDisplayed = true;
			}

			// display the power of x
			if (i > 0)
			{
				if (i == 1)
					cout << "x";
				else
					cout << "x^" << i;
			}
		}
		else if (i == 0 && !firstTermDisplayed)
			cout << coefficients[i];
	}
}

// Operations on Polynomials
Poly Poly::operator=(Poly p)
{
	// set degree
	degree = p.degree;
	// create a new array of size degree+1
	coefficients = new int[degree + 1];
	// loop to copy the coefficients
	for (int i = 0; i <= degree; i++)
		coefficients[i] = p.coefficients[i];

	return *this;
}

Poly Poly::operator+(Poly p)
{
	Poly temp;
	temp.degree = degree > p.degree ? degree : p.degree; // checks if degree is greater than degree of Poly p and assigns to temp
	temp.coefficients = new int[temp.degree + 1];		 // increase size of coefficietns by 1
	for (int i = 0; i <= temp.degree; i++)
	{
		int first = 0, second = 0;
		// set terms in each iteration, check if degree in temp is less than degree from Poly p and current polynomial
		if (i <= degree)
			first = coefficients[i];

		if (i <= p.degree)
			second = p.coefficients[i];

		temp.coefficients[i] = first + second; // addition of terms
	}
	return temp; // return added Poly
}

Poly Poly::operator-(Poly p) // same as operator+ but subracting instead
{
	Poly temp;
	temp.degree = degree > p.degree ? degree : p.degree;
	temp.coefficients = new int[temp.degree + 1];
	for (int i = 0; i <= temp.degree; i++)
	{
		int first = 0, second = 0;

		if (i <= degree)
			first = coefficients[i];

		if (i <= p.degree)
			second = p.coefficients[i];

		temp.coefficients[i] = first - second;
	}
	return temp;
}

Poly Poly::operator*(Poly p)
{
	Poly temp;
	temp.degree = degree + p.degree; // multiplication means we have to add both degrees
	temp.coefficients = new int[temp.degree + 1];
	for (int i = 0; i <= temp.degree; i++) // multiplied degree here
	{
		temp.coefficients[i] = 0;
		for (int j = 0; j <= degree; j++) // degrees of both Poly p and current Poly object
		{
			for (int k = 0; k <= p.degree; k++)
			{
				if ((j + k) == i) // multiplication can happen j + k = temp degree
					temp.coefficients[i] += coefficients[j] * p.coefficients[k];
			}
		}
	}
	return temp;
}
// for +=, -=, and *=, we take the dereferened poly Object and do the appropriate operation using the overloaded operations defined above
Poly Poly::operator+=(Poly p)
{
	(*this) = (*this) + p;
	return *this;
}

Poly Poly::operator-=(Poly p)
{
	(*this) = (*this) - p;
	return *this;
}

Poly Poly::operator*=(Poly p)
{
	(*this) = (*this) * p;
	return *this;
}

bool Poly::operator==(Poly p)
{
	if (this->degree != p.degree) // polynomials with different degrees can't be equal
		return false;
	else
	{
		for (int i = 0; i <= degree; i++)
			if (coefficients[i] != p.coefficients[i]) // polynomials with different coefficents can't be equal
				return false;
	}
	return true;
}

bool Poly::operator!=(Poly p) // use overloaded operator == with ! to check if both Poly objects aren't equal
{
	return !(*this == p);
}

ostream &operator<<(ostream &out, const Poly &p)
{
	int zeroCounter = 0; // keeps track of how many coefficients are equal to 0
	for (int i = p.degree; i >= 0; i--)
	{

		if (p.coefficients[i] == 0)
		{
			zeroCounter++;
			continue;
		} // don't output zero terms
		// normal cases below for degree above 0 and 1
		else if ((i == p.degree && (i != 0 && i != 1)) && p.coefficients[i] > 0)
			out << "+" << p.coefficients[i] << "x^" << i << " ";

		else if ((i == p.degree && (i != 0 && i != 1)) && p.coefficients[i] < 0)
			out << p.coefficients[i] << "x^" << i << " ";

		else if (i == 0 && p.coefficients[i] > 0) // degree is 0 and coefficient is pos
			out << "+" << p.coefficients[i];

		else if (i == 0 && p.coefficients[i] < 0) // degree is 0 and coefficient is neg
			out << p.coefficients[i];

		else if (i == 1 && p.coefficients[i] > 0) // degree is 1 and coefficient is pos
			out << "+" << p.coefficients[i] << "x ";

		else if (i == 1 && p.coefficients[i] < 0) // degree is 1 and coefficient is neg
			out << p.coefficients[i] << "x ";

		else if (p.coefficients[i] < 0) // coefficient is neg
			out << p.coefficients[i] << "x^" << i << " ";

		else if (p.coefficients[i] > 0) // coefficient is pos
			out << "+" << p.coefficients[i] << "x^" << i << " ";
	}
	out << endl;
	if (zeroCounter == p.degree)
	{ // all terms are zero,
		return out << "0";
	}

	return out;
}

istream &operator>>(istream &in, Poly &p)
{
	int coeff, exp;
	while (1)
	{ // always true until coeff and exp is -1 -1, then break is used
		in >> coeff >> exp;
		if (coeff == -1 && exp == -1)
			break;
		p.setCoeff(exp, coeff); // call setCoeff with -1 -1 as params and it won't return anything
	}
	return in;
}

int main()
{
	/*
	Poly A(5, 7), B(2), X;
	Poly C(A);
	cout<<"A: ";
	A.display();
	cout<<endl<<"B: ";
	B.display();
	cout<<endl<<"X: ";
	X.display();
	cout<<endl<<"C: ";
	C.display();

	A.setCoeff(0, -2);
	A.setCoeff(1, 10);
	A.setCoeff(3, -4);
	cout<<endl<<"A: ";
	A.display();

	B.resize(5);
	B.setCoeff(2, 10);
	cout<<endl<<"B: ";
	B.display();

	// Added Tests
	Poly Z1,Z2,Z3,Z4;

	Z1 = B;
	cout<<endl<<"Z1: ";
	Z1.display();

	Z2 = A+B;
	cout<<endl<<"Z2: ";
	Z2.display();

	Z3 -= B;
	cout<<endl<<"Z3: ";
	Z3.display();

	Z4 = Z2*Z3;
	cout<<endl<<"Z4: ";
	Z4.display();

	if(B==Z1)
		cout<<endl<<"B==Z1";
	else
		cout<<endl<<"B!=Z1";

	Poly A(5, 7), B(3, 4), C(2), D(A), X, Y;
	Poly A2, B2, Z1, Z2;

	// set polynomials A and B to desired values
	// A = +5x^7 -4x^3 +10x -2
	// B = +3x^4 +1x^3
	cout << "Enter terms for polynomial A.  Enter a coefficient " << endl
		<< "then exponent for each term. Enter -1 -1 to terminate." << endl;
	cin >> A;                                     // or use a bunch of setCoeff
	cout << "Enter terms for polynomial B.  Enter a coefficient " << endl
		<< "then exponent for each term. Enter -1 -1 to terminate." << endl;
	cin >> B;                                     // or use a bunch of setCoeff

	// outputs exactly what is in quotes: "A = +5x^7 -4x^3 +10x -2"
	cout << "A =" << A << endl;
	// outputs exactly what is in quotes: "B = +3x^4 +1x^3"
	cout << "B =" << B << endl << endl;


	A2 = A;
	B2 = B;
	C = A + B;
	cout << "Compute C = A + B: " << C << endl << endl;

	cout << ((A == B) ? "A == B" : "A is not == B") << endl;
	cout << ((A != B) ? "A is not == B" : "A == B") << endl << endl;

	Z1 = A2 - B2;
	cout << "Compute  Z1 = A2 - B2: " << Z1 << endl;
	Z2 = B2 - A2;
	cout << "Compute  Z2 = B2 - A2: " << Z2 << endl << endl;

	cout << "Compute  D = A * B - 15" << endl;
	cout << "Before: D =" << D << endl;
	D = A * B - 15;
	cout << "After:  D =" << D << endl << endl;

	cout << "Test assignment operators" << endl;
	X = C = D = D;
	Y += A -= B *= A;
	cout << "X =" << X << endl;
	cout << "Y =" << Y << endl << endl;

	cout << "Get and Set coefficient" << endl;
	int coeff = D.getCoeff(0);
	cout << "coeff of subscript 0 of D is: " << coeff << endl;
	cout << "Doing getCoeff for term -20000" << endl;
	coeff = D.getCoeff(-20000);              // handle value out of range
	D.setCoeff(50, 0);                        // set x^0 coeff to 50
	D.setCoeff(50, 20000);                    // set x^20000 coeff to 50
	cout << "D =" << D << endl << endl;



	return 0;
	*/
}

// end of program