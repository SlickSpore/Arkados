


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

/*THis function checks for quit interrupt.*/
void check_Quit(){
  if (get_character()==ESC){
    set_gfxMode(VGA_TXT);
    nosound();
    printf("Glad You've played ArkaDOS!\nSee ya...:)\n");
    exit(0);
  }
}
int check_Resume(){

  int keyCode;
  while(1){
    keyCode = get_character();
    switch(keyCode){
      case ESC:
        set_gfxMode(VGA_TXT);
        exit(0);        
      case KD_SP:
        keyCode = get_character();
        while(keyCode!=KR_SP){keyCode = get_character();if (keyCode == ESC){return 0;}}
        return 1;
    }

  }
  return 1;
}
