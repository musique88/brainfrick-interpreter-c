#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#define POOL 3000

unsigned int get_file_content(char* path, char** content)
{
  FILE* f = fopen(path, "r");
  fseek(f, 0, SEEK_END);
  int size = ftell(f) + 1;
  *content = malloc(size);
  fseek(f, 0, SEEK_SET);
  fread(*content, 1, size, f);
  fclose(f);
  return size;
}

int main(int argc, char** argv)
{
  assert(argc == 2);
  char* content;
  unsigned int size = get_file_content(argv[1], &content);
  unsigned int prg_ptr = 0;
  unsigned int ptr = 0;
  char data[POOL] = {0};
  unsigned int nested_loop_counter = 0;
  while(prg_ptr <= size) {
    switch(content[prg_ptr++]){
      case '>':
        ptr++;
        break;
      case '<':
        ptr--;
        break;
      case '+':
        data[ptr]++;
        break;
      case '-':
        data[ptr]--;
        break;
      case '.':
        fprintf(stdout, "%c", data[ptr]);
        break;
      case ',':
        fscanf(stdin, "%c", &data[ptr]);
        break;
      case '[':
        if(data[ptr] == 0){
          nested_loop_counter = 0;
          while(1) {
            if(content[prg_ptr++] == '[')
              nested_loop_counter++;
            else if (content[prg_ptr - 1] == ']')
              if(nested_loop_counter-- == 0)
                break;
          }
        }
        break;
      case ']':
        if(data[ptr] != 0){
          prg_ptr -= 2;
          nested_loop_counter = 0;
          while(1) {
            if(content[prg_ptr--] == ']')
              nested_loop_counter++;
            else if (content[prg_ptr + 1] == '[')
              if(nested_loop_counter-- == 0)
                break;
          }
        }
        break;
      default:
        break;
    }
  }
  free(content);
}
