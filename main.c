#include "pico/stdlib.h"

int main() {
    // The original Pico uses GPIO 25 for the built-in LED
    const uint LED_PIN = 0;

    // Initialize GPIO pin
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1); // Turn LED on
        sleep_ms(250);        // Wait 250ms
        gpio_put(LED_PIN, 0); // Turn LED off
        sleep_ms(250);        // Wait 250ms
    }
}