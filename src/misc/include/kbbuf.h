#ifndef __KBBUF_H__
#define __KBBUF_H__
#define KEYBUFSIZ 64

typedef struct 
{
  unsigned char buf[KEYBUFSIZ];
  unsigned char *head;
  unsigned char *tail;
} keyboard_buffer_t;
unsigned char keyboard_dequeue(void);

void kb_buf_scan(unsigned char scancode);
void kb_buf_init();
void keyboard_enqueue(unsigned char ascii);
void move_csr_offset(int x, int y);


#endif

