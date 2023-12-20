#include <system.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BIT(x) (1ULL << (x))
void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void iprint(int n)
  { 
    if( n > 9 )
      { int a = n / 10;

        n -= 10 * a;
        iprint(a);
      }
    putchar('0'+n);
  }

void *memset(void *dest, int val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = (char)val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

int a[10];
void brandString(int eaxValues)
{
    if (eaxValues == 1) {
    __asm__("mov $0x80000002 , %eax\n\t");
    }
    else if (eaxValues == 2) {
        __asm__("mov $0x80000003 , %eax\n\t");
    }
    else if (eaxValues == 3) {
        __asm__("mov $0x80000004 , %eax\n\t");
    }
    __asm__("cpuid\n\t");
    __asm__("mov %%eax, %0\n\t":"=r" (a[0]));
    __asm__("mov %%ebx, %0\n\t":"=r" (a[1]));
    __asm__("mov %%ecx, %0\n\t":"=r" (a[2]));
    __asm__("mov %%edx, %0\n\t":"=r" (a[3]));
    puts(a);
}

void getCpuID()
{
    __asm__("xor %eax , %eax\n\t");
    __asm__("xor %ebx , %ebx\n\t");
    __asm__("xor %ecx , %ecx\n\t");
    __asm__("xor %edx , %edx\n\t");
    puts("Processor: ");
    brandString(1);
    brandString(2);
    brandString(3);
    putchar('\n');
}

void main()
{
    char cmd[30];
    int i = 0;
    const unsigned int p1[] = {10, 9, 9, 32, 176, 176, 176, 176, 176, 176, 32, 32, 176, 176, 176, 176, 176, 32, 32, 176, 176, 176, 176, 176, 176, 176, 32, 176, 176, 176, 32, 32, 32, 32, 176, 176, 176, 10, 9, 9, 177, 177, 32, 32, 32, 32, 32, 32, 177, 177, 32, 32, 32, 177, 177, 32, 177, 177, 32, 32, 32, 32, 32, 32, 177, 177, 177, 177, 32, 32, 177, 177, 177, 177, 10, 9, 9, 177, 177, 32, 32, 32, 32, 32, 32, 177, 177, 177, 177, 177, 177, 177, 32, 177, 177, 177, 177, 177, 177, 177, 32, 177, 177, 32, 177, 177, 177, 177, 32, 177, 177, 10, 9, 9, 178, 178, 32, 32, 32, 32, 32, 32, 178, 178, 32, 32, 32, 178, 178, 32, 32, 32, 32, 32, 32, 178, 178, 32, 178, 178, 32, 32, 178, 178, 32, 32, 178, 178, 10, 9, 9, 32, 219, 219, 219, 219, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 32, 32, 32, 32, 32, 32, 219, 219, 10};
    void resetbuffer()
    {
        for(int j=0;j<30;j++)
        {
            cmd[j] = 0;
        }
        i=0;
        puts("\nREADY.\n");
    }
    char msg[] = "\t\t\tVersion 1.1 Beta\n\n";
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();
    timer_install();
    keyboard_install();
    __asm__ __volatile__ ("sti");
    for(int i = 0; i<187; i++)
    {
        putch(p1[i]);
    }
    puts(msg);
    getCpuID();
    resetbuffer();
    while(1==1){
        char out1=getchar();
        putchar(out1);
        if(out1=='?')
        {
            while(1==1)
            {
                i++;
                cmd[i] = getchar();
                putchar(cmd[i]);
                if(cmd[i]==127||cmd[i]==8)
                {
                	if(i==0)
                	{
                		break;
                	}
                	else
                	{
                		i--;
                		cmd[i]=' ';
                		i--;
                	}
                }
                if(cmd[i]=='\n')
                {
                	if(cmd[1]=='a'&&cmd[2]=='b'&&cmd[3]=='o'&&cmd[4]=='u'&&cmd[5]=='t')
                	{
                	    puts("\nC/ASM command line interpreter version 1.2\nThis software is currently in testing and is unstable, user is responsible for  all damages for continued use of CASM.\n");
              	            resetbuffer();
              	            break;
             	        }
             	        
             	        if(cmd[1]=='h'&&cmd[2]=='e'&&cmd[3]=='l'&&cmd[4]=='p')
           	        {
           	            puts("\nCommand | Description\n?help - Displays commands\n?basic - Enters BASIC mode\n?uptime - Displays system uptime in seconds\n?about - Displays version and information about C/ASM\n?clear - Clears terminal screen of text\n?color - Changes color of text\nPress ESC to reset system.\n");
             	            resetbuffer();
           	            break;
          	        }
          	        
             	        if(cmd[1]=='d'&&cmd[2]=='e'&&cmd[3]=='m'&&cmd[4]=='o')
           	        {
           	            for(int i = 0; i<176; i++)
    				{
        				putch(p1[i]);
    				}
             	            resetbuffer();
           	            break;
          	        }
          	        
          	        if(cmd[1]=='b'&&cmd[2]=='a'&&cmd[3]=='s'&&cmd[4]=='i'&&cmd[5]=='c')
          	        {
          	            puts("\nEntering BASIC mode...\n");
          	            application_start();
          	            break;
         	        }
         	        
        	        if(cmd[1]=='c'&&cmd[2]=='l'&&cmd[3]=='e'&&cmd[4]=='a'&&cmd[5]=='r')
        	        {
      	              		cls();
      	              		resetbuffer();
     	              		break;
        	        }
        	        
        	        if(cmd[1]=='c'&&cmd[2]=='o'&&cmd[3]=='l'&&cmd[4]=='o'&&cmd[5]=='r')
        	        {
        	        	int a1=0;
        	        	puts("\nColor code | Color\nA - Blue\nB - Green\nC - Cyan\nD - Red\nE - Magenta\nF - Brown\nG - Light gray\nH - Dark grey\nI - Light blue\nJ - Light Green\nK - Light Cyan\nL - Light Red\nM - Light magenta\nN - Yellow \nO - White\nP - Black");
      	              		puts("\nInsert color for text: ");
      	              		a1=getchar();
      	              		resetbuffer();
      	              		settextcolor(a1,0);
      	              		cls();
     	              		break;
        	        }
        	        
                	if(cmd[1]=='u'&&cmd[2]=='p'&&cmd[3]=='t'&&cmd[4]=='i'&&cmd[5]=='m'&&cmd[6]=='e')
                	{
                    		puts("\nSystem uptime: ");
                    		if(system_uptime_h()<10)
                    		{
                    		    putchar('0');
                    		}
                    		iprint(system_uptime_h());
                    		putchar(':');
                    		if(system_uptime_m()<10)
                    		{
                    		    putchar('0');
                    		}
                    		iprint(system_uptime_m());
                    		putchar(':');
                    		if(system_uptime_s()<10)
                    		{
                    		    putchar('0');
                    		}
                    		iprint(system_uptime_s());
                    		resetbuffer();
                    		break;
                	}
                	
                	if(i>=29)
                	{
                    		puts("\nCommand too long! buffer reset.\n");
		    		resetbuffer();
		    		break;
                	}
                	
                	else
                	{
                		puts("\nUnrecognized command: ");
                		puts(cmd);
                		resetbuffer();
		    		break;
                	}
            	}
        }
     }
   }
    for (;;);
}
