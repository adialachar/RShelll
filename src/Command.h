#include <string>
#ifndef COMMAND_H
#define COMMAND_H



using namespace std;



class Command{
    
  protected:
  
  string command; //contains literal command
 
  int cmdtype;  // an enumeration, used to help differentiate between Executables and Connectors (mostly for debugging purposes)
                // 0 is an executable, 1 is a connector
  
  
  public:
  virtual string getCommand(){  //accessor function, just return the string "command" itself
      return command;
  }
  virtual int getcmdtype(){ //another accessor function, just return the cmdtype
    return cmdtype;
  }
  virtual bool execute(bool& x)=0; //pure virtual function, used to execute Executables nad Connector objects, both of which inherit from this class
  
  
    
    
    
};

#endif