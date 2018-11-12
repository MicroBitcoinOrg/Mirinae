// Copyright (c) 2018 iamstenman
#ifndef MBCHASH_H
#define MBCHASH_H

#ifdef __cplusplus
extern "C" {
#endif

void groestl(const unsigned char* input, int length, char* output);

#ifdef __cplusplus
}
#endif

#endif
