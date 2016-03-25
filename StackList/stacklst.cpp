#include "stacklst.h"

Node::Node(const ValueType v, Node * next)
	:data_{ v }
	, next_{ next }
{
}


StackLst::StackLst(StackLst & rhs)
{
	*this = rhs;
}

StackLst::~StackLst()
{
	while (!isEmpty())
	{
		pop();
	}
}

StackLst & StackLst::operator=(StackLst & rhs)
{
	while (!isEmpty())	{ pop(); }

	if (!rhs.isEmpty())
	{
		StackLst tmp;

		tmp.push(rhs.top());
		Node* N{ rhs.head_ };
		Node* nextN{ N->next_ };

		while (nullptr != nextN)
		{
			N = nextN;
			nextN = N->next_;

			tmp.push(N->data_);
		}
		while (!tmp.isEmpty())
		{
			push(tmp.top());
			tmp.pop();
		}
	}

	return *this;
}

bool StackLst::isEmpty()
{
	return nullptr == head_;
}

void StackLst::pop()
{
	if (isEmpty())
	{
		throw std::exception("Stack is empty!");
	}
	Node* deleted(head_);
	head_ = head_->next_;
	delete deleted;
}

void StackLst::push(ValueType v)
{
	Node* added = new Node(v, head_);
	head_ = added;
}

ValueType StackLst::top()
{
	if (isEmpty())
	{
		throw std::exception("Stack is empty");
	}
	return head_->data_;
}
