#include <stdio.h>
#include "pico/stdlib.h"

#define RED_LED     15
#define YELLOW_LED  14
#define GREEN_LED   13
#define BUTTON_PIN  12
#define BUZZER_PIN  11

void traffic_cycle() {
    gpio_put(GREEN_LED, 1);
    sleep_ms(2000);
    gpio_put(GREEN_LED, 0);

    gpio_put(YELLOW_LED, 1);
    sleep_ms(1000);
    gpio_put(YELLOW_LED, 0);

    gpio_put(RED_LED, 1);
    sleep_ms(2000);
    gpio_put(RED_LED, 0);
}

int main() {
    stdio_init_all();

    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(YELLOW_LED);
    gpio_set_dir(YELLOW_LED, GPIO_OUT);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // internal pull-up resistor

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0) { // Button pressed
            gpio_put(GREEN_LED, 0);
            gpio_put(YELLOW_LED, 0);
            gpio_put(RED_LED, 1);     // Red ON
            gpio_put(BUZZER_PIN, 1);  // Buzzer ON
            sleep_ms(3000);
            gpio_put(BUZZER_PIN, 0);  // Buzzer OFF
        } else {
            traffic_cycle();          // Normal traffic sequence
        }
    }
}
