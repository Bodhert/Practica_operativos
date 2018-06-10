#include "interewe.h"

interewe::interewe(string bewfile_,string memoryName_)
{
	bewfile = bewfile_; memoryName = memoryName_;
}

int interewe::getMemory()
{
	cout << "interewe mapping: " << memoryName << endl;
	int shm = shm_open(memoryName.c_str(), O_RDWR, 0600); // i do not know if this method is going well
	off_t size_mem = 1000;
	pMem = static_cast<unsigned char *>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));

	if ((void *)pMem == (void *)-1)
	{
		cerr << "Problems with memory map" << endl;
		return 1;
	}

	// *(pMem+1001) = 33;
	// cout << *int(pMem+1) << endl;

	cout << "Shared memory already assigned and mapped succefully" << endl;

	// cout << litnum;
	return 0;
}

void interewe::readBew()
{
	// cout << bew << endl;
	ifstream fileToRead(bewfile.c_str(), ios::binary);

	// sometimes it fails we do not why
	unsigned long long addr;
	unsigned char hexNum, opcode, op;
	unsigned short memref, integerAdrs, stringAdrs, memrefSource, memrefDestination,
		memrefOper1, memrefOper2, memrefSize;
	bool datanum = 0;

	while (fileToRead.read((char *)&hexNum, sizeof(unsigned char)))
	{
		// cout << hex << hexNum << endl;
		// int num = hexNum;
		opcode = hexNum >> 4;
		addr = hexNum & 0xF;

		switch (opcode)
		{
			case 0:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
			break;

			case 1:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
			break;

			case 2:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
				break;

			case 3:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
			break;

			case 4:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;

			case 5:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
			break;

			case 6:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
			break;

			case 7:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
			break;

			case 8:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				memref = addr >> 13;
			break;

			case 9:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
			break;

			case 10:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
				addr >>= 30;

				memrefSize = (addr & 0x7FFF);
				memrefDestination = addr >> 15;
			break;

			case 11:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
			break;

			case 12:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
				integerAdrs = addr >> 13;
			break;

			case 13:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
				addr >>= 11;
				integerAdrs = addr & 0x7FF;
				memrefOper2 = ((addr >> 15) & 0x7FF);
				memrefOper1 = ((addr >> 30) & 0x7FF);
				addr >>= 45;
				datanum = addr & 1;
				op = addr >> 1;
			break;

			case 14:
				cout << dec << "opcode: " << int(opcode) << endl;
			break;

			case 15:
				cout << dec << "opcode: " << int(opcode) << endl;
			break;
		}
		cout << endl;
		instructions.push_back(instruction(opcode, addr));
	}
	

	// for(int i = 0; i < instructions.size();++i)	
	// {
	// 	cout << "instrucciones: " <<  hex  << " opcode: " << int(instructions[i].first)
	// 	<<  " addr: " << instructions[i].second  << endl;
	// }

	for (int i = 0; i < instructions.size();++i)
	{

		// cout << "instrucciones: " <<  hex << instructions[i] << endl;
		
		opcode = instructions[i].first;
		addr = instructions[i].second;
		cout << "opcode: " << int(opcode) << " addr:" << addr << endl;
		switch (opcode)
		{
			case 0:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				integerAdrs = (addr & 0x7FFF);
				memref = (addr >> 15);
				cout << "clean addr: " << hex << addr << endl;
				cout << " memref:" << hex << memref << " integerAdr: " << integerAdrs << endl;
			break;

			case 1:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				stringAdrs = (addr & 0x7FFF);
				memref = (addr >> 15);
				cout << "clean addr: " << hex << addr << endl;
				cout << " memref:" << hex << memref << " integerAdrr: " << stringAdrs << endl;
			break;

			case 2:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				integerAdrs = (addr & 0x7FFF);
				memref = (addr >> 15);
				cout << "clean addr: " << hex << addr << endl;
				cout << " memref: " << hex << memref << " integerAdrr: " << integerAdrs << endl;
			break;

			case 3:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
			break;

			case 4:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 29;
				memrefSource = (addr & 0x7FFF);
				memrefDestination = ((addr >> 15) & 0x7FFF);
				datanum = addr >> 30; // later to check what to do;
				if (datanum)		  // do someting in case that datanum is on
			break;

			case 5:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 11;
				memrefOper2 = addr & 0x7FF;
				memrefOper1 = ((addr >> 15) & 0x7FF);
				memrefDestination = ((addr >> 30) & 0x7FF);
				addr >>= 45;
				datanum = addr & 1;
				op = addr >> 1;
			break;

			case 6:
				cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				cout << hex << " hex:" << addr << endl;
				addr >>= 14;
				integerAdrs = (addr & 0x7FFF);
				memrefSource = ((addr >> 15) & 0x7FFF);
				memrefDestination = ((addr >> 30) & 0x7FFF);
				datanum = (addr >> 45);
				if (datanum) // do something
			break;

			case 7:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 14;
				memrefSource = (addr & 0x7FFF);
				integerAdrs = ((addr >> 15) & 0x7FFF);
				memrefDestination = ((addr >> 30) & 0x7FFF);
				datanum = (addr >> 45);
				if (datanum) // do something
			break;

			case 8:
				cout << "opcode: " << int(opcode) << endl;
				memref = addr >> 13;
			break;

			case 9:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
			break;

			case 10:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				memrefSize = (addr & 0x7FFF);
				memrefDestination = addr >> 15;
			break;

			case 11:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
			break;

			case 12:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				integerAdrs = addr >> 13;
			break;

			case 13:
				cout << "opcode: " << int(opcode) << endl;
				cout << hex << " hex:" << addr << endl;
				addr >>= 11;
				integerAdrs = addr & 0x7FF;
				memrefOper2 = ((addr >> 15) & 0x7FF);
				memrefOper1 = ((addr >> 30) & 0x7FF);
				addr >>= 45;
				datanum = addr & 1;
				op = addr >> 1;
			break;

			case 14:
				cout << dec << "opcode: " << int(opcode) << endl;
			break;

			case 15:
				cout << dec << "opcode: " << int(opcode) << endl;
			break;
		}
		cout << endl;
		// stringstream ss;
		// ss << hex << hexNum;
		// word_ = ss.str();
		// cout << hex << "word: " << hexNum << endl;
	}

}

interewe::~interewe()
{
}