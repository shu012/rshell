#!/bin/sh

make -C ..
./../a.out << 'EOF'
mkdir test
test -e test
[ -e test ]
test -e test && ls
[ -e test ] && ls
exit
EOF

make -C ..
./../a.out << 'EOF'
echo hello
echo checking exit
exit
EOF

printf "\n"
ls
rm -rf test


