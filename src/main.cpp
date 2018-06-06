#include <iostream>
#include "Rshell.h"
#ifndef MAIN_CPP
#define MAIN_CPP


using namespace std;



int main(){
    
    
    Rshell rshell;  //Calls Rshell default constructor
    
    while (!(rshell.exitRshellAccessor())){ //makes sure the commands execute again until exit command is typed
       
        rshell.clearTokens(); //clears the tokens vector
        rshell.readInput(); //reads input from command line
        rshell.executeList(); //executes command given to command line by user
    }
    
    
    return 0;
}

#endif