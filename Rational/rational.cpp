#include "rational.h"
#include <iostream>
using namespace std;

Rational::Rational() noexcept
	:Rational{ 0, 1 }
{
}
Rational::Rational(const int inum) noexcept
	: Rational{ inum, 1 }
{
}
Rational::Rational(const int inum, const int iden)
	: numerator{ inum }
	, denominator{ iden }
{
	if (0 == denominator)
	{
		throw domain_error("zero denominator in Rational");
	}
	normalize();
}
Rational::Rational(const Rational& rhs) noexcept = default;
Rational::~Rational() = default;

Rational& Rational::operator=(const Rational& rhs) = default;
Rational& Rational::operator=(Rational&& rhs) = default;
//Rational Rational::operator=(const Rational &op2)
//{
//	numerator = op2.numerator;
//	denominator = op2.denominator;
//	normalize();
//	return *this;
//}

Rational Rational::operator+=(const Rational &op2) 
{
	numerator = numerator*op2.denominator + denominator*op2.numerator;
	denominator *= op2.denominator;
	normalize();
	return *this;
}
Rational Rational::operator-=(const Rational &op2)
{
	numerator = numerator*op2.denominator - denominator*op2.numerator;
	denominator *= op2.denominator;
	normalize();
	return *this;
}
Rational Rational::operator*=(const Rational &op2)
{
	numerator *= op2.numerator;
	denominator *= op2.denominator;
	normalize();
	return *this;
}
Rational Rational::operator/=(const Rational &op2)
{
	numerator *= op2.denominator;
	denominator *= op2.numerator;
	normalize();
	return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	Rational summ{ lhs };
	summ += rhs;
	return summ;
}
Rational operator-(const Rational& lhs, const Rational& rhs)
{
	Rational summ{ lhs };
	summ -= rhs;
	return summ;
}
Rational operator*(const Rational& lhs, const Rational& rhs)
{
	Rational summ{ lhs };
	summ *= rhs;
	return summ;
}
Rational operator/(const Rational& lhs, const Rational& rhs)
{
	Rational summ{ lhs };
	summ /= rhs;
	return summ;
}

Rational Rational::operator++()
{
	numerator += denominator;
	return *this;
}
Rational Rational::operator++(int notused)
{
	Rational temp = *this;
	temp.numerator += temp.denominator;
	return temp;
}
Rational Rational::operator--()
{
	numerator -= denominator;
	return *this;
}
Rational Rational::operator--(int notused)
{
	Rational temp = *this;
	temp.numerator -= temp.denominator;
	return temp;
}

bool Rational::operator<(const Rational &op2) const
{
	return (numerator*op2.denominator < op2.numerator*denominator);
}
bool Rational::operator<=(const Rational &op2) const
{
	return (numerator*op2.denominator <= op2.numerator*denominator);
}
bool Rational::operator>(const Rational &op2) const
{
	return (numerator*op2.denominator > op2.numerator*denominator);
}
bool Rational::operator>=(const Rational &op2) const
{
	return (numerator*op2.denominator >= op2.numerator*denominator);
}
bool Rational::operator==(const Rational &op2) const
{
	return (numerator*op2.denominator == op2.numerator*denominator);
}
bool Rational::operator!=(const Rational &op2) const
{
	return (numerator*op2.denominator != op2.numerator*denominator);
}

int Rational::num() const
{
	return numerator;
}
int Rational::den() const
{
	return denominator;
}
Rational Rational::operator-() const
{
	return Rational{ -numerator,denominator };
}

void Rational::normalize()
{
	if (0 == numerator)
	{
		denominator = 1;
	}
	else if (denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}

	for (int i = 2; i <= numerator; i++)
	{
		if ((numerator%i == 0) && (denominator%i == 0))
		{
			numerator /= i;
			denominator /= i;
			normalize();
		}
	}
}

ostream& Rational::write(ostream& ostrm) const
{
	ostrm << numerator << "/" << denominator ;
	return ostrm;
}

ostream & operator<<(ostream& os, const Rational &op2)
{
	return op2.write(os);
}

istream& Rational::read(istream& istrm)
{
	int num{ 0 };
	istrm >> num;
	char sep{ 0 };
	istrm >> sep;
	if ('/' != sep)
		istrm.setstate(ios_base::failbit);
	int den{ 0 };
	istrm >> den;
	if (istrm)
	{
		numerator = num;
		denominator = den;
		normalize();
	}
	return istrm;
}

istream & operator>>(istream & istrm, Rational &r)
{
	return r.read(istrm);
}