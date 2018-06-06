##RShell Assignment 3


This program aims to create an imiation of a linux shell in C++, which will run basic commands such as ls, echo, and mkdir

## Installation
To install the code, run the makefile in the console.
Then open the bin folder that is generated by the makefile.
Inside the bin folder is an executable called "rshell".
Execute the executable.
When the command is run, you should see something like this: $ 



## Known Bugs

1. Adding more than one space in front of a flag will make the command run incorrectly.
2. Sometimes, when typing in the exit command, it will throw a vector out of range error. 
 (This only seems to happen very rarely, and when I encounter it and try to replicate the scenario in which I encountered it, the error seems to dissapear)
3. Spacing is a big issue, especially when it comes to comments. Something like "echo hello;           #echo hi;" will not execute correctly
   but most of the time, commands like "echo hello;#echo hi;" , "echo hello; #echo hi;" , and "#echo hello echo hi" will work as intended. 


