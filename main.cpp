// Copyright (c) 2018 iamstenman
#include <iostream>
#include <stdint.h>
#include <string.h>

#include "src/converter/base_converter.h"
#include "src/mbchash.h"
#include "src/util.h"

int main() {
    int64_t version = 2;
    int64_t height = 525001;
    std::string prev_block = "0000acc34546b8285eafd0e6419e0fcf4c0577562eac23d632d123931e0fff72";
    std::string merkle_root = "5e9846ebda6e8687582336d52e5a1b54974cc44c1156c267cf46d9c992bad96d";
    int64_t timestamp = 1540596242;
    int64_t bits = 520159231;
    int64_t nonce = 0;

    std::string hash = "";
    std::string prefix = target(bits);

    while (hash.compare(0, prefix.size(), prefix)) {
        std::string header_hex = block_header(version, prev_block, merkle_root, timestamp, bits, nonce);

        unsigned char bytes[header_hex.length() / 2];
        bytes_convert(header_hex, bytes);

        unsigned char bytes_block[32];
        bytes_convert(prev_block, bytes_block);

        const unsigned char *input = bytes;
        const unsigned char *block_hash = bytes_block;
        char output[32];

        mbchash(input, block_hash, height, header_hex.length() / 2, output);
        hash = string_reverse(hex_convert(output, 32));

        std::cout << "Hash: " << hash << " Nonce: " << nonce << std::endl;
        nonce++;
    }

    nonce--;
    std::cout << std::endl;
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Nonce: " << nonce << std::endl;

    return 0;
}
