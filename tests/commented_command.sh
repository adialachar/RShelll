#!/bin/sh
#tests comments

bin/rshell << EOF
ls -a #list directories
echo hello #echo "hi"
mkdir  test #create a directory named test
echo hi #hello echo you should not see this
ls -l #list directories
echo hello # #echo "hi"
mkdir  test1 #create a directory named test
echo hi #hello
exit Rshell
EOF
