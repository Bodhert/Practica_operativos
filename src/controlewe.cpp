#include "controlewe.h"

// is only doing mew not bew yet
controlewe::controlewe(string memoryName, string bews)
{
    memName = memoryName;
}

void controlewe::ajustMemory()
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
    // cout << hex << ajust << endl;
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
    // workloadLimit <<= 2;
    workloadLimit = workloadStart + workloadLimit;
    // cout << hex << "workload start : " << workloadStart << " workload limit: " << workloadLimit << endl;
}

void controlewe::readMemg(string mew)
{
    unsigned int linesPrioReaders , linesPrioWriters, block , noControl;
    unsigned int litnumLines , datanumLines;

    ifstream fileToRead(mew.c_str(), ios::binary);
    for(int i = 0; i < 10; ++i)
    {
        unsigned int hexNum, base , limit;
        fileToRead.read((char *)&hexNum, sizeof(unsigned int));

        memgcopy.push_back(hexNum); // coping the memory;

        base = (hexNum & maskBase) >> 16; // geting the base and limit
        limit = (hexNum & maskLimit);

        // cout << hex << "base: " << base << " limite: " << limit << endl;
        switch(i)
        {
            case 0:
                memgStart = base;
                memgLimit = limit;
                // cout << "limits of .memg: base : " << memgStart << " limit: " << memgLimit << endl;
                // writeMemg(0,hexNum);
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

    for(int i = 0; i < linesPrioWriters; ++i)
    {
        unsigned int base ,  limit , hexNum;
        fileToRead.read((char *)&hexNum, sizeof(unsigned int));
        memgcopy.push_back(hexNum); // coping the memory;
        base = (hexNum & maskBase) >> 16;
        limit = (hexNum & maskLimit);
        // cout << hex << " base A:" << base << " limit A:" << limit << endl;
        bool isDataNum = base >> 15;
        if(isDataNum) dataNumPolitics[i] = 'L';
        else if(!isDataNum) dataStrPolitics[i] = 'L';
    }

    for(int i = 0; i < linesPrioReaders; ++i)
    {
        unsigned int base ,  limit , hexNum;
        fileToRead.read((char *)&hexNum, sizeof(unsigned int));
        memgcopy.push_back(hexNum); // coping the memory;
        base = (hexNum & maskBase) >> 16;
        limit = (hexNum & maskLimit);
        // cout << " base:B " << base  << " limit:B " << limit << endl;
        bool isDataNum = base >> 15;
        if(isDataNum) dataNumPolitics[i] = 'E';
        else if(!isDataNum) dataStrPolitics[i] = 'E';
    }

    for(int i = 0; i < block; ++i)
    {
        unsigned int base ,  limit , hexNum;
        fileToRead.read((char *)&hexNum, sizeof(unsigned int));
        memgcopy.push_back(hexNum); // coping the memory;        
        base = (hexNum & maskBase) >> 16;
        limit = (hexNum & maskLimit);
        // cout << " base:C " << base  << " limit:C " << limit << endl;
        bool isDataNum = base >> 15;
        if(isDataNum) dataNumPolitics[i] = 'B';
        else if(!isDataNum) dataStrPolitics[i] = 'B';
    }

    for(int i = 0; i < noControl; ++i)
    {
        unsigned int base ,  limit , hexNum;
        fileToRead.read((char *)&hexNum, sizeof(unsigned int));
        memgcopy.push_back(hexNum); // coping the memory;        
        base = (hexNum & maskBase) >> 16;
        limit = (hexNum & maskLimit);
        // cout << " baseDDD:" << base  << " limit:" << limit << endl;
        bool isDataNum = base >> 15;
        if(isDataNum) dataNumPolitics[i] = 'N';
        else if(!isDataNum) dataStrPolitics[i] = 'N';
    }

    cout << "memg_size: " << memgcopy.size() << endl;

    ajustMemory();
    int iscreated = createMemory();
    // cout <<  "is" << iscreated << endl;
    if(iscreated) return; // breaking the control in case that already created the memory
    assingPointers();
    writeMemg();

    // reading and saving literal num
    // cout <<  hex << " litnumLimit: " << litnumLimit << endl;
    for(int i = 0; i < litnumLines; ++i)
    {
        // cout << "i:" << i << en
       int num,  hexNum;
       fileToRead.read((char *)&hexNum, sizeof(int));
       int signedNum = static_cast<int>(hexNum);
    //    cout << "num: " << dec << signedNum << endl;
       assignDataNum(i,hexNum);
    }

    // cout << dec << " " << int(*(litnum+1)) << endl;

    int posDs = 0;
    unsigned char dataNum;
    while(fileToRead.read((char *)&dataNum, sizeof(unsigned char)))
    {
        assignDataString(posDs++,dataNum);
        // string word_, clean;
        // // cout << hex << hexNum << endl;
        // stringstream ss;
        // ss << hex << hexNum;
        // word_ = ss.str();
        // // cout << "word_"   << word_ << endl;
        // for(int j = 0; j < word_.size(); j+=2)
        // {
        //     // cout <<  "hexstring: " << word_[j] << word_[j+1] << endl;
        //     string hexChar = "";
        //     hexChar += word_[j]; hexChar += word_[j+1];
        //     // cout << "hex: " << hexChar << endl;
        //     istringstream converter(hexChar);
        //     converter.flags(ios::hex);
        //     int i;
        //     converter >> hex >> i;
        //     // cout << "conversion: " << char(i) << endl;
        //     assignDataString(posDs++, char(i));
        // }
    }


    fileToRead.seekg(0, fileToRead.beg);
    fileToRead.close(); // avoiding that a buffer stays open (previous experiences)
}

int controlewe::createMemory()
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
    pMem = static_cast<unsigned char *>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, shm, 0));

    if ((void *)pMem == (void *)-1)
    {
        cerr << "Problems with memory map" << endl;
        return 1;
    }

    pMemg = (unsigned int *) pMem;
    // writeMemg(0,1);// testing

    return 0;
}

void controlewe::assingPointers()
{

    litnum = (unsigned int *)(pMem + litnumStart);
    // *litnum = -1; // testing
    // *(litnum+1) = 34; // testing

    litstr = (unsigned char *)(pMem + litstrStart);
    // *litstr = 'h';  // testing
    // *(litstr+1) = 'o'; // testing
    // *(litstr+2) = 'l'; // testing
    // *(litstr+3) = '\0'; // testing

    datanum = (unsigned int *)(pMem + dataNumStart);
    datasrt = (unsigned char*)(pMem + datastrStart);
    workload = (unsigned int*)(pMem + workloadStart);

    // datanum = (int *)(dataNumStart);
    // *workload;
}

void controlewe::assignDataNum(unsigned int pos, int num)
{
    *(litnum+pos) = num;
}

void controlewe::assignDataString(unsigned int pos, char word)
{
    *(litstr+pos) = word;
}

void controlewe::writeMemg()
{
    for(int i = 0; i < memgcopy.size(); ++i)
    {
        *(pMemg + i) = memgcopy[i];
    }
}

controlewe::~controlewe()
{
    //dtor
}