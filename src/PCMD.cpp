#include "PCMD.h"
#include <unistd.h> // contains fork
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> //contains wait
#include <sys/types.h>
#include <sys/mman.h> // contains mmap() function 
#ifndef PCMD_CPP
#define PCMD_CPP

using namespace std;

vector <bool> myVector;
bool isEqual( vector<bool> One, vector<bool> Two){
        
    if (One.size() != Two.size()){
        return false;
    }
    
    for ( unsigned int i = 0; i < One.size(); ++i){
        if (One.at(i) != Two.at(i)){
            return false;
        }
    }
    return true;
    
    
    
    
}
//THE EXACT SAME AS THE RSHELL EXECUTE LIST FUNCTION

bool PCMD::execute(bool& x){
  static bool* pleaseDoNotEnter = (bool *)mmap(NULL, sizeof(pleaseDoNotEnter), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  static bool* containsHash = (bool *)mmap(NULL, sizeof(containsHash), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  static unsigned int* i = (unsigned int *)mmap(NULL, sizeof(i), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); 
  *(pleaseDoNotEnter) = false;
  *(containsHash) = false;
  myVector.clear();
  

  
  for ( *(i) = 0; *(i) < v.size(); ++*(i)){
       
   
       
        pid_t pid = fork(); //fork executed
        //Checks for exit command
      /*  if (v.at(*i)->getCommand() == "exit Rshell"){
           
            v.clear();
            
            for (unsigned int j = 0; j < v.size(); ++j){
                cout << v.at(*i)->getCommand() << endl;
                
            }
            
            *(proxy) = true;
       
            *(i) = v.size();
           
            *pleaseDoNotEnter = true;
           
            break;
            
            
            
            
        } */
        
       // else{
        
            
        
          /*
            Fork is a process that returns twice. 
  
  
          */
  
            if ( pid < 0){
                perror("fork failed");
                exit(1);
            }
    
            if (pid == 0 && !(*pleaseDoNotEnter) ){
                //Child
                
                // Checks for comments
                string s = v.at(*i)->getCommand();
               
                for ( unsigned int k = 0; k < s.size(); ++k){
                   
                    if(s.at(k) == '#'){
                        // cout << "Hash found" << endl;
                        *(containsHash) = true;
                    }
                }
                
                //executes each item in the v vector, stores the result in x
                myVector.push_back(x);
                
                if (x && ((v.at(*i)->getcmdtype() == 0) || (v.at(*i)->getcmdtype() == 8)) ){
                    x = v.at(*(i))->execute(x);
                    
                }
                else if (v.at(*i)->getcmdtype() == 1){
                    x = v.at(*i)->execute(x);
                }
                if (*(containsHash)){

                    (*i) = v.size();
                    break;
                }
            }
        
            if (pid > 0 ){
            
                wait(NULL);
            
            }
           
        //}
    
    }

    // cout << isEqual(AND1, myVector) << endl;
    return true;

    
    
    
    
}


#endif