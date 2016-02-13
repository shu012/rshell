# rshell

## Synopsis

**Rshell** works as a command shell that will prompt the user with `$: ` and take in a command or a series of commands, evaluate the command(s), and execute the command(s).  The user will continously be prompted until `exit` is inputted.  Valid commands may be inputted in the format: `executable [arguementList] [connector cmd]`.  Valid connectors include: `||`, `&&`, and `;`.

##Classes
Base class `Input` has a member variable `input` of datatype string that stores the entire inputted command line.  `Input`, also, includes two constructors and two other member functions.
```
class Input
{
    protected:
        string input;
    
    public:
        Input();
        Input(string s);
        void recieveinput(int &check);
        string get_string();
};
```
The member function `recieveinput(int&)` will get input from the user and store the input into the member variable input.  The member function `get_string()` simply returns input.

Class `Command` inherits from Class `Input` and has a member variable `v`, which is a vector of strings.  Class Command includes one constructor and three member functions.
```
class Command : public Input
{
    protected:
        vector<string> v;
    
    public:
        Command();
        vector<string> get_vector();
        void parse_string(string s);
        void exc_command(string command, int& passed);
};
```
The member function, `parse_string(string)`, takes in a string as a parameter and parses the string.  Each section of the string is stored into the member variable, `v`.  The member function, `exc_command(string, int&)`, evaluates each command and executes the command.

***Note:*** *Only the class declarations have been shown above for conciseness.*

## Input

The entire command line will be taken in and stored in a string member variable of Class `Input` called `input`.  
```
void recieveinput(int &check)
{
    string s;
    input.clear();
    cout << "$: ";
    getline(cin, s);
    input = s;
    check = 0;
}
```
Here `recieveinput(int&)` is using `getline(cin, string)` to get input from the user and store it into a string, which will then be stored into `input`.  The variable `check`, is of datatype int and passed in by reference to initialize check to 0, as it will later be used to track evaulated connectors. Each index of the vectors will be evaluated via the `exc_command(string, int&)` function of Class `Command`.

## Example
Example 1:

Input:
```
$: ls
$: echo hello
$: exit
```
Output:
```
$: ls
//List of Directories
$: echo hello
hello
$ exit
```
Example 2:

Input:
```
$: ls -a echo hello; mkdir test
$: exit
```
Output:
```
$: ls -a echo hello; mkdir test
//List of Directories
hello
$: exit
```

## Known Bugs
In certain cases, where a command has failed, *exit* may be needed to be inputted several times.  However, please note that the program will sucessfully exit after the series of *exit's* have been inputted.  For example:
```
$: cd
$: cd
$: cd
$: exit
$: exit
$: exit
```

Single commands that include comments will print out the entire comment, rather than ignoring the comment.  Multiple commands that include comments execute successfully.  For example:

Single Command:
```
$: echo hello #comment
hello #comment
```
Multiple Commands:
```
$: echo hello ; ls #comment
hello
//List of Directories
```

## Contributors
* Sara Hu (https://github.com/shu012)
* Roger Halftermeyer (https://github.com/rhalf001)
