#include <iostream>
#include "controlewe.h"
#include "interewe.h"

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

    interewe *interpreter = new interewe();

    if(arg4 == "") cout << "no .bew especified" << endl;
    else interpreter->readBew(arg4);
     
        

    return 0;
}
