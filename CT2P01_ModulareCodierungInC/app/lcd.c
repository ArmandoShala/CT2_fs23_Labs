/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module lcd
 * --               Performs all the interactions with the lcd
 * --
 * -- $Id: lcd.c 5144 2020-09-01 06:17:21Z ruan $
 * ------------------------------------------------------------------
 */

/* standard includes */
#include <stdio.h>
#include <string.h>

/* user includes */
#include "lcd.h"
#include "reg_ctboard.h"

/* macros */
#define LCD_ADDR_LINE1      0u
#define LCD_ADDR_LINE2      20u

#define NR_OF_CHAR_PER_LINE 20u

#define LCD_CLEAR           "                    "
#define TOTAL_THROW_TEXT    "total throws"

/// STUDENTS: To be programmed
void write_string_to_lcd(uint8_t slot_nr_start, char string[])
{
    uint8_t i;
    for (i=0; i<strlen(string); i++) {
        CT_LCD->ASCII[slot_nr_start++] = string[i];
    }
}

void lcd_write_value(uint8_t slot_nr, uint8_t value)
{
    char buffer[3];
    snprintf(buffer, 3, "%d", value);

    write_string_to_lcd(--slot_nr * 3u, buffer);
}

void lcd_write_total(uint8_t total_value)
{
    char buffer[5];
    write_string_to_lcd(LCD_ADDR_LINE2, TOTAL_THROW_TEXT);

    snprintf(buffer, 5, "%d", total_value);
    write_string_to_lcd(LCD_ADDR_LINE2 + 15u, buffer);
}

void hal_ct_lcd_clear(void)
{
    write_string_to_lcd(LCD_ADDR_LINE1, LCD_CLEAR);
    write_string_to_lcd(LCD_ADDR_LINE2, LCD_CLEAR);

    CT_LCD->BG.GREEN = 65535;
}
/// END: To be programmed