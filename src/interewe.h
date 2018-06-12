#ifndef INTEREWE_H
#define INTEREWE_H
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <pthread.h>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
#include <semaphore.h>

using namespace std;

typedef pair <unsigned char, unsigned long long> instruction;

class interewe
{
	public:
		interewe(string ewe_,string memoryName_);
		void readBew();
		int getMemory();
		void assignPointer();
		virtual ~interewe();
	private:
		unsigned char *pMem;
		unsigned int *pMemg;		
        unsigned int *litnum;
        unsigned char *litstr;
        unsigned int *datanum;
        unsigned char *datastr;
        sem_t *workload;

		unsigned int memgStart, memgLimit;
        unsigned int litnumStart, litnumLimit;
        unsigned int litstrStart, litstrLimit;
        unsigned int dataNumStart, dataNumLimit;
        unsigned int datastrStart, datastrLimit;
        unsigned int workloadStart, workloadLimit;

		string memoryName, bewfile;
		vector<instruction> instructions;

		const int maskLimit = 0xFFFF; 

};

#endif