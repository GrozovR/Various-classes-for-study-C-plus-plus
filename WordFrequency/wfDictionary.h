#ifndef WFDICTIONARY_2015_H
#define WFDICTIONARY_2015_H

#include <iostream>
#include <string>
#include <map>

class WFDictionary
{
public:

	WFDictionary();
	~WFDictionary() = default;

	void run(const std::string path);
	
	std::ostream& print(std::ostream& ostrm) const;

private:
	void getMemory();
	void writeMemory();
	void clearMemory();

	void cleanText(std::string& text_);
	void countWordFrequency();

	std::map<std::string, int> dictionary;
	std::string text_;
};

std::ostream& operator<<(std::ostream& ostrm, const WFDictionary& lhs);

#endif

