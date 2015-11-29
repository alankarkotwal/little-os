#include "framebuffer.h"

#define FB_GREEN     2
#define FB_DARK_GREY 8

char myname[] = "";

/** kmain:
 *  The main function the kernel calls before it goes into an infinite loop
 */
 void kmain() {
 	fb_write(myname, 7);
 }
