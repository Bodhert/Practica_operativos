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

using namespace std;

class interewe
{
	public:
		interewe(string ewe_,string memoryName_);
		void readBew();
		int getMemory();
		virtual ~interewe();
	private:
		unsigned char *pMem;
        unsigned int *litnum;
        unsigned char *litstr;
        unsigned int *datanum;
        unsigned char *datasrt;
        unsigned int *workload;

		string memoryName, bewfile;

};

#endif