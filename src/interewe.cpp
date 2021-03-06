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
    pMemg = (unsigned int *) pMem;
	// cout << *(pMemg) << endl; // test
	return 0;
}

void interewe::readBew()
{
	// cout << bew << endl;
	ifstream fileToRead(bewfile.c_str(), ios::binary);

	// sometimes it fails we do not why
	unsigned long long addr;
	unsigned char hexNum, opcode, op , current;
	unsigned short memref, integerAdrs, stringAdrs, memrefSource, memrefDestination,
		memrefOper1, memrefOper2, memrefSize;
	unsigned int displacement;
	bool flag = 0;

	int readInt;

	string readString;

	while (fileToRead.read((char *)&hexNum, sizeof(unsigned char)))
	{
		// cout << hex << hexNum << endl;
		// int num = hexNum;
		opcode = hexNum >> 4;
		addr = hexNum & 0xF;

		switch (opcode)
		{
			case 0:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
			break;

			case 1:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
			break;

			case 2:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
				break;

			case 3:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
			break;

			case 4:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;

			case 5:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
			break;

			case 6:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
			break;

			case 7:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
			break;

			case 8:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				memref = addr >> 13;
			break;

			case 9:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
			break;

			case 10:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
				addr >>= 30;

				memrefSize = (addr & 0x7FFF);
				memrefDestination = addr >> 15;
			break;

			case 11:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
			break;

			case 12:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 3; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
				integerAdrs = addr >> 13;
			break;

			case 13:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
				addr >>= 11;
				integerAdrs = addr & 0x7FF;
				memrefOper2 = ((addr >> 15) & 0x7FF);
				memrefOper1 = ((addr >> 30) & 0x7FF);
				addr >>= 45;
				flag = addr & 1;
				op = addr >> 1;
			break;

			case 14:
				// cout << dec << "opcode: " << int(opcode) << endl;
			break;

			case 15:
				// cout << dec << "opcode: " << int(opcode) << endl;
			break;
		}
		// cout << endl;
		instructions.push_back(instruction(opcode, addr));
	}
	
	if(getMemory() == 1) return; // fails to ma;
	assignPointer();
	// for(int i = 0; i < instructions.size();++i)	
	// {
	// 	cout << "instrucciones: " <<  hex  << " opcode: " << int(instructions[i].first)
	// 	<<  " addr: " << instructions[i].second  << endl;
	// }

	//testig semaphore of read and write
	// int test;
	// sem_wait(&(*(workload + 0)));
	// cout << "The procces: " << getpid() << " is waiting for input" << endl;
	// cin >> test;
	// cout << "The procces: " << getpid() << " already read " << endl;
	// sem_post(&(*(workload + 0)));

	for (int PC = 0; PC < instructions.size();++PC)
	{

		// cout << "instrucciones: " <<  hex << instructions[i] << endl;
		
		opcode = instructions[PC].first;
		addr = instructions[PC].second;
		// cout << "opcode: " << int(opcode) << " addr:" << addr << endl;
		switch (opcode)
		{
			case 0:
				cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				integerAdrs = (addr & 0x7FFF);
				memref = (addr >> 15);
				*(datanum + memref)  =  *(litnum + integerAdrs);
				// cout << "clean addr: " << hex << addr << endl;
				// cout << " memref:" << hex << memref << " integerAdr: " << integerAdrs << endl;
			break;

			case 1:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				stringAdrs = (addr & 0x7FFF);
				memref = (addr >> 15);

				displacement = 0;
				current = *(litstr + stringAdrs);
				while(current)
				{
					*(datastr+memref+displacement) = current;
					++displacement;
					current = *(litstr + stringAdrs+displacement);
				}
				*(datastr+memref+displacement) = current;

				// cout << "clean addr: " << hex << addr << endl;
				// cout << " memref:" << hex << memref << " integerAdrr: " << stringAdrs << endl;
			break;

			case 2:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				integerAdrs = (addr & 0x7FFF);
				memref = (addr >> 15);

				*(datanum + memref) = PC + integerAdrs;
				// cout << "clean addr: " << hex << addr << endl;
				// cout << " memref: " << hex << memref << " integerAdrr: " << integerAdrs << endl;
			break;

			case 3:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
				PC = memref;
			break;

			case 4:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 29;
				memrefSource = (addr & 0x7FFF);
				memrefDestination = ((addr >> 15) & 0x7FFF);
				flag = addr >> 30;
				if (flag)
				{
					*(datanum + memrefDestination) = *(datanum + memrefSource);
				}
				else
				{
					// ahora se hace .
					displacement = 0;
					current = *(datastr + memrefSource);
					while(current)
					{
						*(datastr + memrefDestination + displacement) = current;
						++displacement;
						current = *(datastr + memrefSource + displacement);
					}
					*(datastr + memrefDestination + displacement) = current;
				}
			break;

			case 5:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 11;
				memrefOper2 = addr & 0x7FF;
				memrefOper1 = ((addr >> 15) & 0x7FF);
				memrefDestination = ((addr >> 30) & 0x7FF);
				addr >>= 45;
				flag = addr & 1;
				op = addr >> 1;
				if(flag)
				{
					switch(op)
					{
						case 0:
							*(datanum + memrefDestination) = 
								*(datanum + memrefOper1) + *(datanum + memrefOper1);
						break;

						case 1:
							*(datanum + memrefDestination) = 
								*(datanum + memrefOper1) - *(datanum + memrefOper1);
						break;

						case 2:
						*(datanum + memrefDestination) = 
								*(datanum + memrefOper1) * *(datanum + memrefOper1);
						break;

						case 3:
						*(datanum + memrefDestination) = 
								*(datanum + memrefOper1) / *(datanum + memrefOper1);
						break;

						case 4:
						*(datanum + memrefDestination) = 
							*(datanum + memrefOper1) - *(datanum + memrefOper1);
						break;

						case 5:
						*(datanum + memrefDestination) = 
								*(datanum + memrefOper1) % *(datanum + memrefOper1);
						break;
					}
				}
				else 
				{
					string memrefOper1_String = "" , memrefOper2_String = "", 
							result = "";
					char curr_oper1, curr_oper2;

					curr_oper1 = *(datastr + memrefOper1);
					displacement = 0;
					while(curr_oper1)
					{
						memrefOper1_String += curr_oper1;
						++displacement;
						curr_oper1 = *(datastr + memrefOper1 + displacement);
					}

					memrefOper1_String += curr_oper1;

					displacement = 0;

					while(curr_oper2)
					{
						memrefOper1_String += curr_oper2;
						++displacement;
						curr_oper2 = *(datastr + memrefOper2 + displacement);
					}

					memrefOper2_String += curr_oper1;


					int sizeOper1 = memrefOper1_String.size();
					int sizeOper2 = memrefOper2_String.size();
					int maxzise = max(sizeOper1,sizeOper2);



					switch(op)
					{
						case 0:
							for(int i = 0; i < maxzise; ++i)
							{
								if(sizeOper1 < i && sizeOper2 < i) 
									result += char(memrefOper1_String[i]) + 
											  char(memrefOper2_String[i]);
								else if(i > sizeOper1)
									result += char(memrefOper2_String[i]);
								else if(i > sizeOper2)
									result += char(memrefOper1_String[i]);									
							}
						break;

						case 1:
							for(int i = 0; i < maxzise; ++i)
							{
								if(sizeOper1 < i && sizeOper2 < i) 
									result += char(memrefOper1_String[i]) -
											  char(memrefOper2_String[i]);
								else if(i > sizeOper1)
									result += char(memrefOper2_String[i]);
								else if(i > sizeOper2)
									result += char(memrefOper1_String[i]);									
							}
						break;

						case 2:
							for(int i = 0; i < maxzise; ++i)
							{
								if(sizeOper1 < i && sizeOper2 < i) 
									result += char(memrefOper1_String[i]) *
											  char(memrefOper2_String[i]);
								else if(i > sizeOper1)
									result += char(memrefOper2_String[i]);
								else if(i > sizeOper2)
									result += char(memrefOper1_String[i]);									
							}
						break;

						case 3:
							for(int i = 0; i < maxzise; ++i)
							{
								if(sizeOper1 < i && sizeOper2 < i) 
									result += char(memrefOper1_String[i]) /
											  char(memrefOper2_String[i]);
								else if(i > sizeOper1)
									result += char(memrefOper2_String[i]);
								else if(i > sizeOper2)
									result += char(memrefOper1_String[i]);									
							}
						break;

						case 4:
							for(int i = 0; i < maxzise; ++i)
							{
								if(sizeOper1 < i && sizeOper2 < i) 
									result += char(memrefOper1_String[i]) % 
											  char(memrefOper2_String[i]);
								else if(i > sizeOper1)
									result += char(memrefOper2_String[i]);
								else if(i > sizeOper2)
									result += char(memrefOper1_String[i]);									
							}
						break;
					}


					for(int i = 0; i < result.size(); ++i)
					{
						*(datastr + memrefDestination + i) = result[i];
					}
				}
			break;

			case 6:
				// cout << "opcode: " << int(opcode) << endl;
				for (int i = 0; i < 7; ++i)
				{
					fileToRead.read((char *)&hexNum, sizeof(unsigned char));
					addr <<= 8;
					addr |= hexNum;
				}
				// cout << hex << " hex:" << addr << endl;
				addr >>= 14;
				integerAdrs = (addr & 0x7FFF);
				memrefSource = ((addr >> 15) & 0x7FFF);
				memrefDestination = ((addr >> 30) & 0x7FFF);
				flag = (addr >> 45);
				if (flag) 
				{
					*(datanum + memrefDestination) = 
						*(datanum + (memrefSource + integerAdrs));
				}
				else
				{
					*(datastr + memrefDestination) = 
						*(datastr + (memrefSource + integerAdrs));
				}
			break;

			case 7:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 14;
				memrefSource = (addr & 0x7FFF);
				integerAdrs = ((addr >> 15) & 0x7FFF);
				memrefDestination = ((addr >> 30) & 0x7FFF);
				flag = (addr >> 45);
				if (flag) 
				{
					*(datanum + memrefDestination + integerAdrs) = 
						*(datanum + memrefSource);
				}
				else
				{
					*(datastr + memrefDestination + integerAdrs) = 
						*(datastr + memrefSource);
				}
			break;

			case 8:
				// cout << "opcode: " << int(opcode) << endl;
					memref = addr >> 13;
					sem_wait(&(*(workload + 0)));
					cout << "The procces: " << getpid() << " is waiting an Int for input" << endl;
					cin >> readInt;
					cout << "The procces: " << getpid() << " already read " << endl;
					sem_post(&(*(workload + 0)));
					*(datanum + memref) = readInt;
			break;

			case 9:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
				sem_wait(&(*(workload + 0)));
				cout << "The procces: " << getpid() << " is writing " << endl <<
						dec << *(datanum + memref);
				sem_post(&(*(workload + 0)));
			break;

			case 10:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 30;
				memrefSize = (addr & 0x7FFF);
				memrefDestination = addr >> 15;
				sem_wait(&(*(workload + 0)));
				cout << "the procces: " << getpid() << " is waiting for a string" << endl;
				cin >> readString;
				sem_post(&(*(workload + 0)));
				for(current= 0; current < readString.size() && current < memrefSize; current)
				{
					*(datastr + memrefDestination + current) = readString[current];
				}
					*(datastr + memrefDestination + current) = 0;


			break;

			case 11:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				memref = addr >> 13;
				current = *(datastr + addr);
				displacement = 0;
				sem_wait(&(*(workload + 0)));
				while(current)
				{
					cout << current;
					++displacement;
					current = *(datastr + addr + displacement);
				}
				sem_post(&(*(workload + 0)));
				cout << endl;
			break;

			case 12:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				integerAdrs = addr >> 13;
				PC = *(litnum + integerAdrs);
			break;

			case 13:
				// cout << "opcode: " << int(opcode) << endl;
				// cout << hex << " hex:" << addr << endl;
				addr >>= 11;
				integerAdrs = addr & 0x7FF;
				memrefOper2 = ((addr >> 15) & 0x7FF);
				memrefOper1 = ((addr >> 30) & 0x7FF);
				addr >>= 45;
				flag = addr & 1;
				op = addr >> 1;
				if(flag)
				{
					switch(op)
					{
						case 0:
							if(*(datanum + memrefOper1) >= *(datanum + memrefOper2))
								PC = *(litnum + integerAdrs);
						break;

						case 1:
							if(*(datanum + memrefOper1) > *(datanum + memrefOper2))
								PC = *(litnum + integerAdrs);
						break;

						case 2:
							if(*(datanum + memrefOper1) <= *(datanum + memrefOper2))
								PC = *(litnum + integerAdrs);
						
						break;

						case 3:
							if(*(datanum + memrefOper1) < *(datanum + memrefOper2))
								PC = *(litnum + integerAdrs);

						break;

						case 4:
							if(*(datanum + memrefOper1) == *(datanum + memrefOper2))
								PC = *(litnum + integerAdrs);
						break;

						case 5:
							if(*(datanum + memrefOper1) != *(datanum + memrefOper2))
								PC = *(litnum + integerAdrs);							
						break;
					}
				}
				else
				{
					switch(op)
					{

						case 0:
								if(*(datastr + memrefOper1) >= *(datastr + memrefOper2))
									PC = *(litnum + integerAdrs);
							break;

							case 1:
								if(*(datastr + memrefOper1) > *(datastr + memrefOper2))
									PC = *(litnum + integerAdrs);
							break;

							case 2:
								if(*(datastr + memrefOper1) <= *(datastr + memrefOper2))
									PC = *(litnum + integerAdrs);
							
							break;

							case 3:
								if(*(datastr + memrefOper1) < *(datastr + memrefOper2))
									PC = *(litnum + integerAdrs);

							break;

							case 4:
								if(*(datastr + memrefOper1) == *(datastr + memrefOper2))
									PC = *(litnum + integerAdrs);
							break;

							case 5:
								if(*(datastr + memrefOper1) != *(datastr + memrefOper2))
									PC = *(litnum + integerAdrs);							
							break;
					}
					
				}
			break;

			case 14:
				// cout << dec << "opcode: " << int(opcode) << endl;
				return;
			break;

			case 15:
				// cout << dec << "opcode: " << int(opcode) << endl;
				sem_wait(&(*(workload + 0)));
				cout << "input 'c' for continue the procces " << endl;
				sem_post(&(*(workload + 0)));
			break;
		}
		// cout << endl;
		// stringstream ss;
		// ss << hex << hexNum;
		// word_ = ss.str();
		// cout << hex << "word: " << hexNum << endl;
	}

	fileToRead.seekg(0, fileToRead.beg);
    fileToRead.close(); // avoiding that a buffer stays open (previous experiences)
	
}

void interewe::assignPointer()
{
	//Pmemg ya esta;
	unsigned int hexMemg = *(pMemg);
	unsigned int hexLitNum = *(pMemg+1);
	unsigned int hexLitStr = *(pMemg+2);
	unsigned int hexDataNum = *(pMemg+3);
	unsigned int hexDataString = *(pMemg+4);
	unsigned int hexWorkload = *(pMemg+5);

	// cout << "hexMemg: " << hex << hexMemg << endl;
	// cout << "hexLitNum: " << hex << hexLitNum << endl;
	// cout << "hexLitStr: " <<  hex << hexLitStr << endl;
	// cout << "hexDataNum: " << hex << hexDataNum << endl;
	// cout << "hexDataString: " << hex << hexDataString << endl;
	// cout << "hexWorkload: " <<  hex << hexWorkload << endl;

	 unsigned int ajust;
    //memg memory starts with no problem or ajust
    memgStart =  (hexMemg >> 16) << 2;
    memgLimit = (hexMemg & maskLimit) << 2;
    cout << "memg: " << hex << " start:" << memgStart << " limit:" <<memgLimit << endl;

    // // start position of litNum
    litnumStart = (hexLitNum >> 16) << 2;
    litnumLimit = (hexLitNum & maskLimit) << 2;
    // // cout << "litnumStart: " << litnumStart << " litnumLimit:" << litnumLimit << endl;
    litnumLimit += litnumStart;
    cout << hex << "litnum start: " << litnumStart << " litnum limit: "  <<  litnumLimit << endl;

    // //ajusting the start position of litstr
    litstrStart = (hexLitStr >>  16) << 2;
	litstrLimit = (hexLitStr & maskLimit) ;
    // // cout << " litstrStart: " << hex <<litstrStart << endl;
    ajust = litstrStart + litstrLimit;
    // // cout << hex << ajust << endl;
    // // cout << " litstrStart: " << hex << litstrStart << endl;
    // // cout << " test:" << hex << litstrStart << " " << hex << litstrStart - (litstrStart%4) + 4 << endl;
    if (ajust % 4 != 0)
        litstrLimit = ajust - (ajust % 4) + 4;
    cout << "litstr start: " << hex << litstrStart << " litsrt limit: " << litstrLimit << endl;

    // //ajusting the start position of dataNum
    // // cout << "dataNumStart: " << dataNumStart << " dataNumLimit: " << dataNumLimit << endl;
    dataNumStart = (hexDataNum >> 16) << 2;
    dataNumLimit = (hexDataNum & maskLimit) << 2;
    dataNumLimit += dataNumStart;
    cout << "dataNum start : " << hex << dataNumStart <<   " dataNum limit:" << dataNumLimit << endl;

    // //ajusting the start position of dataStr
    // // cout << "datastrStart: " << datastrStart << " datastrLimit: " << datastrLimit << endl;
    datastrStart = (hexDataString >> 16) << 2;
    datastrLimit = (hexDataString & maskLimit);
    ajust = datastrStart +  datastrLimit ;
    if (ajust % 4 != 0)
        datastrLimit = ajust - (ajust % 4) + 4;
    cout << hex << "datastr start:  " << datastrStart <<  " datastr limit: "  << datastrLimit << endl;

    // //ajusting the start position of workload
    workloadStart = (hexWorkload >> 16) << 2;
    workloadLimit = (hexWorkload &  maskLimit);
    // workloadLimit = workloadStart + workloadLimit;
    cout << hex << "workload start : " << workloadStart << " workload limit: " << workloadLimit << endl;


	// here I finally assign the pointers
	litnum = (unsigned int *)(pMem + litnumStart);
    // *litnum = -1; // testing
    // *(litnum+1) = 34; // testing

    litstr = (unsigned char *)(pMem + litstrStart);
    // *litstr = 't';  // testing
    // *(litstr+1) = 'o'; // testing
    // *(litstr+2) = '6'; // testing
    // *(litstr+3) = 'Z'; // testing

    datanum = (unsigned int *)(pMem + dataNumStart);
	// *datanum = 4;

    datastr = (unsigned char*)(pMem + datastrStart);
    workload = (sem_t *)(pMem + workloadStart);
	
}

interewe::~interewe()
{
}