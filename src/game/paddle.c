
/*This function draws on the screen the player's paddle.*/
void draw_playerPaddle(paddle_t paddle, buffer_t *FRAME){
  draw_Sprite(paddle.ppos,&paddle.pskin,FRAME->buffer_pointer);
}


paddle_t init_Paddle(ssgSprite_t pskin){
  paddle_t PADDLE;
  PADDLE.pskin = pskin;
  PADDLE.ppos.x = ((X_SIZE/4)*2)-(PADDLE.pskin.reso_X/2); 
  PADDLE.ppos.y = Y_SIZE - 20;
  PADDLE.delta = 0;
  return PADDLE;
}


/*This function checks if the player's paddle pos
is in bounds of the field*/
void paddle_inBounds(point_t *p_pos, float delta, ssgSprite_t paddle){
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
void move_Paddle(paddle_t *PADDLE){
  
  float delta = 0;

  if (PADDLE->delta == 0){
    delta = BASEPS;
    PADDLE->delta = delta;
  }else{
    delta = PSPEED;
    if (delta < 6){
      PADDLE->delta += delta;
    }else{
      delta = 0;
      PADDLE->delta += delta;
    }
  }

  if (check_modifier(ALT)){
    paddle_inBounds(&PADDLE->ppos,-PADDLE->delta,PADDLE->pskin);
  }
  else if (check_modifier(CTRL)){
    paddle_inBounds(&PADDLE->ppos,PADDLE->delta,PADDLE->pskin);
  }
  else{PADDLE->delta = 0;}
}

void check_paddleBallHit(ball_t *ball, paddle_t paddle ){
  
  float variation, delta;
  float angle_mul, hitpoint;

  variation = ball->bskin.reso_X / 2;

  hitpoint = (paddle.ppos.x + (paddle.pskin.reso_X / 2)) - (ball->bpos.x + variation);
  angle_mul = hitpoint / paddle.pskin.reso_X;

  delta = 270 + (angle_mul * 120);

  if ( ball->bpos.x + variation < paddle.ppos.x 
    || ball->bpos.x + variation > paddle.ppos.x + paddle.pskin.reso_X){}
  else if (ball->bpos.y >= paddle.ppos.y && ball->bpos.y <= paddle.ppos.y + paddle.pskin.reso_Y){
    ball->angle_d = delta;
    ball->bpos.y = paddle.ppos.y - ball->bskin.reso_Y;
  }
}
