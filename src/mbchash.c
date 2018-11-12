// Copyright (c) 2018 iamstenman
#include "mbchash.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "sph/sph_groestl.h"

void groestl(const unsigned char* input, int length, char* output)
{
    uint32_t hash[16];
    
    sph_groestl512_context ctx_groestl[2];

    sph_groestl512_init(&ctx_groestl[0]);
    sph_groestl512 (&ctx_groestl[0], input, length);
    sph_groestl512_close(&ctx_groestl[0], hash);
    
    sph_groestl512_init(&ctx_groestl[1]);
    sph_groestl512 (&ctx_groestl[1], hash, 64);
    sph_groestl512_close(&ctx_groestl[1], hash);
    
	memcpy(output, hash, 32);
}
