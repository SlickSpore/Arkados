
#define __MAIN__

#include "game\game.h"
#define FPS_LIMIT 40  //it is not the actual frame rate fking PIT!

void main(){
  
  /* Variables Init */
  buffer_t FRAME = gen_Frame();
  block_t *BLOCKS;
  point_t PAD_POS;
  ball_t BALL;
  paddle_t PADDLE;
  point_t sp;
  ssgSprite_t WTILE = read_ssg_asset(ASSETS[0]);
  ssgSprite_t BACKGROUND = read_ssg_asset(ASSETS[1]);
  ssgSprite_t SPLASH = read_ssg_asset(ASSETS[8]);
  skins_t STAGES = load_blockAssets();

  int lives = 5;
  int run = 1;
  int k;

  ssgSprite_t bskin = read_ssg_asset(ASSETS[7]);
  ssgSprite_t pskin = read_ssg_asset(ASSETS[2]);

  /* Game Init */
  BLOCKS = load_Blocks(STAGES);
  BALL   = init_Ball(bskin);
  PADDLE = init_Paddle(pskin);

  sp.x = 0;
  sp.y = 0;

  /* Set Video Mode (320x200 x 256color x 40fps)*/
  set_gfxMode(VGA_256_CLR);
  set_FPS_LIMIT(FPS_LIMIT);
  start_FPS_COUNT();

  draw_Sprite(sp,&SPLASH,FRAME.buffer_1);
  write_Buffer(&FRAME);
  run = check_Resume();
  
  while(run){

    /* 0) ***    Draw and swap Buffers    *** */
    write_Buffer(&FRAME);
    wait_FRAME_DONE();
    
    /* 1) ***    Player Logic             *** */
    move_Paddle(&PADDLE);
    check_paddleBallHit(&BALL, PADDLE);
    check_blocksBallHit(&BALL, BLOCKS);
    run = move_Ball(&BALL);

    /* 2) ***    Game Scene Draw          *** */
    draw_backGround(BACKGROUND,WTILE,&FRAME);
    draw_playerPaddle(PADDLE,&FRAME);
    draw_Blocks(BLOCKS,&FRAME);
    draw_Ball(BALL, &FRAME);

    /* 3) ***    Control Flow Logic       *** */
    if (!run){
      write_Buffer(&FRAME);
      if (lives > 0){
        run   = check_Resume();
        BALL  = init_Ball(bskin);
        PADDLE= init_Paddle(pskin);
        lives --;
      }else{
        run    = check_Resume();
        lives  = 5;
        BALL   = init_Ball(bskin);
        PADDLE = init_Paddle(pskin);
        //BLOCKS = load_Blocks(skins);
      }
    }
    run = check_Quit();
  }

  set_gfxMode(VGA_TXT);
  printf("Hey, I'm Glad You've played ArkaDOS!\nHope to see you Again!:)\n");

}
