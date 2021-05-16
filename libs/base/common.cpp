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

string getstr_hex(const uint8_t *buf, int size) {
    char res[size + 1];
    const int byte = 0x0f;
    int cnt = 0;
    int i = 4, comple = 4;
    while (size > 0) {
        int tmp = (*buf & (byte<<i)) >> i;
        cout<<tmp<<" ";
        if (tmp < 10)
            res[cnt] = '0' + tmp;
        else
            res[cnt] = 'a' + tmp - 10;
        i = comple - i;
        cnt ++;
        if (i == 4) {
            size --;
            buf ++;
        }
    }cout<<endl;
    res[cnt] = '\0';
    return string("0x") + res;
}

void print_hex(const uint8_t *buf, int size) {
    printf("%s\n", getstr_hex(buf, size).c_str());
}

// int64_t getFileLen(const char *file) {
//     FILE *fp = fopen(file, "rb");
//     int len = fseek(fp, 0, SEEK_END);
//     fclose(fp);
//     return len;
// }

void test_print() {
    cout<<"print print"<<endl;
}