#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <conio.h>
#include <dos.h>
#include <sys/stat.h>
#include "ssg\ssg.c"
#include "ssg\sil.c"


void main(){
  char ASSET[] = ".\\assets\\ssg\\btile.ssg";
  char *data;

  data = read_ssg_asset(ASSET);
  printf("%d",data[1]);
}
