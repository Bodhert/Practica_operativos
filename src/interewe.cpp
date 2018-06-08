#include "interewe.h"

interewe::interewe()
{
	
}

void interewe::readBew(string bew)
{
	string word_, clean;	
	cout << bew << endl;
	ifstream fileToRead(bew.c_str(), ios::binary);

	// sometimes it fails we do not why
	unsigned long long addr , opcode;
	unsigned char hexNum;
	while(fileToRead.read((char *)&hexNum, sizeof(unsigned char)))
	{		
		// cout << hex << hexNum << endl;
		// int num = hexNum;
		opcode = hexNum >> 4;
		addr = (hexNum & 0xF);
		
		switch(opcode)
		{
			case 0:
				for(int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				addr >>= 30;
				int memref = (addr >> 15);
				int integer = (addr & 0x7FFF);

				cout << "clean addr: " <<  hex <<addr << endl;
				cout << " memref:" << hex << memref << " integer: " << integer << endl;
				
				break;
		}

		// stringstream ss;
        // ss << hex << hexNum;
        // word_ = ss.str();
		// cout << hex << "word: " << hexNum << endl;
	}
}

interewe::~interewe()
{

}