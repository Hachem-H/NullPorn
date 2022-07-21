#include "DDoS.h"

int main()
{
    char* ip = DNSLookup("google.com");
    free(ip);
}