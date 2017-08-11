#include "DHT.h"
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <WifiConnect.h>

#define DHTPIN D7
#define DHTTYPE DHT11
#define FAN_PIN D8

#define ssid ""  //WIFI SSID
#define password ""  //WIFI Password
#define storageEndpoint ""

LiquidCrystal lcd(D6, D5, D4, D3, D2, D1);
DHT dht(DHTPIN, DHTTYPE);

String ip;
float temperatureOnLevel = 29;
void setup() {
  Serial.begin(115200);
  // delay(1000);
  // Serial.flush();
  ip = WifiConnect(ssid, password);
  pinMode(FAN_PIN, OUTPUT);
  lcd.begin(16, 2); // initialize the lcd

  dht.begin();
}

void postResult(float h, float t, float hic) {

  HTTPClient http;
  http.begin(storageEndpoint);
  http.addHeader("Content-Type", "application/json; charset=utf-8");
  http.POST("{\"humidity\": " + String(h) + ", \"temperature\":" + String(t) +
            ",\"heat_index\":" + String(hic) + "}");
  Serial.println("POST Result " + http.getString());

}

void loop() {

  // wifi.loop();

  // doHttpGet();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);
  lcd.clear();





  if(!isnan(hic)){

    lcd.home(); // go home
    lcd.print("H:");
    lcd.print(h);
    lcd.print("/T:");
    lcd.print(t);
    lcd.setCursor(0, 1); // go to the next line
    lcd.print("HIC: ");
    lcd.print(hic);

    postResult(h, t, hic);
    if (hic >= temperatureOnLevel) {
      digitalWrite(FAN_PIN, HIGH);
      lcd.print("   ON ");
    } else {
      digitalWrite(FAN_PIN, LOW);
      lcd.print("   OFF");
    }
    delay(60000);

  }else{
    lcd.home(); // go home
    lcd.print("Retrying");
    delay(1000);
  }

  // Serial.print("humidity");
  // Serial.println(temperature[0]);
  // Serial.print("temperature");
  // Serial.println(temperature[1]);
  // Serial.print("HeatIndex");
  // Serial.println(temperature[2]);

}
