#include <base/common.h>

void split_string(const char *src, vector<string> &dest, const char *separator, bool null_part) {
    dest.clear();
    const char *pos;
    while (pos = strstr(src, separator)) {
        if (src != pos || null_part) {
            dest.push_back("");
            dest.back().assign(src, pos - src);
        }
        src = pos + strlen(separator);
    }
    if (*src != '\0' || null_part) {
        dest.push_back(src);
    }
}

uint16_t getCheckSum(const uint16_t *data, size_t len, const uint16_t base) {
    uint32_t checkSum = base;
    while (len >= 2) {
        checkSum += *data;
        len -= 2;
        data ++;
    }
    if (len == 1) {
        uint8_t tt = (*(uint8_t*)data);
        checkSum += tt;
    }
    checkSum = (checkSum>>16) + (checkSum&0xffff);
    checkSum = (checkSum>>16) + (checkSum&0xffff);
    return ~((uint16_t)checkSum);
}

string getstr_hex(const uint8_t *buf, size_t size, HexFormat hex_type) {
    char res[size << 2];
    const int byte = 0x0f;
    size_t idx = 0;
    size_t n_char = 0;  // 2 char 为 1 byte
    size_t n_byte = 0;  // 8 byte 为 1 group
    size_t n_group = 0; // 2 group 为 1 line
    int i = 4, comple = 4;
    while (size > 0) {
        if (n_group == 2) {
            res[idx++] = '\n';
            n_group = 0;
        }
        int tmp = (*buf & (byte<<i)) >> i;
        if (tmp < 10)
            res[idx++] = '0' + tmp;
        else
            res[idx++] = 'a' + tmp - 10;
        i = comple - i;
        n_char ++;
        // cout<<int(*buf)<<"  "<<n_char<<" "<<res[idx-1]<<" "<<endl;
        if (hex_type != HEX_COMMON && (n_char % 2 == 0)) {
            res[idx++] = ' ';
            n_byte ++;
            if (n_byte % hex_type == 0) {
                res[idx++] = ' ';
                n_group ++;
            }
        }
        if (i == 4) {
            size --;
            buf ++;
        }
    }
    // cout<<endl;
    res[idx] = '\0';
    return string(hex_type==HEX_COMMON? "0x": "") + res;
}

void print_hex(const uint8_t *buf, size_t size, HexFormat hex_type) {
    printf("%s\n", getstr_hex(buf, size, hex_type).c_str());
}

// int64_t getFileLen(const char *file) {
//     FILE *fp = fopen(file, "rb");
//     int len = fseek(fp, 0, SEEK_END);
//     fclose(fp);
//     return len;
// }
