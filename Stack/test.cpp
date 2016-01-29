#include "stack.h"
#include  <iostream>

using namespace std;

void testIsEmpty(stack& s)
{
	cout << "\nTest stack empty" << endl;
	cout << "stack.isempty() -> " << s.isempty() << endl;
}
void testStackPop(stack& s)
{
	try
	{
		cout << "\nTest pop() stack" << endl;
		cout << "stack.pop() = " << s.pop();
	}
	catch (exception& e)
	{
		cout << "Error: " << e.what();
	}
	
}
void testStackTop(stack& s)
{
	try
	{
		cout << "\nTest top() stack" << endl;
		cout << "stack.top = " << s.top();
	}
	catch (exception& e)
	{
		cout << "Error: " << e.what();
	}
	
}
void testStackPush(stack& s, const ValueType & i)
{
	cout << "\nTest stack.push(" << i << ")" << endl;
	s.push(i);
}

int main()
{

	stack s;
	
	testIsEmpty(s);
	testStackPop(s);
	testStackTop(s);

	testStackPush(s, 1);
	testStackPush(s, 4);
	testStackPush(s, 7);

	testStackTop(s);
	testStackTop(s);

	testStackPop(s);
	testStackPop(s);
	testStackPop(s);
	testStackPop(s);


	cin.get();
	return 0;
}