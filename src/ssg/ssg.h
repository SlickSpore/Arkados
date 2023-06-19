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
void set_gfxMode (uint8_t mode);
void set_bgrClr  (uint8_t clr, uint8_t *frame_buffer);
void write_Buffer(uint8_t *frame_buffer);
void set_Pixel   (int x, int y, uint8_t clr, uint8_t *frame_buffer);
void draw_Sprite (point_t p, int x_dim, int y_dim, uint8_t *sprite, uint8_t *frame_buffer);
void draw_Square(point_t p, point_t p1, uint8_t clr, uint8_t *frame_buffer);
void interrupt do_FRAME_TICK();
void set_FPS_LIMIT(int FPS);
void start_FPS_COUNT();
volatile int TRIGGER = 0;
