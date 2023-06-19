#include <dos.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <memory.h>
#include "ssg\ssg.c"

unsigned int buffer[500];

void readfile() {
    FILE *f = fopen("..\\assets\\WALLTILE1.bmp", "rb");
    fread(&buffer, 1, 500, f);
    fclose(f);
}


void main(){
  int i, c = 0, l = 0;
  readfile();
  for (i = 0; i < 100; i++){
    if (c == 16){ printf("\n");c=0;}
    if (buffer[i]==158){
        printf("i");
    }
    printf("%i\t ", buffer[i]);
    c++;

  }
}
