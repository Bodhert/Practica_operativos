#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>

using namespace std;

//creating the values of the  memory segements , with initial values of 0
int memgStart, memgLimit;
int litnumStart, litnumLimit;
int litstrStart, litstrLimit;
int dataNumStart, dataNumLimit;
int datastrStart, datastrLimit;
int workloadStart, workloadLimit;

char *pMem;
/*
have in midn that we have to work in this segments too
A,B,C,D,E,
in wich i have no idea what to do with them
*/

/* in this method i have a doubt about if the .memg is always 15??*/
void readMemg(string memg)
{
    if (memg != ".memg")
    {
        cout << "memory format has to be .memg" << endl;
        return;
    }

    ifstream fileToRead(memg);

    char clean;

    //reading and cleaning 0:0x0000 - 0000F (memg segment)
    fileToRead >> clean >> clean;
    fileToRead >> hex >> memgStart; // >> hex, converts to int given the format
    fileToRead >> clean;
    fileToRead >> hex >> memgLimit;
    // cout << "limits of .memg: 1 :" << memgStart << " 2: " << memgLimit << endl;

    //reading and cleaning from format file  (litnum)
    fileToRead >> clean >> clean;
    fileToRead >> hex >> litnumStart;
    fileToRead >> clean;
    fileToRead >> hex >> litnumLimit;
    // cout << "limits of litnum: 1 :" << litnumStart << " 2: " << litnumLimit << endl;

    // reading and cleanig from format file (litstr)
    fileToRead >> clean >> clean;
    fileToRead >> hex >> litstrStart;
    fileToRead >> clean;
    fileToRead >> hex >> litstrLimit;
    // cout << "limits of litstr: 1 :" << litstrStart << " 2: " << litstrLimit << endl;

    // reading and cleanig from format file (data num)
    fileToRead >> clean >> clean;
    fileToRead >> hex >> dataNumStart;
    fileToRead >> clean;
    fileToRead >> hex >> dataNumLimit;
    // cout << "limits of datanum: 1 :" << dataNumStart << " 2: " << dataNumLimit << endl;

    //reding and cleaning from format file (datastr)
    fileToRead >> clean >> clean;
    fileToRead >> hex >> datastrStart;
    fileToRead >> clean;
    fileToRead >> hex >> datastrLimit;
    // cout << "limits of datastr: 1 :" << datastrStart << " 2: " << datastrLimit << endl;

    //reading and cleaning from format file (workload)
    fileToRead >> clean >> clean;
    fileToRead >> hex >> workloadStart;
    fileToRead >> clean;
    fileToRead >> hex >> workloadLimit;
    // cout << "limits of workload: 1 :" << workloadStart << " 2: " << workloadLimit << endl;

    fileToRead.seekg(0, fileToRead.beg);
    fileToRead.close(); // avoiding that a buffer stays open (previous experiences)
}

int createMemory(int argc , string memName)
{
    if (argc != 2)
    {
        cerr << "Usage control: <shmname>" << endl;
        return 1;
    }

    int shm = shm_open(memName.c_str(), O_CREAT | O_RDWR | O_EXCL, 0600);

    if (shm == -1)
    {
        cerr << "Shared memory already created" << endl;
        return 1;
    }

    off_t size_mem = 1000;

    if (ftruncate(shm, size_mem) == -1)
    {
        cerr << "Problems with memory size" << endl;
        return 1;
    }

    pMem = static_cast<char *>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE,
                                          MAP_SHARED, shm, 0));

    if ((void *)pMem == (void *)-1)
    {
        cerr << "Problems with memory map" << endl;
        return 1;
    }
}

/*this method, as it says , do the calculation (if needed) to ajust the memory
to a multiple of 4, and also moves 2 places the bits (same as multiply by 4) 

NOTES: 
 1) I DO NOT KNOW YET HOW TO LIMIT WHERE TO STOP THE POINTER (MAYBE MODULO OR
ERROR)

2) we only have to ajust datasrt and datanum, because the bumners are already 
stored in  multiple of 4 
*/
void ajustMemory()
{
    int tempValue;
    //memg memory starts with no problem or ajust 
    memgStart<<=2; memgLimit<<=2;
    cout << "memg: " << hex << memgStart << endl;

    // start position of litNum
    litnumStart<<=2; litnumLimit<<=2;
    // cout << "litnumStart: " << litnumStart << " litnumLimit:" << litnumLimit << endl;
    litnumStart += litnumLimit;
    cout << hex << "litnum: " << litnumStart << endl;

    //ajusting the start position of litstr
    litstrStart<<=2; 
    // cout << " litstrStart: " << hex <<litstrStart << endl;
    litstrStart += litstrLimit;
    // cout << " litstrStart: " << hex << litstrStart << endl;
    // cout << " test:" << hex << litstrStart << " " << hex << litstrStart - (litstrStart%4) + 4 << endl;
    if(litstrStart%4 != 0) litstrStart = litstrStart - (litstrStart%4) + 4;
    cout << "litstr: " << hex <<litstrStart << endl;

    //ajusting the start position of dataNum
    // cout << "dataNumStart: " << dataNumStart << " dataNumLimit: " << dataNumLimit << endl;
    dataNumStart<<=2; dataNumLimit<<=2;
    dataNumStart += dataNumLimit;
    cout << "dataNum: " << hex << dataNumStart << endl;

    //ajusting the start position of dataStr
    // cout << "datastrStart: " << datastrStart << " datastrLimit: " << datastrLimit << endl;
    datastrStart<<=2; 
    datastrStart += datastrLimit;
    if(datastrStart%4 != 0) datastrStart = datastrStart - (datastrStart%4) + 4;
    cout << hex << "datastr: " << datastrStart << endl;

    //ajusting the start position of workload
    workloadStart<<=2; workloadLimit<<=2;
    workloadStart += workloadLimit;
    cout << hex << "workload: " << workloadStart << endl;
    
}

int main(int argc, char *argv[])
{
    readMemg(".memg");
    createMemory(argc, argv[1]);
    ajustMemory();
    // int *pInt = (int *)(pMem + 500);

    // //writing something in memory
    // char c = 'a';
    // int number = 1;

    // for (;;)
    // {

    //     for (int i = 0; i < 500; ++i)
    //     {
    //         *(pMem + i) = c++;
    //         c = (c > 'z') ? c = 'a' : c;
    //     }

    //     // writing a number in this position of memory just for test
    //     *(pInt) = 1;
    //     // *(pInt+1) = (int32_t)34;        
    //     // for (int i = 0; i < 125; ++i)
    //     // {
    //     //     *(pInt + i) = i;
    //     // }

    //     sleep(3);
    // }

    return 0;
}
