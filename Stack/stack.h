#pragma once
 
#include <memory>

using ValueType = double;

class stack
{
public :
	

public:
	stack() = default;
	stack(const stack& rhs) = default;
	~stack();
	
	stack & operator=(const stack & rhs) = default;

	bool isempty();
	void push(const ValueType v);
	ValueType pop();
	ValueType top();

private:
	int size{ 0 };
	ValueType* data_{ nullptr };
	int itop{ 0 }; 
};
