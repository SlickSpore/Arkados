
#define __MAIN__

#include "game\game.h"
#define FPS_LIMIT 40  //it is not the actual frame rate fking PIT!

void main(){
  
  /* Variables Init */
  buffer_t FRAME = gen_Frame();
  ssgSprite_t PADDLE = read_ssg_asset(ASSETS[2]);
  ssgSprite_t WTILE = read_ssg_asset(ASSETS[0]);
  ssgSprite_t BACKGROUND = read_ssg_asset(ASSETS[1]);
  block_t *BLOCKS;
  point_t PAD_POS;
  ball_t BALL;
  int run = 1;

  ssgSprite_t bskin = read_ssg_asset(ASSETS[7]);


  /* Game Init */
  BLOCKS = load_Blocks();
  BALL   = init_Ball(bskin);

  PAD_POS.x = ((X_SIZE/4)*2)-(PADDLE.reso_X/2); 
  PAD_POS.y = Y_SIZE - 20;

  /* Set Video Mode (320x200 x 256color x 40fps)*/
  set_gfxMode(VGA_256_CLR);
  set_FPS_LIMIT(FPS_LIMIT);
  start_FPS_COUNT();

  while(run){

    /* 0) ***    Draw and swap Buffers    *** */
    write_Buffer(&FRAME);
    wait_FRAME_DONE();
    
    /* 1) ***    Player Logic             *** */
    move_Paddle(&PAD_POS,PADDLE);
    run = move_Ball(&BALL);
    if (!run){
      run = check_Resume();
      BALL = init_Ball(bskin);
    }

    /* 2) ***    Game Scene Draw          *** */
    draw_backGround(BACKGROUND,WTILE,&FRAME);
    draw_playerPaddle(PADDLE,PAD_POS,&FRAME);
    //draw_Blocks(BLOCKS,&FRAME);
    draw_Ball(BALL, &FRAME);

    /* 3) ***    Control Flow Logic       *** */
    check_Quit();
  }

  set_gfxMode(VGA_TXT);
  printf("Glad You've played ArkaDOS!\nSee ya...:)\n");

}
