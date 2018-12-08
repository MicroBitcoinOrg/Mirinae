# Copyright (c) 2018 iamstenman
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#!/bin/bash
cd "$(dirname "$0")" || exit 1

gcc -c crypto/sph/sph_groestl.c
gcc -c crypto/kupyna/kupyna_tables.c
gcc -c crypto/kupyna/kupyna512.c
g++ -c utils/converter/base_converter.cpp
gcc -c mirinae.c

g++ -std=c++11 ./main.cpp -o mbc_hash mirinae.o sph_groestl.o kupyna_tables.o kupyna512.o base_converter.o