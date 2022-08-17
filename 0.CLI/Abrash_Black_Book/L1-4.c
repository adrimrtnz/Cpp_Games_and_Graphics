#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *check_file;
    int byte;
    unsigned int checksum;

    if ( argc != 2) {
        printf("Usage: checksum filename\n");
        return 1;
    }

    if ( (check_file = fopen(argv[1], "rb")) == NULL) {
        printf("Cant't open file %s\n", argv[1]);
        return 1;
    }

    checksum = 0;

    while ( (byte = getc(check_file)) != EOF ) {
        checksum += (unsigned int) byte;
    }

    printf("The checksum is: %u\n", checksum);

    return 0;
}
