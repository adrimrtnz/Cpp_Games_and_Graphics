#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

main(int argc, char *argv[]) {
    int handle;
    unsigned char byte;
    unsigned int checksum;
    int read_length;

    if ( argc != 2) {
        printf("Usage: checksum filename\n");
        exit(1);
    }

    if ( (handle = open(argv[1], O_RDONLY | O_BINARY)) == -1) {
        printf("Cant't open file %s\n", argv[1]);
        exit(1);
    }

    if ( !ChecksumFile(handle, &checksum) ) {
        printf("Error reading file %s\n", argv[1]);
        exit(1);
    }

    printf("The checksum is: %u\n", checksum);
    exit(0);
}