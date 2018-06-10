#include <iostream>
#include "controlewe.h"
#include "interewe.h"
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    string arg1 = (argc > 1) ?  string(argv[1]) : "" ;
    string arg2 = (argc > 2) ?  string(argv[2]) : "" ;
    string arg3 = (argc > 3) ?  string(argv[3]) : "" ;
    string arg4 = (argc > 4) ?  string(argv[4]) : "" ;
    

    if(arg1 != "-n")
    {
        // cout << arg1 << endl;
        cout << "usage -n <nommemcom>" << endl;
        return 1;

        if(arg2 == "")
        {
            // cout << arg2 << "hola" << endl;
            cout << "usage -n <nommemcom>" << endl;
            return 1;
        }
    }

    cout << arg3 << endl;

    controlewe *controler = new controlewe(arg2, "bews");

    if(arg3 == "") cout << "no .mew especified" << endl;
    else controler->readMemg(arg3);


    // later to parse 
    if(arg4 == "") cout << "no .bew especified" << endl;
    else
    {
        interewe *interpreter = new interewe(arg4,arg2); // change args for more descirptive names
        interpreter->readBew();
    } 

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
