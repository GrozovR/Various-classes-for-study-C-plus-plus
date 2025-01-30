#include "complex.h"
#include <iostream>


Complex::Complex(const double real) noexcept
	: Complex{real,0}
{}
Complex::Complex(const double rl, const double im)
	: real{rl}
	, imaginary{im}
{
}
Complex::Complex(const Complex& rhs) noexcept = default;
Complex::~Complex() = default;

Complex& Complex::operator=(const Complex & rhs) = default;
Complex& Complex::operator=(Complex&& rhs) = default;

Complex Complex::operator+=(const Complex & rhs)
{
	real += rhs.real;
	imaginary += rhs.imaginary;
	return *this;
}
Complex Complex::operator-=(const Complex & rhs)
{
	real -= rhs.real;
	imaginary -= rhs.imaginary;
	return *this;
}
Complex Complex::operator*=(const Complex & rhs)
{
	real = real*rhs.real - imaginary*rhs.imaginary;
	imaginary = imaginary*rhs.real + real*rhs.imaginary;
	return *this;
}
Complex Complex::operator/=(const Complex & rhs)
{
	if (rhs.real == 0 && rhs.imaginary == 0)
	{
		throw std::domain_error("zero denominator");
	}
	else
	{
		real = (real*rhs.real + imaginary*rhs.imaginary) / (rhs.real*rhs.real + rhs.imaginary*rhs.imaginary);
		imaginary = (imaginary*rhs.real - real*rhs.imaginary) / (rhs.real*rhs.real + rhs.imaginary*rhs.imaginary);
		return *this;
	}
}

Complex operator+(const Complex & lhs, const Complex & rhs)
{
	Complex summ{ lhs };
	summ += rhs;
	return summ;
}
Complex operator-(const Complex & lhs, const Complex & rhs)
{
	Complex summ{ lhs };
	summ -= rhs;
	return summ;
}
Complex operator*(const Complex & lhs, const Complex & rhs)
{
	Complex summ{ lhs };
	summ *= rhs;
	return summ;
}
Complex operator/(const Complex & lhs, const Complex & rhs)
{
	Complex summ{ lhs };
	summ /= rhs;
	return summ;
}

Complex Complex::operator++()
{
	real++;
	return *this;
}
Complex Complex::operator++(int notused)
{
	Complex temp = *this;
	temp.real++;
	return temp;
}
Complex Complex::operator--()
{
	real--;
	return *this;
}
Complex Complex::operator--(int notused)
{
	Complex temp = *this;
	temp.real--;
	return temp;
}

bool Complex::operator==(const Complex& rhs) const
{
	return (real==rhs.real)&&(imaginary == rhs.imaginary);
}
bool Complex::operator!=(const Complex& rhs) const
{
	return !(*this == rhs);
}


Complex Complex::operator-() const
{
	return Complex{ -real,-imaginary };
}

double Complex::rl() const
{
	return real;
}
double Complex::im() const
{
	return imaginary;
}

std::ostream& Complex::write(std::ostream& ostrm) const
{ 
	ostrm << real << " + " << imaginary << "i" ;
	return ostrm;
}
std::ostream & operator<<(std::ostream & ostrm, const Complex& rhs)
{
	return rhs.write(ostrm);
}
