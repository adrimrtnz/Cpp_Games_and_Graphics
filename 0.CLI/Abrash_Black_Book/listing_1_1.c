#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int handle;
    unsigned char byte;
    unsigned int checksum;
    int read_length;

    if (argc != 2) {
        printf("Usage: checksum filename\n");
        exit(1);
    }

    if ( (handle = open(argv[1], O_RDONLY | O_BINARY)) == -1) {
        printf("Can't open file: %s\n", argv[1]);
        exit(1);
    }

    checksum = 0;

    while ( (read_length = read(handle, &byte, sizeof(byte))) > 0  ) {
        checksum += (unsigned int) byte;
    }

    if (read_length == -1) {
        printf("Error reading file %s\n", argv[1]);
        exit(1);
    }

    printf("The checksum is: %u\n", checksum);
    exit(0);
}
