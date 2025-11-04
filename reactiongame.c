#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LED_PIN 15
#define BUTTON_PIN 14

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    srand(time(NULL)); // Seed for random delay

    while (true) {
        printf("Get ready...\n");
        sleep_ms(2000); // Wait before starting

        gpio_put(LED_PIN, 1);
        printf("Wait for the LED to turn off!\n");

        // Random delay between 2 and 5 seconds
        int delay = 2000 + rand() % 3000;
        sleep_ms(delay);

        gpio_put(LED_PIN, 0);
        printf("GO!\n");

        absolute_time_t start = get_absolute_time();

        // Wait for button press
        while (gpio_get(BUTTON_PIN) == 1) {
            tight_loop_contents();
        }

        absolute_time_t end = get_absolute_time();
        int64_t reaction_time = absolute_time_diff_us(start, end) / 1000; // in ms

        printf("Your reaction time: %lld ms\n\n", reaction_time);
        sleep_ms(3000); // wait before next round
    }
}
