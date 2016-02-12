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

class Command : public Input
{
    protected:
        vector<string> v;
    
    public:
        Command()
        {
            for(unsigned int i = 0; i < v.size(); ++i)
            {
                v.at(i) = "";
            }
        }
        
        vector<string> get_vector()
        {
            return v;
        }
        
        void parse_string(string s)
        {
            unsigned int index = 0;
            string temp = "";
            unsigned int i = 0;
            unsigned int space = i;
            
            for(i = 0; i < s.length(); ++i)
            {
                for(i = space; i < s.length(); ++i)
                {
                    if(s.at(i) != ' ' && s.at(i) != '\0')
                    {
                        temp += s.at(i);
                    }
                    else if(s.at(i) == ' ' || s.at(i) == '\0')
                    {
                        break;
                    }

                }
                v.push_back(temp);
                temp = "";
                ++index;
                space = i + 1;
            }
        }
        
        void exc_command(string command, int& passed)
        {
            passed = 1;
            char* arg[256];
            string tempA = "";
            string tempB = "";
            string tempC = "";
            string tempD = "";
            int counter = 0;
            
            for(unsigned int i = 0; i < command.size(); i++)
            {
                if((command.at(i) != ' ' ) && (counter == 0))
                {
                    tempA += command.at(i);
                }
                else if((command.at(i) != ' ') && (counter == 1))
                {
                    tempB += command.at(i);
                }
                else if((command.at(i) != ' ') && (counter == 2))
                {
                    tempC += command.at(i); 
                }
                else if((command.at(i) != ' ') && (counter == 3))
                {
                    tempD += command.at(i);
                }
                if(command.at(i) == ' ')
                {
                    counter++;
                }
            }
            if(tempB.size() == 0)
            {
                arg[0] = (char*)tempA.c_str();
                arg[1] = NULL;
            }
            if(tempC.size() == 0)
            {
                arg[0] = (char*)tempA.c_str();
                arg[1] = (char*)tempB.c_str();
                arg[2] = NULL;
            }
            if(tempD.size() == 0)
            {
                arg[0] = (char*)tempA.c_str();
                arg[1] = (char*)tempB.c_str();
                arg[2] = (char*)tempC.c_str();
                arg[4] = NULL;
            }
            else
            {
                arg[0] = (char*)tempA.c_str();
                arg[1] = (char*)tempB.c_str();
                arg[2] = (char*)tempC.c_str();
                arg[4] = (char*)tempD.c_str();
                arg[5] = NULL;
            }
            
            pid_t pid = fork();
            if(pid == 0)
            {
                if(execvp(arg[0],arg) == -1)
                {
                    perror("exec");
                    passed = 0;
                }   
            }
            if(pid > 1)
            {
                if(wait(0) == -1)
                {
                    perror("wait");
                    passed = 0;
                }
            }
        }
};
