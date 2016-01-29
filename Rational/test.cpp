#include "rational.h"
#include <iostream>
#include <sstream>
#include <stdexcept>


using namespace std;

void testRationalConstructor(const int num, const int den)
{
	cout << "Rational{" << num << ',' << den << "} -> " << flush;
	cout << Rational{ num, den } << endl;
}
void testRationalOpPlus(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " + " << rhs << " -> " << (lhs + rhs) << endl;
}
void testRationalOpMinus(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " - " << rhs << " -> " << (lhs - rhs) << endl;
}
void testRationalOpMult(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " * " << rhs << " -> " << (lhs * rhs) << endl;
}
void testRationalOpDiv(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " / " << rhs << " -> " << (lhs / rhs) << endl;
}
void testRationalOpCmpEq(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " == " << rhs << " -> " << boolalpha << (lhs == rhs) << endl;
}
void testRationalOpCmpNotEq(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " != " << rhs << " -> " << boolalpha << (lhs != rhs) << endl;
}
void testRationalOpCmpLess(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " < " << rhs << " -> " << boolalpha << (lhs < rhs) << endl;
}
void testRationalOpCmpLessOrEq(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " <= " << rhs << " -> " << boolalpha << (lhs <= rhs) << endl;

}
void testRationalOpCmpMore(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " > " << rhs << " -> " << boolalpha << (lhs > rhs) << endl;

}
void testRationalOpCmpMoreOrEq(const Rational& lhs, const Rational& rhs)
{
	cout << lhs << " >= " << rhs << " -> " << boolalpha << (lhs >= rhs) << endl;

}

void testReadFromStream(const string& s)
{

	istringstream istrm(s);
	Rational r;
	istrm >> r;
	cout << "Read from text \"" << s << "\" -> " << r << ", stream state is " << boolalpha << !!istrm << endl;
}

void main()
{
	
	cout << "Rational{} -> " << Rational{} << endl;
	Rational r02{ 2 };
	cout << "Rational{ 2 } -> " << r02 << endl;

	testRationalConstructor(1, 2);
	testRationalConstructor(-1, 2);
	testRationalConstructor(1, -2);
	testRationalConstructor(-1, -2);
	try
	{
		testRationalConstructor(5, 0);
	}
	catch (domain_error& e)
	{
		cout << "exception caught (" << e.what() << ')' << endl;
	}
	Rational r03{ -1, 5 };
	Rational r04{ 2, -3 };

	cout << "\nTest Rational operator+" << endl;
	testRationalOpPlus(r03, -r03);
	testRationalOpPlus(r03, r04);

	cout << "\nTest Rational operator-" << endl;
	testRationalOpMinus(r03, r03);
	testRationalOpMinus(r03, r04);

	cout << "\nTest Rational operator*" << endl;
	testRationalOpMult(r03, r03);
	testRationalOpMult(r03, r04);

	cout << "\nTest Rational operator/" << endl;
	testRationalOpDiv(r03, r03);
	testRationalOpDiv(r03, r04);

	cout << "\nTest Rational operator==" << endl;
	testRationalOpCmpEq(r03, r03);
	testRationalOpCmpEq(r03, -r03);
	testRationalOpCmpEq(r03, r04);

	cout << "\nTest Rational operator!=" << endl;
	testRationalOpCmpNotEq(r03, r03);
	testRationalOpCmpNotEq(r03, -r03);
	testRationalOpCmpNotEq(r03, r04);

	cout << "\nTest Rational operator<" << endl;
	testRationalOpCmpLess(r03, r03);
	testRationalOpCmpLess(r03, -r03);
	testRationalOpCmpLess(r03, r04);
	
	cout << "\nTest Rational operator<=" << endl;
	testRationalOpCmpLessOrEq(r03, r03);
	testRationalOpCmpLessOrEq(r03, -r03);
	testRationalOpCmpLessOrEq(r03, r04);

	cout << "\nTest Rational operator>" << endl;
	testRationalOpCmpMore(r03, r03);
	testRationalOpCmpMore(r03, -r03);
	testRationalOpCmpMore(r03, r04);

	cout << "\nTest Rational operator>=" << endl;
	testRationalOpCmpMoreOrEq(r03, r03);
	testRationalOpCmpMoreOrEq(r03, -r03);
	testRationalOpCmpMoreOrEq(r03, r04);


	cout << "\nTest Rational read from stream" << endl;
	testReadFromStream("");
	testReadFromStream("1");
	testReadFromStream("1/2");
	testReadFromStream("-4/5");
	testReadFromStream("3/-5");
	testReadFromStream("-5/-2");
	testReadFromStream("-5.0/-2");

	
	/*cout << "a = " << a;
	cout << "b = " << b;

	c = a + b;
	cout << "a + b = " << c << "\n";

	c = a - b;
	cout << "a - b = " << c << "\n";

	c = a * b;
	cout << "a * b = " << c << "\n";

	c = a / b;
	cout << "a / b = " << c << "\n";*/

}