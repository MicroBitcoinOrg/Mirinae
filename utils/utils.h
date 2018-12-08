// Copyright (c) 2018 iamstenman
#include <sstream>
#include <iomanip>
#include <cmath>

std::string hex_convert(const char *data, int len) {
    const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    std::string s(len * 2, ' ');
    for (int i = 0; i < len; ++i) {
        s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
        s[2 * i + 1] = hexmap[data[i] & 0x0F];
    }

    return s;
}

std::string hex_convert(int64_t value) {
    std::string result;
    std::stringstream stream;
    stream << std::hex << value;
    stream >> result;
    stream.str(std::string());
    stream.clear();

    return result;
}

int64_t decimal_convert(std::string value) {
    int64_t result;
    std::stringstream stream;
    stream << value;
    stream >> std::hex >> result;

    return result;
}

std::string string_reverse(std::string str, bool tmpr = false) {
    std::string tmp;
    std::string result;
    for (int i = 0; i < str.length(); i += 2) {
        tmp = str.substr(i, 2);
        if (tmpr) {
            tmp = std::string(tmp.rbegin(), tmp.rend());
        }
        result = tmp + result;
    }

    return result;
}

std::string string_pack(int64_t value, bool tmpr = false) {
    std::stringstream packer;
    std::string result;
    packer << std::setfill('0') << std::setw(8) << std::hex << value;
    packer >> result;
    packer.str(std::string());
    packer.clear();

    return string_reverse(result, tmpr);
}

void bytes_convert(std::string hex, unsigned char* output) {
    int hex_length = hex.length();

    unsigned char bytes[hex_length / 2];
    std::stringstream converter;
    for (int i = 0; i < hex_length; i += 2) {
        converter << std::hex << hex.substr(i, 2);
        int byte;
        converter >> byte;
        bytes[i / 2] = byte & 0xFF;
        converter.str(std::string());
        converter.clear();
    }

    memcpy(output, bytes, hex_length / 2);
}

std::string target(int64_t bits) {
    std::string hex_bits = hex_convert(bits);
    int64_t exponent = decimal_convert(hex_bits.substr(0, 2));
    int64_t coefficient = decimal_convert(hex_bits.substr(2, 8));
    std::string target = std::to_string(coefficient * std::pow(2, (8 * (exponent - 3))));
    target = target.substr(0, target.find("."));
    const BaseConverter& converter = BaseConverter::DecimalToHexConverter();
    std::string result = "";

    for (int i = 0; i < 64 - converter.Convert(target).length(); i++) {
        result += "0";
    }

    return result;
}

std::string block_header(int64_t version, std::string prev_block, std::string merkle_root, int64_t timestamp, int64_t bits, int64_t nonce) {
    return string_reverse(string_pack(version, true)) + string_reverse(prev_block) + string_reverse(merkle_root) + string_pack(timestamp) + string_pack(bits) + string_pack(nonce);
}