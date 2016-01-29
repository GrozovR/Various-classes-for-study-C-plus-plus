#include "r3vector.h"


void testVectorByIndexRead(const R3Vector& v, const ptrdiff_t i) 
{ 
	try 
	{ 
		
		cout << "read v[" << i << "] -> "; 
		cout << v[i]; 
	}
	catch (const out_of_range& ex) 
	{
		cout << "exception caught " << ex.what();
	} 
}

void testVectorOpPlus(const R3Vector& lhs, const R3Vector& rhs)
{
	cout << lhs << " + " << rhs << " -> " << (lhs + rhs) << endl;
}

void testVectorOpDiv(const R3Vector& lhs, const double rhs)
{
	cout << lhs << " / " << rhs << " -> " << (lhs / rhs) << endl;
}

void testVectorOpEq(const R3Vector& lhs, const R3Vector& rhs)
{
	cout << lhs << " == " << rhs << " -> " << (lhs == rhs) << endl;
}
void testVectorOpNotEq(const R3Vector& lhs, const R3Vector& rhs)
{
	cout << lhs << " != " << rhs << " -> " << (lhs != rhs) << endl;
}

int main() 
{ 
	constexpr ptrdiff_t nSize{ 3 * R3Vector::dim() };
	R3Vector v0;
	cout << "x=" << v0.x() << " y=" << v0.y() << " z=" << v0.z() << endl;
	R3Vector v1{ 0.2, 0.6, -5.8 }; 
	cout << v1 << endl; 
	R3Vector v2{ v1 };
	cout << v2 << endl; 
	v2.rx() *= 2;
	v2.ry() *= 2; 
	v2.rz() *= 2; 
	cout << v2 << endl; 
	
	for (ptrdiff_t i{ -2 }; i <= v2.dim(); i += 1)
	{
		testVectorByIndexRead(v2, i); 
		cout << endl; 
	} 
	double scale{ 1.2 }; 
	cout << v2 << " * " << scale << " -> " << flush; 
	cout << (v2 * scale) << endl; 
	
	cout << "\nTest R3Vector operator+" << endl;
	testVectorOpPlus(v1, v2);
	testVectorOpPlus(-v1, v2);

	cout << "\nTest R3Vector operator/" << endl;
	testVectorOpDiv(v1, 3);
	testVectorOpDiv(v2, 2);

	cout << "\nTest R3Vector operator==" << endl;
	testVectorOpEq(v1, v1);
	testVectorOpEq(v2, v1);

	cout << "\nTest R3Vector operator !=" << endl;
	testVectorOpNotEq(v1, v1);
	testVectorOpNotEq(v2, v1);

	cin.get();
	return 0; 


}