#include "sort_util.h"

void main(int args, char** argv)
{
	CSortUtility app;

	app.setReverse(true);
	app.setIgnoreLeadBlanks(true);
	app.setIgnoreLetterCase(true);

	app.setOutFile("D:\\piska\\11.txt");

	app.setPath("D:\\1.txt");
	app.setPath("D:\\2.txt");
	app.setPath("D:\\3.txt");
	//app.setPath("D:\\11.txt");

	app.run();
		
}