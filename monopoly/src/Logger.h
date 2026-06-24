#include "Header.h"
#pragma once
class Logger
{
private:
	string fileName;
	ofstream logFile;
	bool fileIsOpen = false;
public:
	Logger();
	~Logger();

	string getName();
	void setName(string name);

	void openFile();
	void writeToFile(string text);
	void closeFile();
};

