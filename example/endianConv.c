#include <stdio.h>
#include <arpa/inet.h>

int main() {
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;
    
    net_port = htons(host_port);
    net_addr = htonl(host_addr);
    
    printf("Host ordered port : %#x\n", host_port); // %#x
    printf("Network ordered port : %#x\n", net_port);
    printf("Host ordered address : %#lx\n", host_addr); // %#lx
    printf("Network ordered address : %#lx\n", net_addr);
    
    return 0;
}
