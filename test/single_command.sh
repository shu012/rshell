#!/bin/sh

make -C ..
./../a.out << 'EOF'
ls
echo hello
mkdir one
exit
EOF

printf "\n"
ls
rm -rf  one
