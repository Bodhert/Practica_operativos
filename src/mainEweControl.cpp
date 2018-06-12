#include <iostream>
#include "controlewe.h"
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    string memoryOptionName = (argc > 1) ?  string(argv[1]) : "" ;
    string memoryName = (argc > 2) ?  string(argv[2]) : "" ;
    string cfg = (argc > 3) ?  string(argv[3]) : "" ;
    string mew = "" , bew = "";
    vector<string> bews;

    cout << " cfg: " <<  cfg << endl;
    
    if(memoryOptionName != "-n")
    {
        // cout << memoryOptionName << endl;
        cout << "usage -n <nommemcom> [<ficherocfg>]" << endl;
        return 1;

        if(memoryName == "")
        {
            // cout << memoryName << "hola" << endl;
            cout << "usage -n <nommemcom> [<ficherocfg>]" << endl;
            return 1;
        }
    }

    if (cfg != "")
    {
        ifstream readCfg(cfg.c_str());
        readCfg >> mew;
        while(readCfg >> bew)
        {
            // cout << "bew " << bew << endl;
          bews.push_back(bew);  
        } 
        readCfg.seekg(0, readCfg.beg);
        readCfg.close(); // avoiding that a buffer stays open (previous experiences)
    }
    else
    {
        int bewsSize;
        cout << "name of .mew" << endl;
        cin >> mew;
        cout << "how many  .bew do you want to run?  " << endl;
        cin >> bewsSize;
        for(int i = 0; i < bewsSize; ++i )
        {
            cout << "input bew 1: " << endl;        
            cin >> bew;
            bews.push_back(bew);
        }
    }

    // cout << arg3 << endl;

    controlewe *controler = new controlewe(memoryName, "bews");

    if(mew == "") cout << "no .mew especified" << endl;
    else
    {
      cout << "mew: " << mew << endl;
      controler->readMemg(mew);  
    } 


    // exec the program from terminal
    int bewsFilesSize =  bews.size() ;
    if (bewsFilesSize)
    {
        // exec the program in termianl with treads;
        int link[2];
        char foo[4096];
        if(pipe(link) == -1)
        {
            exit(EXIT_FAILURE);
        }  
    //     // int archivo = 4;
        pid_t processes[bewsFilesSize];
        for(int file = 0; file < bewsFilesSize ; ++file) // queme para probar , recordar quitar el -1
        {

            cout << "bew: "<< bews[file] << "  memory name: " << memoryName << endl;

        	if((processes[file] = ::fork()) == -1){
                perror("Exec Process Failed");
        		exit(EXIT_SUCCESS);
        	}
            else if(processes[file] == 0)
            {
                dup2(link[1], STDOUT_FILENO);
                close(link[0]);
                close(link[1]);
                execlp( "./interewe", "./interewe", "-n", memoryName.c_str(), bews[file], NULL);
                _exit(EXIT_SUCCESS);
        	}
            else
            {
                close(link[1]);
                int nbytes = read(link[0], foo, sizeof(foo));
                printf("\nOutput: (%.*s)\n", nbytes, foo);
            }
        }

        int status;
        for(int file=0; file<bewsFilesSize;++file){
        	waitpid(processes[file], &status, 0);
        }

    }
    else 
    {
        cout << " no bews specified" << endl;
    }


 return 0;
}
