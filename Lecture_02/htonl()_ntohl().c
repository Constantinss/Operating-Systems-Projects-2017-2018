int main() 
{
    int a = 0x12345678; 

    printf("Original - 0x%x\n", (a)); 
    printf("Network - 0x%x\n", htonl(a)); 
    printf("Host - 0x%x\n", ntohl(a)); 

    return 0;
}

///////////////////////////////////////////////

Output:

Original - 0x12345678
Network - 0x78563412
Host - 0x78563412
