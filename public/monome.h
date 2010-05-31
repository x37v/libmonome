/*
 * Copyright (c) 2007-2010, William Light <will@visinin.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _MONOME_H
#define _MONOME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <termios.h>

#include <sys/types.h>

typedef enum {
	MONOME_BUTTON_UP           = 0x00,
	MONOME_BUTTON_DOWN         = 0x01,
	MONOME_AUX_INPUT           = 0x02
} monome_event_type_t;

/* clearing statuses (argument to monome_clear) */

typedef enum {
	MONOME_CLEAR_OFF           = 0x00,
	MONOME_CLEAR_ON            = 0x01
} monome_clear_status_t;

/* modes (argument to monome_mode) */

typedef enum {
	MONOME_MODE_NORMAL         = 0x00,
	MONOME_MODE_TEST           = 0x01,
	MONOME_MODE_SHUTDOWN       = 0x02
} monome_mode_t;

/* cable orientation */

typedef enum {
	MONOME_CABLE_LEFT          = 0,
	MONOME_CABLE_BOTTOM        = 1,
	MONOME_CABLE_RIGHT         = 2,
	MONOME_CABLE_TOP           = 3
} monome_cable_t;
	
typedef struct monome_event monome_event_t;
typedef struct monome monome_t; /* opaque data type */

typedef void (*monome_callback_function_t)(const monome_event_t *event, void *data);

struct monome_event {
	monome_t *monome;
	monome_event_type_t event_type;
	uint x;
	uint y;
};

monome_t *monome_open(const char *monome_device, ...);
void monome_close(monome_t *monome);

void monome_set_orientation(monome_t *monome, monome_cable_t cable);
monome_cable_t monome_get_orientation(monome_t *monome);

int monome_get_rows(monome_t *monome);
int monome_get_cols(monome_t *monome);

void monome_register_handler(monome_t *monome, uint event_type, monome_callback_function_t, void *user_data);
void monome_unregister_handler(monome_t *monome, uint event_type);
void monome_main_loop(monome_t *monome);
int monome_next_event(monome_t *monome);

int monome_clear(monome_t *monome, monome_clear_status_t status);
int monome_intensity(monome_t *monome, uint brightness);
int monome_mode(monome_t *monome, monome_mode_t mode);

int monome_led_on(monome_t *monome, uint x, uint y);
int monome_led_off(monome_t *monome, uint x, uint y);
int monome_led_col_8(monome_t *monome, uint col, uint8_t *col_data);
int monome_led_row_8(monome_t *monome, uint row, uint8_t *row_data);
int monome_led_col_16(monome_t *monome, uint col, uint8_t *col_data);
int monome_led_row_16(monome_t *monome, uint row, uint8_t *row_data);
int monome_led_frame(monome_t *monome, uint quadrant, uint8_t *frame_data);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* defined _MONOME_H */