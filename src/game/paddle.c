
/*This function draws on the screen the player's paddle.*/
void draw_playerPaddle(ssgSprite_t paddle, point_t pos, buffer_t *FRAME){
  draw_Sprite(pos,&paddle,FRAME->buffer_pointer);
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
