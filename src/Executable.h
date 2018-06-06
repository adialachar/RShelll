#include "Command.h"
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#ifndef EXECUTABLE_H
#define EXECUTABLE_H

using namespace std;


class Executable : public Command{
    
    protected:
    
    vector <string> flags;  //contains flags of commands, mostly used for debugging purposes
    

    
    public:
    
    Executable(string & cmd);   //Modifies the string "command" from the base class

    
    virtual bool execute(bool& x);  // virtual bool function from the base class
    
    
    
    
    
    
};


#endif