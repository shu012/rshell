#!/bin/sh

make -C ..
./../a.out << 'EOF'
ls -a; echo hello; mkdir test
exit
EOF

printf "\n"
ls
rm -rf test


