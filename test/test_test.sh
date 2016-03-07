#!/bin/sh

make -C ..
./../bin/rshell << 'EOF'
mkdir test
test -e test
[ -e test ]
test -e test && ls
[ -e test ] && ls
exit
EOF

printf "\n"
ls



