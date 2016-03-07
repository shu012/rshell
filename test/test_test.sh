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

printf "\n"
ls



