#include "serial.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
	outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
	outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
}

void serial_configure_line(unsigned short com) {
	/* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
	 * Content: | d | b | prty  | s | dl  |
	 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
	 */
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
	outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
	outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
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
		while (serial_is_transmit_fifo_empty(com) == 0);
		outb(com, buf[i]);
	}
	return len;
}
