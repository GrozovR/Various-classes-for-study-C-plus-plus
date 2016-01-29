#include "queuelist.h"
#include <iostream>

void main()
{
	QueueLst Queue;

	std::cout << Queue.isEmpty() << std::endl;
	int input = 3;
	Queue.enqueue(input);
	/*
	input = 6;
	Queue.enqueue(input);

	input = 9;
	Queue.enqueue(input);*/

	std::cout << Queue.isEmpty()<<std::endl;

}