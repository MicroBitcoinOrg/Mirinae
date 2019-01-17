// Copyright (c) 2018 iamstenman
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "crypto/sph/sph_groestl.h"
#include "crypto/kupyna/kupyna512.h"
#include "mirinae.h"
#include <memory.h>

// You can use any arbitrary data as seed
// In case of MBC mirinae uses previous block hash from block header
void seed_get(const void* input, unsigned char* seed) {
	memcpy(seed, input + 4, (36 - 4) * sizeof(*input));
}

// Let's add some kittens to algo :D
uint32_t murmur3(const uint8_t* key, size_t len, uint32_t seed) {
	uint32_t h = seed;
	if (len > 3) {
		const uint32_t* key_x4 = (const uint32_t*) key;
		size_t i = len >> 2;
		do {
			uint32_t k = *key_x4++;
			k *= 0xcc9e2d51;
			k = (k << 15) | (k >> 17);
			k *= 0x1b873593;
			h ^= k;
			h = (h << 13) | (h >> 19);
			h = (h * 5) + 0xe6546b64;
		} while (--i);
		key = (const uint8_t*) key_x4;
	} else if (len & 3) {
		size_t i = len & 3;
		uint32_t k = 0;
		key = &key[i - 1];
		do {
			k <<= 8;
			k |= *key--;
		} while (--i);
		k *= 0xcc9e2d51;
		k = (k << 15) | (k >> 17);
		k *= 0x1b873593;
		h ^= k;
	}

	h ^= len;
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;

	return h;
}

// All magic is here!
void mirinae(const void* input, void* output, size_t length, int height)
{
	assert(height > 0);
	unsigned char hash[64] = { 0 };
	unsigned char offset[64] = { 0 };
	unsigned char seed[32] = { 0 };
	const int window = 32;
	const int aperture = 32;

	seed_get(input, seed);
	int64_t n = murmur3(seed, 32, height);
	
	sph_groestl512_context ctx_groestl;
	struct kupyna512_ctx_t ctx_kupyna;

	sph_groestl512_init(&ctx_groestl);
	sph_groestl512(&ctx_groestl, input, length);
	sph_groestl512_close(&ctx_groestl, hash);

	unsigned int light = (hash[0] > 0) ? hash[0] : 1;
	for (int i = 0; i < (((n % height) + (height + 1)) % window); i++) {
		unsigned int inner_loop = (light % aperture);
		for (int j = 0; j < inner_loop; j++) {
			kupyna512_init(&ctx_kupyna);
			kupyna512_update(&ctx_kupyna, hash, 64);
			kupyna512_final(&ctx_kupyna, hash);
		}

		light = (hash[inner_loop] > 0) ? hash[inner_loop] : 1;
	}

	sph_groestl512_init(&ctx_groestl);
	sph_groestl512(&ctx_groestl, hash, 64);
	sph_groestl512_close(&ctx_groestl, hash);

	memcpy(output, hash, 32);
}
