#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum FileType_t
{
    FileType_None,

    FileType_IpAddresses,
    FileType_Domains,
} FileType;

char* OpenFile(const char* filepath);
