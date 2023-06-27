

typedef struct {
  int destroyed;
  point_t pos;
  ssgSprite_t skin;
} block_t;

typedef struct {
  ssgSprite_t bskin;
  int angle_d;
  point_t bpos;
} ball_t;


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

/*This function draws the blocks on the screen*/
void draw_Blocks(block_t *blocks,buffer_t *FRAME){
  int i,j,k;

  for (i = 0; i < BNO*8; ++i){
    if (!blocks[i].destroyed){
      draw_Sprite(blocks[i].pos,&blocks[i].skin,FRAME->buffer_pointer);
    }
  }

}

/*This function makes an array of blocks
and their state*/
block_t *load_Blocks(){
  int i, j, k, b, h = 0; 
  point_t p;

  block_t *blocks = malloc(80 * sizeof(block_t));


  ssgSprite_t skins[4];

  for (k = 0; k < 4; k++){
    skins[k] = read_ssg_asset(ASSETS[3+k]);
  }

  p.x = 80;
  p.y = 40;

  for (k = 0; k < 2; k++){
    for (j = 0; j < 4; j++){
      for (i = 0; i < BNO; i++){
        blocks[h].destroyed = 0;
        memcpy(&blocks[h].skin,&skins[j], sizeof(ssgSprite_t));
        blocks[h].pos.x = p.x;
        blocks[h].pos.y = p.y;
        p.x += blocks[h].skin.reso_X;
        h++; 
      }
      p.y += 8;
      p.x = 80;
    }
  }


  return blocks;
}

/*THis function checks for quit interrupt.*/
void check_Quit(){
  if (get_character()==ESC){
    set_gfxMode(VGA_TXT);
    nosound();
    exit(0);
  }
}

/*This function checks if the player's paddle pos
is in bounds of the field*/
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

/*This function moves the ball if the player has press a key*/
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

/*This function draws on the screen the ball*/
void draw_Ball(ball_t ball, buffer_t *FRAME){
  draw_Sprite(ball.bpos, &ball.bskin, FRAME->buffer_pointer);
}

/*This function initializes the ball variables if called*/
ball_t init_Ball(){
  ball_t ball;

  srand(time(0));
  ball.bskin = read_ssg_asset(ASSETS[7]);

  ball.bpos.y = Y_SIZE - 20 - (ball.bskin.reso_Y);
  ball.bpos.x = (X_SIZE / 2) - (ball.bskin.reso_X / 2);

  ball.angle_d = rand()%36;

  return ball;

}
