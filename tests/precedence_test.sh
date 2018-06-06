#!/bin/sh



bin/rshell << EOF
(echo A && echo B) || (echo C && echo D)
EOF