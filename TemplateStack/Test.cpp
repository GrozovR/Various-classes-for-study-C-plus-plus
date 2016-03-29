#include "TemplateStack.h"
#include <iostream>

//TODO: made test of class


void main()
{
	tStack<int> stack;
	int a{ 3 };
	stack.push(a);
	
	//test copy constructor
	//tStack<int> stackcopy(stack);
	
	tStack<char> charstack;
	charstack.push('a');
	
	
	std::cout << stack.top()<<charstack.top()<<std::endl;		

	a = 5; stack.push(a);
	a = 7; stack.push(a);

	
}