#include "Executable.h"
#include "Connector.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <queue>
#ifndef EXECUTABLE_CPP
#define EXECUTABLE_CPP


using namespace std;
char* stringToCharPointer(string s){
    
    return const_cast<char*>(s.c_str());
    
}
Executable::Executable(string & cmd){
    
    
    command = cmd;
    cmdtype = 0;
    
    
    
}

bool Executable::execute(bool& x){
    
   

    string s = (this)->getCommand();
    bool pipeOrRedir = false;
    string path;
   
    if (s == " "){
        
        return true;
        
    }


    if (s.at(0) == ' '){    //Just checks if the first character is a space. If it is, it deletes it.
        s.erase(0,1);
       // cout << "First character was a space, it has been deleted" << endl;
        
    }
    
    
    
    
    for (unsigned int i = 0; i < s.size(); ++i){
        
        if (s.at(i) == '<' || s.at(i) == '>' || s.at(i) == '|'){
            pipeOrRedir = true;
        }
        
    }
    if (pipeOrRedir){
        
    vector<string> executables;
    vector<string> connectors;
    vector<Command*> Commands;
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    typedef boost::tokenizer<boost::char_separator<char> > connectorizer; 
    boost::char_separator<char> cnc{"<>|"}; 
    tokenizer tok{s, cnc};
    
    //range based for loop
    for (const auto &t : tok){
        executables.push_back(t);
    }
    boost::char_separator<char> alphanumspace{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-[]/ "};
    
    connectorizer conn{s, alphanumspace};
    
    for (const auto &t : conn){
        
        connectors.push_back(t);
        // same thing as before, but now all connectors, which are "&&", "||", and ";" are now in one vector of strings
    }
    string copy = s;
    int a;
    int b;
    string x;
    string y;

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int loopCount = 90;
    while(!copy.empty() && loopCount > 0){

        if ( i < executables.size()){
            a = executables.at(i).size();

        
        }
        
        
        if (j < connectors.size()){
            b = connectors.at(j).size();

        }
        
        x = copy.substr(0,a);

        y = copy.substr(0,b);


        if ( i < executables.size() && executables.at(i) == x){

            Commands.push_back(new Executable(executables.at(i)));
            copy.erase(0,a);
            ++i;
            
        }
        
        else if (j < connectors.size() && connectors.at(j) == y){

            Commands.push_back(new Connector(connectors.at(j)));
            copy.erase(0,b);
            ++j;
        }
        --loopCount;
        if(loopCount == 0){cout << "DEATH BY LOOPCOUNT, THIS MIGHT BE AN INFINITE LOOP" << endl;}
    }
    
    
    
    
    for (unsigned int k = 0; k < Commands.size(); ++k){
        cout << Commands.at(k)->getCommand() << endl;
    }
    cout << Commands.size() << endl;
    
    
    if (Commands.at(0)->getCommand().at(Commands.at(0)->getCommand().size() - 1) == ' '){
            Commands.at(0)->getCommand().erase(Commands.at(0)->getCommand().size() - 1, 1);
            cout << "hji" << endl;
        }
    
    
    // cmd 1 < file case
   vector <char*> seperatedBySpace;
    for ( unsigned int k = 0; k < Commands.at(0)->getCommand().size(); ++k){
        cout << "hi " << endl;
        if (Commands.at(0)->getCommand().at(k) == ' '){
            string ss = Commands.at(0)->getCommand().substr(0, k - 1);
            string tt = Commands.at(0)->getCommand().substr(k + 1, (Commands.at(0)->getCommand().size() - 1) - k );
            seperatedBySpace.push_back(stringToCharPointer(ss));
            seperatedBySpace.push_back(stringToCharPointer(tt));
            break;
            
        }
    }
    cout << endl << endl;
    for ( unsigned int i = 0; i < Commands.size(); ++i){
        cout << Commands.at(i)->getCommand() << endl;
        if (Commands.at(i)->getCommand().at(0) == ' '){
            queue<char> q;
            for ( unsigned int j = 0; j < Commands.at(i)->getCommand().size(); ++j){
                if (Commands.at(i)->getCommand().at(j) != ' '){
                    q.push(Commands.at(i)->getCommand().at(j));
                    
                }
            }
            string sza;
            while (!q.empty()){
                sza += q.front();
                q.pop();
            }
            
            Commands.at(i) = new Executable(sza);
            
            cout << Commands.at(i)->getCommand() << endl;
        }
        
    }
    cout << endl << endl;
    
    bool ioredircase = false;
    bool pipecase = false;
    bool in = false;
    bool out = false;
    bool app = false;
    char* aa;
    char* bb;
    char* filename;
    //int fd;
    for (unsigned int i = 0; i < Commands.size(); ++i){
        if ( Commands.at(i)->getCommand() == "<" ){
            cout << "HEllo its a me mario" << endl;
            ioredircase = true;
            in = true;
            string whereverYouAre;
            string YourewithTheBBC;
            whereverYouAre = Commands.at(i - 1)->getCommand();
            YourewithTheBBC = Commands.at(i + 1)->getCommand();
            YourewithTheBBC = "../" + YourewithTheBBC;
            cout << whereverYouAre << endl;
            cout << YourewithTheBBC << endl;
            aa = stringToCharPointer(whereverYouAre);
            bb = stringToCharPointer(YourewithTheBBC);
            
            filename = bb;
            cout << *(aa) << endl;
            cout << *(bb + 1) << endl;
            
        }
        else if (Commands.at(i)->getCommand() == ">"){
            ioredircase = true;
            out = true;
            aa = stringToCharPointer(Commands.at(i - 1)->getCommand());
            bb = stringToCharPointer(Commands.at(i + 1)->getCommand());
            filename = bb;
        }
        else if (Commands.at(i)->getCommand() == ">>"){
            ioredircase = true;
            app = true;
            aa = stringToCharPointer(Commands.at(i - 1)->getCommand());
            bb = stringToCharPointer(Commands.at(i + 1)->getCommand());
            filename = bb;
        }
    }
    
    for (unsigned int i = 0; i < Commands.size(); ++i){
        if (Commands.at(i)->getCommand() == "|"){
            cout << "ITs a me luigi " << endl;
            pipecase = true;
        }
    }
    //int bbq;
   
    string neigh = Commands.at(0)->getCommand();
    string bor = "../" + Commands.at(2)->getCommand();
    cout << bor << endl;
    
     
    // cmd 1 > file case
    
    
    // cmd 1 < file1 > file2 case
    
    
    if (ioredircase){
       
       pid_t pid = fork();
       
       if (pid < 0){
           perror("fork error boi");
       }
       else if (pid == 0){
           
           if(in){
            
            string fat = neigh;
            string got = bor;
            aa = stringToCharPointer(fat);
            bb = stringToCharPointer(got);
            
            char* arr[] = {aa, bb, NULL};
            execvp(arr[0], arr);
                   
           }
           else if (out){
            cout << filename << endl;   
           }
           else if (app){
               
           }
        
           
       }
       else if (pid > 0){
           
           wait(NULL);
           
       }
     
     
     
        
        
        

    }
    
    //cmd 1 | cmd 2 case 
    else if (pipecase){
        

        
    }
    

    

        
        
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
        
    cout << "tetris" << endl;
    return true;
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    }
    
    
    
    else if ((s.at(0) == '[' || s.substr(0,4) == "test") && !pipeOrRedir){
        
    struct stat a;
    string flag;
    string dash_e = "-e";
    string dash_f = "-f";
    string dash_d = "-d";
    string path;
    int flagInd;

    int STAT_RETURN_VALUE;
    
    for ( unsigned int i = 0; i < s.size(); ++i){
        
        if (s.at(i) == '-'){
            flag += s.at(i);
            flag += s.at(i + 1);
            flagInd = i + 1;
            break;
        }
        
        
    }
   
    
    
    for ( unsigned int j = flagInd + 1; j < s.size(); ++j){
        path += s.at(j);
    }
    
    if (path.at(path.size() - 1) == ']' || path.at(path.size() - 1) == ' '){
        
        path.erase((path.size() - 1), 1);
        
    }
    if(path.at(path.size() - 1) == ' '){ path.erase(path.size() - 1, 1);}
    if(path.at(0) == ' '){ path.erase(0, 1);}
    


    STAT_RETURN_VALUE = stat(const_cast<char*>(path.c_str()), &a);  // after making the string something i can deal with, put it through the stat function
    
    if (STAT_RETURN_VALUE == 0){
        
        if (flag == "-f"){
            int isF = S_ISREG(a.st_mode);

            if (isF != 0){
                cout << "(True)" << endl;
            }
            else{
                cout << "(False)" << endl;
            }
    
        }
    
        else if (flag == "-d"){
            int isD = S_ISDIR(a.st_mode);
            if (isD != 0){
                cout << "(True)" << endl;
            }
            else{
                cout << "(False)" << endl;
            }
    
        }
        
        else if (flag == "-e" || flag.empty()){
            cout << "(True)" << endl;
        }
    }
    else if (STAT_RETURN_VALUE == -1){
        cout << "(False)" << endl;
    }
    
        
    return true;  
        
        
        
        
        
    }
    
    
    char* cmd;
     /*
     
     s_f stands for space found. 
     We wanted to differentiate between
     commands that contained spaces and 
     commands that did not in order 
     to make debugging easier
     
     */
     
    bool s_f = false;  
    
    
    
    vector<string> v;
    string tempString;
    const int currMaxIndex = 2;
    int EXECVP_RETURN_VALUE;    // will contain return vaue of execvp in order to call perror properly
    

    
    
    
    
    
    
    /*
    
    Searches whether a space is found in the 
    middle of the command, the last if statement 
    made sure that the first character is not a space
    
    */
    

    for(unsigned int i = 0; i < s.size(); ++i){ 
        if (s.at(i) == ' '){
            s_f = true;
            //cout << "Space found inside string s" << endl;
            
        }
        
    }
  
    
    //for no space commands like ls, pwd, etcetera 
    if(!s_f){

        for (unsigned int j = 0; j < s.size(); ++j){
            if (s.at(j) == '#'){
                
                
                return true;
            }
        }
        
        char* argz[2];
        cmd = const_cast<char*>(s.c_str());
        argz[0] = cmd;
        argz[1] = NULL;
    
        EXECVP_RETURN_VALUE = execvp(cmd, argz);
        
        if (EXECVP_RETURN_VALUE == -1){ 
            perror("Error: command not found");
            return false;
            
        }
        return true;
    
        }
    
    //for any other command including "chmod 711 filename.sh", "ls -a", "echo hello"
    else if(s_f){
        
        for (unsigned int j = 0; j < s.size(); ++j){
            if (s.at(j) == '#'){
                
                
                return true;
            }
        }
        
        
        //argument that is going to passed into execvp
        char* args[] = {0, 0, NULL};
        
        //parses the command into two seperate strings, cleaved at the space
        for (unsigned int i = 0; i < s.size(); ++i){
            
            if (s.at(i) != ' '){
                tempString += s.at(i);
            }
            if (s.at(i) == ' ' || i == s.size() - 1){
                v.push_back(tempString);
                tempString.clear();
            }
        }
        
        
        //if more room in the array is required, for say like a command with 3 parts like "chmod 711 filename.sh", this allows for its expansion
        if (v.size() > currMaxIndex){
            args[v.size()] = NULL;
        }
        
        //properly formats all of the strings so that execvp will take them
        for (unsigned int i = 0; i < v.size(); ++i){
            args[i] = const_cast<char*>((v.at(i)).c_str());
        }
        //execvp takes in arguments passed into the command line, return value stored in EXECVP_RETURN_VALUE
        
        EXECVP_RETURN_VALUE = execvp(args[0], args);
        
        //if execvp was unsuccessful
        if (EXECVP_RETURN_VALUE == -1){
            perror("Error: command not found");
            return false;
        }
            
        return true;
    }
        
        
        
        
        return false;
        
        
        
        
        
        
        

    
}

// string getCommand(){
//     return this->command;
// }

#endif