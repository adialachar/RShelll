#include "Rshell.h"
#include <stack>
#include <string>
#include <queue>
#include <utility>
#include "PCMD.h"

#ifndef RSHELL_CPP
#define RSHELL_CPP
class StringAndInts{
    private:
        string s;
        unsigned int start;
        unsigned int end;
    
    public:
    StringAndInts(){};
    StringAndInts(string x, unsigned int a, unsigned int b){s = x; start = a; end = b;};
    string getS(){return s;};
    unsigned int getStart(){return start;};
    unsigned int getEnd(){return end;};
    
};


using namespace std;


void Rshell::readInput(){
    
    vector <string> executables; // will be used to contain all executables as strings
    vector <string> connectors;  // will be used to contain all connectors as strings
    
    string argz; // used to take the whole line from the user in the "terminal"
    string joinargz;
    //bool firstCharisHash = false;
  
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer; // used to extract executables from the string "argz"
    typedef boost::tokenizer<boost::char_separator<char> > connectorizer; // used to extract connectors from the string "argz"
    //int connectorVectorSize; // used to store the size of the vector of strings later (will be used later)
  
    //Prompt the user
    cout <<"$ ";
    
    //Parsing the string start
    
    getline(cin, argz);
   
    
    //if (argz.at(0) == '#'){
     //   firstCharisHash = true;
    //}
    
    
    
    boost::char_separator<char> cnc{";&|#()"}; // This will filter through argsz, discarding anything that is ;,&,| or #
    tokenizer tok{argz, cnc};
    
    //range based for loop
    for (const auto &t : tok){
        executables.push_back(t);
        //pushes anything that was not ";","&", or "|" into the executable vector, so all executables are now in one place
    }
    
    
    boost::char_separator<char> alphanumspace{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-[]/<> "};
    
    connectorizer conn{argz, alphanumspace};
    
    for (const auto &t : conn){
        
        connectors.push_back(t);
        // same thing as before, but now all connectors, which are "&&", "||", and ";" are now in one vector of strings
    }
    

    

    /* The following code is used to piece all
        of the command pointes back together in
        the original order by comparing them to
        the original string
    */
    
    string copy = argz;
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

            tokens.push_back(new Executable(executables.at(i)));
            copy.erase(0,a);
            ++i;
            
        }
        
        else if (j < connectors.size() && connectors.at(j) == y){

            tokens.push_back(new Connector(connectors.at(j)));
            copy.erase(0,b);
            ++j;
        }
        --loopCount;
        if(loopCount == 0){cout << "DEATH BY LOOPCOUNT, THIS MIGHT BE AN INFINITE LOOP" << endl;}
    }
    
    vector <Command*> bb;
    unsigned int g;
    string pnt;
    for (unsigned int u = 0; u < tokens.size(); ++u){
        
        if (((tokens.at(u)->getCommand()).size() > 1) && (tokens.at(u)->getCommand().at(0) == '(' || tokens.at(u)->getCommand().at(0) == ')')){
            g = tokens.at(u)->getCommand().size();
            for ( unsigned int w = 0; w < g; ++w){
                pnt.push_back(tokens.at(u)->getCommand().at(w));
                bb.push_back(new Connector(pnt));
                pnt.clear();
            }
            
            
        }
        
        else {
            bb.push_back(tokens.at(u));
        }
        
        
    }
    tokens = bb;
    

    for ( unsigned int zz = 0; zz < tokens.size(); ++zz){
        cout << tokens.at(zz)->getcmdtype() << " ";
        cout << "(" << tokens.at(zz)->getCommand() << ")";
        cout << endl;
    }
    
    // string toJoin;
    
    // for ( unsigned int i = 0; i < tokens.size(); ++i){
        
    //     if (tokens.at(i)->getCommand() == "|"){
            
    //     }
        
        
    // }
    bool containsPipe = false;
    for (unsigned int i = 0; i < tokens.size(); ++i){
        if (tokens.at(i)->getCommand() == "|"){
            containsPipe = true;
        }
    }
    
    
    if (containsPipe){
    vector <string> vs;
    queue<StringAndInts*> vp;
    cout << "declarations" << endl;
    bool enteredIf = false;
    for (unsigned int i = 0; i < tokens.size(); ++i){
        unsigned start;
        unsigned end;
        
        cout << "entered for loop" << endl;
        string s = tokens.at(i)->getCommand();
        if (s == "|"){
            start = i - 1;
            end = i + 1;
            enteredIf = true;
            cout << "Found | " << endl;
            if (vs.size() == 0){
                vs.push_back(tokens.at(i - 1)->getCommand() + tokens.at(i)->getCommand() + tokens.at(i + 1)->getCommand());
            }else{
                vs.push_back(vs.at(tokens.size() - 1) + tokens.at(i)->getCommand() + tokens.at(i + 1)->getCommand());
                end = i + 1;
            }
            
        }else if(((s == "||" || s == "&&" || s == ";") || i == tokens.size() - 1) && enteredIf){
       
            
            cout << vs.at(vs.size() - 1) << endl;
            cout << start << endl;
            cout << end << endl;
            StringAndInts* si = new StringAndInts(vs.at(vs.size() - 1), start, end);
            cout << "Pointer declared" << endl;
            vp.push(si);
            cout << "pushed to queue" << endl;
            vs.clear();
            enteredIf = false;
        }
    }    
        
        
        vector<Command*> gg;
        
        for(unsigned int i = 0; i < tokens.size(); ++i){
            cout << "entered gg for loop" << endl;
            cout << tokens.at(i)->getCommand() << endl;
            
            cout << i << " ";
            if (!vp.empty()){cout << vp.front()->getEnd() << endl;}
            if (!vp.empty()){
                if(vp.front()->getStart() == i ){
                    cout << "Hi found start" << endl;
                    string x = vp.front()->getS();
                    cout << "((" << x << "))" << endl;
                    gg.push_back(new Executable(x));
            
                }
                else {
                    cout << "hello vp not empty()" << endl;
                    if (i < vp.front()->getStart()){
                        gg.push_back(tokens.at(i));
                    }
                    if (i == vp.front()->getEnd()){
                        vp.pop();
                    }
            }
                
                
                
                
            }
            
            else if(vp.empty()){
                cout << "This should be the first thing it does" << endl;
                gg.push_back(tokens.at(i));
                
            }
            
        }
           
            
        
        
        
        
        for(unsigned int i = 0; i < gg.size(); ++i){
            cout << "entered this for loop" << endl;   
            cout << "(" << gg.at(i)->getCommand() << ")" << endl;
        }
        
        tokens = gg;
        
        for (unsigned int i = 0; i < tokens.size(); ++i){
            cout << "(("  << tokens.at(i)->getCommand() << "))" << endl;
        }
        
    }
        
    
    
    
    
    
    //Parsing the string end
    

    
    
    
    
}


void Rshell::executeList(){


  
  
  /*
  
  "bool x" is used to store the return value
  of the evaluate function, the evaluate function
  being a pure virtual function in the Command
  base class. It is initialized to true, because as you
  will see later, we always want the first Command in the vector "tokens"
  to be executed
  
  */
  bool x = true;
  static bool* proxy = (bool *)mmap(NULL, sizeof(exitRshell), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  static bool* pleaseDoNotEnter = (bool *)mmap(NULL, sizeof(pleaseDoNotEnter), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  static bool* containsHash = (bool *)mmap(NULL, sizeof(containsHash), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *(proxy) = false;
  exitRshell = proxy;
  *(pleaseDoNotEnter) = false;
  *(containsHash) = false;
  bool containsRP = false;
  unsigned int pInd;
  vector <Command*> PComm;
  stack <Command*> toReverse;
  vector <Command*> first;
  vector <Command*> second;
  unsigned int leftP = 0;
  unsigned int rightP = 0;
 
  /*
  
  mmap is a function we used to communicate between the child and parent processes.
  We found this to be the only solution to the problems we were having
  
  
  */
  

  for (unsigned int j = 0; j < tokens.size(); ++j){
      if (tokens.at(j)->getCommand() == ")"){
         
          containsRP = true;
      }
  }


    /* The above for loop checks for the first right parentheses it finds. 
       Based on that it decides which piece of code it will execute.
       
    */
 
  if (containsRP == true){
        for (unsigned int j = 0; j < tokens.size(); ++j){
            if (tokens.at(j)->getCommand() == ")"){
                rightP = j;
                pInd = j - 1;
                while(tokens.at(pInd)->getCommand() != "("){
                    toReverse.push(tokens.at(pInd));
                    --pInd;
                }
                leftP = pInd;
            break;
            
        }
    }

    
    while (!toReverse.empty()){
            PComm.push_back(toReverse.top());
            toReverse.pop();
        
        
        }
    
    // The following code pieces the vector back together with a new 
    // PCMD object.
    
    for ( unsigned int l = 0; l < leftP; ++l){
        first.push_back(tokens.at(l));
    }
    if ( rightP + 1 != tokens.size()){
        for ( unsigned int m = rightP + 1; m < tokens.size(); ++m){
            second.push_back(tokens.at(m));
        }
    }
    
   
    PCMD* P = new PCMD(PComm);

    
    first.push_back(P);
    
    for ( unsigned int it = 0; it < second.size(); ++it){
        first.push_back(second.at(it));
    }
    
    tokens = first;
    this->executeList();    //Recursive call, which will come here again and again until no parentheses are found
    
  }
  
  else{
  
  static unsigned int* i = (unsigned int *)mmap(NULL, sizeof(i), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
  for ( *(i) = 0; *(i) < tokens.size(); ++*(i)){
       
   
       
        pid_t pid = fork(); //fork executed
        //Checks for exit command
        if (tokens.at(*i)->getCommand() == "exit Rshell"){
           
            tokens.clear();
            
            for (unsigned int j = 0; j < tokens.size(); ++j){
                cout << tokens.at(*i)->getCommand() << endl;
                
            }
            
            *(proxy) = true;
       
            *(i) = tokens.size();
           
            *pleaseDoNotEnter = true;
           
            break;
            
            
            
            
        }
        
        else{
        
            
        
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
                string s = tokens.at(*i)->getCommand();
               
                for ( unsigned int k = 0; k < s.size(); ++k){
                   
                    if(s.at(k) == '#'){
                        // cout << "Hash found" << endl;
                        *(containsHash) = true;
                    }
                }
                
                //executes each item in the tokens vector, stores the result in x

                if (x && ((tokens.at(*i)->getcmdtype() == 0) || (tokens.at(*i)->getcmdtype() == 8)) ){
                   
                    
                    x = tokens.at(*(i))->execute(x);

                }
                else if (tokens.at(*i)->getcmdtype() == 1){
                    x = tokens.at(*i)->execute(x);
                }
                
                
                // if the value returns false, skip the next element in the vector
                
                if (*(containsHash)){
                    // cout << "Contains hash" << endl;
                    (*i) = tokens.size();
                    break;
                }
            }
        
            if (pid > 0 ){
            
                wait(NULL);
            
            }
           
        }
    
  }
  }
    

}

// Used to clear tokens after each iteration of the while loop in "main.cpp"
void Rshell::clearTokens(){
    tokens.clear();
}
// Returns derefrenced value of the bool pointer "extRshell"
bool Rshell::exitRshellAccessor(){
    return *(exitRshell);
}









#endif