#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* Framebuffer sizes */
#define FRAMEBUFFER_WIDTH	80
#define FRAMEBUFFER_HEIGHT	25

/* Framebuffer start address */
extern char *__fb;

/* Present framebuffer writing position */
extern unsigned short __fb_present_pos;

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/** fb_write:
 *  Write a character array to the framebuffer and scroll if necessary.
 *
 *  @param buf	Pointer to the start of the buffer
 *  @param len	Length of the buffer
 */
int fb_write(char *buf, unsigned int len);

#endif
