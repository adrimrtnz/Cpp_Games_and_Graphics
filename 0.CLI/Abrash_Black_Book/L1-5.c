#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>

#define BUFFER_SIZE 0x8000      //32Kb data buffer

int main(int argc, char const *argv[])
{
    int handle;
    unsigned int checksum;
    unsigned char *wordking_buffer, *working_ptr;
    int working_length, length_count;

    if ( argc != 2) {
        printf("Usage: checksum filename\n");
        return 1;
    }

    if ( (handle = open(argv[1], O_RDONLY | O_BINARY)) == -1) {
        printf("Cant't open file %s\n", argv[1]);
        return 1;
    }

    while ( (wordking_buffer = malloc(BUFFER_SIZE)) == NULL ) {
        printf("Can't get enough memory\n");
        return 1;
    }

    checksum = 0;

    do {
        if ( (working_length = read(handle, wordking_buffer,
        BUFFER_SIZE)) == -1 ) {
            printf("Error reading file %s\n", argv[1]);
            return 1;
        }
        
        working_ptr = wordking_buffer;
        length_count = working_length;

        while ( length_count-- ) {
            checksum += (unsigned int) *working_ptr++;
        }

    } while (working_length);

    printf("The checksum is: %u\n", checksum);

    return 0;
}
