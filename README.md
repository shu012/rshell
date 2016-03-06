# rshell

## Synopsis

**Rshell** works as a command shell that will prompt the user with `$: ` and take in a command or a series of commands, evaluate the command(s), and execute the command(s).  The user will continously be prompted until `exit` is inputted.  Valid commands may be inputted in the format: `executable [arguementList] [connector cmd]`.  Valid connectors include: `||`, `&&`, and `;`.  The command `test` or `[]` may be utilized to execute a test command in the format: `test -flag path` or `[ -flag path]`.  Valid flags include: `-f`, `-d`, and `-e`.  Flags may be omitted, in which case the default flag, `-e`, will be used.  A user may, also, indicate precedence with the use of `()`.

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
        void clear_string();
        void getinput(int &check);
        string get_string();
        bool check_prec();
};
```
The member function `clear_string()` clears the member variable input.  `getinput(int&)` will get input from the user and store the input into the member variable input.  `get_string()` simply returns input and `check_prec()` returns `true` if there is precedence in the input and `false` if there is not.

Class `Command` inherits from Class `Input` and has a member variable `v`, which is a vector of strings.  Class Command includes one constructor and three member functions.
```
class Command : public Input
{
    public:
        void exc_command(string command, int& passed);
        bool check_test(string cmd, int& passed);
        void testcommand(string command, int& passed);
        void ctr_parse(string temp, vector<char>& connectors);
        void cmd_parse(string tmp, vector<string>& commands);
        void mult_commands(vector<string> vs1, vector<char> vc1,  int& cmdcnt);
        void skip(string command, int& i);
        void precedencecommand(string command, int& passed);
};
```
The member function, `exc_command(string, int&)`, evaluates each command and executes the command.  `check_test(string, int&)` returns `true` if the `test` command is found, meaning that `test` or `[]` were used to indicate a command, otherwise the function will return `false`.  `testcommand(string, int&)` executes the bash `test` command.  `ctr_parse(string, vector<char>&)` parses out connectors in a given string and store the connectors into a `vector<char>`.  `cmd_parse(string, vector<string>&` works similarly to `ctr_parse(string, vector<char>&)` and will parse out commands and store the commands into a `vector<string>`.  `mult_commands(vector<string>, vector<char>, int&)` deals with the execution of multiple commands.  `skip(string, int&)` will skip the right expression of a connector if needed when precedence is involved.  For example, if `(command1 || command2)` is inputted, where `command1` is true, then `command2` will be skipped.  `precedencecommand(string, int&)` deals with the execution of commands if precedence is present.

***Note:*** *Only the class declarations have been shown above for conciseness.*

## Execution without Precedence

The entire command line will be taken in and stored in a string member variable of Class `Input` called `input`.
```
void getinput(int &check)
{
    cout << "$: ";
    getline(cin, input);
    check = 0;
}
```
Here `getinput(int&)` is using `getline(cin, input)` to get input from the user and store it into `input`.  The variable `check`, is of datatype int and passed in by reference to initialize check to 0, as it will later be used to track evaulated connectors. `input` will always will evaluated to check for precedence using the `check_prec()` function.  If `check_prec()` returns false, then each index of the vectors will be tested to check for a `test` command via `check_test(string, int&)`.  If `check_test(string, int&)` returns false, the command will be evaluated via the `exc_command(string, int&)` function of Class `Command`.  However, if `check_test(string, int&)` returns true, then `testcommand(string, int&)` will be used to evaluate the command.

### Examples
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
Example 3:

Input:
```
$: test -e /test/file/path && echo “path exists”
```
or
```
$ [ -e /test/file/path ] && echo “path exists”
```
Output:
```
(True)
path exits
```

##Execution with Precedence
If `check_prec()` returns `true`, then `precedencecommand(string, int&)` will be used to execute each command along with the uses of `ctr_parse(string, vector<char>&)`, `cmd_parse(string, vector<string>&)`, `mult_commands(vector<string> vs1, vector<char>,  int&)`, and  `skip(string, int&)` if applicable.

###Examples




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
