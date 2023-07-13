
/*This function draws the blocks on the screen*/
void draw_Blocks(block_t *blocks,buffer_t *FRAME){
  int i,j,k;

  for (i = 0; i < BNO*8; ++i){
    if (!blocks[i].destroyed){
      draw_Sprite(blocks[i].pos,&blocks[i].skin[blocks->integrity-1],FRAME->buffer_pointer);
    }
  }

}

skins_t load_blockAssets(){
  ssgSprite_t *b_blk = malloc(4*sizeof(ssgSprite_t));
  ssgSprite_t *r_blk = malloc(3*sizeof(ssgSprite_t));
  ssgSprite_t *g_blk = malloc(2*sizeof(ssgSprite_t));
  ssgSprite_t p_blk;
  skins_t skins;
  int i;

  for (i = 8; i < 8 + 4; i++){
    b_blk[i-8] = read_ssg_asset(ASSETS[i]);
  }
  for (i = 12; i < 12 + 3; i++ ){
    r_blk[i-12] = read_ssg_asset(ASSETS[i]);
  }
  for (i = 15; i < 15 + 2; i++){
    g_blk[i-15] = read_ssg_asset(ASSETS[i]); 
  }
  p_blk = read_ssg_asset(ASSETS[i]);


  skins.blk = b_blk;
  skins.rlk = r_blk;
  skins.glk = g_blk;
  skins.plk = &p_blk;


  return skins;
}


/*This function makes an array of blocks
and their state*/
/*
block_t *old_load_Blocks(ssgSprite_t skins[4]){
  int i, j, k, b, h = 0; 
  point_t p;

  block_t *blocks = malloc(80 * sizeof(block_t));

  p.x = 80;
  p.y = 20;

  for (k = 0; k < 2; k++){
    for (j = 0; j < 4; j++){
      for (i = 0; i < BNO; i++){
        blocks[h].destroyed = 0;
        memcpy(&blocks[h].skin,&skins[j], sizeof(ssgSprite_t));
        blocks[h].integrity = 3 - j;
        blocks[h].pos.x = p.x;
        blocks[h].pos.y = p.y;
        p.x += r;
        h++; 
      }
      p.y += 7;
      p.x = 80;
    }
  }


  return blocks;
*/

block_t *load_Blocks(skins_t skins){
  int i, k, j, h, r;
  point_t p;
  block_t *blocks = malloc(80*sizeof(block_t));
  
  p.x = 80;
  p.y = 20;

  r = skins.blk[0].reso_X;

  for (j = 0; j < 2; j++){
    for (i = 0; i < 10; i++){
      blocks[h].skin = skins.blk;
      blocks[h].integrity = 4;
      blocks[h].destroyed = 0;
      blocks[h].pos.x = p.x;
      blocks[h].pos.y = p.y;
      p.x += r;
      h++; 
    }
    p.x = 80;
    p.y += 7;
    for (i = 0; i < 10; i++){
      blocks[h].skin = skins.rlk;
      blocks[h].integrity = 3;
      blocks[h].destroyed = 0;
      blocks[h].pos.x = p.x;
      blocks[h].pos.y = p.y;
      p.x += r;
      h++; 
    }
    p.x = 80;
    p.y += 7;
    for (i = 0; i < 10; i++){
      blocks[h].skin = skins.glk;
      blocks[h].integrity = 2;
      blocks[h].destroyed = 0;
      blocks[h].pos.x = p.x;
      blocks[h].pos.y = p.y;
      p.x += r;
      h++; 
    }
    p.x = 80;
    p.y += 7;
    for (i = 0; i < 10; i++){
      blocks[h].skin = skins.plk;
      blocks[h].integrity = 1;
      blocks[h].destroyed = 0;
      blocks[h].pos.x = p.x;
      blocks[h].pos.y = p.y;
      p.x += r;
      h++; 
    }
    p.x = 80;
    p.y += 7;
  }

  return blocks;
}

void check_blocksBallHit(ball_t *ball, block_t *blocks ){ //ssgSprite_t *skin_grades){
  int i,rx = blocks[0].skin[0].reso_X,ry = blocks[0].skin[0].reso_Y;
  block_t block;
  point_t bp = ball->bpos;

  float hitpoint, angle, delta;

  for (i = 0; i < 80; i++){
    block = blocks[i];
    if (block.destroyed){
    }
    else if (bp.x < block.pos.x || bp.x > block.pos.x + rx ){
      ;;
    }else if (bp.y <= block.pos.y + ry && bp.y >= block.pos.y){
      if (!blocks[i].integrity){
        blocks[i].destroyed = 1;
      }else{
        blocks[i].integrity --;  
      }
      ball->angle_d = 360 - ball->angle_d;
    }
  }
}
