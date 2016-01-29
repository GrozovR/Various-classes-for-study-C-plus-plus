#pragma once

#include <memory>
using ValueType = int;

struct Node
{
	Node(const int  v, Node* next);
	
	ValueType data_{ 0 };
	Node* next_{ nullptr };
};

class StackLst
{
public:
	StackLst() = default;
	StackLst(StackLst& rhs);
	~StackLst();

	StackLst & operator=(StackLst & rhs);

	bool isEmpty() const;
	void push(const ValueType v );
	ValueType pop();
	ValueType top();
	
private:	
	Node* head_{ nullptr };
};


