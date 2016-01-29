#ifndef QUEUELIST_H_2015
#define QUEUELIST_H_2015
#define _SCL_SECURE_NO_WARNINGS


//возможно без двусвязного списка не обойтись???

#include <memory>
using ValueType = int;

struct Node
{
	Node(const ValueType v);

	ValueType data_{ 0 };
	Node * next_{ nullptr };
};

class QueueLst
{
public:
	QueueLst() = default;
	QueueLst(QueueLst & rhs);
	~QueueLst();

	QueueLst & operator=(QueueLst & rhs);

	bool isEmpty() const;
	void enqueue(const ValueType v);
	ValueType dequeue();
	
private:
	Node* head_{ nullptr };
	Node* tail_{ nullptr };
};

#endif QUEUELIST_H_2015