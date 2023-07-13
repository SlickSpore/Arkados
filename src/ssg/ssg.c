
/*
	(S)lick (S)pore (G)raphics

		  Written by:
	      
        SlickSpore

		  @2023

  https://slickspore.com/ || https://github.com/slickspore/dos-pong

  Rev 3.0 watcom
*/


#define ENTRY 0
#define VGA_SEGMENT 0xA0000L
#define VGA_256_CLR 0x13
#define VGA_TXT     0x03
#define X_SIZE      320
#define Y_SIZE      200
#define VTRACE      0x03da
#define VTCODE      0x08

#define PIT_CHANNEL_0 0x40       // PIT Channel 0 I/O port
#define PIT_COMMAND 0x43         // PIT Command I/O port
#define PIT_FREQUENCY 1193182    // PIT frequency in Hz


typedef struct {
    int x;
    int y;
}point_t;

enum 
{
  BLACK  =  0,
  BLUE   =  1,
  GREEN  =  2,
  CYAN   =  3,
  RED    =  4,
  MGNTA  =  5,
  BROWN  =  6,
  LGRAY  =  7,
  DGRAY  =  8,
  LBLUE  =  9,
  LGREEN = 10,
  LCYAN  = 11,
  LRED   = 12,
  LMGNTA = 13,
  YELLOW = 14,
  WHITE  = 15
};

typedef unsigned char uint8_t;
typedef uint8_t frame_t;
uint8_t *VGA   = (uint8_t*)VGA_SEGMENT;
volatile int TRIGGER = 0;

typedef struct {  //IMPLEMENT CORRECT DOUBLE BUFFER!
  frame_t *buffer_0;
  frame_t *buffer_1;
  frame_t *buffer_pointer;
  int bsel;
} buffer_t;

/*This is the format for a .ssg header file.*/
typedef struct {
  uint32_t reso_x;
  uint32_t reso_y;
  uint32_t f_size;
} ssgHeader_t;

/*This is the type of a .ssg image.*/
typedef struct {
  uint32_t reso_X;
  uint32_t reso_Y;
  uint8_t  *img_data;
} ssgSprite_t;


/*This function is the PIT interrupt*/
void interrupt do_FRAME_TICK() {
  // Increment the timer tick count
  TRIGGER = 1;
  // Send an EOI (End of Interrupt) signal to the PIC
  outp(0x20, 0x20);
}

/*This Function sets the PIT fps Limit.*/
void set_FPS_LIMIT(int FPS) {
  uint16_t divisor = PIT_FREQUENCY / FPS;

  // Send command to Channel 0 of PIT
  outp(PIT_COMMAND, 0x36);     // 0x36 = Channel 0, Latch count value, Mode 3 (Square wave generator)

  // Set the low byte and high byte of the divisor
  outp(PIT_CHANNEL_0, (uint8_t)(divisor & 0xFF));
  outp(PIT_CHANNEL_0, (uint8_t)(divisor >> 8));
}

/*This Funtion starts the pit.*/
void start_FPS_COUNT(){
  _dos_setvect(0x08, do_FRAME_TICK);

  _asm {
      sti
  }
}

/*This Function waits for the pit interrupt*/
void wait_FRAME_DONE(){
  TRIGGER = 0;
  while(!TRIGGER){_asm{NOP};}
}

/*This function sets the video mode*/
void set_gfxMode(uint8_t mode){
  _asm{
    mov ah, 0x00
    mov al, mode
    int 0x10
  }
}
void set_clrFill(int clr, frame_t *frame_buffer){
  memset(frame_buffer,clr,X_SIZE*Y_SIZE);
}

void write_Buffer(buffer_t *frame_buffer){
  if (frame_buffer->bsel){
    frame_buffer->buffer_pointer = frame_buffer->buffer_0;
    frame_buffer->bsel = 0;
  }
  else{
    frame_buffer->buffer_pointer = frame_buffer->buffer_1;
    frame_buffer->bsel = 1;
  }
  while((inp(VTRACE)&VTCODE)==VTCODE);
  while((inp(VTRACE)&VTCODE)==0x00);
  memcpy(VGA,frame_buffer->buffer_pointer,X_SIZE*Y_SIZE);
  TRIGGER = 0;
  
}

void set_Pixel(int x, int y, uint8_t clr, frame_t *frame_buffer){
  *(frame_buffer + (y*X_SIZE+x)) = clr;
}

void set_Line(int sx, int sy, int lenght, frame_t *sprite,  frame_t *frame_buffer){
  memcpy(frame_buffer + (sy*X_SIZE+sx), sprite,lenght*sizeof(frame_t));
}

void draw_Sprite(point_t p, ssgSprite_t *s, frame_t *frame_buffer){
  int i, j, k = 0;

  for (i = 0; i < s->reso_Y; i++){
    set_Line(p.x,p.y+i,s->reso_X,s->img_data+i*s->reso_X,frame_buffer);
  }

}

void draw_Square(point_t p, point_t p1, uint8_t clr, frame_t *frame_buffer){
  uint8_t i, j;
  int endx, endy;
  if (p1.x >= p.x){
    endx = p1.x - p.x;
    endy = p1.y - p.y;
  }else{
    endx = p.x - p1.x;
    endy = p.y - p1.y;
  }
  for (i = 0; i < endy; i++){
    for (j = 0; j < endx; j++){
      set_Pixel(j+p.x, i+p.y, clr, frame_buffer);
    }
  }

}

buffer_t gen_Frame(){
  buffer_t b;

  b.buffer_0 = malloc(X_SIZE*Y_SIZE);
  b.buffer_1 = malloc(X_SIZE*Y_SIZE);
  b.buffer_pointer = b.buffer_0;
  b.bsel = 0;

  if (!b.buffer_0 ||!b.buffer_1){
    printf("[ERROR!] Failed to Alloc Frame Buffer!");
    exit(-1);
  }
  set_clrFill(BLACK,b.buffer_0);
  set_clrFill(BLACK,b.buffer_1);
  return b;
};
