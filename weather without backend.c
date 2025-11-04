#include "pico/stdlib.h"
#include <stdio.h>

#define DHT_PIN 15

void read_dht22(float *temperature, float *humidity) {
    // Simple fake values for Wokwi simulation
    // We’ll just print changing values for display.
    static float t = 25.0;
    static float h = 50.0;
    t += 0.1;
    h += 0.2;
    if (t > 30) t = 25;
    if (h > 70) h = 50;
    *temperature = t;
    *humidity = h;
}

int main() {
    stdio_init_all();
    printf("🌤️ Weather Station (Simulated DHT22)\n");

    float temperature, humidity;

    while (true) {
        read_dht22(&temperature, &humidity);
        printf("Temperature: %.1f °C | Humidity: %.1f %%\n", temperature, humidity);
        sleep_ms(2000);
    }
}
