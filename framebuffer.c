#include "framebuffer.h"

char *__fb = (char *) 0x000B8000;
unsigned short __fb_present_pos = 0x00000000;

void fb_move_cursor(unsigned short pos) {
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT,	((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT,	pos & 0x00FF);
	__fb_present_pos = pos;
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
	__fb[i] = c;
	__fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

int fb_write(char *buf, unsigned int len) {
	
	unsigned int i;
	for(i=0; i<len; i++) {
		
		/* Write character at position i */
		fb_write_cell(2*__fb_present_pos, buf[i], (unsigned char)0, (unsigned char)15);
		fb_move_cursor(__fb_present_pos + 1);
		
		/* If __fb_present_pos goes off the screen, move everything one line up */
		if(__fb_present_pos == FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT) {
			fb_move_cursor((FRAMEBUFFER_HEIGHT-1)*FRAMEBUFFER_WIDTH);
			
			int j;
			for(j=0; j<2*FRAMEBUFFER_WIDTH*(FRAMEBUFFER_HEIGHT-1); j++) { 
				__fb[j] = __fb[j + FRAMEBUFFER_WIDTH*2];
			}
			for(j=j; j<2*FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT; j++) {
				__fb[j] = 0;
			}
		}		
	}
	return len;
}
