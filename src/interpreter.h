#pragma once
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>
#include <map>
#include <pthread.h>
#include <iomanip>

using namespace std;

class Interpreter{

	int *memg;
 	int *litnum;
 	int *litstr;
 	int *datanum;
 	char *datastr;
 	sem_t *workload;



public:
	Interpreter(int *memgin, int *litnumin, int *litstrin, int *datanumin char *datastrin, sem_t *workloadin);
  	~Interpreter();
  	void writeMemg(string nameFile,int limit, int *memg,int *literalnum,int limitNum,int *literalstring,int limitString);
  	int readMemg(int *memg, int position);
  	int readLitnum(int *litnum, int position);
  	char* readLitstr(int *literalstring, int position, int limit);
  	char* readDatastr(char *datastring, int position, int tamano,int politic);
  	int readDatanum(int *datanum, int pos,int politic);
  	void writeDatastr(char *datastring, int position, char* data,int politic);
  	void writeDatanum(int *datanum, int position, int data,int politic);
  	int interprete(int opcode, string value,int pc);
  	void proceso(string file);
};