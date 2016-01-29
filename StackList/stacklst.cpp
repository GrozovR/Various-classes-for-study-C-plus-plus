#include "stacklst.h"

Node::Node(const int v, Node * next)
	:data_{ v }
	, next_{ next }
{
}

StackLst::StackLst(StackLst& rhs)
{
	*this = rhs;
}
StackLst::~StackLst()
{
	while (0 == isEmpty())
		pop();
}

bool StackLst::isEmpty() const
{
	return nullptr == head_;
}

void StackLst::push(const ValueType v)
{
	Node* added = new Node(v, head_);
	head_ = added;
}

ValueType StackLst::pop()
{
	if (isEmpty())
	{
		throw std::exception("Stack is empty");
	}
	ValueType temp{ head_->data_ };
	if (0 == isEmpty())
	{
		Node* deleted{ head_ };
		head_ = head_->next_;
		delete deleted;
	}
	return temp;
}

ValueType StackLst::top()
{
	if (isEmpty())
	{
		throw std::exception("Stack is empty");
	}
	return head_->data_;
}

StackLst& StackLst::operator=(StackLst& rhs)
{
	while (0 == isEmpty()) { pop(); }

	if (!rhs.isEmpty())
	{
		StackLst tmp;

		tmp.push(rhs.top());

		Node* N{ rhs.head_};
		Node* nextN{ N->next_ };

		while (nullptr != nextN)
		{	
			N = nextN;
			nextN = N->next_;
			//head_
			tmp.push(N->data_);
		}
		while (0 == tmp.isEmpty())
		{
			push(tmp.top());
			tmp.pop();
		}
	}
	return *this;
}