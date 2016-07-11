#ifndef SORT_UTIL_H_2016
#define SORT_UTIL_H_2016

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <locale>
#include <io.h>
#include <functional> 
#include <cctype>


class CSortUtility
{
public:
	//конструктор и деструктор
	CSortUtility() = default;
	~CSortUtility();

public:
	//вызов справки
	void help() const;
	//метод выполн¤ющий сортировку и вывод результатов
	void run();

public: 
	//установка пути входного файла
	void setPath(std::string filePath);
	//установка пути выходного файла
	void setOutFile(std::string outFilePath);
	//установка режима ингорировани¤ начальных пробелов
	void setIgnoreLeadBlanks(bool state);
	//установка режима ингорировани¤ заглавных букв
	void setIgnoreLetterCase(bool state);
	//установка режима реверса при сортировке
	void setReverse(bool state);
	
private:	
	void clear();
	//вывод результатов
	void print();
	void sort();
	void trim(std::string &s);

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


