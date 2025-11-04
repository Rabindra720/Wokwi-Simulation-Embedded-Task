#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 22         // GPIO pin connected to DHT22 data pin
#define DHTTYPE DHT22     // Define sensor type DHT22

const char* ssid = "Wokwi-GUEST";      // WiFi SSID for Wokwi
const char* password = "";              // No password needed for Wokwi-GUEST

const char* thingspeakApiKey = "OR6YBDKX1Q3UQW50";  // Replace with your ThingSpeak API Key
const char* thingspeakHost = "http://api.thingspeak.com/update";

DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(thingspeakHost) + "?api_key=" + thingspeakApiKey + 
                 "&field1=" + String(temperature) + "&field2=" + String(humidity);
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.print("Data sent to ThingSpeak, response code: ");
      Serial.println(httpCode);
    } else {
      Serial.print("Failed to send data, error: ");
      Serial.println(httpCode);
    }
    http.end();
  } else {
    Serial.println("WiFi disconnected");
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(15000);  // Wait 15 seconds before next reading, per ThingSpeak update limits
}
