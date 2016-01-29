#include "wfDictionary.h"
#include <algorithm>
//read previous state of dictionary

//must to do
void WFDictionary::getMemory()
{
	//read previous state of dictionary
}
void WFDictionary::writeMemory()
{
}
void WFDictionary::clearMemory()
{
}

void WFDictionary::cleanText(std::string& text_)
{
	std::string space = " ";
	std::string charToReplace = ",./<?;:1234567890-=~!@#$^&*()_+|{}[]";
	//replace trashsign to space
	for (int i = 0; i < text_.length(); i++)
	{
		for (int j = 0; j < charToReplace.length(); j++)
		{
			if (charToReplace[j] == text_[i]) text_.replace(i, 1, space);
		}
	}
	//convert letters to lowercase
	std::transform(text_.begin(), text_.end(),text_.begin(), ::tolower);
	
}
void WFDictionary::countWordFrequency()
{
	int wordBegin{ -1 };
	int wordLength{ 0 };
	char space = ' ';

	for (int i = 0; i < text_.length(); i++)
	{
		if (-1 != wordBegin && text_[i] != space)  wordLength++;
		if (-1 == wordBegin && text_[i] != space) { wordBegin = i; wordLength++; }

		if (text_[i] == ' ' && wordBegin != -1)
		{
			std::string tmp;
			tmp.assign(text_, wordBegin, wordLength);
			dictionary[tmp]++;

			wordBegin = -1;
			wordLength = 0;
		}
	}
}

//std::ostream& WFDictionary::print(std::stream& ostrm) const
//{
//	for (auto i = _map.begin(); i != _map.end(); ++i)
//	{
//		std::ostrim << i->first << " : " << i->second << endl;
//	}
//	return std::ostrim;
//}

WFDictionary::WFDictionary()
{
	getMemory();
}

void WFDictionary::run(const std::string path)
{
	// read text at path

	//writeMemory()
}