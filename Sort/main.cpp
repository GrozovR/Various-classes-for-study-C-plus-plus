#include "sort_util.h"

void main(int args, char** argv)
{
	CSortUtility app;

	std::string line;
	bool syntaxError{ false };

	for (int i = 1; i < args; i++)
	{
		std::string command = argv[i];

		if (command == "-r"){
			app.setReverse(true);
		}
		else if (command == "-f"){
			app.setIgnoreLetterCase(true);
		}
		else if (command == "-b"){
			app.setIgnoreLeadBlanks(true);
		}
		else if (command == "-h"){
			app.help();
		}
		else if (command == "-i"){
			if (i + 1 < args){
				i++;
				std::string path = argv[i];
				app.setPath(path);
			}
			else{
				std::cout << "Syntax error! Missing input file path argument!" << std::endl;
				syntaxError = true;
				break;
			}
		}
		else if (command == "-o"){
			if (i + 1 < args){
				i++;
				std::string path = argv[i];
				app.setOutFile(path);
			}
			else{
				std::cout << "Syntax error! Missing out file path argument!" << std::endl;
				syntaxError = true;
				break;
			}
		}
		else{
			std::cout << "Syntax error! Wrong command: " << command << std::endl << std::endl;
			syntaxError = true;
			break;
		}
	}

	if (!syntaxError) app.run();
}