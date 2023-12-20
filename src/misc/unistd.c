#include <system.h>
#include <tinybasic.h>
void reboot(void)
{
  unsigned char good = 0x02;
  while (good & 0x02)
  {
    good = inportb(0x64);
  }
  outportb(0x64, 0xFE);
 loop:
  asm volatile ("hlt");
  goto loop;
}


void shutdown(void)
{
  reboot();
}


void application_start(void)
{
  char* IL = (char *)0;
  puts("\nREADY.");

  StartTinyBasic(IL);

  for(;;);
}

