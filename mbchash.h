// Copyright (c) 2018 iamstenman
#ifndef MBCHASH_H
#define MBCHASH_H

#ifdef __cplusplus
extern "C" {
#endif

void mbchash(const void* data, size_t length, void* output, int height, const void* seed);

#ifdef __cplusplus
}
#endif

#endif
