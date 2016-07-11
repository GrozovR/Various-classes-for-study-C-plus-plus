#include "sort_util.h"


//for ignore_leading_blanks
struct No_case{
	bool operator() (const std::string& x, const std::string& y) const
	{
		for (int i{ 0 }; i < x.length(); ++i){
			if (i == y.length()) return false;
			char xx = tolower(x[i]);
			char yy = tolower(y[i]);

			if (xx < yy) return true;
			if (yy < xx) return false;
		}
		if (x.length() == y.length()) return false;
		return true;
	}
};

CSortUtility::~CSortUtility()
{
	m_dataFromFiles.clear();
}

void CSortUtility::help() const
{
	std::cout << "SORT [OPTIONS] [FILEPATH] [OUTFILE]" << std::endl << std::endl;
	std::cout << "[OPTIONS]  : -r [reverse]; -f [ignore letter case]; -b [ignore leading blanks]" << std::endl;
	std::cout << "[FILEPATH] : -i [input file path]" << std::endl;
	std::cout << "[OUTFILE]  : -o [out file]" << std::endl;
}

void CSortUtility::clear()
{
	m_dataFromFiles.clear();
	m_filesPath.clear();

	m_errorMessage = "Error: ";
	m_errorState = false;

	m_ignoreLeadingBlanks = false;
	m_ignoreCase = false;
	m_reverse = false;
	m_outInFile = false;
}

void CSortUtility::print()
{
	if (m_errorState)
	{
		std::cout << m_errorMessage << std::endl << std::endl;
		help();
	}
	else if (m_outInFile) {
		//write in file		
		std::ofstream ofs(m_outFilePath);
		if (ofs) {
			for (const auto line : m_dataFromFiles)
				ofs << line << std::endl;
		}
		else {
			m_errorState = true;
			m_errorMessage += "incorrect out file path [" + m_outFilePath + "]; ";
			print();
		}
	}
	else {
		//write in console
		for (const auto line : m_dataFromFiles)
		{
			std::cout << line << std::endl << std::endl;
		}
	}

}

void CSortUtility::run()
{
	for (std::string path : m_filesPath)
	{
		readFile(path);
	}
	print();
}

void CSortUtility::setPath(std::string filePath)
{
	if (fileExists(filePath.c_str())) {
		m_filesPath.push_back(filePath);
	}
	else {
		m_errorState = true;
		m_errorMessage += "incorrect file path [" + filePath + "]; ";
	}
}

void CSortUtility::setIgnoreLeadBlanks(bool state)
{
	m_ignoreLeadingBlanks = state;
}

void CSortUtility::setIgnoreLetterCase(bool state)
{
	m_ignoreCase = state;
}

void CSortUtility::setReverse(bool state)
{
	m_reverse = state;
}

void CSortUtility::setOutFile(std::string outFilePath)
{
	m_outInFile = true;
	m_outFilePath = outFilePath;
}

void CSortUtility::readFile(std::string inStr)
{
	std::ifstream ifs{ inStr };
	std::string line;

	if (ifs)
	{
		while (std::getline(ifs, line))
		{
			if (m_ignoreLeadingBlanks)
			{
				trim(line);
				if (line == "") continue;
			}
		
			m_dataFromFiles.push_back(line);
		}
	}
	ifs.close();
	sort();
}

void CSortUtility::trim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

void CSortUtility::sort()
{
	if (m_ignoreCase){
		if (m_reverse) std::sort(m_dataFromFiles.rbegin(), m_dataFromFiles.rend(), No_case());
		else std::sort(m_dataFromFiles.begin(), m_dataFromFiles.end(), No_case());
	}
	else{
		if (m_reverse) std::sort(m_dataFromFiles.rbegin(), m_dataFromFiles.rend());
		else std::sort(m_dataFromFiles.begin(), m_dataFromFiles.end());
	}
}

bool CSortUtility::fileExists(const char * fname) const
{
	return _access(fname, 0) != -1;	
}

