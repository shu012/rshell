#include <iostream>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>
#include <sys/unistd.h>
#include <cstdlib>

using namespace std;

class Input
{
    protected:
        string input;
    
    public:
        Input()
        {
            input = "";
        }
        
        Input(string s)
        {
            input = s;
        }
        
        void recieveinput(int &check)
        {
            cout << "$: ";
            getline(cin, input);
            check = 0;
        }
        
        string get_string()
        {
            return input;
        }
};
