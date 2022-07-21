#include "FileUtils.h"
#include "DDoS.h"

int main()
{
    char* file = OpenFile("IpAddresses.txt");
    uint32_t amountOfLines = 0;
    for (uint32_t i = 0; i < strlen(file); i++)
        if (file[i] == '\n')
            amountOfLines++;
    printf("%d\n", amountOfLines);
    free(file);
}
