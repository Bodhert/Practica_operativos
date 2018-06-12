#ifndef CONTROLEWE_H
#define CONTROLEWE_H
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
#include <semaphore.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>


using namespace std;


class controlewe
{
    public:
        controlewe(string memoryName, string bews);
        void readMemg(string mew);
        void ajustMemory();
        int createMemory();
        void assingPointers();
        void assignDataNum(unsigned int pos, int num);
        void assignDataString(unsigned int pos, char word);
        void writeMemg();
        virtual ~controlewe();

    private:
        string memName;
        //creating the values of the  memory segments , with initial values of 0
        unsigned int memgStart, memgLimit;
        unsigned int litnumStart, litnumLimit;
        unsigned int litstrStart, litstrLimit;
        unsigned int dataNumStart, dataNumLimit;
        unsigned int datastrStart, datastrLimit;
        unsigned int workloadStart, workloadLimit;

        // pointers to the memory segments
        unsigned char *pMem;
        unsigned int *pMemg;
        unsigned int *litnum;
        unsigned char *litstr;
        unsigned int *datanum;
        unsigned char *datasrt;
        sem_t *workload;  // have my doubts about what is the type of the workload

        // mascaras de bits
        const int maskBase = 0xFFFF0000;
        const int maskLimit = 0xFFFF;

        // politicas
        map<int,char> dataNumPolitics;
        map<int,char> dataStrPolitics;

        //memgvalues
        vector<unsigned int> memgcopy;

};

#endif // CONTROLEWE_H