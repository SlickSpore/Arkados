#ifndef __PACKAGE__  //bit
#define __PACKAGE__
#include "game\game.h"
#undef  __PACKAGE__
#endif

/*This function draws on the screen the ball*/
void draw_Ball(ball_t ball, buffer_t *FRAME){
  draw_Sprite(ball.bpos, &ball.bskin, FRAME->buffer_pointer);
}

/*This function initializes the ball variables if called*/
ball_t init_Ball(ssgSprite_t skin){
  ball_t ball;
  int angles[] = {225,240,270,300,315};

  srand(time(0));
  ball.bskin = skin;

  ball.bpos.y = Y_SIZE - 20 - (ball.bskin.reso_Y);
  ball.bpos.x = (X_SIZE / 2) - (ball.bskin.reso_X / 2);

  ball.angle_d = angles[rand()%5];
  // ball.angle_d = 250;

  return ball;

}

int move_Ball(ball_t *ball){
  double conv = M_PI / 180;

  int x_change = (cos(ball->angle_d * conv) ) * BSPEED;
  int y_change = (sin(ball->angle_d * conv) ) * BSPEED;


  //X check;
  if (ball->bpos.x + x_change <= 80 ){
    ball->bpos.x = 80;
    ball->angle_d = 180 - ball->angle_d;
  }else if(ball->bpos.x + x_change >= X_SIZE - 80 - ball->bskin.reso_X){
    ball->bpos.x = X_SIZE - 80 - ball->bskin.reso_X;
    ball->angle_d = 180 - ball->angle_d;
  }else{ //if enough space
    ball->bpos.x += x_change;
  }

  //Y check
  if (ball->bpos.y + y_change <= 0){
    ball->bpos.y = 0;
    ball->angle_d = 360 - ball->angle_d;
  }else if(ball->bpos.y + y_change >= Y_SIZE - ball->bskin.reso_Y){ //player has lost a ball!!
    ball->bpos.y = Y_SIZE;
    return 0;
  }else{
    ball->bpos.y += y_change;
  }
  return 1;

}
