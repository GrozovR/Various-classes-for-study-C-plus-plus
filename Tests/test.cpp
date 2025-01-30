#include "pch.h"
#include "../DataStructures/CircularBuffer.h"
#include "../DataStructures/headers/complex.h"
#include <stdio.h>

/*
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
*/

TEST(CircuralBufferTest, SimpleTest) {	
	// TODO: CircuralBuffer<int> buffer( 10 );
}

using namespace std;

void testComplexConstructor(const double rl, const double im)
{
	cout << "Complex{" << rl << ',' << im << "} -> " << flush;
	cout << Complex{ rl, im } << endl;
}

void testComplexOpPlus(const Complex& lhs, const Complex& rhs)
{
	cout << lhs << " + " << rhs << " -> " << (lhs + rhs) << endl;
}

void testComplexOpMinus(const Complex& lhs, const Complex& rhs)
{
	cout << lhs << " - " << rhs << " -> " << (lhs - rhs) << endl;
}

void testComplexOpMult(const Complex& lhs, const Complex& rhs)
{
	cout << lhs << " * " << rhs << " -> " << (lhs * rhs) << endl;
}

void testComplexOpDiv(const Complex& lhs, const Complex& rhs)
{
	cout << lhs << " / " << rhs << " -> " << (lhs / rhs) << endl;
}

void testComplexOpCmpEq(const Complex& lhs, const Complex& rhs)
{
	cout << lhs << " == " << rhs << " -> " << boolalpha << (lhs == rhs) << endl;
}

void testComplexOpCmpNotEq(const Complex& lhs, const Complex& rhs)
{
	cout << lhs << " != " << rhs << " -> " << boolalpha << (lhs != rhs) << endl;
}

TEST(ComplexTest, SimpleTest)
{


	cout << "Complex{} -> " << Complex{} << endl;
	Complex r02{ 2 };
	cout << "Complex{ 2 } -> " << r02 << endl;

	testComplexConstructor(1, 2);
	testComplexConstructor(2.4, 1.3);
	testComplexConstructor(-2.1, 3.2);

	Complex r03{ -1.2, 5.3 };
	Complex r04{ 2.2, -3.12 };

	cout << "\nTest Complex operator+" << endl;
	testComplexOpPlus(r03, -r03);
	testComplexOpPlus(r03, r04);

	cout << "\nTest Complex operator+" << endl;
	testComplexOpPlus(r03, -r03);
	testComplexOpPlus(r03, r04);

	cout << "\nTest Complex operator-" << endl;
	testComplexOpMinus(r03, r03);
	testComplexOpMinus(r03, r04);

	cout << "\nTest Complex operator*" << endl;
	testComplexOpMult(r03, r03);
	testComplexOpMult(r03, r04);

	cout << "\nTest Complex operator/" << endl;
	testComplexOpDiv(r03, r03);
	testComplexOpDiv(r03, r04);

	cout << "\nTest Complex operator==" << endl;
	testComplexOpCmpEq(r03, r03);
	testComplexOpCmpEq(r03, -r03);
	testComplexOpCmpEq(r03, r04);

	cout << "\nTest Complex operator!=" << endl;
	testComplexOpCmpNotEq(r03, r03);
	testComplexOpCmpNotEq(r03, -r03);
	testComplexOpCmpNotEq(r03, r04);

}