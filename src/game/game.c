//cool header...

#ifndef ENTRY  //for vs autocomplete
#include "ssg/ssg.c"
#include "ssg/sil.c"
#include "ssg/pki.c"
#endif

#define PSPEED 10;

char ASSETS[50][250] = {
  "./assets/ssg/WTILE.SSG",
  "./assets/ssg/FTILE.SSG",
  "./assets/ssg/PTILE.ssg",
  "./assets/ssg/BBLK.ssg",
  "./assets/ssg/RBLK.ssg",
  "./assets/ssg/GBLK.ssg",
  "./assets/ssg/PBLK.ssg"
};


/*This Function draws in an optimized way the background on the current buffer.*/
void draw_backGround(ssgSprite_t FTILE, ssgSprite_t WTILE, buffer_t *FRAME){
  int i, j;
  point_t FTL1_POS;
  point_t FTL2_POS;
  set_clrFill(BLACK,FRAME->buffer_pointer);

  //fillers
  FTL1_POS.x = 0;
  FTL1_POS.y = 0;
  FTL2_POS.x = X_SIZE - 80;
  FTL2_POS.y = 0;

  for (i = 0; i < 4; i ++){
    for (j = 0; j < 10; j ++){
        draw_Sprite(FTL1_POS,&FTILE,FRAME->buffer_pointer);
        draw_Sprite(FTL2_POS,&FTILE,FRAME->buffer_pointer);
        FTL2_POS.y += 20;
        FTL1_POS.y += 20;
    }
    FTL1_POS.y = 0;
    FTL1_POS.x += 20;
    FTL2_POS.y = 0;
    FTL2_POS.x += 20;
  }
  
  //bounds
  FTL1_POS.x = 80 - WTILE.reso_X;
  FTL1_POS.y = 0;
  FTL2_POS.x = X_SIZE - 80;
  FTL2_POS.y = 0; 

  for (i = 0; i < Y_SIZE / 20; i++){
    draw_Sprite(FTL1_POS,&WTILE,FRAME->buffer_pointer);
    FTL1_POS.y += WTILE.reso_Y;
    draw_Sprite(FTL2_POS,&WTILE,FRAME->buffer_pointer);
    FTL2_POS.y += WTILE.reso_Y;
  }

}

/*This function draws on the screen the player's paddle.*/
void draw_playerPaddle(ssgSprite_t paddle, point_t pos, buffer_t *FRAME){
  draw_Sprite(pos,&paddle,FRAME->buffer_pointer);
}

/*This is the function that checks weather
 the player wants to continue or not.*/
void check_Pause(int *run){
  int keyCode;
  while(!*run){
    keyCode = get_character();
    switch(keyCode){
      case ESC:
        set_gfxMode(VGA_TXT);
        exit(0);        
      case KD_SP:
        keyCode = get_character();
        while(keyCode!=KR_SP){keyCode = get_character();if (keyCode == ESC){*run = 1; break;}}
        *run = 1;
        break;
    }
  }
}

void draw_Blocks(ssgSprite_t blocks[4],buffer_t *FRAME){
  int i,j,k;

  #define BNO 10
  #define PAD 5

  point_t b_p;

  b_p.x = 80;
  b_p.y = 40;
  for (k = 0; k < 2; k++){
    for (j = 0; j < 4; j++){
      for (i = 0; i < BNO; i++){
        draw_Sprite(b_p, &blocks[j], FRAME->buffer_pointer);
        b_p.x += blocks[0].reso_X;
      }
      b_p.y+=blocks[0].reso_Y + 1;
      b_p.x = 80;
    }
  }
}

void load_Blocks(ssgSprite_t *blocks){
  int i;
  for (i = 0; i < 4; i++){
    blocks[i] = read_ssg_asset(ASSETS[3+i]);
  }
}

/*THis function checks for quit interrupt.*/
void check_Quit(){
  if (get_character()==ESC){
    set_gfxMode(VGA_TXT);
    nosound();
    exit(0);
  }
}

void paddle_inBounds(point_t *p_pos, int delta, ssgSprite_t paddle){
  if (p_pos->x+delta>=80&&p_pos->x+delta<=X_SIZE-80-paddle.reso_X){
    p_pos->x += delta;
  }else if (delta < 0){
    p_pos->x = 80;
  }else if (delta > 0)
  {
    p_pos->x = X_SIZE-80-paddle.reso_X;
  }
  
      
  else{;}
}

void move_Paddle(point_t *p_pos, ssgSprite_t paddle){
  
  int delta = 0;

  if (check_modifier(ALT)){
    delta = -PSPEED;
    paddle_inBounds(p_pos,delta,paddle);
  }
  else if (check_modifier(CTRL)){
    delta = PSPEED;
    paddle_inBounds(p_pos,delta,paddle);
  }
  else{;}
}
