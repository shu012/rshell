#!/bin/sh

make -C ..
./../a.out << 'EOF'
ls ; echo hello #r
exit
EOF



printf "\n"
