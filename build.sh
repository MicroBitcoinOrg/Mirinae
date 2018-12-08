# Copyright (c) 2018 iamstenman
#!/bin/bash
cd "$(dirname "$0")" || exit 1

gcc -c crypto/sph/sph_groestl.c
gcc -c crypto/kupyna/kupyna_tables.c
gcc -c crypto/kupyna/kupyna512.c
g++ -c utils/converter/base_converter.cpp
gcc -c mbchash.c

g++ -std=c++11 ./main.cpp -o mbc_hash mbchash.o sph_groestl.o kupyna_tables.o kupyna512.o base_converter.o