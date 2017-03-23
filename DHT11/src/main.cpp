#include <Arduino.h>
#include <SimpleDHT.h>
#define DHT11_PIN D5

SimpleDHT11 dht11;

void setup() {
  Serial.begin(115200);
  // pinMode(DHT11_PIN, INPUT);
}



void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(DHT11_PIN, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");

  // DHT11 sampling rate is 1HZ.
  delay(1000);
}
