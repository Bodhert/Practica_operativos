#include <iostream>
#include "interewe.h"    
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    string memoryOptionName = (argc > 1) ?  string(argv[1]) : "" ;
    string memoryName = (argc > 2) ?  string(argv[2]) : "" ;
    string ficheroBinEwe = (argc > 3) ?  string(argv[3]) : "" ;
    
    if(memoryOptionName != "-n")
    {
        // cout << memoryOptionName << endl;
        cout << "usage -n <nommemcom> <ficherobinewe>" << endl;
        return 1;

        if(memoryName == "")
        {
            // cout << memoryName << "hola" << endl;
            cout << "usage -n <nommemcom> <ficherobinewe>" << endl;
            return 1;
        }
    }

    if(ficheroBinEwe == "") 
    {
        cout << "usage -n <nommemcom> <ficherobinewe>" << endl;
        return 1;
    }

    interewe *interpreter = new interewe(ficheroBinEwe,memoryName); 
    interpreter->readBew();
     

    // int eweFiles=argc-4;
    // int archivo = 4;
	// pid_t processes[eweFiles];
	// for(int file =0; file<eweFiles;++file){
	// 	if((processes[file] = ::fork())==0){
	// 		interpreter->readBew(argv[archivo]);
	// 		archivo++;
	// 		//cout << "Child: " << processes[file] << endl;
	// 		exit(EXIT_SUCCESS);
	// 	}else{
	// 		//cout<< "Father: " << processes[file] << endl;
	// 	}
	// }

	// int status;
	// for(int file=0; file<eweFiles;++file){
	// 	//waitpaid(processes[file], &status, 0);
	// }

 return 0;
}
