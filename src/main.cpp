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
#include <sys/stat.h>

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
        
        void clear_string()
        {
            input.clear();
        }
        
        string get_string()
        {
            return input;
        }
        
        void getinput(int &check)
        {
            cout << "$: ";
            getline(cin, input);
            check = 0;
        }
        
        bool check_prec()
        {
            for(int i = 0; i < input.size(); ++i)
            {
                if(input.at(i) == '(')
                {
                    return true;
                }
            }
            
            return false;
        }
};

class Command
{
    public:
        void executecommand(string command,int& passed)
        {
            passed = 1;
            char* arg[256];
            string temp = "";
            string temp1 = "";
            string temp2 = "";
            string temp3 = "";
            int counter = 0;               
            for(unsigned int i = 0; i < command.size(); i++)
            {
                if((command.at(i) != ' ') && (counter == 0))
                {
                    temp += command.at(i);
                }
                else if((command.at(i) != ' ') && (counter == 1))
                {
                    temp1 += command.at(i);
                }
                else if((command.at(i) != ' ') && (counter == 2))
                {
                    temp2 += command.at(i);
                }
                else if((command.at(i) != ' ') && (counter == 3))
                {
                    temp3 += command.at(i);
                }
                if(command.at(i) == ' ')
                {
                    counter++;
                }
            }
            if(temp1.size() == 0)
            {
                arg[0] = (char*)temp.c_str();
                arg[1] = NULL;
            }
            else if (temp2.size() == 0)
            {
                arg[0] = (char*)temp.c_str();
                arg[1] = (char*)temp1.c_str();
                arg[2] = NULL;
            }
            else if (temp3.size() == 0)
            {
                arg[0] = (char*)temp.c_str();
                arg[1] = (char*)temp1.c_str();
                arg[2] = (char*)temp2.c_str();
                arg[3] = NULL;
            }
            else
            {
                arg[0] = (char*)temp.c_str();
                arg[1] = (char*)temp1.c_str();
                arg[2] = (char*)temp2.c_str();
                arg[3] = (char*)temp3.c_str();
                arg[4] = NULL;
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
        
        bool check_test(string cmd,int& passed)
        {
            Command test;

            if(cmd.at(0) =='[')
            {
                int j = 2;
                for(int i = 0; i < cmd.size() - 4; ++ i)
                {
                    cmd.at(i) = cmd.at(j);
                    ++j;
                }

                cmd.resize(cmd.size()-4);
                test.testcommand(cmd,passed);
                
                return true;
            }

            string t = "test ";
            int cnt = 0;
            if(cmd.size() > 5)
            {
                for(unsigned int i = 0; i < 5; ++i)
                {
                    if(cmd.at(i) == t.at(i))    
                    {
                        ++cnt;
                    }
                }
            }

            if(cnt == 5)
            {
                for(unsigned int i = 0; i < cmd.size() - 5; ++ i)
                {
                    cmd.at(i) = cmd.at(cnt);
                    ++cnt;
                }
 
                cmd.resize(cmd.size()-5);
                test.testcommand(cmd,passed);
                
                return true;
            }
            
            return false;
        }
        
        void testcommand(string command,int& passed)
        {
            string path = "";
            int size = command.size() - 3;
            if(command.at(0) == '-')
            {
                path = command.substr(3,size);
                if(command.at(command.size()-1) == ' ')
                {
                    path.resize(path.size() -1);
                }
            }
            else
            {
                path = command;
            }
            
            bool flag;
            struct stat buffer;

            stat(path.c_str(),&buffer); 

            if(command.at(0) == '-' && command.at(1) == 'f')
            {
                flag = S_ISREG(buffer.st_mode);
            }
            else if(command.at(0) == '-' && command.at(1) == 'd')
            {
                flag = S_ISDIR(buffer.st_mode);   
            }
            else
            {
                flag = (stat(path.c_str(),&buffer) == 0);
            }
            
            if(flag)
            {
                cout << "(True)" << endl;
                passed = 1;
            }
            else
            {
                cout << "(False)"<< endl;
                passed = 0;
            }
            return;
        }
        
        void ctr_parse(string temp, vector<char>& connectors)
        {
            int cnt = connectors.size();
            
            for(int i = 0; i < temp.size() - 1; ++i)
            {
                if(temp.at(i) == '&' && temp.at(i + 1) == '&')
                {
                    connectors.push_back(temp.at(i));
                    connectors.push_back(temp.at(i + 1));
                }
                
                else if(temp.at(i) == '|' && temp.at(i + 1) == '|')
                {
                    connectors.push_back(temp.at(i));
                    connectors.push_back(temp.at(i + 1));
                }
                
                else if(temp.at(i) == ';')
                {
                    connectors.push_back(temp.at(i));
                }
            }
        }
        
        void cmd_parse(string tmp, vector<string>& commands)
        {
            string temp = "";
            
            char *input;
            input = new char[tmp.length()]; 
            for(unsigned int i = 0; i < tmp.length(); i++)
            {
                input[i] = tmp[i];
            }
            input[tmp.length()] = '\0';  // command string is now in c string format
            
            char *pointer;    // ls -lt; echo hello && echo hi
            pointer = strtok(input,";&&||"); // parse until you find any of this
            while(pointer != NULL) // read in, remove #, put into vs1 holding all commands
            {
                int i = 0;
                while((pointer[i] != '\0') && (pointer[i] != '#')) // remove comments #
                {
                    temp += pointer[i];
                    i++;
                }
                if(temp.at(0) == ' ') // remove if there's a space at start for execvp command to not crash
                {
                    string a = temp;
                    temp.clear();
                    for(unsigned int i = 0; i < a.size(); i++) // remove space at beginning
                    {
                        if(i == 0)
                        {
                            // do nothing
                        }
                        else
                        {
                            temp += a.at(i);
                        }
                    }
                }

                commands.push_back(temp);
                pointer = strtok(NULL,";&&||");
                temp.clear();
            }
        }
        
        void mult_commands(vector<string>& vs1, vector<char>& vc1,int& cmncnt)
        {
            int cmdcnt = 0;  
            int skip = 0; // used for skipping over multiple connectors, focus one at a time
            bool check_if_test;
            Command cmd;

            char track = vc1.at(vc1.size() - 1); // has list of ; && ||
            string track2 = vs1.at(vs1.size() - 1); // has list of commands to do 

            check_if_test = cmd.check_test(track2,cmdcnt);
            if(!check_if_test)
            {
                cmd.executecommand(track2,cmdcnt);
            }
            vs1.pop_back();
            do
            {
                if(track == ';')
                {
                    vc1.pop_back();
                    skip = 1;
                }
                if((track == '&') && (cmdcnt == 1) && (skip == 0))
                {
                    vc1.pop_back();
                    vc1.pop_back();
                    if((vc1.size() != 0) && (vs1.size() != 0))
                    {
                        track = vc1.at(vc1.size() - 1);
                        track2 = vs1.at(vs1.size() - 1);  
                        check_if_test = cmd.check_test(track2,cmdcnt);
                        if(!check_if_test)
                        {
                                cmd.executecommand(track2,cmdcnt);
                        }
                        vs1.pop_back();
                    }
                    skip = 1;
                }
                else if((track == '&') && (cmdcnt == 0) && (skip == 0))
                {
                    vc1.pop_back();
                    vc1.pop_back();
                    vs1.pop_back();
                    skip = 1;
                }
                if((track == '|') && (cmdcnt == 0) && (skip == 0))
                {
                    vc1.pop_back();
                    vc1.pop_back();
                    if(vs1.size() != 0)
                    {
                        track2 = vs1.at(vs1.size() - 1); 
                        check_if_test = cmd.check_test(track2,cmdcnt);
                        if(!check_if_test)
                        {
                            cmd.executecommand(track2,cmdcnt);
                        }
                        vs1.pop_back();
                    }
                    skip = 1;
                }
                else if((track == '|') && (cmdcnt == 1) && (skip == 0))
                {
                    vc1.pop_back();
                    vc1.pop_back();
                    vs1.pop_back();
                    skip = 1;
                }
                skip = 0;
                if(vc1.size() != 0)
                {
                    track = vc1.at(vc1.size() - 1);
                }
                else
                {
                    track = '0';
                }
                if(vs1.size() != 0)
                {
                     track2 = vs1.at(vs1.size() - 1);
                }
                else
                {
                    track2 = "";
                }
                if((track == ';') && (track2.size() > 1))
                {
                    check_if_test = cmd.check_test(track2,cmdcnt);
                    if(!check_if_test)
                    {
                            cmd.executecommand(track2,cmdcnt);
                    }
                    vs1.pop_back();
                }
                else if((track == '|') && (track2.size() > 1))
                {
                    if(cmdcnt == 0)
                    {
                        check_if_test = cmd.check_test(track2,cmdcnt);
                        if(!check_if_test)
                        {
                            cmd.executecommand(track2,cmdcnt);
                        }
                        vs1.pop_back();
                    }
                }
                else if((track == '&') && (track2.size() > 1))
                {
                    if(cmdcnt == 1)
                    {
                        check_if_test = cmd.check_test(track2,cmdcnt);
                        if(!check_if_test)
                        {
                            cmd.executecommand(track2,cmdcnt);
                        }
                        vs1.pop_back();
                    }
                }
                else
                {
                    if(track2.size() > 1)
                    {
                        check_if_test = cmd.check_test(track2,cmdcnt);
                        if(!check_if_test)
                        {
                            cmd.executecommand(track2,cmdcnt);
                        }
                        vs1.pop_back();   
                    }
                }
            }
            while((vs1.size() != 0));
            cmncnt = cmdcnt;
        }
        
        void skip(string command, int& i)
        {
            int beg_par = 0;
            int end_par = 0;
            
            for(int j = i; j < command.size(); ++j)
            {
                if(command.at(j) == '(')
                {
                    ++beg_par;
                }
                
                else if(command.at(j) == ')')
                {
                    ++end_par;
                }
                
                if((beg_par == end_par && beg_par != 0 && end_par != 0) || (beg_par == 0 && end_par == 1))
                {
                    i = j + 1;
                    return;
                }
            }
            
            if(beg_par == 0 && end_par == 0)
            {
                for(int j = i; j < command.size(); ++j)
                {
                    if(command.at(j) == '&')
                    {
                        i = j + 2;
                        return;
                    }
                    
                    else if(command.at(j) == '|')
                    {
                        i = j + 2;
                        return;
                    }
                    
                    else if(command.at(j) == ';')
                    {
                        i = j + 1;
                        return;
                    }
                }
            }
        }
        
        void precedencecommand(string command,int& passed)
        {
            //needs to be added
        }
        
};

int main()
{
    int check = 0; 
    vector<char> vc1;
    vector<char> vc2;
    vector<string> vs1;
    vector<string> vs2;
    
    bool check_if_test;
    bool precedence_check;
    Input in;
    Command cmd;
    string command = "";
    in.getinput(check); // get input from user displaying host and login name
    while(in.get_string() != "exit")
    {
        //check for '('
        precedence_check = in.check_prec();
        if(precedence_check)
        {
            int cmdcnt = 1;
            cmd.precedencecommand(in.get_string(), cmdcnt);
            
            in.clear_string();
            in.getinput(check);
        }
        else
        {
            for(unsigned int i = 0; i < in.get_string().size(); i++) // checks for connectors
            {
                if((in.get_string().at(i) == ';') || (in.get_string().at(i) == '&') || (in.get_string().at(i) == '|'))
                {
                    check = 1;
                    vc1.push_back(in.get_string().at(i));
                }
            }
            if(check == 0) // only 1 command
            {
                int cmdcnt = 1;
                check_if_test = cmd.check_test(in.get_string(),cmdcnt);
                if(!check_if_test)
                {
                    cmd.executecommand(in.get_string(),cmdcnt);
                }
            }
            else if(check == 1)   // multiple commands
            {
                string temp = "";
            
                // used to take input and break into cstring then break into individual commands
                char *input;
                input = new char[in.get_string().length()]; // create c string 
                for(unsigned int i = 0; i < in.get_string().length(); i++) // copy string into c string
                {
                    input[i] = in.get_string()[i];
                }
                input[in.get_string().length()] = '\0';  // command string is now in c string format
            
                char *pointer;    // ls -lt; echo hello && echo hi
                pointer = strtok(input,";&&||"); // parse until you find any of this
                while(pointer != NULL) // read in, remove #, put into vs1 holding all commands
                {
                    int i = 0;
                    while((pointer[i] != '\0') && (pointer[i] != '#')) // remove comments #
                    {
                        temp += pointer[i];
                        i++;
                    }
                    if(temp.at(0) == ' ') // remove if there's a space at start for execvp command to not crash
                    {
                        string a = temp;
                        temp.clear();
                        for(unsigned int i = 0; i < a.size(); i++) // remove space at beginning
                        {
                            if(i == 0)
                            {
                                // do nothing
                            }
                            else
                            {
                                temp += a.at(i);
                            }
                        }
                    }   
                    vs1.push_back(temp);
                    pointer = strtok(NULL,";&&||");
                    temp.clear();
                }
                vc2 = vc1;
                vs2 = vs1;
                vc1.clear();
                vs1.clear();
                for(int i = vc2.size() - 1; i > -1; i--)  // reverse order into v1
                {
                    vc1.push_back(vc2.at(i));
                }
                for(int i = vs2.size() - 1; i > -1; i--)  // reverse order into vs1
                {
                    vs1.push_back(vs2.at(i));
                }
            
                int cmdcnt = 0;  // status of whether execvp cmdcnted or failed for connectors
                // vs1 is keeping track of all commands entered with vs1.at(vs1.size() - 1) being the first command
                // v is keeping track of all connectors entered with vc1.at(vc1.size() - 1) being the first connector
                int skip = 0; // used for skipping over multiple connectors, focus one at a time
 
                char track = vc1.at(vc1.size() - 1); // has list of ; && ||
                string track2 = vs1.at(vs1.size() - 1); // has list of commands to do 

                check_if_test = cmd.check_test(track2,cmdcnt);
                if(!check_if_test)
                {
                    cmd.executecommand(track2,cmdcnt);
                }
                vs1.pop_back();
                do
                {
                    if(track == ';')
                    {
                        vc1.pop_back();
                        skip = 1;
                    }
                    if((track == '&') && (cmdcnt == 1) && (skip == 0))
                    {
                        vc1.pop_back();
                        vc1.pop_back();
                        if((vc1.size() != 0) && (vs1.size() != 0))
                        {
                            track = vc1.at(vc1.size() - 1);
                            track2 = vs1.at(vs1.size() - 1);  
                            check_if_test = cmd.check_test(track2,cmdcnt);
                            if(!check_if_test)
                            {
                                cmd.executecommand(track2,cmdcnt);
                            }
                            vs1.pop_back();
                        }
                        skip = 1;
                    }
                    else if((track == '&') && (cmdcnt == 0) && (skip == 0))
                    {
                        vc1.pop_back();
                        vc1.pop_back();
                        vs1.pop_back();
                        skip = 1;
                    }
                    if((track == '|') && (cmdcnt == 0) && (skip == 0))
                    {
                        vc1.pop_back();
                        vc1.pop_back();
                        if(vs1.size() != 0)
                        {
                            track2 = vs1.at(vs1.size() - 1); 
                            check_if_test = cmd.check_test(track2,cmdcnt);
                            if(!check_if_test)
                            {
                                cmd.executecommand(track2,cmdcnt);
                            }
                            vs1.pop_back();
                        }
                        skip = 1;
                    }
                    else if((track == '|') && (cmdcnt == 1) && (skip == 0))
                    {
                        vc1.pop_back();
                        vc1.pop_back();
                        vs1.pop_back();
                        skip = 1;
                    }
                    skip = 0;
                    if(vc1.size() != 0)
                    {
                        track = vc1.at(vc1.size() - 1);
                    }
                    else
                    {
                        track = '0';
                    }
                    if(vs1.size() != 0)
                    {
                        track2 = vs1.at(vs1.size() - 1);
                    }
                    else
                    {
                        track2 = "";
                    }
                    if((track == ';') && (track2.size() > 1))
                    {
                        check_if_test = cmd.check_test(track2,cmdcnt);
                        if(!check_if_test)
                        {
                            cmd.executecommand(track2,cmdcnt);
                        }
                        vs1.pop_back();
                    }
                    else if((track == '|') && (track2.size() > 1))
                    {
                        if(cmdcnt == 0)
                        {
                            check_if_test = cmd.check_test(track2,cmdcnt);
                            if(!check_if_test)
                            {
                                cmd.executecommand(track2,cmdcnt);
                            }
                            vs1.pop_back();
                        }
                    }
                    else if((track == '&') && (track2.size() > 1))
                    {
                        if(cmdcnt == 1)
                        {
                            check_if_test = cmd.check_test(track2,cmdcnt);
                            if(!check_if_test)
                            {
                                cmd.executecommand(track2,cmdcnt);
                            }
                            vs1.pop_back();
                        }
                    }
                    else
                    {
                        if(track2.size() > 1)
                        {
                            check_if_test = cmd.check_test(track2,cmdcnt);
                            if(!check_if_test)
                            {
                                cmd.executecommand(track2,cmdcnt);
                            }
                            vs1.pop_back();   
                        }
                    }
                }
                while((vs1.size() != 0) && (vc1.size() != 0));
            }
            vc1.clear();
            vc2.clear();
            vs1.clear();
            vs2.clear();
            in.clear_string();
            in.getinput(check);
        }
    }
    return 0;
}
