#include "serial.h"

void serial_configure(unsigned short com, unsigned short divisor) {
	outb(SERIAL_DATA_PORT(com) + 1, 0x00);				// Disable all interrupts
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x80);			// Enable DLAB (set baud rate divisor)
	outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);			// Set divisor to (lo byte)
	outb(SERIAL_DATA_PORT(com) + 1, (divisor >> 8) & 0x00FF);	//                (hi byte)
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);			// 8 bits, no parity, one stop bit
	outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);			// Enable FIFO, clear them, with 14-byte threshold
	outb(SERIAL_MODEM_COMMAND_PORT(com), 0x0B);			// IRQs enabled, RTS/DSR set
}

int serial_is_transmit_fifo_empty(unsigned short com) {
	/* 0x20 = 0010 0000 */
	return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

int serial_received(unsigned short com) {
	return inb(SERIAL_LINE_STATUS_PORT(com)) & 1;
}

int serial_write(unsigned short com, char *buf, unsigned int len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		while(serial_is_transmit_fifo_empty(com) == 0);
		outb(com, buf[i]);
	}
	return len;
}
