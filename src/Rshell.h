#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <boost/tokenizer.hpp> //included so that tokenization can occur using boost
#include <unistd.h> // contains fork
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> //contains wait
#include <sys/types.h>
#include <sys/mman.h> // contains mmap() function 
#include <stack>
#include "Command.h"
#include "Executable.h"
#include "Connector.h"
#include "PCMD.h"


#ifndef RSHELL_H
#define RSHELL_H

using namespace std;







class Rshell{
    
    protected:
  
    vector<Command*> tokens;    //Contains all of the commands
    bool* exitRshell;   //points to the truth value for whether the exit command was typed or not
    

    public:
    
    void readInput(); //Parses string into commands and pushes them into vector
    void executeList(); //Executes commands on the vector
    void clearTokens(); // Clears the tokens vector each time commands are executed
    // void accessExitRshell(bool& e);
    bool exitRshellAccessor(); // exits rshell
    
    
    
    
};

#endif