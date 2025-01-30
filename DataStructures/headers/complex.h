#ifndef COMPLEX_H_2015
#define COMPLEX_H_2015
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>

class Complex
{
public:
	Complex() noexcept = default;
	Complex(const double real) noexcept;
	Complex(const double real,const double im);
	Complex(const Complex& rhs) noexcept;
	~Complex();

	Complex& operator=(const Complex & rhs);
	Complex& operator=(Complex&& rhs);

	Complex operator+=(const Complex &);
	Complex operator-=(const Complex &);
	Complex operator*=(const Complex &);
	Complex operator/=(const Complex &);

	Complex operator++();
	Complex operator++(int notused);
	Complex operator--();
	Complex operator--(int notused);

	bool operator==(const Complex &) const;
	bool operator!=(const Complex &) const;
		
	Complex operator-() const;
	double rl() const;
	double im() const;

	std::ostream& write(std::ostream& ostrm) const;

	// istream& read(istream& istrm);
	 
protected:
	double real{0};
	double imaginary{0};
};

Complex operator+(const Complex & lhs, const Complex & rhs);
Complex operator-(const Complex & lhs, const Complex & rhs);
Complex operator*(const Complex & lhs, const Complex & rhs);
Complex operator/(const Complex & lhs, const Complex & rhs);
std::ostream & operator<<(std::ostream & ostrm, const Complex&);

#endif COMPLEX_H_2015