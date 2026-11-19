#include "pico/stdlib.h"
#include <stdio.h>

const uint PIN_LCD_RS = 17;
const uint PIN_LCD_E = 16;
const uint PIN_LCD_D4 = 21;
const uint PIN_LCD_D5 = 20;
const uint PIN_LCD_D6 = 19;
const uint PIN_LCD_D7 = 18;

void pulse_enable() {
    gpio_put(PIN_LCD_E, 0);
    sleep_us(1);
    gpio_put(PIN_LCD_E, 1);
    sleep_us(1);
    gpio_put(PIN_LCD_E, 0);
    sleep_us(100);
}

void nib4_put(uint snack) {
    // MSb goes on D4
    gpio_put(PIN_LCD_D4, (snack >> 0) & 1);
    gpio_put(PIN_LCD_D5, (snack >> 1) & 1);
    gpio_put(PIN_LCD_D6, (snack >> 2) & 1);
    gpio_put(PIN_LCD_D7, (snack >> 3) & 1);

    pulse_enable();
}

void nib8_put(uint snack) {
    nib4_put((snack >> 4) & 0x0F);  // MSB
    nib4_put(snack & 0x0F);         // LSB
}

int main() {
    // Initialize chosen serial interface (USB in this case)
    stdio_init_all();

    printf("hello yes I am here");

    gpio_init(PIN_LCD_D4);
    gpio_set_dir(PIN_LCD_D4, GPIO_OUT);
    gpio_init(PIN_LCD_D5);
    gpio_set_dir(PIN_LCD_D5, GPIO_OUT);
    gpio_init(PIN_LCD_D6);
    gpio_set_dir(PIN_LCD_D6, GPIO_OUT);
    gpio_init(PIN_LCD_D7);
    gpio_set_dir(PIN_LCD_D7, GPIO_OUT);

    gpio_init(PIN_LCD_E);
    gpio_set_dir(PIN_LCD_E, GPIO_OUT);
    gpio_init(PIN_LCD_RS);
    gpio_set_dir(PIN_LCD_RS, GPIO_OUT);

    /* INIT */
    sleep_ms(20);
    nib4_put(0x3);
    sleep_ms(5);
    nib4_put(0x3);
    // reset into 8-bit state
    sleep_ms(150);
    nib4_put(0x3);
    // 4 bit mode
    sleep_ms(150);
    nib4_put(0x2);
    sleep_ms(150);

    /* CONFIG */
    gpio_put(PIN_LCD_RS, 0);
    nib8_put(0x28); // 4 bit, 2 line, 5x8 dots
    gpio_put(PIN_LCD_RS, 0);
    nib8_put(0x0F); // DISPLAY ON, CURSOR FLASH
    gpio_put(PIN_LCD_RS, 0);
    nib8_put(0x06); // INCREMENT
    gpio_put(PIN_LCD_RS, 0);
    nib8_put(0x01); // CLEAR
    sleep_ms(2);

    // set cursor 0,0?
    gpio_put(PIN_LCD_RS, 0);
    nib8_put(0x80 | (0 + 0));

    // Type letter A?
    gpio_put(PIN_LCD_RS, 1);
    nib8_put(65);

    while (true) {
        printf("MEOW MEOW MEOW352!!\n");
    }
}