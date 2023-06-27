

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
