#include "stack.h"

stack::~stack()
{
	delete[] data_;
}

void stack::push(const ValueType v)
{	
	if (size == 0)
	{
		size++;
		double* newData{ new double[size] };
		delete[] data_;
		data_ = newData;
		data_[itop] = v;
	}
	if (itop == size)
	{
		
		double* newData{ new double[size * 2] };
		for (int i{ 0 }; i < size; i++)
		{
			newData[i] = data_[i];
		}
		delete[] data_;
		data_ = newData;
		size *= 2;
	}
	data_[itop] = v; 
	itop++;
}

bool stack::isempty()
{
	return 0 == itop;
}

ValueType stack::pop()
{
	if (isempty())
	{
		throw std::exception("Stack is empty!");

	}
		itop--;
		return data_[itop];
}

double stack::top() 
{
	if (isempty())
	{
		throw std::exception("Stack is empty!");
	}
	return data_[itop-1];
}