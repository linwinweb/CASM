#include <system.h>
unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void scroll(void)
{
    unsigned blank, temp;

    blank = 0x20 | (attrib << 8);

    if(csr_y >= 25)
    {
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

void move_csr(void)
{
    unsigned temp;

    temp = csr_y * 80 + csr_x;

    /* This sends a command to indicies 14 and 15 in the CRT Control Register of the VGA controller. These are the high and low bytes of the index that show where the hardware cursor is to be 'blinking'.*/
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void cls()
{
    unsigned blank;
    int i;

    blank = 0x20 | (attrib << 8);

    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(int c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    if(c == 8)
    {
        if(csr_x != 0) csr_x--;
    }
    
    else if(c == 9)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    
    else if(c == 13)
    {
        csr_x = 0;
    }

    else if(c == 10)
    {
        csr_x = 0;
        csr_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= 1)
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    scroll();
    move_csr();
}

int puts(char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
    return i;
}

//Sets the forecolor and backcolor that we will use
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(void)
{
    /* Light-blue, color 0x03, to use as foreground */
    outportb(0x03c8, 0x0A);
    outportb(0x03c9, 0x72 >> 2);
    outportb(0x03c9, 0x9f >> 2);
    outportb(0x03c9, 0xcf >> 2);

    /* Dark-blue, color 0x01, to use as background */
    outportb(0x03c8, 0x0F);
    outportb(0x03c9, 0x34 >> 2);
    outportb(0x03c9, 0x65 >> 2);
    outportb(0x03c9, 0xA4 >> 2);

    // settextcolor(0x01, 0x01);
    textmemptr = (unsigned short *)0xB8000;
    cls();
}

