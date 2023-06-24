#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include "ssg\ssg.c"
#include "ssg\pki.c"
#include "ssg\sil.c"
#include "game\game.c"

#define FPS_LIMIT 60;

void main(){
  
  uint8_t *FRAME = gen_Frame();
  ssgSprite_t PADDLE = read_ssg_asset(ASSETS[2]);
  ssgSprite_t WTILE = read_ssg_asset(ASSETS[0]);
  ssgSprite_t BACKGROUND = read_ssg_asset(ASSETS[1]);
  point_t PAD_POS;

  PAD_POS.x = ((X_SIZE/4)*2)-(PADDLE.reso_X/2); 
  PAD_POS.y = Y_SIZE - 20;

  set_gfxMode(VGA_256_CLR);
  set_FPS_LIMIT(50);
  start_FPS_COUNT();

  while(1){
    write_Buffer(FRAME);
    wait_FRAME_DONE();
    
    move_Paddle(&PAD_POS,PADDLE);
    draw_backGround(BACKGROUND,WTILE,FRAME);
    draw_playerPaddle(PADDLE,PAD_POS,FRAME);

    check_Quit();
  }

  getch();
  set_gfxMode(VGA_TXT);

}
