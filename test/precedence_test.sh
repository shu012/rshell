#!/bin/sh

make -C ..
./../a.out << 'EOF'
(ls) && (ls)
(ls && ls) || (ls && ls)
(ls && ls) && (ls && ls) || (ls && ls)
ls && (ls || ls) && ls
exit
EOF

printf "\n"
ls


