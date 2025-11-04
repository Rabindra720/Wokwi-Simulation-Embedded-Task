#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"


#define PIR_PIN     14   // PIR sensor output connected here
#define LED_PIN     15   // LED output
#define BUZZER_PIN  11   // Buzzer output

#define ALERT_DURATION_MS 5000  // Alert lasts for 5 seconds

int main() {
    stdio_init_all();

    // Initialize PIR sensor
    gpio_init(PIR_PIN);
    gpio_set_dir(PIR_PIN, GPIO_IN);
    // No pull-up or pull-down: PIR has its own output driver

    // Initialize LED and Buzzer
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);

    printf("System armed. Waiting for motion...\n");

    while (true) {
        // Read PIR sensor output
        if (gpio_get(PIR_PIN)) { // HIGH when motion detected
            printf("ALERT: Motion detected!\n");

            gpio_put(LED_PIN, 1);
            gpio_put(BUZZER_PIN, 1);

            sleep_ms(ALERT_DURATION_MS);

            gpio_put(LED_PIN, 0);
            gpio_put(BUZZER_PIN, 0);

            printf("System reset. Monitoring again...\n");
            sleep_ms(2000); // cooldown before next trigger
        }

        sleep_ms(100); // small delay for stable readings
    }
}
