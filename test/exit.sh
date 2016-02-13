#!/bin/sh

make -C ..
./../a.out << 'EOF'
exit
EOF

printf "\n"

