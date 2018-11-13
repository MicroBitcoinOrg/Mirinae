# Copyright (c) 2018 iamstenman
#!/bin/bash
cd "$(dirname "$0")" || exit 1

gcc -c src/mbchash.c
gcc -c src/sph/sph_groestl.c
gcc -c src/sph/sph_whirlpool.c
g++ -c src/converter/base_converter.cpp
g++ ./main.cpp -o mbc_hash mbchash.o sph_groestl.o sph_whirlpool.o base_converter.o