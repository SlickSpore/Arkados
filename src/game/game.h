

#ifndef __PACKAGE__
//#include "game\game.c"
#include "game\ball.c"
#include "game\paddle.c"
#include "game\blocks.c"
#include "game\scene.c"

#endif


#ifdef __PACKAGE__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <math.h>
#include "ssg\ssg.c"
#include "ssg\pki.c"
#include "ssg\sil.c"

#define PSPEED 10;
#define BNO 10
#define BSPEED 5;
#define M_PI 3.14592


char ASSETS[50][250] = {
  "./assets/ssg/WTILE.SSG",
  "./assets/ssg/FTILE.SSG",
  "./assets/ssg/PTILE.ssg",
  "./assets/ssg/BBLK.ssg",
  "./assets/ssg/RBLK.ssg",
  "./assets/ssg/GBLK.ssg",
  "./assets/ssg/PBLK.ssg",
  "./assets/ssg/BTILE.ssg"
};

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
#endif
