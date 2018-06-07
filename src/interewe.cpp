#include "interewe.h"

interewe::interewe()
{
	
}

void interewe::readBew(string bew)
{
	string word_, clean;	
	cout << bew << endl;
	ifstream fileToRead(bew.c_str(), ios::binary);

	int hexNum;
	while(fileToRead.read((char *)&hexNum, sizeof(char)))
	{				
		stringstream ss;
        ss << hex << hexNum;
        word_ = ss.str();
		cout << hex << "word: " << word_ << endl;
	}
}

interewe::~interewe()
{

}


	


