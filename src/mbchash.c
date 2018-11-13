// Copyright (c) 2018 iamstenman
#include "mbchash.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "sph/sph_groestl.h"
#include "sph/sph_whirlpool.h"

void groestl(const unsigned char* input, int length, char* output)
{
	uint8_t hash[64];
	
	sph_groestl512_context ctx_groestl[2];

	sph_groestl512_init(&ctx_groestl[0]);
	sph_groestl512 (&ctx_groestl[0], input, length);
	sph_groestl512_close(&ctx_groestl[0], hash);
	
	sph_groestl512_init(&ctx_groestl[1]);
	sph_groestl512 (&ctx_groestl[1], hash, 64);
	sph_groestl512_close(&ctx_groestl[1], hash);
	
	memcpy(output, hash, 32);
}

// Draft
void mbchash(const unsigned char* data, int length, char* output)
{
	unsigned char hash[64] = { 0 };
	const void *input = data;
	int iterations = 4;
	int size = length;
	
	sph_groestl512_context ctx_groestl;
	sph_whirlpool_context ctx_whirlpool;

	for (int i = 0; i < iterations; i++) {
		sph_groestl512_init(&ctx_groestl);
		sph_groestl512 (&ctx_groestl, input, size);
		sph_groestl512_close(&ctx_groestl, hash);

		for (int j = 0; j < hash[0]; j++) {
			sph_whirlpool_init(&ctx_whirlpool);
			sph_whirlpool (&ctx_whirlpool, hash, 64);
			sph_whirlpool_close(&ctx_whirlpool, hash);
		}

		sph_groestl512_init(&ctx_groestl);
		sph_groestl512 (&ctx_groestl, hash, 64);
		sph_groestl512_close(&ctx_groestl, hash);

		input = (void*)hash;
		size = 64;
	}
	
	memcpy(output, hash, 32);
}
