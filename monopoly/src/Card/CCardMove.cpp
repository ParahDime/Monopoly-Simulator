#include "CCardMove.h"

CCardMove::CCardMove(istream& file) : CCard(file)
{
	file >> *this;
}

CCardMove::~CCardMove()
{

}

void CCardMove::GetText(unique_ptr<Logger>& ioLog)
{
	ioLog->writeToFile(mName + "\n");
}

void CCardMove::SetSpecific(bool tSpecific)
{
	isSpecific = tSpecific;
}

bool CCardMove::GetSpecific()
{
	return isSpecific;
}

void CCardMove::SetNaming()
{
}

string CCardMove::GetNaming()
{
	return mNaming;
}

void CCardMove::SetTyping()
{
}

int CCardMove::GetTyping()
{
	return mTyping;
}

bool GetSpecific()
{
	return true;
}

istream& operator>>(istream& inputStream, CCardMove& cCardMove)
{
	//reads the no (0 for false, 1 for true)
	int cBool;
	inputStream >> cBool;
	
	//input into the object
	if (cBool == 0)
	{
		cCardMove.isSpecific = false;
	}
	else {
		cCardMove.isSpecific = true;
	}
	


	if (cCardMove.isSpecific == true) //if it is specific (named)
	{
		bool nextWord = false;

		//use nextChar to peek at next item
		int nextChar = 0;
		nextChar = inputStream.peek();

		do {

			string sWord;

			if (isdigit(nextChar)) //if next char is a digit
			{
				break; //break from while loop
			}
			else { //else add it to the name

				inputStream >> sWord;
				inputStream >> ws;
				cCardMove.mNaming += sWord + " ";
				nextChar = inputStream.peek();
			}

			nextWord = !isdigit(nextChar) && nextChar != EOF;

		} while (nextWord);
	}
	else //if not specific (typed)
	{
		inputStream >> cCardMove.mTyping;
	}

	if (!cCardMove.mNaming.empty()) {
		// 1. Shave off trailing spaces/tabs/newlines from the back
		while (!cCardMove.mNaming.empty() && std::isspace(static_cast<unsigned char>(cCardMove.mNaming.back()))) {
			cCardMove.mNaming.pop_back();
		}

		// 2. Shave off leading spaces/tabs/newlines from the front
		size_t startPos = 0;
		while (startPos < cCardMove.mNaming.length() && std::isspace(static_cast<unsigned char>(cCardMove.mNaming[startPos]))) {
			startPos++;
		}
		if (startPos > 0) {
			cCardMove.mNaming.erase(0, startPos);
		}
	}

	return inputStream;
}
