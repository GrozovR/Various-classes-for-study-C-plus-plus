#include <iostream>
using namespace std;

class Rational
{
public:
	Rational() noexcept;
	Rational(const int num) noexcept;
	Rational(const int num, const int den);
	Rational(const Rational& rhs) noexcept;
	~Rational();

	Rational& operator=(const Rational& rhs); 
	Rational& operator=(Rational&& rhs);
	//Rational operator=(const Rational &);

	Rational operator+=(const Rational &);
	Rational operator-=(const Rational &);
	Rational operator*=(const Rational &);
	Rational operator/=(const Rational &);
	
	Rational operator++();
	Rational operator++(int notused);
	Rational operator--();
	Rational operator--(int notused);

	bool operator<(const Rational &) const;
	bool operator>(const Rational &) const;
	bool operator<=(const Rational &) const;
	bool operator>=(const Rational &) const;
	bool operator==(const Rational &) const;
	bool operator!=(const Rational &) const;

	Rational operator-() const;
	int num() const;
	int den() const;

	ostream& write(ostream& ostrm) const;	
	istream& read(istream& istrm);

private:
	void normalize();
	
private:
	int numerator;
	int denominator;

};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
std::ostream & operator<<(std::ostream & ostrm,const Rational&);
std::istream & operator>>(std::istream & ostrm,Rational&);