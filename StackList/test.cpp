#include "stacklst.h"
#include <iostream>

using namespace std;

void testStacklstIsEmpty( StackLst& s)
{
	cout << "\nTest stack empty" << endl;
	cout << "stack.isempty() -> " << s.isEmpty() << endl;
}
void testStacklstPop(StackLst& s)
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
void testStacklstTop(StackLst& s)
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
void testStacklstPush(StackLst& s, const ValueType & i)
{
	cout << "\nTest stack.push(" << i << ")" << endl;
	s.push(i);
}

void main()
{
	StackLst s;

	testStacklstIsEmpty(s);
	testStacklstPop(s);
	testStacklstTop(s);

	testStacklstPush(s, 1);
	testStacklstPush(s, 4);
	testStacklstPush(s, 7);

	testStacklstTop(s);
	testStacklstTop(s);

	StackLst copys(s);
	
	std::cout << copys.top() << endl;
	copys.pop();
	
	std::cout << copys.top() << endl;
	copys.pop();

	std::cout << copys.top() << endl;
	copys.pop();	

	system("pause");
}