#include "Connector.h"
#include <iostream>

#ifndef CONNECTOR_CPP
#define CONNECTOR_CPP


using namespace std;





Connector::Connector(string& s){
    
    command = s;

    cmdtype = 1;
    
}



bool Connector::execute(bool &x){
    string s = this->getCommand();
    
    for (unsigned int i = 0; i < s.size(); ++i){
        if (s.at(i) == '&'){    //If the command is an &&
            return x;
        }
        else if(s.at(i) == '|'){    //If the command is an ||
            return !x;
        }
        else if(s.at(i) == ';'){    //If the command is an ;
            return true;
        }
    }
    
    return true;
    
   
}



#endif