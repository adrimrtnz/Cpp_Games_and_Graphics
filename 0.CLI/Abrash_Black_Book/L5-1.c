#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>

#define BLOCK_SIZE 0x4000       /* process the file in 16KB blocks */

int SearchForString(unsigned char *buffer, int search_length,
                    unsigned char *search_string, int search_string_length)
{
    unsigned char *potential_match;

    while (search_length) {

        // See if the first character of search_string can be found
        if ( (potential_match = memchr(buffer, *search_string, search_length)) == NULL ) {
            // No matches in this buffer
            break;
        }

        // The first char matches, see if the rest of the string also matches
        if ( search_length == 1 ) {
            return 1;
        }
        else {
            if ( !memcmp(potential_match + 1, search_string + 1, search_string_length - 1) ) {
                return 1;
            }
        }

        search_length -= potential_match - buffer + 1;
        buffer = potential_match + 1;
    }

    // No match found
    return 0;
}


int main(int argc, char const *argv[])
{
    int done;
    int handle;
    int working_length;
    int search_string_length;
    int block_search_length;
    int found;
    int next_load_count;

    unsigned char *working_block;
    unsigned char *search_string;
    unsigned char *next_load_ptr;

    if ( argc != 3) {
        printf("Usage: search <filename> <search-string>\n");
        return -1;
    }

    if ( (handle = open(argv[1], O_RDONLY | O_BINARY)) == -1) {
        printf("Can't open file: %s\n", argv[1]);
        return -1;
    }

    if ( (working_block = malloc(BLOCK_SIZE)) == NULL ) {
        printf("Can't get enough memory\n");
        return -1;
    }

    /** 
     * @brief Load the first block at the start of the buffer, and try to fill
     * the entire buffer
    */
   next_load_ptr = working_block;
   next_load_count = BLOCK_SIZE;
   done = 0;
   found = 0;

   // Search the file in BLOCK_SIZE chunks
   do {

    if ( (working_length = read(handle, next_load_ptr, next_load_count)) == -1 ) {
        printf("Error reading file %s\n", argv[1]);
        return -1;
    }

    // If we didn't read all the requested bytes, we're done
    if ( working_length != next_load_count ) {
        done = 1;
    }

    // Account for any bytes we copied from the end of the last block in
    // the total length of this block
    working_length += next_load_ptr - working_block;

    if ( (block_search_length = working_length - search_string_length + 1 ) <= 0) {
        done = 1;
    }
    else {
        if ( SearchForString(working_block, block_search_length, search_string, search_string_length) ) {
            found = 1;
            done = 1;
        }
        else {
            if ( search_string_length > 1 ) {
                memcpy(working_block, 
                working_block + BLOCK_SIZE - search_string_length + 1,
                search_string_length - 1);
            }

            next_load_ptr = working_block + search_string_length - 1;
            next_load_count = BLOCK_SIZE - search_string_length + 1;
        }
        
    }

   } while ( !done );

    if ( found ) {
        printf("String found\n");
    } else {
        printf("String not found\n");
    }

    return found;
}
