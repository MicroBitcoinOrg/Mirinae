// Copyright (c) 2018 iamstenman
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "utils/converter/base_converter.h"
#include "utils/utils.h"
#include "mirinae.h"

#include <iostream>
#include <stdint.h>
#include <string.h>

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

        const unsigned char *input = bytes;
        char output[32];

        mirinae(input, output, header_hex.length() / 2, height);
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
