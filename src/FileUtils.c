#include "FileUtils.h"

char* OpenFile(const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (!file)
        fprintf(stderr, "[ERR]: Could not open file @ %s.\n", filepath);

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char* buffer = (char*) malloc(size+1);
    fread(buffer, size, 1, file);
    buffer[size] = 0;

    return buffer;
}
