#include "queuelist.h"

Node::Node(const ValueType v)
	:data_{ v }
{
}

QueueLst::QueueLst(QueueLst & rhs)
{
	*this = rhs;
}

QueueLst & QueueLst::operator=(QueueLst & rhs)
{

}

QueueLst::~QueueLst()
{
	while (0 == isEmpty())
		dequeue();
}

bool QueueLst::isEmpty() const
{
	return nullptr == head_;
}

void QueueLst::enqueue(const ValueType v)
{
	Node* added = new Node(v);
	if (isEmpty()) head_->next_ = added;
	else tail_->next_ = added;
}

ValueType QueueLst::dequeue()
{
	if (isEmpty())
	{
		throw std::exception("Queue is empty");
	}
	ValueType temp{ head_->data_ };
	if (0 == isEmpty())
	{
		Node * deleted{ head_ };
		head_ = head_->next_;
	}
	return temp;
}