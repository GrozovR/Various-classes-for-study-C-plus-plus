#ifndef STACKLST_H_2016

#include <memory>
using ValueType = int;

struct Node
{
	Node(const ValueType v, Node* next);

	ValueType data_{ 0 };
	Node* next_{ nullptr };
};


class StackLst
{
public:
	StackLst() = default;
	StackLst(StackLst& rhs);
	~StackLst();

	StackLst &operator=(StackLst& rhs);

	bool isEmpty();
	void pop();
	void push(ValueType v);
	ValueType top();

private:
	Node* head_{ nullptr };
};

#endif // !STACKLST_H_2016
