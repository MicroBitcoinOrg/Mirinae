// Copyright (c) 2018 iamstenman
#include "mbchash.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "sph/sph_groestl.h"
#include "kupyna/kupyna512.h"

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

void mbchash(const unsigned char* block_raw, const unsigned char* prev_block, int height, int size, char* output)
{
	const void *block_hash = prev_block;
	const void *block = block_raw;
	
	unsigned char hash[64] = { 0 };
	unsigned char offset[8] = { 0 };
	int window = 4096;
	int64_t n = 0;

	sph_groestl512_context ctx_groestl;
	struct kupyna512_ctx_t ctx_kupyna;

	kupyna512_init(&ctx_kupyna);
	kupyna512_update(&ctx_kupyna, block_hash, 8);
	kupyna512_final(&ctx_kupyna, offset);
	
	memcpy(&n, offset, 8);
	int iterations = (((n % height) + (height + 1)) % window);

	sph_groestl512_init(&ctx_groestl);
	sph_groestl512(&ctx_groestl, block, size);
	sph_groestl512_close(&ctx_groestl, hash);

	for (int i = 0; i < iterations; i++) {
		for (int j = 0; j < hash[0]; j++) {
			kupyna512_init(&ctx_kupyna);
			kupyna512_update(&ctx_kupyna, hash, 64);
			kupyna512_final(&ctx_kupyna, hash);
		}
	}

	sph_groestl512_init(&ctx_groestl);
	sph_groestl512(&ctx_groestl, hash, 64);
	sph_groestl512_close(&ctx_groestl, hash);

	memcpy(output, hash, 32);
}
