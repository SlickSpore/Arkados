typedef struct {
  uint32_t reso_x;
  uint32_t reso_y;
  uint32_t f_size;
} ssgHeader_t;

uint8_t *read_ssg_asset(char path[512]){
  ssgHeader_t header;
  FILE *fp;
  uint8_t *data;
  int fd,f_size,header_end = sizeof(ssgHeader_t);

  memset(&header,0,sizeof(ssgHeader_t));

  fp = fopen(path,"rb");
  if (!fp){
    printf("[ERROR!] File '%s%s' not found!\n",path);
    return NULL;
  }
  
  fread(&header,sizeof(ssgHeader_t),1,fp);
  printf("[Info] Image: X SIZE: %d; Y SIZE: %d; FILE SIZE: %d\n",header.reso_x,header.reso_y,header.f_size);
  
  data = malloc(header.f_size);
  fseek(fp,header_end,SEEK_SET);
  fread(data,sizeof(uint8_t),header.f_size-header_end,fp);
  
  return data;

}