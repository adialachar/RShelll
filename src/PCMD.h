#include <vector>
#include <iostream>
#include "Command.h"
#ifndef PCMD_H
#define PCMD_H

using namespace std;


bool isEqual( vector<bool> One, vector<bool> Two);




class PCMD : public Command{
    
    protected:
    
    vector<Command*> v;
    
    vector <bool> AND1;
    vector <bool> OR1;
    vector <bool> OR2;
    
    bool AND = true;
    bool OR = false;
    
    //vector <bool> myVector;
    
    public:
    
    PCMD(vector <Command*> s){
        //cout << "Entered PCMD constructor" << endl;
        for ( unsigned int i = 0; i < s.size(); ++i){
            command += s.at(i)->getCommand();
        }
        v = s;
        cmdtype = 8;
        //Holy parse it lol
        //v.push_back and all
        AND1 = {true, true, true};
        OR1 = {true, false};
        OR2 = {false, true};
        
        
    }
    int atcmdtype(unsigned int a){
        return v.at(a)->getcmdtype();
    }
    unsigned int size(){
        return v.size();
    }
    bool execute(bool& x);
    
    
    
    
    
    
};


#endif