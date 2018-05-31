#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>

using namespace std;

//creating the memory segements , with initial values of 0
int memgStart, memgLimit;
int litnumStart, litnumLimit;
int litstrStart, litstrLimit;
int dataNumStart, dataNumLimit;
int datastrStart, datastrLimit;
int workloadStart, workloadLimit;
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
    fileToRead >> hex >> dataNumLimit;
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


int main(int argc, char *argv[])
{
    readMemg(".memg");
    if (argc != 2)
    {
        cerr << "Usage control: <shmname>" << endl;
        return 1;
    }

    int shm = shm_open(argv[1], O_CREAT | O_RDWR | O_EXCL, 0600);

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

    char *pMem = static_cast<char *>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE,
                                          MAP_SHARED, shm, 0));

    if ((void *)pMem == (void *)-1)
    {
        cerr << "Problems with memory map" << endl;
        return 1;
    }

    int *pInt = (int *)pMem + 500;

    //
    char c = 'a';
    int number = 0;

    for (;;)
    {

        for (int i = 0; i < 500; ++i)
        {
            *(pMem + i) = c++;
            c = (c > 'z') ? c = 'a' : c;
        }

        for (int i = 0; i < 125; ++i)
        {
            *(pInt + i) = number++;
        }

        sleep(3);
    }

    return 0;
}
