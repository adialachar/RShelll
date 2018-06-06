#!/bin/sh


bin/rshell << EOF
[ -e ../src]
[ -d ../src]
[ -f ../src]
[ -e ../src/Command.cpp]
[ -d ../src/Command.cpp]
[-f ../src/Command.cpp]
test -e ../src/Connector.cpp
test -d ../src/Connector.cpp
test -f ../src/Connector.cpp
exit Rshell
EOF