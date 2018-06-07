#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;


string memName;

//creating the values of the  memory segements , with initial values of 0
unsigned int memgStart, memgLimit;
unsigned int litnumStart, litnumLimit;
unsigned int litstrStart, litstrLimit;
unsigned int dataNumStart, dataNumLimit;
unsigned int datastrStart, datastrLimit;
unsigned int workloadStart, workloadLimit;

// pointers to the memory segments
char *pMem;
int *litnum;
char *litstr;
int *datanum;
char *datasrt;
int *workload;  // have my doubts about what is the type of the workload

// mascaras de bits
const int maskBase = 0xFFFF0000;
const int maskLimit = 0xFFFF;


/*
have in midn that we have to work in this segments too
A,B,C,D,E,
in wich i have no idea what to do with them
*/

// depends of the file i can read 4 with 
// change later to read with binary

// mejorar el calculo de los apuntadores

void assignDataNum(int pos, int num)
{
    *(litnum+pos) = num;
}

// how do i know where the last pinter was...
void assignDataString(int pos, char word)
{
    *(litstr+pos) = word;
}


void ajustMemory()
{
    unsigned int ajust;
    //memg memory starts with no problem or ajust
    memgStart <<= 2;
    memgLimit <<= 2;
    // cout << "memg: " << hex << memgStart << endl;

    // start position of litNum
    litnumStart <<= 2;
    litnumLimit <<= 2;
    // cout << "litnumStart: " << litnumStart << " litnumLimit:" << litnumLimit << endl;
    litnumLimit += litnumStart;
    // cout << hex << "litnum start: " << litnumStart << " litnum limit: "  <<  litnumLimit << endl;

    //ajusting the start position of litstr
    litstrStart <<= 2;
    // cout << " litstrStart: " << hex <<litstrStart << endl;
    ajust = litstrStart + litstrLimit;
    cout << hex << ajust << endl;
    // cout << " litstrStart: " << hex << litstrStart << endl;
    // cout << " test:" << hex << litstrStart << " " << hex << litstrStart - (litstrStart%4) + 4 << endl;
    if (ajust % 4 != 0)
        litstrLimit = ajust - (ajust % 4) + 4;
    // cout << "litstr start: " << hex << litstrStart << " litsrt limit: " << litstrLimit << endl;

    //ajusting the start position of dataNum
    // cout << "dataNumStart: " << dataNumStart << " dataNumLimit: " << dataNumLimit << endl;
    dataNumStart <<= 2;
    dataNumLimit <<= 2;
    dataNumLimit += dataNumStart;
    // cout << "dataNum start : " << hex << dataNumStart <<   " dataNum limit" << dataNumLimit << endl;

    //ajusting the start position of dataStr
    // cout << "datastrStart: " << datastrStart << " datastrLimit: " << datastrLimit << endl;
    datastrStart <<= 2;
    ajust = datastrStart +  datastrLimit ;
    if (ajust % 4 != 0)
        datastrLimit = ajust - (ajust % 4) + 4;
    // cout << hex << "datastr start:  " << datastrStart <<  " datastr limit: "  << datastrLimit << endl;

    //ajusting the start position of workload
    workloadStart <<= 2;
    workloadLimit <<= 2;
    workloadLimit = workloadStart + workloadLimit;
    cout << hex << "workload start : " << workloadStart << " workload limit: " << workloadLimit << endl;
}

void asingPointers()
{

    litnum = (int *)(pMem + litnumStart);
    // *litnum = -1; // testing
    // *(litnum+1) = 34; // testing
    
    litstr = (char *)(pMem + litstrStart);
    // *litstr = 'h';  // testing
    // *(litstr+1) = 'o'; // testing
    // *(litstr+2) = 'l'; // testing
    // *(litstr+3) = '\0'; // testing
    
    datanum = (int *)(pMem + dataNumStart);
    datasrt = (char*)(pMem + datastrStart);
    workload = (int*)(pMem + workloadStart);

    // datanum = (int *)(dataNumStart);
    // *workload;
}

int createMemory()
{
    int shm = shm_open(memName.c_str(), O_CREAT | O_RDWR | O_EXCL, 0600);

    if (shm == -1)
    {
        cerr << "Shared memory already created" << endl;
        return 1;
    }

    off_t size_mem = workloadLimit; // have to change the size acording to .memgdescription

    if (ftruncate(shm, size_mem) == -1)
    {
        cerr << "Problems with memory size" << endl;
        return 1;
    }

    // pMem start, im not using memgStart
    pMem = static_cast<char *>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, shm, 0));  

    if ((void *)pMem == (void *)-1)
    {
        cerr << "Problems with memory map" << endl;
        return 1;
    }
}

void readMemg(string mew)
{
    
    unsigned int linesPrioReaders , linesPrioWriters, block , noControl;
    unsigned int litnumLines , datanumLines;
    
    ifstream fileToRead(mew.c_str(), ios::binary);
    for(int i = 0; i < 10; ++i)
    {
        unsigned int hexNum, base ,  limit;
        fileToRead.read((char *)&hexNum, sizeof(unsigned int));
        
        base = (hexNum & maskBase) >> 16; // geting the base and limit
        limit = (hexNum & maskLimit);
        
        cout << hex << "base: " << base << " limite: " << limit << endl;  
        switch(i)
        {
            case 0:
                memgStart = base;
                memgLimit = limit;
                // cout << "limits of .memg: base : " << memgStart << " limit: " << memgLimit << endl;    
                break;
            case 1:
                litnumStart = base;
                litnumLimit = limit;
                litnumLines = limit;
                break;
            case 2:
                litstrStart =  base;
                litstrLimit = limit;
                break;                
            case 3:
                dataNumStart = base;
                dataNumLimit = limit;
                break;
            case 4:
                datastrStart = base;
                datastrLimit =  limit;
                break;
            case 5:
                workloadStart = base;
                workloadLimit = limit;
                break;
            case 6:
                linesPrioWriters = limit - base;
                // cout << linesPrioWriters << endl;
                break;
            case 7:
                linesPrioReaders = limit - base;
                break;
            case 8:
                block = limit - base;
                break;
            case 9:
                noControl = limit - base;
                break;
        }
    }

    // ignoring for the moment, later to see what to do with this policy
    int Numpolicies = linesPrioWriters + linesPrioReaders + block + noControl;
    for(int i = 0; i < Numpolicies; ++i)
    {
        unsigned base ,  limit , hexNum;;
        fileToRead.read((char *)&hexNum, sizeof(int));
        cout << "hexnum: " << hexNum << endl;
        base = (hexNum & maskBase) >> 16 ; // geting the base and limit
        limit = (hexNum & maskLimit);
        cout << " base:" << base << endl << " limit:" << limit << endl;
    }

    ajustMemory();
    createMemory();
    asingPointers();

    // // reading and saving literal num
    // // cout <<  hex << " litnumLimit: " << litnumLimit << endl;
    // for(int i = 0; i < litnumLines; ++i)
    // {
    //     // cout << "i:" << i << en
    //    unsigned int num;
    //    string numString, clean;
    //    fileToRead >>  setw(2) >> clean;
    //    fileToRead >> numString;
    //    stringstream converter(numString);
    //    int signedNum = static_cast<int>(num);
    // //    cout << "num: " << dec << signedNum << endl;
    //    assignDataNum(i,signedNum);
    // }

    // int posDs = 0;
    // while(!fileToRead.eof())
    // {
    //     int string_;
    //     string word_, clean;
    //     fileToRead >> setw(2) >> clean; 
    //     fileToRead >>  word_;
    //     // cout << hex << word_ << endl;
    //     for(int j = 0; j < word_.size(); j+=2)
    //     {

    //         // cout <<  "hexstring: " << word_[j] << word_[j+1] << endl;
    //         string hexChar = "";
    //         hexChar += word_[j]; hexChar += word_[j+1];
    //         cout << "hex: " << hexChar << endl;
    //         istringstream converter(hexChar);
    //         converter.flags(ios::hex);
    //         int i;
    //         converter >> hex >> i;
    //         cout << "conversion: " << char(i) << endl;
    //         assignDataString(posDs++, char(i));
    //     }
    // }


    fileToRead.seekg(0, fileToRead.beg);
    fileToRead.close(); // avoiding that a buffer stays open (previous experiences)
}



/*this method, as it says , do the calculation (if needed) to ajust the memory
to a multiple of 4, and also moves 2 places the bits (same as multiply by 4) 

NOTES: 
 1) I DO NOT KNOW YET HOW TO LIMIT WHERE TO STOP THE POINTER (MAYBE MODULO OR
ERROR)

2) we only have to ajust datasrt and datanum, because the bumners are already 
stored in  multiple of 4 
*/

int main(int argc, char *argv[])
{
    string arg1 = (argc > 1) ?  string(argv[1]) : "" ;
    string arg2 = (argc > 2) ?  string(argv[2]) : "" ;
    string arg3 = (argc > 3) ?  string(argv[3]) : "" ;
    
    if(arg1 != "-n")
    {
        // cout << arg1 << endl;
        cout << "usage -n <nommemcom>" << endl;
        if(arg2 == "")
        {
            // cout << arg2 << "hola" << endl;
            cout << "usage -n <nommemcom>" << endl;
            return 1;
        }
        return 1;
    }

    memName = arg2;
    readMemg(arg3); // only reads segment memg
    
    return 0;
}
