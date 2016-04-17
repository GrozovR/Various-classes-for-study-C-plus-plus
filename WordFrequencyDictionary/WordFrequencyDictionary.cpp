#include "WordFrequencyDictionary.h"

void WFDictionary::countWordFrequency()
{
	int wordBegin{ -1 };
	int wordLength{ 0 };
	char space = ' ';

	for (int i = 0; i < m_text.length(); i++)
	{
		if (-1 != wordBegin && m_text[i] != space)  wordLength++;
		if (-1 == wordBegin && m_text[i] != space) { wordBegin = i; wordLength++; }

		if (m_text[i] == ' ' && wordBegin != -1)
		{
			std::string tmp;
			tmp.assign(m_text, wordBegin, wordLength);
			m_dictionary[tmp]++;

			wordBegin = -1;
			wordLength = 0;
		}
	}
}


void WFDictionary::setPathToFile(const std::string path)
{
	m_path = path;
	readFile();
}

void WFDictionary::printResult()
{
	for (auto it = m_dictionary.begin(); it != m_dictionary.end(); ++it)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

void WFDictionary::readFile()
{
	std::ifstream istream;
	std::string line;
	istream.open(m_path);

	while (!istream.eof())
	{
		std::getline(istream, line);

		m_text = line;
		countWordFrequency();
		m_text.clear();
	}
}