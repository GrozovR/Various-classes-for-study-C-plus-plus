#ifndef SORT_UTIL_H_2016
#define SORT_UTIL_H_2016

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <locale>
#include <io.h>

class CSortUtility
{
public:
	CSortUtility() = default;
	~CSortUtility();

public:
	void help() const;
	void run();

public: 
	void setPath(std::string filePath);
	void setIgnoreLeadBlanks(bool state);
	void setIgnoreLetterCase(bool state);
	void setReverse(bool state);
	void setOutFile(std::string outFilePath);

private:	
	void clear();
	void print();
	void sort();
	bool fileExists(const char *fname) const;
	void readFile(std::string inStr);

private:	
	std::string m_errorMessage = "Error: ";
	bool m_errorState{ false };

	std::vector<std::string> m_dataFromFiles;
	std::vector<std::string> m_filesPath;
	std::string m_outFilePath;

	bool m_ignoreLeadingBlanks{ false };
	bool m_ignoreCase{ false };
	bool m_reverse{ false };
	bool m_outInFile{ false };	
};

#endif // !SORT_UTIL_H_2016


