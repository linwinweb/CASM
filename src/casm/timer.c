#include <system.h>
int timer_ticks = 0;
int sys_seconds = 0;
int sys_minutes = 0;
int sys_hours = 0;
char debug[] = "test";
long int waittime =0;
void timer_handler(struct regs *r)
{
    timer_ticks++;

    if (timer_ticks % 18 == 0)
    {
      if(sys_seconds == 60)
      {
          sys_minutes++;
          sys_seconds = 0;
      }
      if(sys_minutes == 60)
      {
         sys_hours++;
         sys_minutes = 0;
      }
      sys_seconds++;
    }
}

int system_uptime_s()
{
    return sys_seconds;
}

int system_uptime_m()
{
    return sys_minutes;
}

int system_uptime_h()
{
    return sys_hours;
}

void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks)
    {
        strlen(debug);
    }
    ;
}

void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
