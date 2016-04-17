#include "WordFrequencyDictionary.h"

void main()
{
	WFDictionary dict;
	const std::string path = "C:\\....";
	dict.setPathToFile(path);
	//dict.countWordFrequency();
	dict.printResult();

	system("pause");
}