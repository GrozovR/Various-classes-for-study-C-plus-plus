#ifndef WFDICTIONARY_2016
#define WFDICTIONARY_2016

#include <iostream>
#include <string>
#include <map>
#include <fstream>

class WFDictionary
{
public:
	WFDictionary() = default;
	~WFDictionary() = default;

	//std::ostream& print(std::ostream& ostrm) const;

	void setPathToFile(const std::string path);
	void printResult();
private:
	void readFile();
	void countWordFrequency();
private:
	std::string m_path;
	std::map<std::string, int> m_dictionary;
	std::string m_text;
};

#endif // !WFDICTIONARY_2016
