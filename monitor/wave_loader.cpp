#include <stdio.h>

#define SAMPLE_RATE 44100
#define NUM_CHANNELS 1
#define SAMPLE_SIZE (sizeof(short))

#include "wave_loader.hpp"

void readWaveFileIntoMemory(char *filename, wavedata_t *p_sound) {
    assert(p_sound);

    // The PCM data in a wave file starts after the header:
    const int PCM_DATA_OFFSET = 44;

    // Open the wave file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Unable to open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    int size_in_bytes = ftell(file) - PCM_DATA_OFFSET;
    p_sound->num_samples = size_in_bytes / SAMPLE_SIZE;

    // Search to the start of the data in the file
    fseek(file, PCM_DATA_OFFSET, SEEK_SET);

    // Allocate space to hold all PCM data
    p_sound->p_data = malloc(size_in_bytes);
    if (p_sound->p_data == 0) {
        fprintf(stderr, "ERROR: Unable to allocate %d bytes for file %s.\n",
                size_in_bytes, filename);
        exit(EXIT_FAILURE);
    }

    // Read PCM data from wave file into memory
    int samples_read = fread(p_sound->p_data, SAMPLE_SIZE, p_sound->num_samples, file);
    if (samples_read != p_sound->num_samples) {
        fprintf(stderr, "ERROR: Unable to read %d samples from file %s (read %d).\n",
                p_sound->num_samples, filename, samples_read);
        exit(EXIT_FAILURE);
    }
}