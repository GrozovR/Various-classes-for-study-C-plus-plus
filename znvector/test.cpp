#include "znvector.h"

void testvectorOpPlusEq(ZnVector& lsh, const ZnVector& rhs)
{
	try
	{
		std::cout << lsh << " += " << rhs << " = ";
		lsh += rhs;
		std::cout << lsh << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Warning: " << e.what() << std::endl;
	}
}
void testvectorOpPlus(const ZnVector& lsh, ZnVector& rhs)
{
	try
	{
		std::cout << lsh << " + " << rhs << " = ";
		std::cout << (lsh + rhs) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Warning: " << e.what() << std::endl;
	}
}
void testvectorOpIncrmDecrm( ZnVector& lsh)
{
	std::cout << lsh << "++ = ";
	lsh++;
	std::cout << lsh << std::endl;
	std::cout << "++" << lsh << " = ";
	++lsh;
	std::cout << lsh << std::endl;

	std::cout << lsh << "-- = ";
	lsh--;
	std::cout << lsh << std::endl;
	std::cout << "--" << lsh << " = ";
	--lsh;
	std::cout << lsh << std::endl;
}
void testvectorOpEqNotEq(const ZnVector& lsh, const ZnVector& rhs)
{
	std::cout << lsh << " == " << rhs << " -> ";
	std::cout << (ZnVector(lsh) == rhs) << std::endl;

	std::cout << lsh << " != " << rhs << " -> ";
	std::cout << (ZnVector(lsh) != rhs) << std::endl;
}
void main()
{

	ZnVector z0{ 12,-3,4,35 };
	ZnVector z1{ 5 ,12,3,4 };
	ZnVector z2{ 2,3,34,5,3 };

	std::cout << "z0 = " << z0 << std::endl;
	std::cout << "z1 = " << z1 << std::endl;
	std::cout << "z2 = " << z2 << std::endl;

	std::cout << "\nTest ZnVector operator+=" << std::endl;
	testvectorOpPlusEq(z0, z1);
	testvectorOpPlusEq(z1, z2);

	std::cout << "\nTest ZnVector operator+" << std::endl;
	testvectorOpPlus(z0, z1);
	testvectorOpPlus(z0, z2);

	std::cout << "\nTest ZnVector operators ++ and --" << std::endl;
	testvectorOpIncrmDecrm(z0);

	std::cout << "\nTest ZnVector operator == and !=" << std::endl;
	testvectorOpEqNotEq(z0, z0);
	testvectorOpEqNotEq(z0, z1);
	testvectorOpEqNotEq(z1, z2);

	std::cin.get();
}