#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (!f) {
    perror("Error opening file");
  }

  // Find filesize
  if (fseek(f, 0, SEEK_END) != 0) {
    perror("Error seeking end of file");
    fclose(f);
    return NULL;
  }
  long size = ftell(f);
  if (size < 0) {
    perror("Error with size of file");
    fclose(f);
    return NULL;
  }
  rewind(f);

  // Allocate buffer (+1 for \0)
  char *buffer = malloc(size + 1);
  if (!buffer) {
    perror("Error allocating buffer");
    fclose(f);
    return NULL;
  }

  // Read into buffer
  size_t read_size = fread(buffer, 1, size, f);
  if (read_size != (size_t)size) {
    perror("Error reading into buffer");
    free(buffer);
    fclose(f);
    return NULL;
  }
  buffer[size] = '\0';

  fclose(f);
  return buffer;
}
