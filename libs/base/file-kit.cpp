#include "file-kit.h"

int64_t getFileLen(const char *file) {
    FILE *fp = fopen(file, "rb");
    int len = fseek(fp, 0, SEEK_END);
    fclose(fp);
    return len;
}
