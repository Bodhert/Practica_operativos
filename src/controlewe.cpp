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

//creating the values of the  memory segements , with initial values of 0
int memgStart, memgLimit;
int litnumStart, litnumLimit;
int litstrStart, litstrLimit;
int dataNumStart, dataNumLimit;
int datastrStart, datastrLimit;
int workloadStart, workloadLimit;

// pointers to the memory segments
char *pMem;
int *litnum;
char *litstr;
int *datanum;
char *datasrt;
int *workload;  // have my doubts about what is the type of the workload


/*
have in midn that we have to work in this segments too
A,B,C,D,E,
in wich i have no idea what to do with them
*/

// depends of the file i can read 4 with 
// change later to read with binary

void assignDataNum(int pos, int num)
{
    *(litnum+pos) = num;
}

// how do i know where the last pinter was...
void assignDataString(int pos, string word)
{
    for(int i = 0; i < word.size();++i)
    {
        *(litstr+i) = word[i];
    }
}

void ajustMemory()
{
    //memg memory starts with no problem or ajust
    memgStart <<= 2;
    memgLimit <<= 2;
    cout << "memg: " << hex << memgStart << endl;

    // start position of litNum
    litnumStart <<= 2;
    litnumLimit <<= 2;
    // cout << "litnumStart: " << litnumStart << " litnumLimit:" << litnumLimit << endl;
    litnumStart += litnumLimit;
    cout << hex << "litnum: " << litnumStart << endl;

    //ajusting the start position of litstr
    litstrStart <<= 2;
    // cout << " litstrStart: " << hex <<litstrStart << endl;
    litstrStart += litstrLimit;
    // cout << " litstrStart: " << hex << litstrStart << endl;
    // cout << " test:" << hex << litstrStart << " " << hex << litstrStart - (litstrStart%4) + 4 << endl;
    if (litstrStart % 4 != 0)
        litstrStart = litstrStart - (litstrStart % 4) + 4;
    cout << "litstr: " << hex << litstrStart << endl;

    //ajusting the start position of dataNum
    // cout << "dataNumStart: " << dataNumStart << " dataNumLimit: " << dataNumLimit << endl;
    dataNumStart <<= 2;
    dataNumLimit <<= 2;
    dataNumStart += dataNumLimit;
    cout << "dataNum: " << hex << dataNumStart << endl;

    //ajusting the start position of dataStr
    // cout << "datastrStart: " << datastrStart << " datastrLimit: " << datastrLimit << endl;
    datastrStart <<= 2;
    datastrStart += datastrLimit;
    if (datastrStart % 4 != 0)
        datastrStart = datastrStart - (datastrStart % 4) + 4;
    cout << hex << "datastr: " << datastrStart << endl;

    //ajusting the start position of workload
    workloadStart <<= 2;
    workloadLimit <<= 2;
    workloadStart += workloadLimit;
    cout << hex << "workload: " << workloadStart << endl;
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

void readMemg(string mew)
{
    // int value;
    // if(fileToRead.is_open())
    // {
    //     while(!fileToRead.eof())
    //     {
    //         // cout << "hola" << endl;
    //         // fileToRead.read((char*)&value,sizeof(int));
    //         fileToRead >> setw(4) >> (char*)&value,sizeof(int); // 
    //         cout << hex << value << endl;
    //     }
    // }

    int linesPrioReaders , linesPrioWriters, block , noControl;
    int litnumLines , datanumLines;
    
    ifstream fileToRead(mew.c_str());
    for(int i = 0; i < 10; ++i)
    {
        string baseString  , limitString , clean;
        int base ,  limit;
        fileToRead >> setw(2) >> clean; 
        fileToRead >> setw(4) >> baseString >> limitString;
        stringstream converterbase(baseString);
        stringstream converterlimit(limitString);
        converterbase >> hex >> base;
        converterlimit >> hex >> limit;
        
        
        // cout << baseString << " " << limitString << endl;
        // cout << hex << base << " " << limit << endl;
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
        string baseString  , limitString , clean;
        int base ,  limit;
        fileToRead >> setw(2) >> clean; 
        fileToRead >> setw(4) >> baseString >> limitString;
        stringstream converterbase(baseString);
        stringstream converterlimit(limitString);
        converterbase >> hex >> base;
        converterlimit >> hex >> limit;
        // cout << baseString << " " << limitString << endl;
        // cout << hex << base << " " << limit << endl;
    }

    ajustMemory();
    asingPointers();

    // reading and saving literal num
    // cout <<  hex << " litnumLimit: " << litnumLimit << endl;
    for(int i = 0; i < litnumLines; ++i)
    {
        // cout << "i:" << i << en
       unsigned int num;
       string numString, clean;
       fileToRead >>  setw(2) >> clean;
       fileToRead >> numString;
       stringstream converter(numString);
       converter >> hex >> num;
       int signedNum = static_cast<int>(num);
    //    cout << "num: " << dec << signedNum << endl;
       assignDataNum(i,signedNum);
    }

    int posDs = 0;
    while(!fileToRead.eof())
    {
        int string_;
        string word, clean;
        fileToRead >> setw(2) >> clean; 
        fileToRead >> word;
        cout << word << endl;
        assignDataString(posDs++, word);
    }


    fileToRead.seekg(0, fileToRead.beg);
    fileToRead.close(); // avoiding that a buffer stays open (previous experiences)
}

int createMemory(string memName)
{
    int shm = shm_open(memName.c_str(), O_CREAT | O_RDWR | O_EXCL, 0600);

    if (shm == -1)
    {
        cerr << "Shared memory already created" << endl;
        return 1;
    }

    off_t size_mem = workloadStart + 1000; // have to change the size acording to .memgdescription

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

    createMemory(arg2);

    readMemg(arg3); // only reads segment memg
    // // it may also recieve standard input instead of a file
    
    return 0;
}
