#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc < 3) {
        printf("Usage: %s <input wav file> <output wav file>\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("Failed to open %s for reading\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, file);

    //check_format usage
    if (check_format(header)) {
        fclose(file);
        return 1;
    }
    int block_size = get_block_size(header);
    int num_samples = header.subchunk2Size / block_size;
    int16_t *buffer = malloc(num_samples * block_size);
    fread(buffer, block_size, num_samples, file);

    fclose(file);

    
    // Open output file for writing
    FILE *outfile = fopen(argv[2], "wb");
    if (!outfile) {
    printf("Failed to open %s for writing\n", argv[2]);
    return 1;
    }
    fwrite(&header, sizeof(WAVHEADER), 1, outfile);   // Write header to file
    
    // Use get_block_size to calculate size of block in 

    // Write reversed audio to file
       for (int i = 0; i < num_samples; i++) {
        uint8_t temp = buffer[i * block_size];
        buffer[i * block_size] = buffer[i * block_size + 1];
        buffer[i * block_size + 1] = temp;
    }

    fwrite(buffer, block_size, num_samples, outfile);;

    fclose(outfile);
    free(buffer);


    return 0;
}


int check_format(WAVHEADER header)
{
     if (header.format[0] == 'W' || header.format[1] == 'A' || header.format[2] == 'V' || header.format[3] == 'E') {
        return 0;
    } else {
        printf("Invalid WAV format\n");
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    int block_size = header.numChannels * header.bitsPerSample / 8; //these calculates it in byte per second cause our header file is in bit per second
    return block_size;
}