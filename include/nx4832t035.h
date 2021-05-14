#ifndef NX4832T035
#define NX4832T035

#include <stdint.h>
#include <stddef.h>

#include "queue.h"

#define DISPLAY_EVENT_SIZE 10

enum {
	D_INVALID = 0x00,
	D_SUCCESSFUL = 0x01,
	D_INVALID_COMP_ID = 0x02,
	D_INVALID_PAGE_ID = 0x03,
	D_INVALID_PIC_ID = 0x04,
	D_INVALID_FONT_ID = 0x05,
	D_INVALID_FILE_OP = 0x06,
	D_INVALID_CRC = 0x09,
	D_INVALID_BAUD = 0x11,
	D_INVALID_WAFEFORM_CH_ID = 0x12,
	D_INVALID_VAR_NAME = 0x1a,
	D_INVALID_VAR_OP = 0x1b,
	D_INVALID_ASSIGN_FAILED = 0x1c,
	D_INVALID_EEPROM_FAILED = 0x1d,
	D_INVALID_QUANTITY_PARAMETER = 0x1e,
	D_IO_OP = 0x1f,
	D_ESCAPE_CHAR = 0x20,
	D_VAR_NAME_TOOLONG = 0x23,
};

enum {
	D_NEXT_STARTUP = 0x000000,
	D_SERIAL_OVERFLOW = 0x24,

	D_TOUCH_EVENT = 0x65,
	D_CURR_PAGE = 0x66,
	D_TOUCH_CORD_AWAKE = 0x67,
	D_TOUCH_CORD_SLEEP = 0x68,
	D_STRING = 0x70,
	D_NUM = 0x71,

	D_AUTO_SLEEP = 0x86,
	D_AUTO_WAKE = 0x87,
	D_READY = 0x88,
	D_SD_UPGRADE = 0x89,
	D_TRANSPARENT_DATA_FIN = 0xfd,
	D_TRANSPARENT_DATA_READY = 0xfe,
};

enum {
	D_PRESS = 0x01,
	D_RELEASE = 0x00,
};

struct display_event {
	void (*handler)(char[], size_t size);
	uint8_t event_type;
};

extern struct display_event d_events[DISPLAY_EVENT_SIZE];

struct D_TOUCH_EVENT {
	uint8_t page_num;
	uint8_t component_id;
	uint8_t event;
};

struct D_CURR_PAGE {
	uint8_t current_page;
};

struct coordinate {
	uint16_t x;
	uint16_t y;
};

struct D_TOUCH_CORD {
	struct coordinate cord;
	uint8_t event;
};

struct D_STRING {
	char string[QUEUE_SIZE];
};

struct D_NUM {
	uint32_t num;
};

void display_send(const char instruction[], size_t size);
size_t display_read(char out[], const size_t out_size);

void display_event_init();
void display_event_loop();

#endif
