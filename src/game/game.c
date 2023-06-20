//cool header...

#ifndef ENTRY  //for vs autocomplete
#include "ssg/ssg.c"
#include "ssg/sil.c"
#endif

char ASSETS[50][250] = {
  "./assets/ssg/WTILE.SSG",
  "./assets/ssg/FTILE.SSG"
};

void draw_backGround(uint8_t *FRAME){
  int i, j;
  ssgSprite_t WTILE = read_ssg_asset(ASSETS[0]);
  ssgSprite_t FTILE = read_ssg_asset(ASSETS[1]);
  point_t FTL1_POS;
  point_t WTL1_POS;

  //fillers
  FTL1_POS.x = 0;
  FTL1_POS.y = 0;

  for (i = 0; i < 4; i ++){
    for (j = 0; j < 10; j ++){
        draw_Sprite(FTL1_POS,FTILE,FRAME);
        FTL1_POS.y += 20;
    }
    FTL1_POS.y = 0;
    FTL1_POS.x += 20;
  }

  FTL1_POS.x = X_SIZE - 80;
  FTL1_POS.y = 0;


  for (i = 0; i < 4; i ++){
    for (j = 0; j < 10; j ++){
        draw_Sprite(FTL1_POS,FTILE,FRAME);
        FTL1_POS.y += 20;
    }
    FTL1_POS.y = 0;
    FTL1_POS.x += 20;
  }


  //bounds
  WTL1_POS.x = 80 - WTILE.reso_X;
  WTL1_POS.y = 0;

  for (i = 0; i < Y_SIZE / 20; i++){
    draw_Sprite(WTL1_POS,WTILE,FRAME);
    WTL1_POS.y += WTILE.reso_Y;
  }

  WTL1_POS.x = X_SIZE - 80;
  WTL1_POS.y = 0; 

  for (i = 0; i < Y_SIZE / 20; i++){
    draw_Sprite(WTL1_POS,WTILE,FRAME);
    WTL1_POS.y += WTILE.reso_Y;
  }

}
