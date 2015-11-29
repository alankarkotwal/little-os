#ifndef __INCLUDE_SERIAL_H
#define __INCLUDE_SERIAL_H

#include "io.h" /* io.h is implement in the section "Moving the cursor" */

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* Define the debug COM port as COM1. This is used for serial debugging. */
#define DEBUG_SERIAL SERIAL_COM1_BASE

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB         0x80

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure(unsigned short com, unsigned short divisor);

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */

int serial_is_transmit_fifo_empty(unsigned short com);

/** serial_recieved:
 *  Checks if we have received anything on the serial port
 *
 *  @param  com The COM port
 */
int serial_received(unsigned short com);

/** serial_write:
 *  Write the first len characters from the contents of buf to com
 *
 *  @param com	The COM port
 *  @param buf	Pointer to the start of the buffer
 *  @param len	Length of the buffer
 */
int serial_write(unsigned short com, char *buf, unsigned int len);

#endif
