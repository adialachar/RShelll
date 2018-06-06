#include "Command.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;
#ifndef CONNECTOR_H
#define CONNECTOR_H



class Connector : public Command{
    
  
  
  public:
  
  Connector(string& s); // takes a string argument, just modifies the "command" string from the base class
  virtual bool execute(bool& x); // virtual function from the base class

  
  
    
    
    
};

#endif