#pragma once

#include <base/common.h>

uint16_t getCheckSum(const uint16_t *data, size_t len, const uint16_t base=0);
template<typename T> T swap_bytes(const T data);

enum HexFormat {
    HEX_COMMON = 0,
    HEX_ASCII = 8,
};
string getstr_hex(const uint8_t *buf, size_t size, HexFormat hex_type=HEX_ASCII);
void print_hex(const uint8_t *buf, size_t size, HexFormat hex_type=HEX_ASCII);
template<typename T> string getstr_hex(const T data);
template<typename T> void print_hex(const T data);
template<typename T> string getstr_bin(const T data);
template<typename T> void print_bin(const T data);




template<typename T>
T swap_bytes(const T data) {
    T res = 0;
    const int byte = 0xff;
    int cnt = 0;
    int left = sizeof(T);
    while(left--) {
        res <<= 8;
        res |= (data & (byte<<cnt)) >> cnt;
        // print_hex((data & (byte<<cnt)) >> cnt);
        cnt += 8;
    }
    return res;
}

template<typename T>
string getstr_hex(const T data) {
    char res[17];
    const int byte = 0x0f;
    int cnt = 0;
    int i = sizeof(T) * 8;
    while ((i -= 4) >= 0) {
        int tmp = (data & (byte<<i)) >> i;
        if (tmp < 10)
            res[cnt] = '0' + tmp;
        else 
            res[cnt] = 'a' + tmp - 10;
        cnt ++;
    }
    res[cnt] = '\0';
    return string("0x") + res;
}

template<typename T>
void print_hex(const T data) {
    printf("%s\n", getstr_hex(data).c_str());
}

template<typename T>
string getstr_bin(const T data) {
    char res[65];
    int cnt = 0;
    int i = sizeof(T) * 8;
    while ((i -= 1) >= 0) {
        int tmp = (data & (1<<i)) >> i;
        res[cnt] = '0' + tmp;
        cnt ++;
    }
    res[cnt] = '\0';
    return string("0b") + res;
}

template<typename T>
void print_bin(const T data) {
    printf("%s\n", getstr_bin(data).c_str());
}

