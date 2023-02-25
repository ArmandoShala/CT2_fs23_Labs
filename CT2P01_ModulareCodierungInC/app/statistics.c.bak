/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module statistics
 * --               Collect and provide statistical data on throws
 * --               of the dice
 * --
 * -- $Id: statistics.c 2977 2016-02-15 16:05:50Z ruan $
 * ------------------------------------------------------------------
 */

/* user includes */
#include "statistics.h"

/* variables visible within the whole module*/

// index 0:         total number of throws
// index 1 to 6:    number of throws for each digit
static uint8_t nr_of_throws[NR_OF_DICE_VALUES + 1];

/* function definitions */

/// STUDENTS: To be programmed
void stat_add_throw(uint8_t throw_value)
{
    if (throw_value > 0 && throw_value <= NR_OF_DICE_VALUES) {
        nr_of_throws[--throw_value]++;
    }
}

static uint8_t sum_of_array(uint8_t arr[], uint8_t lenght) {
    uint8_t sum = 0;
    uint8_t i = 0;
    for (i = 0; i < lenght; i++) {
        sum += arr[i];
    }
    return sum;
}

uint8_t stat_read(uint8_t dice_number)
{
    if (dice_number == 0) {
        return sum_of_array(nr_of_throws, NR_OF_DICE_VALUES);
    } else if (dice_number > 0 && dice_number < 7) {
        return nr_of_throws[--dice_number];
    }
    return ERROR_VALUE;
}
/// END: To be programmed