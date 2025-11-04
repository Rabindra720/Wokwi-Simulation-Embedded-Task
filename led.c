#include <stdio.h>
#include "pico/stdlib.h"


#define LED_PIN 15
#define BUTTON_PIN 14

int main() {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); 

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0) {
            gpio_put(LED_PIN, 1); // LED ON when pressed
        } else {
            gpio_put(LED_PIN, 0); // LED OFF when released
        }
        sleep_ms(10); // small delay
    }
}
