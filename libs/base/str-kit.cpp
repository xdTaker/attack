#include "str-kit.h"

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
