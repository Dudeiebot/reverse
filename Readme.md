## REVERSE


### USAGE
* These program calculates the block size, which is the number of bytes per sample in the audio data. This is determined by the number of channels and bits per sample in the WAV file.

* The program calculates the number of samples in the audio data by dividing the size of the audio data chunk by the block size.

* The program allocates memory for a buffer to hold the audio data.

* The program reads the audio data from the input file into the buffer.

* The program iterates over each sample in the audio data.

* For each sample, the program swaps the positions of the two bytes representing the audio data. For example, if the original audio data was represented by the bytes 0x12 and 0x34, the program would swap these bytes to create the reversed audio data represented by the bytes 0x34 and 0x12.

* The program writes the reversed audio data to the output file.

The program frees the memory allocated for the buffer.

Overall, the program reverses the audio data by iterating over each sample, swapping the bytes representing the audio data, and then writing the reversed audio data to the output file.
