#include "utils.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

namespace izxml {

unsigned int Utils::getFileSize(const char *file)
{
    struct stat buf;
    if ((stat(file, &buf)) != 0) {
        return 0;
    }

    return (unsigned int) buf.st_size;
}

char *Utils::loadFileData(const char *file)
{
    char c;
    unsigned int i = 0;
    unsigned int size = 0;
    char* data = NULL;
    size = Utils::getFileSize(file);
    data = (char*) malloc(sizeof(char)*size+1);

    if (data == NULL) {
        return NULL;
    }

    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        return NULL;
    }
    while ( (c = fgetc(fp)) != -1) {
        data[i] = c;
        i++;
    }
    fclose(fp);

    return data;
}

} // namespace izxml
