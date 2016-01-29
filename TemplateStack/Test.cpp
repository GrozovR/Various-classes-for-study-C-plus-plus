#include "TemplateStack.h"
#include <iostream>

void main()
{
	tstack<int> stack;
	int a{ 3 };
	stack.push(a);
	
	//test copy constructor
	tstack<int> stackcopy(stack);
	
	tstack<char> charstack;
	charstack.push('a');
	
	
	std::cout << stack.top()<<stackcopy.top()<<charstack.top()<<std::endl;		

	a = 5; stack.push(a);
	a = 7; stack.push(a);

	stackcopy = stack;
	std::cout << stackcopy.top();
	stackcopy.pop();
	std::cout << stackcopy.top();

	std::cin.get();
}