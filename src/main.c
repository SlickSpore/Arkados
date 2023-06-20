#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include "ssg\ssg.c"
#include "ssg\sil.c"
#include "game\game.c"

void main(){

  uint8_t *FRAME = gen_Frame();
  //background init...
  draw_backGround(FRAME);

  set_gfxMode(VGA_256_CLR);

  write_Buffer(FRAME);

  getch();

  set_gfxMode(VGA_TXT);

}
