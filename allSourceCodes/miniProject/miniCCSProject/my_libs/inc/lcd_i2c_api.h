/*
 * lcd_i2c_api.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#include "config_peripherals_api.h"
#include "driverlib/i2c.h"

#ifndef MY_LIBS_INC_LCD_I2C_API_H_
#define MY_LIBS_INC_LCD_I2C_API_H_

#define BL    0x08
#define E     0x04
#define RW    0x02
#define RS    0x01

#define HD44780_CLEAR_DISPLAY    0x01
#define HD44780_RETURN_HOME    0x02
#define HD44780_ENTRY_MODE_SET    0x04
#define HD44780_DISPLAY_CTRL    0x08
#define HD44780_SHIFT        0x10
#define HD44780_FUNCTION_SET    0x20
#define HD44780_CGRAM_ADDR    0x40
#define HD44780_DDRAM_ADDR    0x80

#define HD44780_DL_8BITS    0x10
#define HD44780_DL_4BITS    0x00
#define HD44780_N_2LINES    0x08
#define HD44780_N_1LINE        0x00

#define HD44780_D_DISPLAY_ON    0x04
#define HD44780_D_DISPLAY_OFF    0x00
#define HD44780_C_CURSOR_ON    0x02
#define HD44780_C_CURSOR_OFF    0x00
#define HD44780_B_BLINK_ON    0x01
#define HD44780_B_BLINK_OFF    0x00

#define HD44780_ID_INCREMENT    0x02
#define HD44780_ID_DECREMENT    0x00
#define HD44780_S_SHIFT_ON    0x01
#define HD44780_S_SHIFT_OFF    0x00

#define I2C_HANDLER I2C1_BASE
#define SLAVE_ADDRESS 0x27
#define BUF_SIZE        64
#define ESC_SEQ_BUF_SIZE    4

struct hd44780_geometry {
    int cols;
    int rows;
    int start_addrs[];
};

/* just a struct describing for the LCD */
struct hd44780 {
    struct hd44780_geometry *geometry;

    /* Current cursor position on the display */
    struct {
        int row;
        int col;
    } pos;

    char buf[BUF_SIZE];
    struct {
        char buf[ESC_SEQ_BUF_SIZE];
        int length;
    } esc_seq_buf;
    bool is_in_esc_seq;

    bool backlight;
    bool cursor_blink;
    bool cursor_display;

    bool dirty;
};

extern void hd44780_write(struct hd44780 *, const char *, size_t);
extern void hd44780_init_lcd(struct hd44780 *);
extern void hd44780_print(struct hd44780 *, const char *);
extern void hd44780_flush(struct hd44780 *);
extern void hd44780_set_geometry(struct hd44780 *, struct hd44780_geometry *);
extern void hd44780_set_backlight(struct hd44780 *, bool);
extern void hd44780_set_cursor_blink(struct hd44780 *, bool);
extern void hd44780_set_cursor_display(struct hd44780 *, bool);

extern struct hd44780_geometry *hd44780_geometries[];

#endif /* MY_LIBS_INC_LCD_I2C_API_H_ */
