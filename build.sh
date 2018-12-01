# Copyright (c) 2018 iamstenman
#!/bin/bash
cd "$(dirname "$0")" || exit 1

gcc -c src/mbchash.c
gcc -c src/sph/sph_groestl.c
gcc -c src/kupyna/kupyna_tables.c
gcc -c src/kupyna/kupyna512.c
g++ -c src/converter/base_converter.cpp
g++ ./main.cpp -o mbc_hash mbchash.o sph_groestl.o kupyna_tables.o kupyna512.o base_converter.o