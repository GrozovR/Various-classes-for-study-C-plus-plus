#include "MatrixArr.h"
#include <iostream>


void main()
{
	MatrixArr m(3, 4);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = i+j;
		}
	}

	MatrixArr d(m);
	MatrixArr z = d;

	std::cout << m[0][0]<< " " << m[1][1] << " " << m[2][2]<<std::endl;
	std::cout << d[0][0] << " " << d[1][1] << " " << d[2][2] << std::endl;
	std::cout << z[0][0] << " " << z[1][1] << " " << z[2][2] << std::endl;

	std::cin.get();
}