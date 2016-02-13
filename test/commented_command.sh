#!/bin/sh

make -C ..
./../a.out << 'EOF'
ls -a #mkdir one
echo hello
exit
EOF 

printf "\n"
ls

