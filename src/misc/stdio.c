#include <kbbuf.h>
#include <stdio.h>

FILE *stdin = (FILE *)0x1234;

int printf(const char *format, ...)
{
  return 0;
}


FILE *fopen(const char *path, const char *mode)
{
  return NULL;
}


int fgetc(FILE *stream)
{
  return 0;
}


char *fgets(char *s, int size, FILE *stream)
{
  return NULL;
}


int fputc(int c, FILE *stream)
{
  return 0;
}


int fclose(FILE *fp)
{
  return 0;
}


int fseek(FILE *stream, long offset, int whence)
{
  return 0;
}


long ftell(FILE *stream)
{
  return 0;
}


size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  return 0;
}


int putchar(int c)
{
  putch(c);
  return c;
}


int getchar(void)
{
  unsigned char ascii = 0;
  while(ascii == 0)
  {
    ascii = keyboard_dequeue();
  }
  return ascii;
}

